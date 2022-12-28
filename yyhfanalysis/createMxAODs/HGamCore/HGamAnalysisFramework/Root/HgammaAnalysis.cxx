// STL include(s):
#include <cstdlib>
#include <omp.h>

// EDM include(s):
#include "EventLoop/Job.h"
#include "EventLoop/StatusCode.h"
#include "EventLoop/OutputStream.h"
#include "PATInterfaces/SystematicVariation.h"
#include "PATInterfaces/SystematicsUtil.h"
#include "PhotonVertexSelection/PhotonVertexHelpers.h"
#include "PhotonVertexSelection/PhotonPointingTool.h"
#include "xAODMetaData/FileMetaData.h"
#include "EventLoop/OutputStream.h"

#include <xAODRootAccess/Init.h>

// ROOT include(s):
#include "TTree.h"
#include "TBranch.h"

// Local include(s):
#include "HGamAnalysisFramework/HgammaAnalysis.h"
#include "HGamAnalysisFramework/HGamVariables.h"

#include <xAODRootAccess/Init.h>

typedef ElementLink<xAOD::TruthParticleContainer> TruthLink_t;
typedef ElementLink<xAOD::PhotonContainer> PhotonLink_t;

// this is needed to distribute the algorithm to the workers
ClassImp(HgammaAnalysis)

HgammaAnalysis :: HgammaAnalysis(const char *name)
  : m_event(nullptr)
  , m_store(nullptr)
  , m_metaDataTool(nullptr)
  , m_truthDataTool(nullptr)
  , m_histoStore(nullptr)
  , m_name(name)
  , m_vertexTool(nullptr)
  , m_photonHandler(nullptr)
  , m_electronHandler(nullptr)
  , m_jetHandler(nullptr)
  , m_jetHandlerPFlow(nullptr)
  , m_tauHandler(nullptr)
  , m_muonHandler(nullptr)
  , m_eventHandler(nullptr)
  , m_truthHandler(nullptr)
  , m_overlapHandler(nullptr)
  , m_etmissHandler(nullptr)
  , m_etmissHandlerPFlow(nullptr)
  , m_catTool(nullptr)
  , m_yybbTool(nullptr)
  , m_yyHFTool(nullptr)
  , m_GammaORTool(nullptr)
  , m_HGamVLQTool(nullptr)
  , m_HGamHiggsHFTool(nullptr)
  , m_metCatTool(nullptr)
  , m_fcncTool(nullptr)
  , m_hcTool(nullptr)
  , m_isInit(false)
  , m_doPileupWeight(false)
  , m_doVertexWeight(false)
{
  this->SetName(name); // Set name for AsgMsgStream
  // Must have no pointer initialization, for CINT
}

