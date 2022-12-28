#include "HGamTools/SkimAndSlim.h"
#include "HGamAnalysisFramework/HGamCommon.h"
#include "HGamAnalysisFramework/HGamVariables.h"

#include <AsgTools/MsgStream.h>
#include <AsgTools/MsgStreamMacros.h>

#include "xAODMetaData/FileMetaData.h"
#include "xAODMetaData/FileMetaDataAuxInfo.h"

#include "xAODTruth/TruthMetaDataContainer.h"
#include "xAODTruth/TruthMetaDataAuxContainer.h"

#include "GoodRunsLists/GoodRunsListSelectionTool.h"

// this is needed to distribute the algorithm to the workers
ClassImp(SkimAndSlim)



SkimAndSlim::SkimAndSlim(const char *name)
  : HgammaAnalysis(name)
  , m_applyGRL(false)
  , m_removeDuplicates(false)
  , m_updatePRW(false)
  , m_updateMu(false)
  , m_prwSF(1.0)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



SkimAndSlim::~SkimAndSlim()
{
  // Here you delete any memory you allocated during your analysis.
}



EL::StatusCode SkimAndSlim::fileExecute()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed

  TFile *output = dynamic_cast<TFile *>(wk()->getOutputFile("MxAOD"));

  // Copy cut flow and other histograms from input file
  TFile *input = dynamic_cast<TFile *>(wk()->inputFile());
  TIter next(input->GetListOfKeys());
  TKey *key = nullptr;

  while ((key = (TKey *)next())) {
    std::string className = key->GetClassName();

    if (className.find("TH1") != std::string::npos) {
      const char *name = key->GetName();
      TH1 *cutflow = dynamic_cast<TH1 *>(wk()->inputFile()->Get(name));

      if (m_cutflows.find(name) == m_cutflows.end()) {
        m_cutflows[name] = dynamic_cast<TH1 *>(cutflow->Clone());
        m_cutflows[name]->SetDirectory(output);
      } else {
        m_cutflows[name]->Add(cutflow);
      }
    }
  }

  // Check if metadata in secondary files matches first file
  ANA_CHECK(writeMetaData());

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SkimAndSlim::createOutput()
{
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SkimAndSlim::initialize()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  ANA_CHECK_SET_TYPE(EL::StatusCode);

  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK_THROW(getConstContainer<xAOD::EventInfo>(eventInfo, "EventInfo"));

  // Set isMC global variable.
  HG::setAndLock_isMC(eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION));

  // Setup output TEvent, add to file
  TFile *file = wk()->getOutputFile("MxAOD");
  m_outEvent = std::make_unique<xAOD::TEvent>(xAOD::TEvent::kClassAccess);
  ANA_CHECK(m_outEvent->writeTo(file));

  // Save available metadata in first file
  ANA_CHECK(writeMetaData());

  // Create user defined histograms
  createOutput();

  for (auto hist : histoStore()->getListOfHistograms())
  { hist->SetDirectory(wk()->getOutputFile("MxAOD")); }

  // Connect HGam variables
  HG::VarHandler::getInstance()->setEventAndStore(wk()->xaodEvent(), wk()->xaodStore());

  // Which containers to save
  m_contToSave = config()->getStdStrV("SkimAndSlim.ContainersToSave");

  for (std::string cont : m_contToSave) {
    std::string bname    = cont + "Aux.";
    std::string branches = "SkimAndSlim.BranchesToSave." + cont;

    if (config()->isDefined(branches.c_str())) {
      std::vector<std::string> branchesV = config()->getStdStrV(branches);
      branches = "";

      for (std::string branch : branchesV) {
        if (branches == "")
        { branches = branch; }
        else
        { branches = branches + "." + branch; }
      }
      m_outEvent->setAuxItemList(bname, branches.c_str());
    }
  }

  // Systematics, if configured
  if (config()->isDefined("SkimAndSlim.SystematicsToSave"))
  { m_sysComps = config()->getStdStrV("SkimAndSlim.SystematicsToSave"); }


  // In this vector we will store all the systmatics listed that are in the inputfile 
  std::vector<std::string> sysToCheck;

  for (std::string sys : m_sysComps) {
    ATH_MSG_INFO( "Checking HGamEventInfo" + sys );
    if( !contains<xAOD::EventInfo>( "HGamEventInfo" + sys ) ){
      ATH_MSG_INFO( "---- Does not contain " << "HGamEventInfo" + sys << " -- ignore");
      continue;
    }
    sysToCheck.push_back( sys ) ; 

    std::string bname    = "HGamEventInfo" + sys + "Aux.";
    std::string branches = "SkimAndSlim.BranchesToSave.HGamEventInfo_SYS";

    if (config()->isDefined(branches.c_str())) {
      std::vector<std::string> branchesV = config()->getStdStrV(branches);
      branches = "";

      for (std::string branch : branchesV) {
        if (branches == "")
        { branches = branch; }
        else
        { branches = branches + "." + branch; }
      }

      m_outEvent->setAuxItemList(bname, branches.c_str());   
    }
  }
  //  Now we only will try and save systematics that are in the input file
  m_sysComps = sysToCheck;

  // Check if configured to apply updated GRL
  if (config()->getBool("SkimAndSlim.ApplyGRL", false)) {
    const xAOD::EventInfo *eventInfo = nullptr;
    ANA_CHECK(wk()->xaodEvent()->retrieve(eventInfo, "EventInfo"));

    if (eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      ATH_MSG_WARNING("Applying the GRL to MC is not supported, defaulting to pass-through");
    } else {
      m_applyGRL = true;

      m_grlTool.setTypeAndName("GoodRunsListSelectionTool/SkimAndSlimGRL");
      ANA_CHECK(m_grlTool.setProperty("GoodRunsListVec", config()->getStdStrV("SkimAndSlim.GRL")));
      ANA_CHECK(m_grlTool.retrieve());
    }
  }

  // Check if configured to reject duplicate events
  if (config()->getBool("SkimAndSlim.RemoveDuplicateEvents", false))
  { m_removeDuplicates = true; }

  // Check if configured to update pileup weight or mu
  m_updatePRW = config()->getBool("SkimAndSlim.UpdatePileupWeight", false);
  m_updateMu  = config()->getBool("SkimAndSlim.UpdateMu", false);

  if (m_updatePRW || m_updateMu) {
    const xAOD::EventInfo *eventInfo = nullptr;
    ANA_CHECK(wk()->xaodEvent()->retrieve(eventInfo, "EventInfo"));

    if (m_updateMu && eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      ATH_MSG_WARNING("Can't be configured to update mu in MC simulation, ignoring this option");
    }

    if (m_updatePRW && !eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      ATH_MSG_WARNING("Can't be configured to apply pileup weights to data, ignoring this option");
    }

    m_prwTool.setTypeAndName("CP::PileupReweightingTool/SkimAndSlim_PRW");

    ANA_CHECK(m_prwTool.setProperty("LumiCalcFiles", config()->getStdStrV("SkimAndSlim.LumiCalcFiles")));
    ANA_CHECK(m_prwTool.setProperty("ConfigFiles", config()->getStdStrV("SkimAndSlim.ConfigFiles")));

    m_prwSF = config()->getNum("SkimAndSlim.DataScaleFactor");
    ANA_CHECK(m_prwTool.setProperty("DataScaleFactor", m_prwSF));

    if (std::find(m_sysComps.begin(), m_sysComps.end(), "_PRW_DATASF__1up") != m_sysComps.end()) {
      ANA_CHECK(m_prwTool.setProperty("DataScaleFactorUP", config()->getNum("SkimAndSlim.DataScaleFactorUP")));
      m_prwSysUp.insert(CP::SystematicVariation("PRW_DATASF", 1));
    }

    if (std::find(m_sysComps.begin(), m_sysComps.end(), "_PRW_DATASF__1down") != m_sysComps.end()) {
      ANA_CHECK(m_prwTool.setProperty("DataScaleFactorDOWN", config()->getNum("SkimAndSlim.DataScaleFactorDOWN")));
      m_prwSysDown.insert(CP::SystematicVariation("PRW_DATASF", -1));
    }

    ANA_CHECK(m_prwTool.retrieve());
  }

  // Apply simple reco skimming based on cutFlow
  m_cutFlowSkimMin  = config()->getNum("SkimAndSlim.SkimmingCutFlowMin", -1);
  m_cutFlowSkimName = config()->getStr("SkimAndSlim.SkimmingCutFlowName", "cutFlow").Data();

  // Extra generator weights to be saved
  m_extraMCWeights.clear();
  StrV emptyStrVec;
  StrV vecS = config()->getStrV("SkimAndSlim.MCGenExtraWeights", emptyStrVec);

  for (uint i = 0; i < vecS.size(); ++i) {
    m_extraMCWeights.push_back(atoi(vecS[i].Data()));

    if (m_extraMCWeights[i] > 0)
    { ATH_MSG_INFO("Extra MC generator weight to be saved: " << m_extraMCWeights[i]); }
    else
    { ATH_MSG_INFO("Extra MC generator weight to be saved: 1/" << -m_extraMCWeights[i]); }
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SkimAndSlim::execute()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  ANA_CHECK_SET_TYPE(EL::StatusCode);

  // Check if the event passes skimming configuration
  bool skip = false;
  ANA_CHECK(skipEvent(skip));

  if (skip) { return EL::StatusCode::SUCCESS; }

  // Record configured containers to output
  ANA_CHECK(recordContainers());

  // Fill output file with event
  fillEvent();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SkimAndSlim::finalize()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  ANA_CHECK_SET_TYPE(EL::StatusCode);

  // Finish writing output xAOD
  TFile *file = wk()->getOutputFile("MxAOD");
  ANA_CHECK(m_outEvent->finishWritingTo(file));

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SkimAndSlim::skipEvent(bool &skip)
{
  // Return true if the event should be skipped (not kept by skimming)
  // or false if the event should be kept. Default: false
  skip = false;

  // Apply simple cut flow skimming, if configured
  if (m_cutFlowSkimMin > 0 && !passCutFlowSkim()) {
    skip = true;
    return EL::StatusCode::SUCCESS;
  }

  if (!m_removeDuplicates && !m_applyGRL)
  { return EL::StatusCode::SUCCESS; }

  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK(getConstContainer<xAOD::EventInfo>(eventInfo, "EventInfo"));

  // Remove duplicate events, if configured
  if (m_removeDuplicates && isDuplicate(*eventInfo)) {
    ATH_MSG_INFO("Removing duplicate event from sample.");
    skip = true;
    return EL::StatusCode::SUCCESS;
  }

  // Apply specified GRL, if configured
  if (m_applyGRL && !passGRL(*eventInfo)) {
    skip = true;
    return EL::StatusCode::SUCCESS;
  }

  return EL::StatusCode::SUCCESS;
}



void SkimAndSlim::fillEvent()
{
  // Fill output with TEvent
  m_outEvent->fill();
}



std::vector<std::string> SkimAndSlim::getSystematicNames()
{
  return m_sysComps;
}



std::vector<std::string> SkimAndSlim::getContainersToSave()
{
  return m_contToSave;
}



bool SkimAndSlim::isDuplicate(const xAOD::EventInfo &eventInfo)
{
  // runNumber for data, DSID for MC simulation
  unsigned int runNumber = eventInfo.runNumber();

  if (eventInfo.eventType(xAOD::EventInfo::IS_SIMULATION))
  { runNumber = eventInfo.mcChannelNumber(); }

  // Check if event is a duplicate
  if (!m_eventNumberSet[runNumber].insert(eventInfo.eventNumber()).second) { // is a duplicate
    // Correct cutflow histogram (currently data only)
    if (!eventInfo.eventType(xAOD::EventInfo::IS_SIMULATION)) {
      std::string name = "CutFlow_Run%d" + std::to_string(runNumber);

      if (m_cutflows[name]) {
        for (int bin = 6; bin <= var::cutFlow(); ++bin)
        { m_cutflows[name]->SetBinContent(bin, m_cutflows[name]->GetBinContent(bin) - 1); }
      }
    }

    // Skip event
    return true;
  }

  return false;
}



bool SkimAndSlim::passGRL(const xAOD::EventInfo &eventInfo)
{
  // Check if event fails the GRL
  if (!m_grlTool->passRunLB(eventInfo)) {
    // Correct cutflow histogram
    std::string name = "CutFlow_Run%d" + std::to_string(eventInfo.runNumber());

    if (m_cutflows[name]) {
      for (int bin = 6; bin <= var::cutFlow(); ++bin)
      { m_cutflows[name]->SetBinContent(bin, m_cutflows[name]->GetBinContent(bin) - 1); }
    }

    // Skip event
    return false;
  }

  return true;
}



bool SkimAndSlim::passCutFlowSkim()
{
  static SG::AuxElement::ConstAccessor<int> cutFlow(m_cutFlowSkimName.c_str());
  const xAOD::EventInfo *eventInfo = nullptr;

  // Loop over possible systematics and check cutFlow
  for (std::string sys : m_sysComps) {
    std::string cont = "HGamEventInfo" + sys;

    if (!wk()->xaodEvent()->retrieve(eventInfo, cont).isSuccess()) {
      ATH_MSG_ERROR("Couldn't retrieve " << cont.c_str() << ", defaulting to NOT skimming event.");
      return true;
    }

    if (m_cutFlowSkimMin <= cutFlow(*eventInfo))
    { return true; }
  }

  // Check nominal event cutFlow
  if (!wk()->xaodEvent()->retrieve(eventInfo, "HGamEventInfo").isSuccess()) {
    ATH_MSG_ERROR("Couldn't retrieve HGamEventInfo, defaulting to NOT skimming event.");
    return true;
  }

  if (m_cutFlowSkimMin <= cutFlow(*eventInfo))
  { return true; }

  return false;
}



EL::StatusCode SkimAndSlim::updateMu(const std::string &name)
{
  // Need to update pileupWeight and weight variables
  // Nominal HGamEventInfo, and systematic shifts of PRW

  // // Make a copy of HGamEventInfo, and put it in the output TEvent
  // ANA_CHECK( recordInfo<xAOD::EventInfo>(name) );

  // Retrieve the copy of HGamEventInfo
  const xAOD::EventInfo *constInfo = nullptr;
  ANA_CHECK(m_outEvent->retrieve(constInfo, name));

  xAOD::EventInfo *hgamInfo = const_cast<xAOD::EventInfo *>(constInfo);

  // Retrieve EventInfo
  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK(wk()->xaodEvent()->retrieve(eventInfo, "EventInfo"));

  // Accessors and decorators
  static SG::AuxElement::Accessor<float> acc_mu("mu");

  acc_mu(*hgamInfo) = m_prwTool->getCorrectedAverageInteractionsPerCrossing(*eventInfo) * m_prwSF;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SkimAndSlim::writeMetaData()
{
  // If the output event isn't set yet do nothing
  if (!m_outEvent) {
    ATH_MSG_DEBUG("The output TEvent isn't set yet, skipping MetaData writing for now.");
    return EL::StatusCode::SUCCESS;
  }

  // Only copy file metadata if it's available in the input
  if (wk()->xaodEvent()->containsMeta<xAOD::FileMetaData>("FileMetaData")) {
    const xAOD::FileMetaData *input = nullptr;
    ANA_CHECK(wk()->xaodEvent()->retrieveMetaInput(input, "FileMetaData"));

    if (m_outEvent->containsMeta<xAOD::FileMetaData>("FileMetaData")) {
      xAOD::FileMetaData *output = nullptr;
      ANA_CHECK(m_outEvent->retrieveMetaOutput(output, "FileMetaData"));

      if (*output != *input) {
        ATH_MSG_WARNING("Processing input files with different conditions.");
        ATH_MSG_WARNING("Consistent xAOD::FileMetaData can't be provided "
                        "for the output");
        // ATH_MSG_INFO("Reference metadata " << *output);
        // ATH_MSG_INFO("New file metadata " << *input);
      }
    } else {
      auto output = std::make_unique<xAOD::FileMetaData>();
      auto outputAux = std::make_unique<xAOD::FileMetaDataAuxInfo>();
      output->setStore(outputAux.get());

      *output = *input;

      ANA_CHECK(m_outEvent->recordMeta(std::move(output), "FileMetaData"));
      ANA_CHECK(m_outEvent->recordMeta(std::move(outputAux), "FileMetaDataAux."));
    }
  }

  // Only copy truth metadata if it's available in the input
  if (wk()->xaodEvent()->containsMeta<xAOD::TruthMetaDataContainer>("TruthMetaData")) {
    const xAOD::TruthMetaDataContainer *input = nullptr;
    ANA_CHECK(wk()->xaodEvent()->retrieveMetaInput(input, "TruthMetaData"));

    if (!m_outEvent->containsMeta<xAOD::TruthMetaDataContainer>("TruthMetaData")) {
      auto output = std::make_unique<xAOD::TruthMetaDataContainer>();
      auto outputAux = std::make_unique<xAOD::TruthMetaDataAuxContainer>();
      output->setStore(outputAux.get());

      for (const xAOD::TruthMetaData *meta : *input) {
        auto out = std::make_unique<xAOD::TruthMetaData>();
        output->push_back(std::move(out));
        *output->back() = *meta;
      }

      ANA_CHECK(m_outEvent->recordMeta(std::move(output), "TruthMetaData"));
      ANA_CHECK(m_outEvent->recordMeta(std::move(outputAux), "TruthMetaDataAux."));
    } else {
      xAOD::TruthMetaDataContainer *output = nullptr;
      ANA_CHECK(m_outEvent->retrieveMetaOutput(output, "TruthMetaData"));

      for (const xAOD::TruthMetaData *in : *input) {
        bool exists = false;

        for (const xAOD::TruthMetaData *out : *output) {
          if (out->mcChannelNumber() == in->mcChannelNumber()) {
            exists = true;
          }
        }

        if (!exists) {
          ATH_MSG_WARNING("Processing input files with different mcChannelNumbers.");
          ATH_MSG_WARNING("Only TruthMetaData for first mcChannelNumber can currently be stored.");
        }
      }
    }
  }

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode SkimAndSlim::addMCGenExtraWeights()
{
  // this member function creates HGamEventInfo decorations
  // with additional MC weights.
  // It can be useful if one wants to look for instance at NLO vs NNLO
  // distributions of the same sample, if it contains both weights.
  // In alternative one should persist the full mcEventWeights vector
  // of the EventInfo object (an easier solution but producing less
  // compact output files)
  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK(wk()->xaodEvent()->retrieve(eventInfo, "EventInfo"));

  xAOD::EventInfo *hgamEventInfo = nullptr;
  ANA_CHECK(m_outEvent->retrieve(hgamEventInfo, "HGamTruthEventInfo"));

  static SG::AuxElement::ConstAccessor<std::vector<float> > acc_mcw("mcEventWeights");
  static SG::AuxElement::Accessor<std::vector<float> > extraW("mcGenWeights");
  std::vector<float> mcW;

  for (uint i = 0; i < m_extraMCWeights.size(); i++) {
    int weight = m_extraMCWeights[i];

    if (weight > 0)
    { mcW.push_back(acc_mcw(*eventInfo)[weight]); }
    else
    { mcW.push_back(1. / acc_mcw(*eventInfo)[-weight]); }
  }

  extraW(*hgamEventInfo) = mcW;

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode SkimAndSlim::updatePileupWeight(const std::string &name)
{
  // Need to update pileupWeight and weight variables
  // Nominal HGamEventInfo, and systematic shifts of PRW

  // Retrieve the copy of HGamEventInfo
  const xAOD::EventInfo *constInfo = nullptr;
  ANA_CHECK(m_outEvent->retrieve(constInfo, name));

  xAOD::EventInfo *hgamInfo = const_cast<xAOD::EventInfo *>(constInfo);

  // Accessors and decorators
  static SG::AuxElement::ConstAccessor<std::vector<float> > acc_mcw("mcEventWeights");
  static SG::AuxElement::ConstAccessor<float> acc_vw("vertexWeight");
  static SG::AuxElement::ConstAccessor<float> acc_sf("scaleFactor");

  static SG::AuxElement::Accessor<float> acc_pw("pileupWeight");
  static SG::AuxElement::Accessor<float> acc_wi("weightInitial");
  static SG::AuxElement::Accessor<float> acc_w("weight");

  // First get the scaleFactor weight from the leading photons
  float weightSF = 1.0;

  const xAOD::PhotonContainer *photons = nullptr;
  ANA_CHECK(wk()->xaodEvent()->retrieve(photons, "HGamPhotons"));

  if (photons->size() > 1) {
    const xAOD::Photon *y1 = (*photons)[0], *y2 = (*photons)[1];

    if (acc_sf.isAvailable(*y1) && acc_sf.isAvailable(*y2)) {
      weightSF = acc_sf(*y1) * acc_sf(*y2);
    } else {
      ATH_MSG_FATAL("scaleFactor decoration not found on HGamPhotons, but");
      ATH_MSG_FATAL("code is configured to update pileup weight? Exiting.");
      return EL::StatusCode::FAILURE;
    }
  }

  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK(wk()->xaodEvent()->retrieve(eventInfo, "EventInfo"));

  if (name.find("_PRW_DATASF__1up") != std::string::npos) {
    ANA_CHECK(m_prwTool->applySystematicVariation(m_prwSysUp));
  } else if (name.find("_PRW_DATASF__1down") != std::string::npos) {
    ANA_CHECK(m_prwTool->applySystematicVariation(m_prwSysDown));
  } else {
    ANA_CHECK(m_prwTool->applySystematicVariation(m_prwSysNom));
  }

  float pileupWeight = m_prwTool->getCombinedWeight(*eventInfo);
  acc_pw(*hgamInfo) = pileupWeight;

  float weightInitial = acc_mcw(*eventInfo)[0] * pileupWeight * acc_vw(*hgamInfo); // WRONG!!! SHOULD NOT USE WEIGHT[0]!!!!
  acc_wi(*hgamInfo) = weightInitial;

  float weight = weightInitial * weightSF;
  acc_w(*hgamInfo) = weight;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SkimAndSlim::recordContainers()
{
  ANA_CHECK_SET_TYPE(EL::StatusCode);

  // Add containers to output
  for (std::string cont : m_contToSave) {
    if (cont == "HGamPhotons") {
      ANA_CHECK((recordContainer<xAOD::PhotonContainer, xAOD::Photon>(cont)));
    } else if (cont == "HGamElectrons") {
      ANA_CHECK((recordContainer<xAOD::ElectronContainer, xAOD::Electron>(cont)));
    } else if (cont == "HGamMuons") {
      ANA_CHECK((recordContainer<xAOD::MuonContainer, xAOD::Muon>(cont)));
    } else if (cont == "HGamAntiKt4EMTopoJets") {
      ANA_CHECK((recordContainer<xAOD::JetContainer, xAOD::Jet>(cont)));
    } else if (cont == "HGamMET_Reference_AntiKt4EMTopo") {
      ANA_CHECK((recordContainer<xAOD::MissingETContainer, xAOD::MissingET>(cont)));
    } else if (cont == "HGamTruthPhotons") {
      ANA_CHECK((recordContainer<xAOD::TruthParticleContainer, xAOD::TruthParticle>(cont)));
    } else if (cont == "HGamTruthElectrons") {
      ANA_CHECK((recordContainer<xAOD::TruthParticleContainer, xAOD::TruthParticle>(cont)));
    } else if (cont == "HGamTruthMuons") {
      ANA_CHECK((recordContainer<xAOD::TruthParticleContainer, xAOD::TruthParticle>(cont)));
    } else if (cont == "HGamAntiKt4TruthJets") {
      ANA_CHECK((recordContainer<xAOD::JetContainer, xAOD::Jet>(cont)));
    } else if (cont == "HGamTruthHiggsBosons") {
      ANA_CHECK((recordContainer<xAOD::TruthParticleContainer, xAOD::TruthParticle>(cont)));
    } else if (cont == "TruthEvents") {
      ANA_CHECK((recordContainer<xAOD::TruthEventContainer, xAOD::TruthEvent>(cont)));
    } else if (cont == "EventInfo") {
      ANA_CHECK(recordInfo<xAOD::EventInfo>(cont));
    } else if (cont == "HGamEventInfo") {
      ANA_CHECK(recordInfo<xAOD::EventInfo>(cont));
    } else if (cont == "HGamTruthEventInfo") {
      ANA_CHECK(recordInfo<xAOD::EventInfo>(cont));
    } else {
      ATH_MSG_FATAL("Unknown class type for container: " << cont.c_str());
      return EL::StatusCode::FAILURE;
    }

  }

  // Add extra MC generator weights
  if (m_extraMCWeights.size() > 0)
  { ANA_CHECK(addMCGenExtraWeights()); }

  // Update pileup weights
  if (m_updatePRW)
  { ANA_CHECK(updatePileupWeight("HGamEventInfo")); }

  // Update mu variable
  if (m_updateMu)
  { ANA_CHECK(updateMu("HGamEventInfo")); }

  // Save systematics, if configured
  for (std::string sys : m_sysComps) {
    std::string cont = "HGamEventInfo" + sys;

    ANA_CHECK(recordInfo<xAOD::EventInfo>(cont));

    if (m_updatePRW)
    { ANA_CHECK(updatePileupWeight(cont)); }
  }

  return EL::StatusCode::SUCCESS;
}