EL::StatusCode HgammaAnalysis :: setupJob(EL::Job &job)
{
  job.useXAOD();

  // let's initialize the algorithm to use the xAODRootAccess package
  xAOD::Init(m_name.Data()).ignore(); // call before opening first file

  // tell EventLoop about our output ntuple:
  EL::OutputStream out("MxAOD", "xAODNoMeta");
  out.options()->setString(EL::OutputStream::optMergeCmd, "xAODMerge -m xAODMaker::FileMetaDataTool -m xAODMaker::TruthMetaDataTool");
  job.outputAdd(out);

  // Uncomment these if you would like to see som i/o stats at the end of the job
  //job.options()->setDouble (EL::Job::optXAODPerfStats, 1);
  //job.options()->setDouble (EL::Job::optPrintPerFileStats, 1);

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode HgammaAnalysis :: createOutput()
{
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode HgammaAnalysis :: histInitialize()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  m_histoStore = new HistogramStore();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HgammaAnalysis :: fileExecute()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HgammaAnalysis :: changeInput(bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.

  // file name
  Info("changeInput", "Processing file \"%s\"", wk()->inputFile()->GetName());
  Info("changeInput", "This file has %lli entries", wk()->xaodEvent()->getEntries());

  TTree *MetaData = dynamic_cast<TTree *>(wk()->inputFile()->Get("MetaData"));

  if (MetaData == nullptr)
  { HG::fatal("Couldn't find MetaData TTree in event, is this a proper xAOD file? Exiting."); }

  if (firstFile) {
    bool isAOD = MetaData->GetBranch("StreamAOD");
    bool isMAOD = !MetaData->GetBranch("TriggerMenu");
    HG::setAndLock_InputType(isAOD, isMAOD);
  }

  // HG::isDAOD() = !HG::isAOD() && !HG::isMAOD(); -- see HgammaUtils

  m_newFile = true;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HgammaAnalysis :: initialize()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  // Set appropriate return type for ANA_CHECK
  ANA_CHECK_SET_TYPE(EL::StatusCode);

  TString nproc = std::getenv("ATHENA_PROC_NUMBER");

  if (nproc == "")
  { omp_set_num_threads(1); }
  else
  { omp_set_num_threads(atoi(nproc.Data())); }

  m_eventCounter = 0;

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  HG::VarHandler::getInstance()->setEventAndStore(event(), store());

  // asg::SgTEventMeta meta(asg::SgTEventMeta::InputStore);
  // const xAOD::FileMetaData *metad = nullptr;
  // if (meta.retrieve(metad, "MetaData").isFailure())
  //   HG::fatal("Couldn't retrieve MetaData");
  // std::string val;
  // metad->value(xAOD::FileMetaData::conditionsTag, val);

  const xAOD::EventInfo *eventInfo = 0;

  if (m_event->retrieve(eventInfo, "EventInfo").isFailure()) {
    HG::fatal("Cannot access EventInfo");
  }

  HG::setAndLock_isMC(eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION));

  bool isAFII = false;

  if (HG::isMC()) {
    int mcID = eventInfo->mcChannelNumber();

    // When the MetaDataTool is fully available, we will get rid of the
    // ability/need to set IsAFII via the config file.
    asg::AsgMetadataTool amdt("MetaDataTool");

    if (!amdt.inputMetaStore()->contains<xAOD::FileMetaData>("FileMetaData")) {
      // HG::fatal("There is no FileMetaData in the input file.");
      Warning("", "There is no FileMetaData in the input file (only available since 21.2 derivations). Proceeding with whatever is in the config files.");

      if (m_config.isDefined(Form("IsAFII.%d", mcID))) {
        isAFII = m_config.getBool(Form("IsAFII.%d", mcID));
      }

      TString mcType = m_config.getStr("MonteCarloType", "MC15a");

      // Override for specifically-set MonteCarloTypes (Only in the case FileMetaData does not exist)
      if (m_config.isDefined(Form("MonteCarloType.%d", mcID))) {
        mcType = m_config.getStr(Form("MonteCarloType.%d", mcID));
      }

      HG::setAndLock_mcType(mcType);

    } else {
      const xAOD::FileMetaData *fmd = nullptr;
      ANA_CHECK(amdt.inputMetaStore()->retrieve(fmd, "FileMetaData"));

      std::string productionRelease, amiTag, AODFixVersion, AODCalibVersion, dataType, geometryVersion, conditionsTag, beamType, simFlavour;
      float beamEnergy, mcProcID;

      fmd->value(xAOD::FileMetaData::productionRelease, productionRelease); // Release that was used to make the file
      fmd->value(xAOD::FileMetaData::amiTag, amiTag); // AMI tag used to process the file the last time
      fmd->value(xAOD::FileMetaData::AODFixVersion, AODFixVersion); // Version of AODFix that was used on the file last
      fmd->value(xAOD::FileMetaData::AODCalibVersion, AODCalibVersion); // Version of AODCalib that was used on the file last
      fmd->value(xAOD::FileMetaData::dataType, dataType); // Data type that's in the file
      fmd->value(xAOD::FileMetaData::geometryVersion, geometryVersion); // Geometry version
      fmd->value(xAOD::FileMetaData::conditionsTag, conditionsTag); // Conditions version used for simulation/reconstruction
      fmd->value(xAOD::FileMetaData::beamEnergy, beamEnergy); // Beam energy
      fmd->value(xAOD::FileMetaData::beamType, beamType); // Beam type
      fmd->value(xAOD::FileMetaData::mcProcID, mcProcID); // Same as mc_channel_number [float]

      // Fast or Full sim
      if (!fmd->value(xAOD::FileMetaData::simFlavour, simFlavour)) {
        HG::fatal("There is no simFlavour in FileMetaData.");
      }

      if (simFlavour == "FullG4") { isAFII = false; }
      else if (simFlavour == "AtlfastII") { isAFII = true; }
      else {
        HG::fatal("Unknown simFlavour " + simFlavour + " in FileMetaData.");
      }

      TString mcType = HG::get_mcTypeUsingAmiTag(amiTag);
      HG::setAndLock_mcType(mcType);

      // Print out this information as a cross-check
      Info("initialize()", "productionRelease = %s", productionRelease.c_str());
      Info("initialize()", "amiTag            = %s (%s)", amiTag.c_str(), mcType.Data());
      Info("initialize()", "AODFixVersion     = %s", AODFixVersion.c_str());
      Info("initialize()", "AODCalibVersion   = %s", AODCalibVersion.c_str());
      Info("initialize()", "dataType          = %s", dataType.c_str());
      Info("initialize()", "geometryVersion   = %s", geometryVersion.c_str());
      Info("initialize()", "conditionsTag     = %s", conditionsTag.c_str());
      Info("initialize()", "beamEnergy        = %2.0f", beamEnergy);
      Info("initialize()", "beamType          = %s", beamType.c_str());
      Info("initialize()", "mcProcID          = %2.0f", mcProcID);
      Info("initialize()", "simFlavour        = %s", simFlavour.c_str());

    } // end of FileMetaData block

  } // end of if (HG::isMC()) block

  HG::setAndLock_isAFII(isAFII);

  // What systematics to save
  HG::StrV uncComps = config()->getStrV("HgammaAnalysis.UncertaintyComponents", {"*"});

  for (TString unc : uncComps) {
    TRegexp exp(unc, true);
    m_uncComps.push_back(exp);
  }

  HG::StrV ignoreUncComps = config()->getStrV("HgammaAnalysis.IgnoreUncertaintyComponents", {});

  for (TString unc : ignoreUncComps) {
    TRegexp exp(unc, true);
    m_ignoreUncComps.push_back(exp);
  }

  // Print configuration database, if requested
  if (m_config.getBool("HgammaAnalysis.PrintConfig", true)) {
    Info("initialize()", "Printing full configuration:");
    m_config.printDB();
    Info("initialize()", " ");
  }

  // sample name
  TString sampleName = wk()->metaData()->castString("sample_name");
  Info("initialize()", "Sample name = %s", sampleName.Data());

  // Vertex selection tool
  m_tpoint.setTypeAndName("CP::PhotonPointingTool/yyVtxPointingTool");
  ANA_CHECK(m_tpoint.initialize());

  m_vertexTool = new CP::PhotonVertexSelectionTool("PhotonVertexSelectionTool");
  ANA_CHECK(m_vertexTool->setProperty("PhotonPointingTool", m_tpoint.getHandle()));
  ANA_CHECK(m_vertexTool->initialize());

  m_markPhotonCand = m_config.getBool("PhotonHandler.SortCandidatesFirst", false);

  m_eventHandler = new HG::EventHandler("EventHandler", m_event, m_store);
  ANA_CHECK(m_eventHandler->initialize(m_config));

  m_photonHandler = new HG::PhotonHandler("PhotonHandler", m_event, m_store);
  ANA_CHECK(m_photonHandler->initialize(m_config));

  m_electronHandler = new HG::ElectronHandler("ElectronHandler", m_event, m_store);
  ANA_CHECK(m_electronHandler->initialize(m_config));

  m_jetHandler = new HG::JetHandler("JetHandler", m_event, m_store);
  ANA_CHECK(m_jetHandler->initialize(m_config));

  m_jetHandlerPFlow = new HG::JetHandler("JetHandlerPFlow", m_event, m_store);
  ANA_CHECK(m_jetHandlerPFlow->initialize(m_config));

  m_tauHandler = new HG::TauHandler("TauHandler", m_event, m_store);
  ANA_CHECK(m_tauHandler->initialize(m_config));

  m_muonHandler = new HG::MuonHandler("MuonHandler", m_event, m_store);
  ANA_CHECK(m_muonHandler->initialize(m_config));

  m_truthHandler = new HG::TruthHandler(m_event, m_store);
  ANA_CHECK(m_truthHandler->initialize(m_config));

  m_overlapHandler = new HG::OverlapRemovalHandler();
  ANA_CHECK(m_overlapHandler->initialize(m_config));

  m_etmissHandler = new HG::ETmissHandler("ETmissHandler", m_event, m_store);
  ANA_CHECK(m_etmissHandler->initialize(m_config));

  //m_etmissHandlerPFlow = new HG::ETmissHandler("ETmissHandlerPFlow", m_event, m_store);
  //ANA_CHECK(m_etmissHandlerPFlow->initialize(m_config));

  m_catTool = 0;

  if (config()->getBool("DoHGamCategoryTool", true)) {
    m_catTool = new HG::HGamCategoryTool("CategoryTool", m_eventHandler);
    ANA_CHECK(m_catTool->initialize(m_config));
  }

  m_yybbTool = 0;

  if (config()->getBool("DoHHyybbTool", true)) {
    m_yybbTool = new HG::HHyybbTool("HHyybbTool", m_eventHandler, m_truthHandler);
    ANA_CHECK(m_yybbTool->initialize(m_config));
  }

  m_yyHFTool = 0;

  if (config()->getBool("DoDiphotonHF", false)) {
    m_yyHFTool = new HG::yyHFTool("yyHFTool", m_eventHandler, m_truthHandler);
  }

  m_GammaORTool = 0;

  if (config()->getBool("DoVGammaOverlap", false)) {
    m_GammaORTool = new HG::GammaORTool("GammaORTool", m_eventHandler, m_truthHandler);
  }

  m_HGamVLQTool = 0;

  if (config()->getBool("DoVLQTool", true)) {
    m_HGamVLQTool = new HG::HGamVLQTool("HGamVLQTool", m_eventHandler, m_truthHandler);
    ANA_CHECK(m_HGamVLQTool->initialize(m_config));
  }

  m_HGamHiggsHFTool = 0;

  if (config()->getBool("DoHiggsHFTool", true)) {
    m_HGamHiggsHFTool = new HG::HGamHiggsHFTool("HGamHiggsHFTool", m_eventHandler, m_truthHandler);
    ANA_CHECK(m_HGamHiggsHFTool->initialize(m_config));
  }

  m_metCatTool = 0;

  if (config()->getBool("DoHGamMETCatTool", true)) {
    m_metCatTool = new HG::HGamMETCatTool(m_eventHandler);
    ANA_CHECK(m_metCatTool->initialize(m_config));
  }

  m_fcncTool = 0;

  if (config()->getBool("DoFCNCTool", true)) {
    m_fcncTool = new HG::FCNCTool(m_eventHandler);
    ANA_CHECK(m_fcncTool->initialize(m_config));

    if (HG::isMC())
    { m_fcncTool->truthHandler(m_truthHandler); }
  }

  m_hcTool = 0;

  if (config()->getBool("DoHcTool", true)) {
    m_hcTool = new HG::HcgamgamTool("HcgamgamTool", m_eventHandler, m_truthHandler);
    ANA_CHECK(m_hcTool->initialize(m_config));
  }

  m_anaTrigs = m_config.getStrV("HgammaAnalysis.AnalysisTriggers", {""});
  m_doAnaTrig = m_anaTrigs[0] != "";

  m_doPileupWeight = m_config.getBool("HgammaAnalysis.DoPileupWeight", true);
  m_doVertexWeight = m_config.getBool("HgammaAnalysis.DoVertexWeight", true);

  m_doTwoGoodPhotonsCut = m_config.getBool("HgammaAnalysis.CheckTwoGoodPhotons", true);

  m_doRelPtCut = m_config.getBool("HgammaAnalysis.CheckRelativePtCuts", true);
  m_relPtCut1  = m_config.getNum("HgammaAnalysis.RelPtFractionFirst", 0.35);
  m_relPtCut2  = m_config.getNum("HgammaAnalysis.RelPtFractionSecond", 0.25);

  m_doVertex   = m_config.getBool("HgammaAnalysis.SelectVertex", true);
  m_doHardPV   = m_config.getBool("HgammaAnalysis.UseHardestVertex", false);

  m_doMyyCut   = m_config.getBool("HgammaAnalysis.CheckMyyWindowCut", true);
  m_myyLow     = m_config.getNum("HgammaAnalysis.LowMyyGeV", 105.0) * HG::GeV;
  m_myyHigh    = m_config.getNum("HgammaAnalysis.HighMyyGeV", 13000.0) * HG::GeV;

  m_doJetClean  = m_config.getBool("HgammaAnalysis.CheckJetEventCleaning", false);

  if (m_doJetClean && m_config.getStr("JetHandler.Selection.CutLevel", "") != "LooseBad")
  { HG::fatal("Currently you must clean jets with LooseBad to check CheckJetEventCleaning."); }

  // Fill list of systematics
  fillSystematicsList();

  // Need this after tools initialized, so that all systematic histograms are made
  // histInitialize();
  ANA_CHECK(createOutput());

  // move to the user class? This is pretty standard
  TFile *file = wk()->getOutputFile("MxAOD");

  m_metaDataTool = new xAODMaker::FileMetaDataTool();
  ANA_CHECK(m_metaDataTool->initialize());

  m_truthDataTool = new xAODMaker::TruthMetaDataTool();
  ANA_CHECK(m_truthDataTool->initialize());

  if (!m_event->writeTo(file).isSuccess()) {
    Error("initialize()", "Failed to write event to output file!");
    return EL::StatusCode::FAILURE;
  }

  TTree *colltree = dynamic_cast<TTree *>(file->Get("CollectionTree"));

  colltree->SetAutoFlush(100);
  colltree->SetAutoSave(0);

  // register all histograms
  for (auto *histo : m_histoStore->getListOfHistograms()) {
    wk()->addOutput(histo);
  }

  m_isInit = true;

  // Get Photon Fake Rate 2D Histogram file
  TString fileLocation = PathResolverFindCalibFile(config()->getStr("HgammaAnalysis.PhotonSelection.PhotonFakeFile").Data());
  m_PhotonFakeRateFile = TFile::Open(fileLocation, "read");

  if (m_PhotonFakeRateFile == 0)
  { Fatal("Initialize", "Failed to open photon fake rate file..."); }

  m_PhotonFakes2DHist = (TH2F *)m_PhotonFakeRateFile->Get("PhotonFakeRates");

  if (m_PhotonFakes2DHist == 0)
  { Fatal("Initialize", "Failed to fetch photon fake histogram..."); }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HgammaAnalysis :: execute()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  if (!m_isInit)
  { HG::fatal("HgammaAnalysis was not initialized. Did you forget to call HgammaAnalysis::initialize() ?"); }

  if (m_eventCounter == 0) { m_startTime = time(nullptr); } //time in seconds

  static int progressInterval = config()->getInt("OutputMessage.ProcessedEventsInterval", 1000);

  if (m_eventCounter && m_eventCounter % progressInterval == 0) {
    Info("execute()", "%i events processed so far  <<<===", static_cast< int >(m_eventCounter));
    Info("execute()", "Processing rate = %.3f Hz", float(m_eventCounter) / (time(nullptr) - m_startTime));
  }

  m_eventCounter++;

  // This function will print the errors, no checking is required
  CP_CHECK(m_name, applySystematicVariation(CP::SystematicSet()));

  // Clear containers which point to objects from previous event
  HG::VarHandler::getInstance()->clearContainers();

  // Must call PRW before getting photon SFs
  eventHandler()->prwApply();

  // Retrieves nominal photons for diphoton pointing vertex
  if (m_doVertex) { selectVertex(); } // Selecting PV from the new HggPrimaryVertices container

  if (m_newFile) { // do things that should only be done once per file but require initialize()
    if (HG::isMC()) {
      if (config()->isDefined(Form("SampleName.%d", eventInfo()->mcChannelNumber()))) {
        m_jetHandler->setMCGen(getMCSampleName(eventInfo()->mcChannelNumber()));
        m_jetHandlerPFlow->setMCGen(getMCSampleName(eventInfo()->mcChannelNumber()));
      } else {
        m_jetHandlerPFlow->setMCGen("UNKNOWN");
      }
    }

    m_newFile = false;
  }

  setWeightInitial();

  return EL::StatusCode::SUCCESS;
}




EL::StatusCode HgammaAnalysis :: postExecute()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode HgammaAnalysis :: finalize()
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

  Info("finalize()", "Finished processing %i events", m_eventCounter);
  double nSecs = time(nullptr) - m_startTime;
  Info("finalize()", "Total time elapsed: %dh %dm %ds", int(nSecs) / 3600, (int(nSecs) % 3600) / 60, int(nSecs) % 60);
  Info("finalize()", "Processing rate = %.3f Hz", float(m_eventCounter) / (time(nullptr) - m_startTime));

  // Delete the Photon Fake Rates File
  if (m_PhotonFakeRateFile != 0) {
    m_PhotonFakeRateFile->Close();
  }

  SafeDelete(m_PhotonFakeRateFile);
  SafeDelete(m_vertexTool);
  SafeDelete(m_photonHandler);
  SafeDelete(m_electronHandler);
  SafeDelete(m_jetHandler);
  SafeDelete(m_jetHandlerPFlow);
  SafeDelete(m_tauHandler);
  SafeDelete(m_muonHandler);
  SafeDelete(m_histoStore);
  SafeDelete(m_eventHandler);
  SafeDelete(m_truthHandler);
  SafeDelete(m_overlapHandler);
  SafeDelete(m_etmissHandler);
  //SafeDelete(m_etmissHandlerPFlow);
  SafeDelete(m_catTool);
  SafeDelete(m_yybbTool);
  SafeDelete(m_yyHFTool);
  SafeDelete(m_GammaORTool);
  SafeDelete(m_HGamVLQTool);
  SafeDelete(m_HGamHiggsHFTool);
  SafeDelete(m_metCatTool);
  SafeDelete(m_fcncTool);
  SafeDelete(m_hcTool);

  TFile *file = wk()->getOutputFile("MxAOD");

  if (!m_event->finishWritingTo(file).isSuccess()) {
    Error("finalize()", "Failed to finish writing event to output file!");
    return EL::StatusCode::FAILURE;
  }

  SafeDelete(m_metaDataTool);
  SafeDelete(m_truthDataTool);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HgammaAnalysis :: histFinalize()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}

/// Fill m_sysList with systematics
void HgammaAnalysis::fillSystematicsList()
{

  // Clear the list, in case it was filled before.
  m_sysList.clear();

  std::vector<CP::SystematicSet> tempList;

  if (HG::isMAOD()) {
    // Always consider nominal
    tempList.push_back(CP::SystematicSet());

    // if the file is an MxAOD, then get the systematics list from branch names

    TTree *collectionTree = dynamic_cast<TTree *>(wk()->inputFile()->Get("CollectionTree"));

    if (collectionTree == nullptr)
    { HG::fatal("Couldn't find CollectionTree in input file, is this a proper xAOD file? Exiting."); }

    TObjArray *branches = collectionTree->GetListOfBranches();

    for (int i = 0; i < branches->GetEntries(); i++) {

      TBranch *branch = (TBranch *)branches->At(i);

      if (TString(branch->GetClassName()) != "xAOD::EventInfo_v1") { continue; }

      TString bname = branch->GetName();

      if (!bname.Contains("HGamEventInfo")) { continue; }

      bname.ReplaceAll("HGamEventInfo_", "");
      bname.ReplaceAll("HGamEventInfo", "");

      // Ignore nominal case (added above)
      if (bname.IsNull()) { continue; }

      tempList.push_back(CP::SystematicSet(bname.Data()));

    }

  } else {
    // Get list of systematic uncertainties from the helper tools.
    // Must be done after all helper tools defined
    const CP::SystematicRegistry &registry = CP::SystematicRegistry::getInstance();
    auto recommendedSystematics = registry.recommendedSystematics();

    tempList = CP::make_systematics_vector(recommendedSystematics);
  }

  // Now prune the list according to "UncertaintyComponents" and "IgnoreUncertaintyComponents"

  for (auto sys : tempList) {
    TString sysname = sys.name().c_str();

    // Always run over nominal
    if (sysname == "") {
      m_sysList.push_back(sys);
      continue;
    }

    // Check if we want to run over this shift
    bool considerSys = false;

    for (TRegexp exp : m_uncComps) {
      if (sysname.Contains(exp)) {
        considerSys = true;
        break;
      }
    }

    for (TRegexp exp : m_ignoreUncComps) {
      if (sysname.Contains(exp)) {
        considerSys = false;
        break;
      }
    }

    if (not considerSys) { continue; }

    m_sysList.push_back(sys);

  }

  return;
}

/// Check if systematic is available (for us in MxAODs)
bool HgammaAnalysis::isSystematicAvailable(const CP::SystematicSet &sys)
{
  CP_CHECK("execute()", HG::VarHandler::getInstance()->applySystematicVariation(sys));

  bool isAvailable = true;

  if (HG::isMAOD() && !var::isPassed.exists())
  { isAvailable = false; }

  CP_CHECK("execute()", HG::VarHandler::getInstance()->applySystematicVariation(CP::SystematicSet()));

  return isAvailable;
}

/// Configures all handlers for systematic variation according to the specified systematic set
CP::SystematicCode HgammaAnalysis::applySystematicVariation(const CP::SystematicSet &sys)
{
  static const char *METHOD = "HgammaAnalysis::applySystematicVariation";
  CP_CHECK(METHOD, m_eventHandler               ->applySystematicVariation(sys));
  CP_CHECK(METHOD, m_photonHandler              ->applySystematicVariation(sys));
  CP_CHECK(METHOD, m_muonHandler                ->applySystematicVariation(sys));
  CP_CHECK(METHOD, m_tauHandler                 ->applySystematicVariation(sys));
  CP_CHECK(METHOD, m_electronHandler            ->applySystematicVariation(sys));
  CP_CHECK(METHOD, m_jetHandler                 ->applySystematicVariation(sys));
  CP_CHECK(METHOD, m_jetHandlerPFlow            ->applySystematicVariation(sys));
  CP_CHECK(METHOD, m_etmissHandler              ->applySystematicVariation(sys));
  //CP_CHECK(METHOD, m_etmissHandlerPFlow         ->applySystematicVariation(sys));
  CP_CHECK(METHOD, HG::VarHandler::getInstance()->applySystematicVariation(sys));

  setWeightInitial();

  return CP::SystematicCode::Ok;
}



bool HgammaAnalysis::pass(const xAOD::PhotonContainer   *photons,
                          const xAOD::ElectronContainer *electrons,
                          const xAOD::MuonContainer     *muons,
                          const xAOD::JetContainer      *jets)
{
  if (var::isPassed.exists())
  { return var::isPassed(); }

  if (m_doTwoGoodPhotonsCut) {
    if (photons == nullptr) { return false; }

    if (!passTwoGoodPhotonsCut(*photons)) { return false; }
  }

  if (m_eventHandler->doTrigMatch() &&
      !passTriggerMatch(photons, electrons, muons, jets))
  { return false; }

  if (m_doRelPtCut) {
    if (photons == nullptr) { return false; }

    if (!passRelativePtCuts(*photons)) { return false; }
  }

  if (m_doMyyCut) {
    if (photons == nullptr) { return false; }

    if (!passMyyWindowCut(*photons)) { return false; }
  }

  if (m_doJetClean &&
      !passJetEventCleaning())
  { return false; }

  return true;
}

// Return the generator Higgs mass, in GeV, from config specified by
//   GeneratorHiggsMass.MCCHANNELNUMBER
// if not defined, the code is aborted
double HgammaAnalysis::getGeneratorHiggsMass(int mcID)
{
  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_higgsMass.find(mcID) == m_higgsMass.end())
  { m_higgsMass[mcID] = config()->getNum(Form("GeneratorHiggsMass.%d", mcID)); }

  return m_higgsMass[mcID];
}

// Return the generator efficiency from config specified by
//   GeneratorEfficiency.MCCHANNELNUMBER
// if not defined, 1.0 is returned
double HgammaAnalysis::getGeneratorEfficiency(int mcID)
{
  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_genEffs.find(mcID) == m_genEffs.end())
  { m_genEffs[mcID] = config()->getNum(Form("GeneratorEfficiency.%d", mcID), 1.0); }

  return m_genEffs[mcID];
}

// Return the kFactor from config specified by
//   GeneratorEfficiency.MCCHANNELNUMBER
// if not defined, 1.0 is returned
double HgammaAnalysis::getKFactor(int mcID)
{
  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_kFactors.find(mcID) == m_kFactors.end())
  { m_kFactors[mcID] = config()->getNum(Form("kFactor.%d", mcID), 1.0); }

  return m_kFactors[mcID];
}

// Return the cross section, in pb, from config specified by
//   CrossSection.MCCHANNELNUMBER
// if not defined, the code is aborted
double HgammaAnalysis::getCrossSection(int mcID)
{
  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_crossSections.find(mcID) == m_crossSections.end())
  { m_crossSections[mcID] = config()->getNum(Form("CrossSection.%d", mcID)); }

  return m_crossSections[mcID];
}

TString HgammaAnalysis::getMCSampleName(int mcID)
{
  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_mcNames.find(mcID) == m_mcNames.end())
  { m_mcNames[mcID] = config()->getStr(Form("SampleName.%d", mcID)).ReplaceAll(" ", ""); }

  return m_mcNames[mcID];
}

int HgammaAnalysis::getNtotalEvents(int mcID)
{
  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_nTotEvents.find(mcID) == m_nTotEvents.end())
  { m_nTotEvents[mcID] = config()->getInt(Form("TotalNEvents.%d", mcID)); }

  return m_nTotEvents[mcID];
}

TH1F *HgammaAnalysis::getCutFlowHistogram(int mcID, TString suffix)
{
  // access the initial number of weighed events
  TString cutFlowName(Form("CutFlow_%s%d%s", HG::isData() ? "Run" : "MC", mcID, suffix.Data()));
  bool hasMCname = config()->isDefined(Form("SampleName.%d", mcID));

  if (hasMCname) cutFlowName = Form("CutFlow_%s%s",
                                      getMCSampleName(mcID).Data(), suffix.Data());
  else { Warning("", "SampleName.%d not specfied in config!", mcID); }

  TH1F *cflowHist = (TH1F *)wk()->inputFile()->Get(cutFlowName);

  if (cflowHist == nullptr)
  { HG::fatal("Cannot access cut-flow histogram " + cutFlowName + " in input file"); }

  return cflowHist;
}

// sum of events, including pileup weights an skimming fraction
double HgammaAnalysis::getSumOfWeights(int mcID)
{
  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_NevtsInitial.find(mcID) == m_NevtsInitial.end()) {
    TString opt = "SumOfWeights" + HG::mcType();
    opt += ".";
    opt += mcID;

    if (config()->isDefined(opt)) {
      m_NevtsInitial[mcID] = config()->getNum(opt);
    } else {
      // Hard-coding to bin number 3 = ALLEVTS
      HG::fatal(opt + " not defined in configuration, needed by getSumOfWeights");
    }
  }

  return m_NevtsInitial[mcID];
}

// intial sum of events, including pileup weights
double HgammaAnalysis::getIntialSumOfWeights(int mcID)
{
  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_NevtsInitial.find(mcID) == m_NevtsInitial.end()) {
    // Hard-coding to bin number 3 = ALLEVTS
    m_NevtsInitial[mcID] = getCutFlowHistogram(mcID, "_noDalitz_weighted")->GetBinContent(3);
  }

  return m_NevtsInitial[mcID];
}

// Return the cross section * BR * filter Eff, in pb, from config specified by
//   CrossSection.MCCHANNELNUMBER
//   GeneratorEfficiency.MCCHANNELNUMBER
//   kFactor.MCCHANNELNUMBER
// if CrossSection not defined, -99 is returned
double HgammaAnalysis::crossSectionBRfilterEff(int mcID)
{
  if (HG::isData()) { return -99; }

  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_crossSectionBRfilterEff.find(mcID) != m_crossSectionBRfilterEff.end())
  { return m_crossSectionBRfilterEff[mcID]; }

  double xs = -99, kf = 1.0, ge = 1.0;

  TString opt = TString::Format("CrossSection.%d", mcID);

  if (config()->isDefined(opt)) {
    xs = getCrossSection(mcID);

    opt = TString::Format("GeneratorEfficiency.%d", mcID);

    if (config()->isDefined(opt))
    { ge = getGeneratorEfficiency(); }

    opt = TString::Format("kFactor.%d", mcID);

    if (config()->isDefined(opt))
    { kf = getKFactor(); }
  }

  m_crossSectionBRfilterEff[mcID] = xs * kf * ge;

  return m_crossSectionBRfilterEff[mcID];
}

double HgammaAnalysis::lumiXsecWeight(double intLumi, int mcID, bool printFirst)
{
  if (intLumi < 0) { intLumi = config()->getNum("IntegratedLuminosity_fbInv" + HG::mcType(), 1.0); }

  if (mcID == -1) { mcID = eventInfo()->mcChannelNumber(); }

  if (m_weightXsec.find(mcID) == m_weightXsec.end()) {
    double sigma      = getCrossSection(mcID);
    double gen_eff    = getGeneratorEfficiency(mcID);
    double kFactor    = getKFactor(mcID);

    // Hard-coding to bin number 1,2
    double sumInitial = 0, NxAOD = 1.0, NDxAOD = 1.0;
    TString opt = "SumOfWeights" + HG::mcType();
    opt += ".";
    opt += mcID;
    bool sumDefined = config()->isDefined(opt);

    if (sumDefined) {
      sumInitial = getSumOfWeights(mcID);
    } else {
      sumInitial = getIntialSumOfWeights(mcID);
      NxAOD      = getCutFlowHistogram(mcID, "_weighted")->GetBinContent(1);
      NDxAOD     = getCutFlowHistogram(mcID, "_weighted")->GetBinContent(2);
    }

    // int Ntot = config()->isDefined(Form("TotalNEvents.%d",mcID)) ? getNtotalEvents(mcID) : -1;
    double skim_eff = NDxAOD / NxAOD;

    m_weightXsec[mcID] = intLumi * 1e3 * sigma * gen_eff * skim_eff * kFactor / sumInitial;

    if (printFirst) {
      printf("\nMC sample %d: %s\n", mcID, getMCSampleName(mcID).Data());
      printf("  Cross section:                %10.4e pb\n", sigma);

      if (gen_eff != 1.0) { printf("  Generator efficiency:         %10.4e\n", gen_eff); }

      if (kFactor != 1.0) { printf("  k-factor:                     %10.2f\n", kFactor); }

      // if (Ntot) printf("  N events in AMI:              %10d\n",Ntot);
      if (sumDefined) {
        printf("  Sum of event weights:  %10.2f\n\n", sumInitial);
      } else {
        printf("  sum w in xAOD:                %10.2f\n", NxAOD);
        printf("  sum w in DxAOD:               %10.2f\n", NDxAOD);

        if (skim_eff != 1.0) { printf("  DxAOD efficiency:             %10.2f%%\n", skim_eff * 100); }

        printf("  Sum of inital event weights:  %10.2f\n\n", sumInitial);
      }

      // L * sigma * eff * kFactor / Nevts
      printf("  Integrated lumi.:             %10.4f fb-1\n", intLumi);
      printf("  N exp. events for analysis:   %10.2e\n", intLumi * 1e3 * sigma * gen_eff * skim_eff * kFactor);
      printf("  Cross section event weight:   %10.4e\n\n", m_weightXsec[mcID]);
    }
  }

  return m_weightXsec[mcID];
}




void HgammaAnalysis::selectVertex()
{
  // If the event doesn't contain PVs, can't correct anything
  if (!m_event->contains<xAOD::VertexContainer>("PrimaryVertices")) {
    static bool first = true;

    if (first && not HG::isMAOD()) Warning("selectVertex", "No PrimaryVertices container.%s",
                                             " No PV correction can be applied!!");

    first = false;
    return;
  }

  // set m_isVtxCorr to false everywhere
  m_photonHandler->setVertexCorrected(false);
  m_jetHandler->setVertexCorrected(false);
  m_jetHandlerPFlow->setVertexCorrected(false);
  m_electronHandler->setVertexCorrected(false);
  m_muonHandler->setVertexCorrected(false);
  m_tauHandler->setVertexCorrected(false);

  const xAOD::Vertex *vertex = nullptr;

  if (m_doHardPV) {
    const xAOD::VertexContainer *vertices = nullptr;

    if (m_event->retrieve(vertices, "PrimaryVertices").isFailure())
    { HG::fatal("Couldn't retrieve PrimaryVertices, exiting!"); }

    vertex = xAOD::PVHelpers::getHardestVertex(vertices);
  } else {

    const xAOD::VertexContainer *vertices = nullptr;

    if (m_event->retrieve(vertices, "HggPrimaryVertices").isFailure()) {
      Warning("HgammaAnalysis::selectVertex()", "Couldn't retrieve HggPrimaryVertices, will build it locally");
      xAOD::PhotonContainer photons = photonHandler()->getCorrectedContainer();
      xAOD::PhotonContainer presel  = photonHandler()->applyPreSelection(photons);

      presel.resize(2);

      // Mark the nominal preselected photons as the Higgs candidate
      if (m_markPhotonCand                                &&
          (!photonHandler()->markAsCandidate(presel[0]) ||
           !photonHandler()->markAsCandidate(presel[1])))
      { Warning("selectVertex()", "Couldn't mark leading photons as Higgs candidates"); }

      vertex = m_vertexTool->getVertex(presel)[0].first;

      // select PV vertex if getVertex function fails
      if (vertex == nullptr) {
        const xAOD::VertexContainer *vertices = nullptr;

        if (m_event->retrieve(vertices, "PrimaryVertices").isFailure())
        { HG::fatal("Couldn't retrieve PrimaryVertices, exiting!"); }

        vertex = xAOD::PVHelpers::getHardestVertex(vertices);
      }

    } else {
      for (auto vtx : *vertices) {
        if (vtx->vertexType() == xAOD::VxType::PriVtx) { // NN selected vertex
          vertex = vtx;
          break;
        }
      }

      // select PV vertex if no vertex is PriVtx
      if (vertex == nullptr) {
        const xAOD::VertexContainer *vertices = nullptr;

        if (m_event->retrieve(vertices, "PrimaryVertices").isFailure())
        { HG::fatal("Couldn't retrieve PrimaryVertices, exiting!"); }

        vertex = xAOD::PVHelpers::getHardestVertex(vertices);
      }
    }


  }



  // Only set the vertex to use for kinematic corrections if it's not a nullptr
  if (vertex != nullptr) {
    ConstDataVector<xAOD::VertexContainer> *vcont = new ConstDataVector<xAOD::VertexContainer>(SG::VIEW_ELEMENTS);
    vcont->push_back(vertex);

    if (m_store->record(vcont, "HGamVertices").isFailure())
    { HG::fatal("Couldn't add HGamVertices to TStore, exiting."); }
  }

}




void HgammaAnalysis::setWeightInitial()
{
  // Always calculate weightInitial, for updating pileup weight

  // Determine the initial event weight
  double weight = 1.0;

  if (HG::isMC()) {
    // First MC generator weights
    weight *= eventHandler()->mcWeight();

    if (m_doPileupWeight) {
      // Pileup weight
      weight *= eventHandler()->pileupWeight();
    }

    if (m_doVertexWeight) {
      // z-vertex weight
      weight *= eventHandler()->vertexWeight();
    }
  }

  var::weightInitial.setValue(weight);
}


/// Get initial event weight: MC, pileup, z-vertex
double HgammaAnalysis::weightInitial()
{
  if (!var::weightInitial.exists()) {
    HG::fatal("Initial event weight not found, did you call HgammaAnalysis::execute() ?");
    return -1.0; // should never get called
  }

  return var::weightInitial();
}



/// Get event weight: initial weight * leading two photon SFs
double HgammaAnalysis::weight()
{
  if (!var::weight.exists()) {
    HG::fatal("You must call setSelectedObjects before retrieving the weight!");
    return -1.0; // should never get called
  }

  return var::weight();
}

void HgammaAnalysis::addTruthLinks(std::string recoName, std::string truthName)
{
  // Get the containers
  xAOD::IParticleContainer *recoCont = nullptr;

  if (m_event->retrieve(recoCont, recoName).isFailure())
  { HG::fatal("Couldn't retrieve reco container"); }

  xAOD::TruthParticleContainer *truthCont = nullptr;

  if (m_event->retrieve(truthCont, truthName).isFailure())
  { HG::fatal("Couldn't retrieve truth container"); }

  addTruthLinks(recoCont, truthCont);
}

void HgammaAnalysis::addTruthLinks(xAOD::IParticleContainer *recoCont, xAOD::TruthParticleContainer *truthCont)
{

  // Helpful variables
  std::vector<size_t> linked;
  static SG::AuxElement::Accessor<ElementLink<xAOD::IParticleContainer> > accTruthLink("truthLink");
  static SG::AuxElement::Accessor<ElementLink<xAOD::IParticleContainer> > accRecoLink("recoLink");

  //Loop over each reco particle
  for (auto recoPtcl : *recoCont) {
    // Grab the truth link from the reconstructed particle
    TruthLink_t link = recoPtcl->auxdata<TruthLink_t>("truthParticleLink");

    // Create a null truthPtcl. This is set to the truth particle in the new container
    xAOD::TruthParticle *truthPtcl = nullptr;

    // Only try search if we have a valid link
    if (link.isValid()) {
      // Get barcode of truth particle in original particle container
      int origPtclBarcode = (*link)->barcode();

      // Search through new container for the truth particle barcode (From old container link)
      for (auto ptcl : *truthCont) {
        if (ptcl->barcode() == origPtclBarcode) {
          truthPtcl = ptcl;
          break;
        }
      }
    }

    if (truthPtcl != nullptr) {
      ElementLink<xAOD::IParticleContainer> truthLink(*truthCont, truthPtcl->index());
      accTruthLink(*recoPtcl) = truthLink;

      ElementLink<xAOD::IParticleContainer> recoLink(*recoCont, recoPtcl->index());
      accRecoLink(*truthPtcl) = recoLink;

      linked.push_back(truthPtcl->index());
    } else {
      ElementLink<xAOD::IParticleContainer> truthLink;
      accTruthLink(*recoPtcl) = truthLink;
    }
  }

  // For all truth particles not linked already, add a null-link
  for (auto ptcl : *truthCont) {
    if (std::find(linked.begin(), linked.end(), ptcl->index()) == linked.end()) {
      ElementLink<xAOD::IParticleContainer> recoLink;
      accRecoLink(*ptcl) = recoLink;
    }
  }
}

xAOD::PhotonContainer HgammaAnalysis::getFakePhotons(double &photonFakeWeight)
{
  photonFakeWeight = 1;

  xAOD::PhotonContainer fakeCombination(SG::VIEW_ELEMENTS);
  static SG::AuxElement::ConstAccessor<float> fakeWeightAcc("weightFakePhotons");

  if (HG::isMAOD() && fakeWeightAcc.isAvailable(*eventInfo())) {
    photonFakeWeight = fakeWeightAcc(*eventInfo());

    return photonHandler()->getCorrectedContainer();
  } else if (HG::isMAOD() && not fakeWeightAcc.isAvailable(*eventInfo())) {
    Fatal("getFakePhotons()", "getFakePhotons() called on MxAOD that does not have fakes enabled. Please run over a DxAOD with the option enabled to produce a fakePhoton MxAOD.");
  }

  //Do not carry on if we do not have MC (No truth info in data)
  if (HG::isData()) { return fakeCombination; }

  //Here fakePhotons are preSelected photons that do not overlap truth photons
  //Here realPhotons are the photons which do overlap with truth photons (With the exception of some origin and IDs)
  xAOD::PhotonContainer fakePhotons(SG::VIEW_ELEMENTS);
  xAOD::PhotonContainer realPhotons(SG::VIEW_ELEMENTS);
  xAOD::PhotonContainer realTightPhotons(SG::VIEW_ELEMENTS);

  xAOD::TruthParticleContainer truthPhotons = truthHandler()->getPhotons();
  xAOD::PhotonContainer all_photons = photonHandler()->getCorrectedContainer();
  xAOD::PhotonContainer selPhotons = photonHandler()->applySelection(all_photons);

  for (auto photon : selPhotons) {
    // Must pass preselction (Object Quality and pT/Eta Cuts)
    if (!photonHandler()->passPtEtaCuts(photon) ||
        !photonHandler()->passAmbCut(photon) ||
        !photonHandler()->passAuthorCut(photon)) { continue; }

    // photons with a deltaR < 0.2 are labelled as real
    if (HG::minDR(photon, truthPhotons) < 0.2)
    { realTightPhotons.push_back(photon); }
  }

  for (auto photon : all_photons) {
    // Must pass preselction (Object Quality and pT/Eta Cuts)
    if (!photonHandler()->passPtEtaCuts(photon) ||
        !photonHandler()->passAmbCut(photon) ||
        !photonHandler()->passAuthorCut(photon)) { continue; }

    // photons with a deltaR > 0.2 are labelled as fake
    if (HG::minDR(photon, truthPhotons) < 0.2)
    { realPhotons.push_back(photon); }
    else
    { fakePhotons.push_back(photon); }
  }

  //Count the number of photons that are not fakes and pass Tight,Iso cuts
  int trueTightPhotonCount = realTightPhotons.size();

  //Count the number of photons that are not fakes and pass Tight,Iso cuts
  int truePhotonCount = realPhotons.size();

  //Count the number of fake photons
  int fakePhotonCount = fakePhotons.size();

  //If we have two real photons then we do not return any fake combinations. (No need)
  if (trueTightPhotonCount >= 2)
  { return fakeCombination; }

  //Do not continue if we can never make two photons
  if (truePhotonCount + fakePhotonCount < 2)
  { return fakeCombination; }

  //Fetch good combinations and choose one that pass myy cut if there is any
  std::vector<std::pair<xAOD::PhotonContainer, double>> goodCombi = getPhotonCombinations(realPhotons, fakePhotons);
  std::pair<xAOD::PhotonContainer, double> selCombination = chooseRandomComb(goodCombi);

  //Now check if we have at least two photon candidates
  if (selCombination.first.size() >= 2) {
    fakeCombination = selCombination.first;
    photonFakeWeight = selCombination.second;
    return fakeCombination; //No need to continue from here
  }

  return fakeCombination;
}

double HgammaAnalysis::getFPprob(xAOD::Photon *photon)
{
  TLorentzVector photon4V = photon->p4() * HG::invGeV;
  double photonPt = photon4V.Pt();
  double photonEta = std::fabs(photon4V.Eta());

  int xbin = m_PhotonFakes2DHist->GetXaxis()->FindBin(photonPt);
  int ybin = m_PhotonFakes2DHist->GetYaxis()->FindBin(photonEta);

  double prob = m_PhotonFakes2DHist->GetBinContent(xbin, ybin);

  return prob;
}

std::vector<std::pair<xAOD::PhotonContainer, double>> HgammaAnalysis::getPhotonCombinations(xAOD::PhotonContainer &realPhotons, xAOD::PhotonContainer &fakePhotons)
{
  std::vector<std::pair<xAOD::PhotonContainer, double>> fakeCombi;

  int fakeCount = fakePhotons.size();

  //Loop over all possible combinations of fake photons being promoted or not.
  //2 fakes have 4 possible unique combinations: (0 = fake, 1 = promoted)
  // 00 01 10 11 => This is given by 2^2 or 2^fakeCount which is what 1 << fakeCount does using bitshifts
  for (int combi = 0; combi < 1 << fakeCount; combi++) {
    xAOD::PhotonContainer promotedPhotons = realPhotons;
    double fakeComboWt = 1;

    for (int i = 0; i < fakeCount; i++) {
      double fakeWt = getFPprob(fakePhotons[i]);

      if (combi & (1 << i))
      { promotedPhotons.push_back(fakePhotons[i]); }
      else
      { fakeWt = 1 - fakeWt; }

      fakeComboWt *= fakeWt;
    }

    //Sort the true and promoted photons by pT
    promotedPhotons.sort(photonHandler()->comparePt);
    //Returning all combinations
    fakeCombi.push_back({promotedPhotons, fakeComboWt});
  }

  return fakeCombi;
}

std::pair<xAOD::PhotonContainer, double> HgammaAnalysis::chooseRandomComb(std::vector<std::pair<xAOD::PhotonContainer, double>> &fakeCombi)
{
  //Create empty selected photons and weight = 1;
  xAOD::PhotonContainer selPhotons(SG::VIEW_ELEMENTS);
  double combiWeight = 1;
  std::pair<xAOD::PhotonContainer, double> selCombi = {selPhotons, combiWeight};

  //First check size of fake combinations. If zero then we return empty photons and weight =1.
  int combiCount = fakeCombi.size();

  if (combiCount == 0)
  { return selCombi; }

  //Get ready to filter out the good combinations
  std::vector<std::pair<xAOD::PhotonContainer, double>> goodFakeCombi;

  double goodSumWt = 0;

  //Loop over all fake combinations and sum weights for good fake combinations (Ones that pass cuts)
  for (auto comb : fakeCombi)
    if (passRelativePtCuts(comb.first) && passMyyWindowCut(comb.first) && comb.second != 0) {
      goodSumWt += comb.second;
      goodFakeCombi.push_back(comb);
    }

  //Now we have all good combinations

  //Starting value for random selection (Ranged based on combination weight). Generate random num.
  //Setting seed as event number
  double rndmNum = goodSumWt * gRandom->Rndm(eventInfo()->eventNumber());
  double start = 0.0;

  // Choose a random good combinations. Based on their weights. (Larger = more likely)
  for (int i = 0; i < (int)goodFakeCombi.size(); i++) {
    // check to see where the random number falls between [0, goodSumWt]
    // pick the combination in whose range the random number falls
    if (rndmNum > start && rndmNum < (start + goodFakeCombi[i].second)) {
      selCombi = {goodFakeCombi[i].first, goodSumWt};
      break;
    }

    start += goodFakeCombi[i].second;
  }

  return selCombi;
}


/// Set selected collections
void HgammaAnalysis::setSelectedTruthObjects(const xAOD::TruthParticleContainer *photons,
                                             const xAOD::TruthParticleContainer *electrons,
                                             const xAOD::TruthParticleContainer *muons,
                                             const xAOD::TruthParticleContainer *taus,
                                             const xAOD::JetContainer           *jets,
                                             const xAOD::MissingETContainer     *mets)
{
  HG::VarHandler::getInstance()->setTruthContainers(photons, electrons, muons, taus, jets, mets);

  setWeightInitial();

  if (!var::weight.exists())
  { var::weight.setValue(weightInitial()); }

}



/// Set selected collections
void HgammaAnalysis::setSelectedObjects(const xAOD::PhotonContainer    *photons,
                                        const xAOD::ElectronContainer  *electrons,
                                        const xAOD::MuonContainer      *muons,
                                        const xAOD::TauJetContainer      *taus,
                                        const xAOD::JetContainer       *jets,
                                        const xAOD::MissingETContainer *mets,
                                        const xAOD::JetContainer       */*jetsNoJvt*/)
{
  HG::VarHandler::getInstance()->setContainers(photons, electrons, muons, taus, jets, mets);

  if (!var::weightSF.exists()) {
    // determine SF weight
    double myweight = 1.0;

    if (HG::isMC()) {
      static SG::AuxElement::Accessor<float> scaleFactor("scaleFactor");

      if (photons != nullptr) {
        for (size_t i = 0; i < photons->size() && i < 2; ++i)
        { myweight *= scaleFactor(*photons->at(i)); }
      }

      var::weightTrigSF.setValue(eventHandler()->getSF_g35_medium_g25_medium_L12EM20VH(*photons));

      myweight *= var::weightTrigSF();
    }

    var::weightSF.setValue(myweight);
  }

  // total weight (mc, prw, vtx, sf)
  // Reset evertime, since weightInitial() might be updated
  // for new pileup weighting
  double myweight = weightInitial();
  myweight *= var::weightSF();
  var::weight.setValue(myweight);

}

/// Checks if event level jet cleaning cut is passed
bool HgammaAnalysis::passJetEventCleaning()
{
  if (var::isPassedJetEventClean.exists())
  { return var::isPassedJetEventClean(); }

  xAOD::PhotonContainer    all_photons  = photonHandler()->getCorrectedContainer();
  xAOD::PhotonContainer    photons      = photonHandler()->applySelection(all_photons);

  xAOD::JetContainer       all_jets     = jetHandler()->getCorrectedContainer();
  xAOD::JetContainer       jets         = jetHandler()->applySelectionNoCleaning(all_jets);

  xAOD::ElectronContainer  all_elecs    = electronHandler()->getCorrectedContainer();
  xAOD::ElectronContainer  electrons    = electronHandler()->applySelection(all_elecs);

  xAOD::MuonContainer      all_muons    = muonHandler()->getCorrectedContainer();
  xAOD::MuonContainer      muons        = muonHandler()->applySelection(all_muons);

  xAOD::TauJetContainer      all_taus    = tauHandler()->getCorrectedContainer();
  xAOD::TauJetContainer      taus        = tauHandler()->applySelection(all_taus);

  overlapHandler()->removeOverlap(photons, jets, electrons, muons, taus);

  static SG::AuxElement::ConstAccessor<char>  isClean("isClean");

  bool isEventClean = true;

  for (auto jet : jets) {
    if (not isClean(*jet)) {
      isEventClean = false;
      break;
    }
  }

  var::isPassedJetEventClean.setValue(isEventClean);

  return isEventClean;
}

bool HgammaAnalysis::passCrackVetoCleaning(const xAOD::PhotonContainer &photons, const xAOD::ElectronContainer &electrons)
{
  for (auto eg : photons) {
    if (!photonHandler()->passCrackVetoCleaning(*eg)) { return false; }
  }

  for (auto eg : electrons) {
    if (!electronHandler()->passCrackVetoCleaning(*eg)) { return false; }
  }

  return true;
}


//______________________________________________________________________________
bool HgammaAnalysis::passTwoGoodPhotonsCut(const xAOD::PhotonContainer &photons)
{
  if (photons.size() < 2)
  { return false; }

  xAOD::PhotonContainer leading = photons;
  leading.resize(2);

  xAOD::PhotonContainer sel = photonHandler()->applySelection(leading);

  if (sel.size() < 2)
  { return false; }

  return true;
}

/// Checks if relative pT cuts for photons are passed
bool HgammaAnalysis::passRelativePtCuts(const xAOD::PhotonContainer &photons)
{
  // If there aren't two photons, the cut fails
  if (photons.size() < 2) { return false; }

  // Assume Higgs mass from two leading photons
  double myy = (photons[0]->p4() + photons[1]->p4()).M();

  // Check if relative pT cuts are satisfied
  if (photons[0]->pt() / myy < m_relPtCut1) { return false; }

  if (photons[1]->pt() / myy < m_relPtCut2) { return false; }

  return true;
}

/// Checks if myy is in the required window
bool HgammaAnalysis::passMyyWindowCut(const xAOD::PhotonContainer &photons)
{
  // If there aren't two photons, the cut fails
  if (photons.size() < 2) { return false; }

  double myy = (photons[0]->p4() + photons[1]->p4()).M();
  return m_myyLow <= myy && myy < m_myyHigh;
}


bool HgammaAnalysis::passTriggerMatch(const xAOD::PhotonContainer   *photons,
                                      const xAOD::ElectronContainer *electrons,
                                      const xAOD::MuonContainer     *muons,
                                      const xAOD::JetContainer      *jets)
{
  // If the analysis only cares about one trigger, only check that trigger
  if (m_doAnaTrig) {
    for (auto trig : m_anaTrigs) {
      if (m_eventHandler->passTrigger(trig) &&
          m_eventHandler->passTriggerMatch(trig.Data(), photons, electrons, muons, jets))
      { return true; }
    }

    return false;
  }

  // Check whether at least one passing trigger is matched to selected objects
  for (auto trig : eventHandler()->getRequiredTriggers()) {
    if (m_eventHandler->passTrigger(trig) &&
        m_eventHandler->passTriggerMatch(trig.Data(), photons, electrons, muons, jets))
    { return true; }
  }

  return false;
}

bool HgammaAnalysis::passTriggerMatch(const TString &trig,
                                      const xAOD::PhotonContainer   *photons,
                                      const xAOD::ElectronContainer *electrons,
                                      const xAOD::MuonContainer     *muons,
                                      const xAOD::JetContainer      *jets)
{
  return eventHandler()->passTriggerMatch(trig, photons, electrons, muons, jets);
}

