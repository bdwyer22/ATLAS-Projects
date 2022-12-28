// EDM include(s):
#include "EventLoop/Worker.h"
#include "PhotonVertexSelection/PhotonPointingTool.h"
#include "PhotonVertexSelection/PhotonVertexHelpers.h"
#include "xAODCutFlow/CutBookkeeper.h"
#include "xAODCutFlow/CutBookkeeperContainer.h"

// Local include(s):
#include "HGamAnalysisFramework/HGamVariables.h"
#include "HGamTools/HGamCutflowAndMxAOD.h"

#include "xAODTau/TauxAODHelpers.h"

// this is needed to distribute the algorithm to the workers
ClassImp(HGamCutflowAndMxAOD)

HGamCutflowAndMxAOD::HGamCutflowAndMxAOD(const char *name)
  : HgammaAnalysis(name), m_goodFakeComb(false), m_N_xAOD(0), m_N_DxAOD(0),
    m_sumw_xAOD(0.0), m_sumw2_xAOD(0.0), m_sumw_DxAOD(0.0), m_sumw2_DxAOD(0.0) { }

HGamCutflowAndMxAOD::~HGamCutflowAndMxAOD() {}

void HGamCutflowAndMxAOD::declareOutputVariables(TString outName, TString configKey, HG::StrV extra, HG::StrV ignore)
{
  if (config()->isDefined(configKey)) {

    TString vars = config()->getStr(configKey).Data();

    if (m_saveDetailed) {
      TString detailKey = configKey.ReplaceAll("Variables", "DetailedVariables");

      if (config()->isDefined(detailKey)) {
        TString detailed = config()->getStr(detailKey);
        vars += "." + detailed;
      }
    }

    for (TString val : extra)
    { vars += val; }

    for (TString val : ignore)
    { vars = vars.ReplaceAll(val, ""); }

    vars.ReplaceAll(" ", "");

    event()->setAuxItemList((outName + "Aux.").Data(), vars.Data());
  } else { HG::fatal("Cannot find " + configKey); }
}

EL::StatusCode HGamCutflowAndMxAOD::createOutput()
{
  // Read the output branch names - add option to make this configurable in future ?
  m_photonContainerName = "HGam" + config()->getStr("PhotonHandler.ContainerName");
  m_jetContainerName    = "HGam" + config()->getStr("JetHandler.ContainerName");
  m_elecContainerName   = "HGam" + config()->getStr("ElectronHandler.ContainerName");
  m_muonContainerName   = "HGam" + config()->getStr("MuonHandler.ContainerName");
  m_tauContainerName    = "HGam" + config()->getStr("TauHandler.ContainerName");
  m_evtInfoName         = "EventInfo";
  m_truthEvtsName       = "TruthEvents";
  m_truthParticlesName   = "TruthParticles";
  m_truthVerticesName   = "TruthVertices";

  // What selection to require. For defintion, see CutEnum in the header file
  // Negative values means no event selection
  m_skimCut = config()->getInt("SkimmingCut", -1);

  // Whether or not to apply systematic variations
  // If true, all variables will be stored
  m_applySystematics = config()->getBool("ApplySystematicVariations", false);

  if (m_applySystematics && m_skimCut >= 1)
  { HG::fatal("Running over systematics and applying a skimming cut is currently not possible."); }

  // Whether to allow more than two good photons
  m_allowMoreThanTwoPhotons = config()->getBool("AllowMoreThanTwoPhotons", false);

  // Whether to save objects (photons, jets ...)
  m_saveObjects = config()->getBool("SaveObjects", false);

  // Whether to save the list of differential variables
  m_saveDetailed = config()->getBool("SaveDetailedVariables", false);

  // Whether to save the truth objects and differential variables
  m_saveTruthObjects = HG::isMC() && config()->getBool("SaveTruthObjects", false);
  m_saveTruthVars    = HG::isMC() && config()->getBool("SaveTruthVariables", false);

  //Save fake photon combinations
  m_enableFakePhotons = HG::isMC() && config()->getBool("SaveFakePhotonCombinations", false);

  // Whether we are running with yybb-tool in detailed mode.
  m_detailedHHyybb = config()->getBool("HHyybb.DetailedInfo", false);

  // Temporary hack for large PhotonAllSys samples
  m_photonAllSys = config()->getStr("PhotonHandler.Calibration.decorrelationModel") == "FULL_v1";

  // a. Event variables
  HG::StrV ignore = {};

  // FIXME need to add all HTXS variables, this is an outdated list
  if (HG::isData()) ignore = {".mcChannelNumber", ".mcEventWeights", ".RandomRunNumber", ".truthCentralEventShapeDensity", ".truthForwardEventShapeDensity", ".HTXS_Higgs_eta", ".HTXS_Higgs_m", ".HTXS_Higgs_phi", ".HTXS_Higgs_pt", ".HTXS_Njets_pTjet25", ".HTXS_Njets_pTjet30", ".HTXS_Stage0_Category", ".HTXS_Stage1_Category_pTjet25", ".HTXS_Stage1_Category_pTjet30", ".HTXS_Stage1_FineIndex_pTjet25", ".HTXS_Stage1_FineIndex_pTjet30", ".HTXS_V_jets30_eta", ".HTXS_V_jets30_m", ".HTXS_V_jets30_phi", ".HTXS_V_jets30_pt", ".HTXS_V_pt", ".HTXS_errorCode", ".HTXS_prodMode", ".HTXS_Stage1_1_Category_pTjet25", ".HTXS_Stage1_1_Category_pTjet30", ".HTXS_Stage1_1_FineIndex_pTjet30", ".HTXS_Stage1_1_FineIndex_pTjet25", ".HTXS_Stage1_1_Fine_Category_pTjet25", ".HTXS_Stage1_1_Fine_Category_pTjet30", ".HTXS_Stage1_1_Fine_FineIndex_pTjet30", ".HTXS_Stage1_1_Fine_FineIndex_pTjet25", ".HTXS_Stage1_2_Category_pTjet25", ".HTXS_Stage1_2_Category_pTjet30", ".HTXS_Stage1_2_FineIndex_pTjet25", ".HTXS_Stage1_2_FineIndex_pTjet30", ".HTXS_Stage1_2_Fine_Category_pTjet25", ".HTXS_Stage1_2_Fine_Category_pTjet30", ".HTXS_Stage1_2_Fine_FineIndex_pTjet25", ".HTXS_Stage1_2_Fine_FineIndex_pTjet30", ".HTXS_isZ2vvDecay"};

  HG::StrV trigs = config()->getStrV("EventHandler.RequiredTriggers");

  HG::StrV extra = {};

  for (auto trig : trigs) { extra.push_back(".passTrig_" + trig); }

  declareOutputVariables(m_evtInfoName, "MxAOD.Variables.EventInfo", extra, ignore);

  // a.2 TruthEvents variables
  ignore = {};
  extra = {};
  declareOutputVariables(m_truthEvtsName, "MxAOD.Variables.TruthEvents", extra, ignore);

  // a.3 TruthParticles and TruthVertices variables
  declareOutputVariables(m_truthParticlesName, "MxAOD.Variables.TruthParticles", extra, ignore);
  declareOutputVariables(m_truthVerticesName, "MxAOD.Variables.TruthVertices", extra, ignore);

  // b. Selected objects

  // If we have a detailed run then append a list of extra variables to add to jets
  if (m_detailedHHyybb) {
    TString yybb_detailedJetVars = config()->getStr("MxAOD.Variables.Jet");// + config()->getStr("MxAOD.yybb-Detailed.Jet");
    yybb_detailedJetVars.ReplaceAll(" ", ""); //Remove spaces in lists...
    config()->setValue("MxAOD.Variables.Jet", yybb_detailedJetVars.Data());
  }

  if (HG::isData()) ignore = {".isEMTight_nofudge", ".isTight_nofudge", ".topoetcone20_DDcorrected", ".topoetcone40_DDcorrected", ".truthOrigin", ".truthType", ".truthConvRadius", ".scaleFactor", ".truthLink", ".parentPdgId", ".pdgId"};

  if (config()->getBool("PhotonHandler.AmbiguityExtraInfo", false)) {
    // declareOutputVariables just append the extra string(s) to the nominal one
    extra = {"." + config()->getStr("MxAOD.Variables.PhotonAmb")};
    declareOutputVariables(m_photonContainerName, "MxAOD.Variables.Photon", extra, ignore);
  } else {
    declareOutputVariables(m_photonContainerName, "MxAOD.Variables.Photon", {}, ignore);
  }

  if (m_enableFakePhotons)
  { declareOutputVariables("HGamPhotonsWithFakes", "MxAOD.Variables.Photon", {}, ignore); }

  if (HG::isData()) {
    for (TString taggerName : config()->getStrV("JetHandler.BTagging.TaggerNames")) {
      ignore = {".SF_" + taggerName + "_FixedCutBEff_60", ".SF_" + taggerName + "_FixedCutBEff_70", ".SF_" + taggerName + "_FixedCutBEff_77", ".SF_" + taggerName + "_FixedCutBEff_85", ".Eff_" + taggerName + "_FixedCutBEff_60", ".Eff_" + taggerName + "_FixedCutBEff_70", ".Eff_" + taggerName + "_FixedCutBEff_77", ".Eff_" + taggerName + "_FixedCutBEff_85", ".InEff_" + taggerName + "_FixedCutBEff_60", ".InEff_" + taggerName + "_FixedCutBEff_70", ".InEff_" + taggerName + "_FixedCutBEff_77", ".InEff_" + taggerName + "_FixedCutBEff_85", ".HadronConeExclTruthLabelID", ".PartonTruthLabelID"};
    }
  }

  declareOutputVariables(m_jetContainerName, "MxAOD.Variables.Jet", {}, ignore);

  TString m_pfjetContainerName = "HGam" + config()->getStr("JetHandlerPFlow.ContainerName");
  declareOutputVariables(m_pfjetContainerName, "MxAOD.Variables.PFlowJet", {}, ignore);

  TString m_btContainerName = "BTagging_";
  m_btContainerName += m_jetContainerName;
  m_btContainerName.ReplaceAll("Jets", "");
  declareOutputVariables(m_btContainerName, "MxAOD.Variables.BTag", {}, ignore);

  m_btContainerName = "BTagging_";
  m_btContainerName += m_pfjetContainerName;
  m_btContainerName.ReplaceAll("Jets", "");
  declareOutputVariables(m_btContainerName, "MxAOD.Variables.BTag", {}, ignore);

  if (HG::isData()) ignore = {".scaleFactor", ".truthLink", ".truthOrigin", ".truthType"};

  declareOutputVariables(m_elecContainerName, "MxAOD.Variables.Electron", {}, ignore);
  declareOutputVariables(m_muonContainerName, "MxAOD.Variables.Muon", {}, ignore);
  declareOutputVariables("HGamMuonsInJets", "MxAOD.Variables.Muon", {}, ignore);

  if (HG::isData()) ignore = {".truthOrigin", ".truthType", ".truthLink", ".jetLink", ".chargedPFOLinks", ".pi0PFOLinks", ".isHadronicTau", ".isTruthJet", ".truthMatchID", ".pdgId", ".classifierType"};

  declareOutputVariables(m_tauContainerName, "MxAOD.Variables.Tau", {}, ignore);

  // c. Truth objects
  if (HG::isMC()) {
    m_photonTruthContainerName = "HGam" + config()->getStr("TruthHandler.PhotonContainerName");
    m_elecTruthContainerName   = "HGam" + config()->getStr("TruthHandler.ElectronContainerName");
    m_muonTruthContainerName   = "HGam" + config()->getStr("TruthHandler.MuonContainerName");
    m_tauTruthContainerName    = "HGam" + config()->getStr("TruthHandler.TauContainerName");
    m_jetTruthContainerName    = "HGam" + config()->getStr("TruthHandler.JetContainerName");

    declareOutputVariables(m_photonTruthContainerName, "MxAOD.Variables.TruthPhotons");
    declareOutputVariables(m_elecTruthContainerName, "MxAOD.Variables.TruthElectrons");
    declareOutputVariables(m_muonTruthContainerName, "MxAOD.Variables.TruthMuons");
    declareOutputVariables(m_tauTruthContainerName, "MxAOD.Variables.TruthTaus");
    declareOutputVariables(m_jetTruthContainerName, "MxAOD.Variables.TruthJets");
    declareOutputVariables("HGam" + config()->getStr("TruthHandler.HiggsBosonContainerName"), "MxAOD.Variables.TruthHiggsBosons");
  }

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode HGamCutflowAndMxAOD::execute()
{
  // Needed for all underlaying tools to be working corectly!
  ANA_CHECK(HgammaAnalysis::execute());

  // if it's a new file, update the book-keeper
  if (m_newFile && HG::isDAOD()) {
    addBookKeeping(getCutFlowHisto(), m_N_xAOD, m_N_DxAOD);

    if (HG::isMC()) {
      addBookKeeping(getCutFlowHisto(false), m_N_xAOD, m_N_DxAOD);
      addBookKeeping(getCutFlowWeightedHisto(), m_sumw_xAOD, m_sumw_DxAOD, m_sumw2_xAOD, m_sumw2_DxAOD);
      addBookKeeping(getCutFlowWeightedHisto(false), m_sumw_xAOD, m_sumw_DxAOD, m_sumw2_xAOD, m_sumw2_DxAOD);
    }

    doTruthPtclVtx = false;

    if (HG::isMC()) {
      // decide whether save truth particle and vertices
      TString SampleName = config()->getStr(Form("SampleName.%d", eventInfo()->mcChannelNumber())).ReplaceAll(" ", "");
      StrV defaultSampleTruthPtclVtx;

      for (TString temp_SampleName : config()->getStrV("SampleTruthPtclVtx", defaultSampleTruthPtclVtx)) {
        if (m_newFile && SampleName.Contains(temp_SampleName)) { doTruthPtclVtx = true; }
      }

      if (m_newFile && doTruthPtclVtx) { doTruthPtclVtx = config()->getBool("SaveTruthPtclVtx", false); }
    }

    m_newFile = false;
  }

  // apply cuts. Returned value will be the last passed cut
  m_cutFlow = cutflow();

  // flag current event as a MC Dalitz event
  // (needed for cut-flow histograms)
  m_isDalitz = HG::isMC() && eventHandler()->isDalitz();

  // fill the cut-flow histograms up to tight selection
  double wi = weightInitial();

  for (int cut = ALLEVTS; cut < m_cutFlow; ++cut) {
    if (cut <= GAM_TIGHTID)
    { fillCutFlow(CutEnum(cut), wi); }
  }

  // if desired, apply skimming.
  // That is, only write events that pass a given cut to the output
  if (m_skimCut >= 1 && m_cutFlow <= m_skimCut)
  { return EL::StatusCode::SUCCESS; }

  // Selects the objects, does overlap removal, and calculate all
  // variables that will be saved
  ANA_CHECK(doReco());

  // fill the cut-flow histograms after tight selection including SF weights
  double w = weight();

  for (int cut = ALLEVTS; cut < m_cutFlow; ++cut) {
    if (cut > GAM_TIGHTID)
    { fillCutFlow(CutEnum(cut), w); }
  }

  // check if we should apply systematics or not
  if (m_applySystematics) {
    for (auto sys : getSystematics()) {
      // ignore nominal case, already done!
      if (sys.name() == "") { continue; }

      // apply the systmeatic variation and calculate the outupt
      CP_CHECK("HGamCutflowAndMxAOD::execute()", applySystematicVariation(sys));
      m_cutFlow = cutflow();
      ANA_CHECK(doReco(true));
    }
  }

  if (HG::isMC() && (m_saveTruthObjects || m_saveTruthVars))
  { ANA_CHECK(doTruth()); }

  // Write nominal EventInfo to output
  ANA_CHECK(eventHandler()->writeEventInfo());

  // Save all information written to output
  event()->fill();

  return EL::StatusCode::SUCCESS;
}

// Returns value of the last cut passed in the cut sequence
HGamCutflowAndMxAOD::CutEnum HGamCutflowAndMxAOD::cutflow()
{
  //Check if there are two good fakes. Needed so we dont slim the event at trigger.
  m_goodFakeComb = false;

  if (HG::isMC() && m_enableFakePhotons) {
    double weightFakePhotons = 1;
    xAOD::PhotonContainer photonsWithFakes = getFakePhotons(weightFakePhotons);
    m_goodFakeComb = photonsWithFakes.size() > 1 ? true : false;

    if (m_goodFakeComb) { return PASSALL; }
  }

  //==== CUT 0 : Remove duplicate events (only for data) ====
  static bool checkDuplicates = config()->getBool("EventHandler.CheckDuplicates");

  if (checkDuplicates && HG::isData() && eventHandler()->isDuplicate()) { return DUPLICATE; }

  //==== CUT 1 : GRL ====
  static bool requireGRL = config()->getBool("EventHandler.CheckGRL");

  if (requireGRL && HG::isData() && !eventHandler()->passGRL(eventInfo())) { return GRL; }

  //==== CUT 2 : Require trigger ====
  static bool requireTrigger = config()->getBool("EventHandler.CheckTriggers");

  if (requireTrigger && !eventHandler()->passTriggers()) { return TRIGGER; }

  //==== CUT 3 : Detector quality ====
  if (!(eventHandler()->passLAr(eventInfo()) &&
        eventHandler()->passTile(eventInfo()) &&
        eventHandler()->passSCT(eventInfo())))
  { return DQ; }

  //==== CUT 4 : Require a vertex ====
  if (!eventHandler()->passVertex(eventInfo())) { return VERTEX; }

  // retrieve the photons
  xAOD::PhotonContainer   all_photons  = photonHandler() -> getCorrectedContainer();
  xAOD::PhotonContainer   loosePhotons = photonHandler() -> applyPreSelection(all_photons);
  int nloose = 0, namb = 0, nHV = 0;

  for (auto gam : all_photons) {
    if (photonHandler()->passOQCut(gam)       &&
        photonHandler()->passCleaningCut(gam) &&
        photonHandler()->passPtEtaCuts(gam)   &&
        photonHandler()->passPIDCut(gam, egammaPID::PhotonIDLoose))
    { ++nloose; }

    if (photonHandler()->passOQCut(gam)       &&
        photonHandler()->passCleaningCut(gam) &&
        photonHandler()->passPtEtaCuts(gam)   &&
        photonHandler()->passPIDCut(gam, egammaPID::PhotonIDLoose) &&
        photonHandler()->passAmbCut(gam))
    { ++namb; }

    if (photonHandler()->passOQCut(gam)       &&
        photonHandler()->passCleaningCut(gam) &&
        photonHandler()->passPtEtaCuts(gam)   &&
        photonHandler()->passPIDCut(gam, egammaPID::PhotonIDLoose) &&
        photonHandler()->passAmbCut(gam)       &&
        photonHandler()->passHVCut(gam))
    { ++nHV; }
  }

  //==== CUT 5 : Require two loose photons, pT>25 GeV ====
  if (nloose < 2) { return TWO_LOOSE_GAM; }

  //==== CUT 6 : Preselection
  // - Require two loose photons that also pass e-gamma ambiguity ====
  static bool requireAmbiguity = config()->getBool("PhotonHandler.Selection.ApplyAmbiguityCut", false);

  if (requireAmbiguity && namb < 2) { return AMBIGUITY; }

  static bool requireHV = config()->getBool("PhotonHandler.Selection.ApplyHVCut", false);

  if (requireHV && nHV < 2) { return AMBIGUITY; }

  //==== CUT 7 : Require two loose photons to pass trigger matching
  static bool requireTriggerMatch = config()->getBool("EventHandler.CheckTriggerMatching", true);

  if (requireTriggerMatch && !passTriggerMatch(&loosePhotons)) { return TRIG_MATCH; }

  // Our *Higgs candidate photons* are the two, leading pre-selected photons
  // These are also the photons used to define the primary vertex
  xAOD::Photon *gam1 = loosePhotons[0], *gam2 = loosePhotons[1];

  //==== CUT 8 : Require both photons to pass photon ID (isEM) ====
  static bool requireTight = config()->getBool("PhotonHandler.Selection.ApplyPIDCut", true);

  if (requireTight && (!photonHandler()->passPIDCut(gam1) ||
                       !photonHandler()->passPIDCut(gam2)))
  { return GAM_TIGHTID; }

  //==== CUT 9 : Require both photons to fulfill the isolation criteria ===
  static bool requireIso = config()->getBool("PhotonHandler.Selection.ApplyIsoCut", true);

  if (requireIso && (!photonHandler()->passIsoCut(gam1) ||
                     !photonHandler()->passIsoCut(gam2)))
  { return GAM_ISOLATION; }

  //==== CUT 10 : Relative pT cuts ====
  if (!passRelativePtCuts(loosePhotons)) { return RELPTCUTS; }

  //==== CUT 11 : Mass window cut ====
  if (!passMyyWindowCut(loosePhotons)) { return MASSCUT; }

  /*
  // loop over the tigh photons and print if we find a tight photon that is not loose
  for (auto gam:tightPhotons)
    if (!photonHandler()->passPIDCut(gam,egammaPID::IsEMLoose)) {
      photonHandler()->printPhoton(gam,"Tight-ID photon that failes Loose-ID");
      if (!m_MxAODinput)
        for (auto tgam:HG::getGoodTruthPhotons(truthPtcls))
          HG::printTruthPtcl(tgam,"Truth photon");
  }
  */

  return PASSALL;
}

EL::StatusCode  HGamCutflowAndMxAOD::doReco(bool isSys)
{
  // Get object containers
  m_allPhotons = photonHandler()->getCorrectedContainer();
  m_preSelPhotons = photonHandler()->applyPreSelection(m_allPhotons);

  // selected the two Higgs candidate photons (used for pointing)
  m_selPhotons = xAOD::PhotonContainer(SG::VIEW_ELEMENTS);

  if (m_preSelPhotons.size()) { m_selPhotons.push_back(m_preSelPhotons[0]); }

  if (m_preSelPhotons.size() > 1) { m_selPhotons.push_back(m_preSelPhotons[1]); }

  // The below logic is for use in background side-band studies
  // For example, the loose-not-tight background category, where a leading loose photon
  // is still considered as part of the diphoton system
  // When checking for isPassed events, all photons are guaranteed to be tight
  if (m_allowMoreThanTwoPhotons) {
    // any tight isolated additional photon, is also treated as a photon
    for (size_t i = 2; i < m_preSelPhotons.size(); ++i) {
      xAOD::Photon *gam = m_preSelPhotons[i];

      if (photonHandler()->passIsoCut(gam) &&
          photonHandler()->passPIDCut(gam))
      { m_selPhotons.push_back(gam); }
    }
  }

  // If we enable fake photons then we replace the existing photon selection with the fake combinations.
  if (m_enableFakePhotons) {
    double weightFakePhotons = 1;
    xAOD::PhotonContainer photonsWithFakes(SG::VIEW_ELEMENTS);

    if (m_goodFakeComb) {
      photonsWithFakes = getFakePhotons(weightFakePhotons);
      eventHandler()->storeVar<float>("weightFakePhotons", weightFakePhotons);
      m_preSelPhotons = photonsWithFakes;
      m_selPhotons    = photonsWithFakes;
    }
  }

  m_allJets = jetHandler()->getCorrectedContainer();
  m_selJets = jetHandler()->applySelection(m_allJets);

  xAOD::JetContainer allPFlowJets = jetHandlerPFlow()->getCorrectedContainer();
  xAOD::JetContainer selPFlowJets = jetHandlerPFlow()->applySelection(allPFlowJets);
  m_allElectrons = electronHandler()->getCorrectedContainer();
  m_selElectrons = electronHandler()->applySelection(m_allElectrons);

  m_allMuons = muonHandler()->getCorrectedContainer();
  xAOD::MuonContainer dirtyMuons = muonHandler()->applySelection(m_allMuons);

  // Muon cleaning
  m_selMuons = muonHandler()->applyCleaningSelection(dirtyMuons);

  m_allTaus = tauHandler()->getCorrectedContainer();
  m_selTaus = tauHandler()->applySelection(m_allTaus);

  // Rebuild MET using selected objects
  m_allMET = etmissHandler()->getCorrectedContainer(&m_selPhotons,
                                                    &m_allJets,
                                                    &allPFlowJets,
                                                    &m_selElectrons,
                                                    &m_selMuons,
                                                    &m_selTaus);
  m_selMET = etmissHandler()->applySelection(m_allMET);

  /*
  // Rebuild pflow MET using selected objects
  xAOD::MissingETContainer m_allpfMET = etmissHandlerPFlow()->getCorrectedContainer(&m_selPhotons,
                                        &allPFlowJets,
                                        &m_selElectrons,
                                        &m_selMuons);
  xAOD::MissingETContainer m_selpfMET = etmissHandlerPFlow()->applySelection(m_allpfMET);
  */

  // Removes overlap with candidate diphoton system, and any additional tight photons (if option set)
  if (m_cutFlow > VERTEX) { overlapHandler()->removeOverlap(m_selPhotons, m_selJets, m_selElectrons, m_selMuons, m_selTaus); }

  // Veto for electron/photon in crack association bug for PFlow MET
  eventHandler()->storeVar<char>("passCrackVetoCleaning", passCrackVetoCleaning(m_selPhotons, m_selElectrons));

  // NOTICE!! we don't actually remove jets overlapping taus
  // we just give these jets a tag: "overlapTau"
  xAOD::JetContainer jets_in_taus = overlapHandler()->jetsInTaus(m_selJets, m_selTaus, -1);
  xAOD::TauJetContainer taus_in_jets = overlapHandler()->tausInJets(m_selTaus, m_selJets, -1);

  static SG::AuxElement::Accessor<bool> overlapTau("overlapTau");
  static SG::AuxElement::Accessor<bool> overlapJet("overlapJet");

  for (auto jet : m_selJets) {
    overlapTau(*jet) = false;
  }

  for (auto tau : m_selTaus) {
    overlapJet(*tau) = false;
  }

  for (auto jet : jets_in_taus) {
    overlapTau(*jet) = true;
  }

  for (auto tau : taus_in_jets) {
    overlapJet(*tau) = true;
  }

  // Add decoration for isolation SF : this also call applyScaleFactor for the muons
  muonHandler()->decorateDeltaRJet(m_selMuons, m_selJets);

  // Save JVT weight (needs special overlap removal)
  m_jvtJets = jetHandler()->applySelectionNoJvt(m_allJets);
  xAOD::ElectronContainer jvtElecs = m_selElectrons;
  xAOD::MuonContainer jvtMuons = m_selMuons;
  xAOD::TauJetContainer jvtTaus = m_selTaus;

  if (m_cutFlow > VERTEX) { overlapHandler()->removeOverlap(m_selPhotons, m_jvtJets, jvtElecs, jvtMuons, jvtTaus); }

  // Special overlap removal for PFlow jets
  xAOD::ElectronContainer pflowElecs = m_selElectrons;
  xAOD::MuonContainer pflowMuons = m_selMuons;
  xAOD::TauJetContainer pflowTaus = m_selTaus;

  if (m_cutFlow > VERTEX) { overlapHandler()->removeOverlap(m_selPhotons, selPFlowJets, pflowElecs, pflowMuons, pflowTaus); }

  // NOTICE!! we don't actually remove jets overlapping taus
  // we just give these jets a tag: "overlapTau"
  xAOD::JetContainer pfjets_in_taus = overlapHandler()->jetsInTaus(selPFlowJets, pflowTaus, -1);

  for (auto jet : selPFlowJets) {
    overlapTau(*jet) = false;
  }

  for (auto jet : pfjets_in_taus) {
    overlapTau(*jet) = true;
  }

  // Adds event weights and catgory to TStore
  // Also sets pointer to photon container, etc., which is used by var's
  setSelectedObjects(&m_selPhotons, &m_selElectrons, &m_selMuons, &m_selTaus, &m_selJets, &m_selMET, &m_jvtJets);

  if (catTool()) { catTool()->saveHGamCategoryInfo(&m_selPhotons, &m_selElectrons, &m_selMuons, &m_selJets, &m_selMET, &m_jvtJets); }

  if (not m_photonAllSys) {
    // Decorate yybb and VLQ information to HGamEventInfo
    // Must come before writing out containers (Detailed mode decorates objects for studying)
    if (yybbTool()) { yybbTool()->saveHHyybbInfo(m_preSelPhotons, m_allElectrons, m_allMuons, m_selJets, m_jvtJets, m_selMET); }

    if (HGamVLQTool()) { HGamVLQTool()->saveHGamVLQInfo(m_preSelPhotons, m_selJets, m_jvtJets, m_selMuons, m_selElectrons); }

    // Decorate MET information to HGamEventInfo
    if (metCatTool()) { metCatTool()->saveCategoryAndWeight(m_selPhotons, m_selElectrons, m_selMuons, m_selJets, m_selMET); }

    // Decorate FCNC information to HGamEventInfo
    if (fcncTool()) { fcncTool()->saveFCNCInfo(m_selPhotons, m_selMuons, m_selElectrons, m_selMET, m_selJets, eventInfo()); }
  }

  // Decorate HiggsHF information to HGamEventInfo
  if (HGamHiggsHFTool()) { HGamHiggsHFTool()->saveHGamHiggsHFInfo(m_preSelPhotons, m_selJets, m_jvtJets, m_selMuons, m_selElectrons); }

  // Decorate yy+HF information to HGamEventInfo, if we are doing this
  if (yyHFTool()) { yyHFTool()->saveyyHFInfo(m_preSelPhotons, m_selJets, m_jvtJets, m_selMET, m_selMuons, m_selElectrons); }

  //Decorate H+c info to HGamEventInfo
  if (hcTool()) { hcTool()->saveHCInfo(m_preSelPhotons, m_selJets, m_selMuons, m_selElectrons); }

  // Adds event-level variables to TStore
  if (m_photonAllSys) {
    writePhotonAllSys(isSys);
  } else {
    writeNominalAndSystematic(isSys);
  }

  if (not isSys && not m_photonAllSys) {
    writeNominalOnly();

    if (m_saveDetailed) { writeDetailed(); }

    if (m_saveObjects) {
      CP_CHECK("execute()", photonHandler()->writeContainer(m_selPhotons));
      CP_CHECK("execute()", electronHandler()->writeContainer(m_selElectrons));
      CP_CHECK("execute()", jetHandler()->writeContainerAndBjetContainer(m_selJets));
      CP_CHECK("execute()", jetHandlerPFlow()->writeContainerAndBjetContainer(selPFlowJets));
      CP_CHECK("execute()", muonHandler()->writeContainer(m_selMuons));
      CP_CHECK("execute()", tauHandler()->writeContainer(m_selTaus));
      CP_CHECK("execute()", etmissHandler()->writeContainer(m_selMET));

      //CP_CHECK("execute()", etmissHandlerPFlow()->writeContainer(m_selpfMET));
      if (yybbTool()) { CP_CHECK("execute()", yybbTool()->writeContainers()); }
    }
  }

  for (auto photon : m_selPhotons) {
    if (photon->pt() != photon->pt()) {
      HG::fatal("Photons have NaN pT?");
    }
  }

  // Adds all event variables (weight, category, isPassed, and pT_yy etc.)
  // to the TEvent output stream
  ANA_CHECK(HG::VarHandler::getInstance()->write());

  return EL::StatusCode::SUCCESS;
}

void HGamCutflowAndMxAOD::writePhotonAllSys(bool isSys)
{
  // Basic event selection flags
  var::isPassedBasic.setValue(m_goodFakeComb ? true : eventHandler()->pass());
  var::isPassed.setValue(m_goodFakeComb ? true : eventHandler()->pass() && pass(&m_selPhotons, &m_selElectrons, &m_selMuons, &m_selJets));
  var::cutFlow.setValue(m_cutFlow);

  if (HG::isMC()) { var::isDalitzEvent.setValue(m_isDalitz); }

  if (!isSys) {
    int Nloose = m_preSelPhotons.size();
    eventHandler()->storeVar<char>("isPassedPreselection", Nloose >= 2);
  }

  // Define the signal jets from the no-jvt cut collection
  // Jets with pT > 30/50 GeV are used for pT_j1_30, N_j_50, etc.
  xAOD::JetContainer jvtJets30(SG::VIEW_ELEMENTS), jvtJets50(SG::VIEW_ELEMENTS);

  for (auto jet : m_jvtJets) {
    if (jet->pt() < 30.0 * HG::GeV)
    { continue; }

    jvtJets30.push_back(jet);

    if (jet->pt() < 50.0 * HG::GeV)
    { continue; }

    jvtJets50.push_back(jet);
  }

  eventHandler()->storeVar<float>("weightJvt_30", HG::JetHandler::multiplyJvtWeights(&jvtJets30));
  eventHandler()->storeVar<float>("weightJvt_50", HG::JetHandler::multiplyJvtWeights(&jvtJets50));

  eventHandler()->storeVar<float>("weightFJvt", HG::JetHandler::multiplyFJvtWeights(&m_jvtJets));
  eventHandler()->storeVar<float>("weightFJvt_30", HG::JetHandler::multiplyFJvtWeights(&jvtJets30));

  // Cross-section fiducial regions
  xAOD::JetContainer jets30(SG::VIEW_ELEMENTS);
  double weightBJet30 = 1.0;
  static SG::AuxElement::ConstAccessor<float> SF_bjet("SF_DL1r_FixedCutBEff_70");

  for (auto jet : m_selJets) {
    if (jet->pt() < 30.0 * HG::GeV) { continue; }

    jets30.push_back(jet);
    weightBJet30 *= SF_bjet(*jet);
  }

  xAOD::JetContainer bjets30 = jetHandler()->applyBJetSelection(jets30);
  int nbjet30 = bjets30.size();

  eventHandler()->storeVar<int>("N_j_btag30", nbjet30);

  char xsec_ttHsemi = var::N_lep_15() >= 1 && var::N_j_30() >= 3 && nbjet30 >= 1;
  char xsec_ttHhad = var::N_lep_15() == 0 && var::N_j_30() >= 4 && nbjet30 >= 1;
  eventHandler()->storeVar<char>("catXS_ttH", xsec_ttHsemi || xsec_ttHhad);
  eventHandler()->storeVar<float>("weightCatXS_ttH", weightBJet30 * var::weightN_lep_15() * eventHandler()->getVar<float>("weightJvt_30"));

  int xs_nbjet = -99;

  if (var::N_j_central30() == 0 || var::N_lep() > 0)
  { xs_nbjet = 0; }
  else if (nbjet30 == 0)
  { xs_nbjet = 1; }
  else if (nbjet30 == 1)
  { xs_nbjet = 2; }
  else
  { xs_nbjet = 3; }

  eventHandler()->storeVar<char>("catXS_nbjet", xs_nbjet);
  eventHandler()->storeVar<float>("weightCatXS_nbjet", weightBJet30 * var::weightN_lep() * eventHandler()->getVar<float>("weightJvt_30"));

  int xs_HiggsHF = -99;
  xAOD::MuonContainer muonsPassing(SG::VIEW_ELEMENTS);
  // Apply muon requirements
  std::copy_if(m_selMuons.begin(), m_selMuons.end(), std::back_inserter(muonsPassing), [this](const xAOD::Muon * muon) {
    return (muon->pt() >= 10.0 * HG::GeV);
  });

  xAOD::ElectronContainer electronsPassing(SG::VIEW_ELEMENTS);
  // Apply electron requirements
  std::copy_if(m_selElectrons.begin(), m_selElectrons.end(), std::back_inserter(electronsPassing), [this](const xAOD::Electron * electron) {
    return (electron->pt() >= 10.0 * HG::GeV);
  });

  if (var::N_j_central30() > 0 && var::N_j_central30() < 4 && (muonsPassing.size() == 0) && (electronsPassing.size() == 0)) {
    xAOD::JetContainer jets_central(SG::VIEW_ELEMENTS);
    std::copy_if(m_selJets.begin(), m_selJets.end(), std::back_inserter(jets_central), [this](const xAOD::Jet * j) {
      return fabs(j->eta()) <= 2.5;
    });

    xAOD::JetContainer jets_central30(SG::VIEW_ELEMENTS);
    std::copy_if(jets_central.begin(), jets_central.end(), std::back_inserter(jets_central30), [this](const xAOD::Jet * j) {
      return (j->pt() >= 30 * HG::GeV);
    });

    xAOD::JetContainer sortedJets(SG::VIEW_ELEMENTS);

    for (auto jet : jets_central30) { sortedJets.push_back(jet); }

    // first sort jets by pT then do a stable sort by DL1r discriminant
    std::sort(sortedJets.begin(), sortedJets.end(), [](const xAOD::Jet * i, const xAOD::Jet * j) {
      return i->pt() > j->pt();
    });

    std::stable_sort(sortedJets.begin(), sortedJets.end(), [](const xAOD::Jet * i, const xAOD::Jet * j) {
      return i->auxdata<double>("DL1r_discriminant") > j->auxdata<double>("DL1r_discriminant");
    });


    if (sortedJets.size() > 0) {
      if (sortedJets[0]->auxdata<char>("DL1r_FixedCutBEff_60") || sortedJets[0]->auxdata<char>("DL1r_FixedCutBEff_70")) { xs_HiggsHF = 2; }
      else if (sortedJets[0]->auxdata<char>("DL1r_FixedCutBEff_77")) { xs_HiggsHF = 1; }
      else { xs_HiggsHF = 0; }
    }
  }

  eventHandler()->storeVar<char>("catXS_HiggsHF", xs_HiggsHF);
  eventHandler()->storeVar<float>("weightCatXS_HiggsHF", weightBJet30 * var::weightN_lep() * eventHandler()->getVar<float>("weightJvt_30"));

  // Mass measurement variables
  xAOD::EventInfo *ei = HG::VarHandler::getInstance()->getEventInfoFromStore();
  static SG::AuxElement::Accessor<float> eta_y1("eta_y1"), eta_y2("eta_y2");
  static SG::AuxElement::Accessor<float> etas2_y1("etas2_y1"), etas2_y2("etas2_y2");
  static SG::AuxElement::Accessor<int> conversionType_y1("conversionType_y1"), conversionType_y2("conversionType_y2");

  if (m_selPhotons.size() > 0) {
    eta_y1(*ei) = m_selPhotons[0]->eta();
    etas2_y1(*ei) = m_selPhotons[0]->caloCluster()->etaBE(2);
    conversionType_y1(*ei) = m_selPhotons[0]->conversionType();
  } else {
    eta_y1(*ei) = -99;
    etas2_y1(*ei) = -99;
    conversionType_y1(*ei) = -99;
  }

  if (m_selPhotons.size() > 1) {
    eta_y2(*ei) = m_selPhotons[1]->eta();
    etas2_y2(*ei) = m_selPhotons[1]->caloCluster()->etaBE(2);
    conversionType_y2(*ei) = m_selPhotons[1]->conversionType();
  } else {
    eta_y2(*ei) = -99;
    etas2_y2(*ei) = -99;
    conversionType_y2(*ei) = -99;
  }

  // Add MC only variables
  if (HG::isMC()) {
    if (config()->isDefined(TString::Format("CrossSection.%d", eventInfo()->mcChannelNumber()))) {
      double xs = getCrossSection(), kf = 1.0, ge = 1.0;

      if (config()->isDefined(TString::Format("kFactor.%d", eventInfo()->mcChannelNumber())))
      { kf = getKFactor(); }

      if (config()->isDefined(TString::Format("GeneratorEfficiency.%d", eventInfo()->mcChannelNumber())))
      { ge = getGeneratorEfficiency(); }

      eventHandler()->storeVar<float>("crossSectionBRfilterEff", xs * kf * ge);
    } else {
      eventHandler()->storeVar<float>("crossSectionBRfilterEff", -1);
    }
  }

  writePhotonAllSysVars();
}

void HGamCutflowAndMxAOD::writePhotonAllSysVars(bool truth)
{
  var::m_yy.addToStore(truth);

  var::N_j.addToStore(truth);
  var::Dphi_y_y.addToStore(truth);

  var::pT_y1.addToStore(truth);
  var::pT_y2.addToStore(truth);

  // Fiducial regions
  var::catXS_VBF.addToStore(truth);
  var::N_lep_15.addToStore(truth);

  // Differential variables
  var::pT_yy.addToStore(truth);
  var::yAbs_yy.addToStore(truth);
  var::cosTS_yy.addToStore(truth);
  var::pTt_yy.addToStore(truth);
  var::Dy_y_y.addToStore(truth);

  var::N_j_30.addToStore(truth);
  var::N_j_50.addToStore(truth);
  var::pT_j1_30.addToStore(truth);
  var::pT_j2_30.addToStore(truth);
  var::pT_j3_30.addToStore(truth);
  var::yAbs_j1_30.addToStore(truth);
  var::yAbs_j2_30.addToStore(truth);
  var::HT_30.addToStore(truth);
  var::HTall_30.addToStore(truth);
  var::m_jj_30.addToStore(truth);
  var::Dy_j_j_30.addToStore(truth);
  var::Dphi_j_j_30.addToStore(truth);
  var::Dphi_j_j_30_signed.addToStore(truth);

  var::sumTau_yyj_30.addToStore(truth);
  var::maxTau_yyj_30.addToStore(truth);
  var::pT_yyj_30.addToStore(truth);
  var::pT_yyjj_30.addToStore(truth);
  var::pT_yyjj_50.addToStore(truth);
  var::Dy_yy_jj_30.addToStore(truth);
  var::Dphi_yy_jj_30.addToStore(truth);
  var::Dphi_yy_jj_50.addToStore(truth);
  var::m_yyj.addToStore(truth);
  var::m_yyj_30.addToStore(truth);

  if (!truth) {
    var::weightN_lep_15.addToStore(truth);
    var::met_TST.addToStore(truth);
    //var::met_Sig.addToStore(truth);
  }
}

void HGamCutflowAndMxAOD::writeNominalAndSystematic(bool isSys)
{
  // Basic event selection flags
  var::isPassedBasic.setValue(m_goodFakeComb ? true : eventHandler()->pass());
  var::isPassed.setValue(m_goodFakeComb ? true : var::isPassedBasic() && pass(&m_selPhotons, &m_selElectrons, &m_selMuons, &m_selJets));
  var::cutFlow.setValue(m_cutFlow);

  if (HG::isMC()) {
    var::isDalitzEvent.setValue(m_isDalitz);

    // Basic event weights
    eventHandler()->pileupWeight();
    eventHandler()->vertexWeight();

  }

  if (m_cutFlow > VERTEX) { passJetEventCleaning(); }

  // Define the signal jets from the no-jvt cut collection
  // Jets with pT > 30/50 GeV are used for pT_j1_30, N_j_50, etc.
  xAOD::JetContainer jvtJets30(SG::VIEW_ELEMENTS), jvtJets50(SG::VIEW_ELEMENTS);

  for (auto jet : m_jvtJets) {
    if (jet->pt() < 30.0 * HG::GeV)
    { continue; }

    jvtJets30.push_back(jet);

    if (jet->pt() < 50.0 * HG::GeV)
    { continue; }

    jvtJets50.push_back(jet);
  }

  eventHandler()->storeVar<float>("weightJvt", HG::JetHandler::multiplyJvtWeights(&m_jvtJets));
  eventHandler()->storeVar<float>("weightJvt_30", HG::JetHandler::multiplyJvtWeights(&jvtJets30));
  eventHandler()->storeVar<float>("weightJvt_50", HG::JetHandler::multiplyJvtWeights(&jvtJets50));

  eventHandler()->storeVar<float>("weightFJvt", HG::JetHandler::multiplyFJvtWeights(&m_jvtJets));
  eventHandler()->storeVar<float>("weightFJvt_30", HG::JetHandler::multiplyFJvtWeights(&jvtJets30));

  // Default b-jet information for people outside the framework
  xAOD::JetContainer bjets = jetHandler()->applyBJetSelection(m_selJets);
  eventHandler()->storeVar<int>("N_j_btag", bjets.size());

  xAOD::JetContainer jets30(SG::VIEW_ELEMENTS);
  double weightBJet30 = 1.0;
  static SG::AuxElement::ConstAccessor<float> SF_bjet("SF_DL1r_FixedCutBEff_70");

  for (auto jet : m_selJets) {
    if (jet->pt() < 30.0 * HG::GeV) { continue; }

    jets30.push_back(jet);
    weightBJet30 *= SF_bjet(*jet);
  }

  xAOD::JetContainer bjets30 = jetHandler()->applyBJetSelection(jets30);
  int nbjet30 = bjets30.size();

  eventHandler()->storeVar<int>("N_j_btag30", nbjet30);

  char xsec_ttHsemi = var::N_lep_15() >= 1 && var::N_j_30() >= 3 && nbjet30 >= 1;
  char xsec_ttHhad = var::N_lep_15() == 0 && var::N_j_30() >= 4 && nbjet30 >= 1;
  eventHandler()->storeVar<char>("catXS_ttH", xsec_ttHsemi || xsec_ttHhad);
  eventHandler()->storeVar<float>("weightCatXS_ttH", weightBJet30 * var::weightN_lep_15() * eventHandler()->getVar<float>("weightJvt_30"));

  int xs_nbjet = -99;

  if (var::N_j_central30() == 0 || var::N_lep() > 0)
  { xs_nbjet = 0; }
  else if (nbjet30 == 0)
  { xs_nbjet = 1; }
  else if (nbjet30 == 1)
  { xs_nbjet = 2; }
  else
  { xs_nbjet = 3; }

  int xs_HiggsHF = -99;
  xAOD::MuonContainer muonsPassing(SG::VIEW_ELEMENTS);
  // Apply muon requirements
  std::copy_if(m_selMuons.begin(), m_selMuons.end(), std::back_inserter(muonsPassing), [this](const xAOD::Muon * muon) {
    return (muon->pt() >= 10.0 * HG::GeV);
  });

  xAOD::ElectronContainer electronsPassing(SG::VIEW_ELEMENTS);
  // Apply electron requirements
  std::copy_if(m_selElectrons.begin(), m_selElectrons.end(), std::back_inserter(electronsPassing), [this](const xAOD::Electron * electron) {
    return (electron->pt() >= 10.0 * HG::GeV);
  });

  if (var::N_j_central30() > 0 && var::N_j_central30() < 4 && (muonsPassing.size() == 0) && (electronsPassing.size() == 0)) {
    xAOD::JetContainer jets_central(SG::VIEW_ELEMENTS);
    std::copy_if(m_selJets.begin(), m_selJets.end(), std::back_inserter(jets_central), [this](const xAOD::Jet * j) {
      return fabs(j->eta()) <= 2.5;
    });

    xAOD::JetContainer jets_central30(SG::VIEW_ELEMENTS);
    std::copy_if(jets_central.begin(), jets_central.end(), std::back_inserter(jets_central30), [this](const xAOD::Jet * j) {
      return (j->pt() >= 30 * HG::GeV);
    });

    xAOD::JetContainer sortedJets(SG::VIEW_ELEMENTS);

    for (auto jet : jets_central30) { sortedJets.push_back(jet); }

    // first sort jets by pT then do a stable sort by DL1r discriminant
    std::sort(sortedJets.begin(), sortedJets.end(), [](const xAOD::Jet * i, const xAOD::Jet * j) {
      return i->pt() > j->pt();
    });

    std::stable_sort(sortedJets.begin(), sortedJets.end(), [](const xAOD::Jet * i, const xAOD::Jet * j) {
      return i->auxdata<double>("DL1r_discriminant") > j->auxdata<double>("DL1r_discriminant");
    });

    if (sortedJets.size() > 0) {
      if (sortedJets[0]->auxdata<char>("DL1r_FixedCutBEff_60") || sortedJets[0]->auxdata<char>("DL1r_FixedCutBEff_70")) { xs_HiggsHF = 2; }
      else if (sortedJets[0]->auxdata<char>("DL1r_FixedCutBEff_77")) { xs_HiggsHF = 1; }
      else { xs_HiggsHF = 0; }
    }
  }

  eventHandler()->storeVar<char>("catXS_HiggsHF", xs_HiggsHF);
  eventHandler()->storeVar<float>("weightCatXS_HiggsHF", weightBJet30 * var::weightN_lep() * eventHandler()->getVar<float>("weightJvt_30"));

  eventHandler()->storeVar<char>("catXS_nbjet", xs_nbjet);
  eventHandler()->storeVar<float>("weightCatXS_nbjet", weightBJet30 * var::weightN_lep() * eventHandler()->getVar<float>("weightJvt_30"));

  //Fake photon weight to be included into final weight. If we have it enabled.
  if (m_goodFakeComb)
  { var::weight.setValue(weight()*eventHandler()->getVar<float>("weightFakePhotons")); }

  if (!isSys) {
    // Make sure every trigger is checked, and decorated to EventInfo
    eventHandler()->getPassedTriggers();
  }

  // Additional variables useful for non-framework analysis
  int Nloose = m_preSelPhotons.size();
  eventHandler()->storeVar<float>("m_yy_resolution", diphotonMassResolution(m_selPhotons));
  eventHandler()->storeVar<int>("NLoosePhotons", Nloose);
  eventHandler()->storeVar<float>("met_hardVertexTST", m_selMET["hardVertexTST"] ? m_selMET["hardVertexTST"]->met() : m_selMET["TST"]->met());
  eventHandler()->storeVar<float>("sumet_hardVertexTST", m_selMET["hardVertexTST"] ? m_selMET["hardVertexTST"]->sumet() : m_selMET["TST"]->sumet());
  eventHandler()->storeVar<float>("phi_hardVertexTST", m_selMET["hardVertexTST"] ? m_selMET["hardVertexTST"]->phi() : m_selMET["TST"]->phi());
  //eventHandler()->storeVar<float>("met_Sig_hardVertexTST", m_selMET["hardVertexmetSig"] ? m_selMET["hardVertexmetSig"]->met() : m_selMET["metSig"]->met());

  // High mass variables
  bool passPID = false, passIsoLoose = false, passPtLow = false, passIsoTight = false, passRelPtHighMyy = false;
  float weightLowHighMyy = 1.0;
  int convCat = -1;

  static SG::AuxElement::ConstAccessor<float> trigSF_2g20("SF_HLT_g20_tight_icalovloose_L1EM15VHI");

  if (Nloose >= 2) {
    xAOD::Photon *y1 = m_preSelPhotons[0], *y2 = m_preSelPhotons[1];

    passPID = m_goodFakeComb ? true : photonHandler()->passPIDCut(y1) && photonHandler()->passPIDCut(y2);
    passIsoLoose = photonHandler()->passIsoCut(y1, HG::Iso::FixedCutLoose) &&
                   photonHandler()->passIsoCut(y2, HG::Iso::FixedCutLoose);
    passPtLow = y1->pt() >= 22.0 * HG::GeV && y2->pt() >= 22.0 * HG::GeV;

    passIsoTight = photonHandler()->passIsoCut(y1, HG::Iso::FixedCutTight) &&
                   photonHandler()->passIsoCut(y2, HG::Iso::FixedCutTight);

    double myy = (y1->p4() + y2->p4()).M();
    passRelPtHighMyy = y1->pt() / myy >= 0.3 && y2->pt() / myy >= 0.25;

    if (y1->conversionType() == 0 && y2->conversionType() == 0) {
      convCat = 0; // UU
    } else if (y1->conversionType() != 0 && y2->conversionType() != 0) {
      convCat = 2; // CC
    } else {
      convCat = 1; // UC and CU
    }

    weightLowHighMyy *= trigSF_2g20(*y1) * trigSF_2g20(*y2);
  }

  bool passTrigMatch_2g20 = (eventHandler()->passTrigger("HLT_2g20_tight") && passTriggerMatch("HLT_2g20_tight", &m_preSelPhotons))
                            || (eventHandler()->passTrigger("HLT_2g22_tight") && passTriggerMatch("HLT_2g22_tight", &m_preSelPhotons))
                            || (eventHandler()->passTrigger("HLT_2g20_tight_icalovloose_L12EM15VHI") /*&& passTriggerMatch("HLT_2g20_tight_icalovloose_L12EM15VHI", &m_preSelPhotons)*/);

  if (!eventHandler()->passTrigger("HLT_2g20_tight_icalovloose_L12EM15VHI") /*|| passTriggerMatch("HLT_2g20_tight_icalovloose_L12EM15VHI", &m_preSelPhotons)*/)
  { weightLowHighMyy = 1.0; }

  // Spin-0 selection
  eventHandler()->storeVar<char>("isPassedTrigMatchLowHighMyy", passTrigMatch_2g20);
  eventHandler()->storeVar<char>("isPassedIsolationLowMyy", passIsoLoose);
  eventHandler()->storeVar<char>("isPassedIsolationHighMyy", passIsoTight);
  eventHandler()->storeVar<char>("isPassedPtCutsLowHighMyy", passPtLow);
  eventHandler()->storeVar<char>("isPassedLowMyy", var::isPassedBasic() && Nloose >= 2 && passTrigMatch_2g20 && passPID && passIsoLoose && passPtLow);
  eventHandler()->storeVar<char>("isPassedHighMyy", var::isPassedBasic() && Nloose >= 2 && passPID && passIsoTight && passRelPtHighMyy);
  eventHandler()->storeVar<int>("catLowHighMyy_conv", convCat);
  eventHandler()->storeVar<float>("weightLowHighMyy", weightLowHighMyy);

  writeNominalAndSystematicVars();
}

void HGamCutflowAndMxAOD::writeNominalAndSystematicVars(bool truth)
{
  var::m_yy.addToStore(truth);

  // Fiducial regions
  var::catXS_VBF.addToStore(truth);
  var::N_lep_15.addToStore(truth);

  // Differential variables
  var::pT_y1.addToStore(truth);
  var::pT_y2.addToStore(truth);
  var::pT_yy.addToStore(truth);
  var::yAbs_yy.addToStore(truth);
  var::cosTS_yy.addToStore(truth);
  var::pTt_yy.addToStore(truth);
  var::Dy_y_y.addToStore(truth);

  var::N_j_30.addToStore(truth);
  var::N_j_50.addToStore(truth);
  var::pT_j1_30.addToStore(truth);
  var::pT_j2_30.addToStore(truth);
  var::pT_j3_30.addToStore(truth);
  var::yAbs_j1_30.addToStore(truth);
  var::yAbs_j2_30.addToStore(truth);
  var::HT_30.addToStore(truth);
  var::HTall_30.addToStore(truth);
  var::m_jj_30.addToStore(truth);
  var::m_jj_50.addToStore(truth);
  var::Dy_j_j_30.addToStore(truth);
  var::Dphi_j_j_30.addToStore(truth);
  var::Dphi_j_j_30_signed.addToStore(truth);
  var::Dphi_j_j_50.addToStore(truth);
  var::Dphi_j_j_50_signed.addToStore(truth);

  var::sumTau_yyj_30.addToStore(truth);
  var::maxTau_yyj_30.addToStore(truth);
  var::pT_yyj_30.addToStore(truth);
  var::pT_yyjj_30.addToStore(truth);
  var::pT_yyjj_50.addToStore(truth);
  var::Dy_yy_jj_30.addToStore(truth);
  var::Dphi_yy_jj_30.addToStore(truth);
  var::Dphi_yy_jj_50.addToStore(truth);
  var::m_yyj.addToStore(truth);
  var::m_yyj_30.addToStore(truth);
  var::Zepp.addToStore(truth);

  var::pT_hard.addToStore(truth);
  var::N_mu   .addToStore(truth);
  var::N_e    .addToStore(truth);

  if (!truth) {
    var::weightN_lep_15.addToStore(truth);
    var::met_TST  .addToStore(truth);
    //var::met_Sig  .addToStore(truth);
    var::sumet_TST.addToStore(truth);
    var::phi_TST  .addToStore(truth);
  }
}


void HGamCutflowAndMxAOD::writeNominalOnly()
{
  eventHandler()->mu();
  eventHandler()->runNumber();

  // Additional cut flow granularity
  int Nloose = m_preSelPhotons.size();
  bool passTrigMatch = passTriggerMatch(&m_preSelPhotons);
  bool passIso = false, passPID = false;

  if (Nloose >= 2) {
    xAOD::Photon *y1 = m_preSelPhotons[0], *y2 = m_preSelPhotons[1];
    passIso = m_goodFakeComb ? true : photonHandler()->passIsoCut(y1) && photonHandler()->passIsoCut(y2);
    passPID = m_goodFakeComb ? true : photonHandler()->passPIDCut(y1) && photonHandler()->passPIDCut(y2);
  }

  eventHandler()->storeVar<char>("isPassedPreselection", Nloose >= 2);
  eventHandler()->storeVar<char>("isPassedTriggerMatch", passTrigMatch);
  eventHandler()->storeVar<char>("isPassedPID", passPID);
  eventHandler()->storeVar<char>("isPassedIsolation", passIso);
  eventHandler()->storeVar<char>("isPassedRelPtCuts", passRelativePtCuts(m_preSelPhotons));
  eventHandler()->storeVar<char>("isPassedMassCut", passMyyWindowCut(m_preSelPhotons));

  // Masses with different PV definitions
  const CP::PhotonPointingTool *pointingTool = photonHandler()->getPointingTool();

  if (pointingTool) {
    if (m_cutFlow > AMBIGUITY) {
      xAOD::PhotonContainer leadPhotons = m_preSelPhotons;
      leadPhotons.resize(2);

      // Store m_yy using hardest vertex
      eventHandler()->storeVar<float>("m_yy_hardestVertex",  pointingTool->getCorrectedMass(leadPhotons, eventHandler()->hardestVertexZ()));

      if (HG::isMC())
      { eventHandler()->storeVar<float>("m_yy_truthVertex", pointingTool->getCorrectedMass(leadPhotons, truthHandler()->vertexZ())); }

      // Store m_yy using zCommon
      eventHandler()->storeVar<float>("m_yy_zCommon",  pointingTool->getCorrectedMass(leadPhotons, xAOD::PVHelpers::getZCommonAndError(eventInfo(), &leadPhotons).first));
      var::zCommon.setValue(xAOD::PVHelpers::getZCommonAndError(eventInfo(), &leadPhotons).first);
    } else {
      eventHandler()->storeVar<float>("m_yy_hardestVertex", -99);

      if (HG::isMC())
      { eventHandler()->storeVar<float>("m_yy_truthVertex", -99); }

      eventHandler()->storeVar<float>("m_yy_zCommon", -99);
    }
  }

  // Vertex information
  eventHandler()->numberOfPrimaryVertices();
  eventHandler()->selectedVertexZ();
  eventHandler()->selectedVertexPhi();
  eventHandler()->selectedVertexSumPt2();
  eventHandler()->hardestVertexZ();
  eventHandler()->hardestVertexPhi();
  eventHandler()->hardestVertexSumPt2();
  eventHandler()->pileupVertexSumPt2(); // also sets pileupVertexZ internally

  if (HG::isMC()) { truthHandler()->vertexZ(); }

  const xAOD::VertexContainer *vertices = nullptr;

  if (event()->contains<xAOD::VertexContainer>("HggPrimaryVertices")) {
    if (event()->retrieve(vertices, "HggPrimaryVertices").isFailure())
    { HG::fatal("Error retrieving PrimaryVertices, exiting"); }

    std::vector<float> verticesZ;
    std::vector<float> verticesScore;
    static SG::AuxElement::ConstAccessor<float> vertexScore("vertexScore");

    if (vertices->size() == 1) {
      // DxAODs in p2669 have issues with only dummy vertex and vertex score decoration
      verticesZ.push_back(-999);
      verticesScore.push_back(-99);
    } else {
      for (auto vertex : *vertices) {
        verticesZ.push_back(vertex->z());
        verticesScore.push_back(vertexScore(*vertex));
      }
    }

    eventHandler()->storeVar<std::vector<float> >("HggPrimaryVerticesZ", verticesZ);
    eventHandler()->storeVar<std::vector<float> >("HggPrimaryVerticesScore", verticesScore);
  }

  // Bunch train information
  eventHandler()->bunchDistanceFromFront();
  eventHandler()->bunchGapBeforeTrain();

  // Add MC only variables
  if (HG::isMC()) {
    truthHandler()->catCoup();
    truthHandler()->isVyyOverlap();

    if (config()->isDefined(TString::Format("CrossSection.%d", eventInfo()->mcChannelNumber()))) {
      double xs = getCrossSection(), kf = 1.0, ge = 1.0;

      if (config()->isDefined(TString::Format("kFactor.%d", eventInfo()->mcChannelNumber())))
      { kf = getKFactor(); }

      if (config()->isDefined(TString::Format("GeneratorEfficiency.%d", eventInfo()->mcChannelNumber())))
      { ge = getGeneratorEfficiency(); }

      eventHandler()->storeVar<float>("crossSectionBRfilterEff", xs * kf * ge);
    } else {
      eventHandler()->storeVar<float>("crossSectionBRfilterEff", -1);
    }
  }

  writeNominalOnlyVars();

}

void HGamCutflowAndMxAOD::writeNominalOnlyVars(bool truth)
{
  // Truth and reco vars
  var::passMeyCut   .addToStore(truth);
  var::pT_y1        .addToStore(truth);
  var::pT_y2        .addToStore(truth);
  var::E_y1         .addToStore(truth);
  var::E_y2         .addToStore(truth);
  var::phiStar_yy   .addToStore(truth);
  var::DR_y_y       .addToStore(truth);

  var::massTrans    .addToStore(truth);
  var::pTlepMET     .addToStore(truth);

  var::N_j          .addToStore(truth);
  var::N_j_central  .addToStore(truth);
  var::N_j_central30.addToStore(truth);
  var::pT_j1        .addToStore(truth);
  var::pT_j2        .addToStore(truth);
  var::pT_jj        .addToStore(truth);
  var::m_jj         .addToStore(truth);
  var::Dy_j_j       .addToStore(truth);
  var::Dphi_j_j     .addToStore(truth);

  var::Dphi_yy_jj   .addToStore(truth);
  var::DRmin_y_j    .addToStore(truth);
  var::cosTS_yyjj   .addToStore(truth);

  var::N_e          .addToStore(truth);
  var::N_mu         .addToStore(truth);
  var::N_lep        .addToStore(truth);
  var::m_ee         .addToStore(truth);
  var::m_mumu       .addToStore(truth);
  var::pt_llmax     .addToStore(truth);

  if (not truth) {
    var::Deta_j_j     .addToStore(truth);
    var::DRmin_y_j_2  .addToStore(truth);
    var::m_alljet     .addToStore(truth);
    var::m_alljet_30  .addToStore(truth);
    var::Dy_yy_jj     .addToStore(truth);
  }

}

void HGamCutflowAndMxAOD::writeDetailed()
{
  // Just calling these adds the variables to the TStore
  eventHandler()->centralEventShapeDensity();
  eventHandler()->forwardEventShapeDensity();

  writeDetailedVars();
}

void HGamCutflowAndMxAOD::writeDetailedVars(bool truth)
{
  var::Dphi_y_y     .addToStore(truth);
  var::yAbs_j1      .addToStore(truth);
  var::yAbs_j2      .addToStore(truth);
  var::Dy_yy_jj     .addToStore(truth);
  var::m_yyjj       .addToStore(truth);

}

EL::StatusCode  HGamCutflowAndMxAOD::doTruth()
{
  // Truth particles
  xAOD::TruthParticleContainer all_photons   = truthHandler()->getPhotons();
  xAOD::TruthParticleContainer all_electrons = truthHandler()->getElectrons();
  xAOD::TruthParticleContainer all_dms       = truthHandler()->getDM();
  xAOD::TruthParticleContainer all_muons     = truthHandler()->getMuons();
  xAOD::TruthParticleContainer all_taus      = truthHandler()->getTaus();
  xAOD::JetContainer           all_jets      = truthHandler()->getJets();
  xAOD::MissingETContainer     all_met       = truthHandler()->getMissingET();
  xAOD::TruthParticleContainer all_higgs     = truthHandler()->getHiggsBosons();

  // Apply fiducial selections to all containers
  xAOD::TruthParticleContainer photons   = truthHandler()->applyPhotonSelection(all_photons);
  xAOD::TruthParticleContainer electrons = truthHandler()->applyElectronSelection(all_electrons);
  xAOD::TruthParticleContainer muons     = truthHandler()->applyMuonSelection(all_muons);
  xAOD::TruthParticleContainer taus      = truthHandler()->applyTauSelection(all_taus);
  xAOD::JetContainer           jets      = truthHandler()->applyJetSelection(all_jets);
  xAOD::JetContainer           bjets     = truthHandler()->applyBJetSelection(jets);
  xAOD::JetContainer           cjets     = truthHandler()->applyCJetSelection(jets);
  xAOD::MissingETContainer     met       = truthHandler()->applyMissingETSelection(all_met);

  // remove truth jets that are from electrons or photons
  truthHandler()->removeOverlap(photons, jets, electrons, muons, taus);

  //decorate truth tau
  /*for (auto part : taus) {
    decorateVisP4(part);
  }*/

  // Save truth containers, if configured
  if (m_saveTruthObjects) {
    ANA_CHECK(truthHandler()->writePhotons(all_photons));
    ANA_CHECK(truthHandler()->writeElectrons(all_electrons));
    ANA_CHECK(truthHandler()->writeMuons(all_muons));
    ANA_CHECK(truthHandler()->writeTaus(all_taus));
    ANA_CHECK(truthHandler()->writeJets(all_jets));
    ANA_CHECK(truthHandler()->writeMissingET(met));
    ANA_CHECK(truthHandler()->writeHiggsBosons(all_higgs));
    ANA_CHECK(truthHandler()->writeTruthEvents());

    // Save truth particle and truth vertices
    if (doTruthPtclVtx) { truthHandler()->writeTruthParticlesAndVertices(); }

    addTruthLinks(m_photonContainerName.Data(), m_photonTruthContainerName.Data());
    addTruthLinks(m_elecContainerName.Data(), m_elecTruthContainerName.Data());
    addTruthLinks(m_tauContainerName.Data(), m_tauTruthContainerName.Data());
  }

  HG::VarHandler::getInstance()->setTruthContainers(&all_photons, &electrons, &muons, &taus, &jets, &met);
  HG::VarHandler::getInstance()->setHiggsBosons(&all_higgs);

  // Adds event-level variables to TStore (this time using truth containers)
  bool truth = true;

  if (m_saveTruthVars) {

    if (m_photonAllSys) {
      writePhotonAllSysVars(truth);
      ANA_CHECK(HG::VarHandler::getInstance()->writeTruth());
      return EL::StatusCode::SUCCESS;
    }

    writeNominalAndSystematicVars(truth);
    writeNominalOnlyVars(truth);

    if (m_saveDetailed)
    { writeDetailedVars(truth); }

    truthHandler()->passFiducial(&all_photons); // calls passFiducialKinOnly internally
    truthHandler()->centralEventShapeDensity();
    truthHandler()->forwardEventShapeDensity();


    var::pT_h1.addToStore(truth);
    var::pT_h2.addToStore(truth);
    var::y_h1.addToStore(truth);
    var::y_h2.addToStore(truth);
    var::m_h1.addToStore(truth);
    var::m_h2.addToStore(truth);
    var::m_hh.addToStore(truth);


    xAOD::JetContainer bjets30_y25(SG::VIEW_ELEMENTS);

    for (auto jet : bjets) {
      if (jet->pt() < 30.0 * HG::GeV) { continue; }

      if (fabs(jet->eta()) > 2.5) { continue; }

      bjets30_y25.push_back(jet);
    }

    eventHandler()->storeTruthVar<int>("N_j_btag30", bjets30_y25.size());

    char xsec_ttHsemi = var::N_lep_15.truth() >= 1 && var::N_j_30.truth() >= 3 && bjets30_y25.size() >= 1;
    char xsec_ttHhad = var::N_lep_15.truth() == 0 && var::N_j_30.truth() >= 4 && bjets30_y25.size() >= 1;
    eventHandler()->storeTruthVar<char>("catXS_ttH", xsec_ttHsemi || xsec_ttHhad);

    if (HGamHiggsHFTool()) { HGamHiggsHFTool()->saveHGamHiggsHFTruthInfo(all_photons, jets, bjets30_y25, cjets, muons, electrons); }

    // Decorate with yyHF information, if so desired
    if (yyHFTool()) { yyHFTool()->saveyyHFTruthInfo(all_photons, jets, bjets, cjets, met, muons, electrons); }

    if (GammaORTool()) { GammaORTool()->saveGammaORTruthInfo(all_photons, jets, bjets, cjets, met, muons, electrons); }


    // Decorate with H+C information, if so desired
    if (hcTool()) { hcTool()->saveHCTruthInfo(all_photons, jets, bjets, cjets, muons, electrons); }

    int xs_nbjet = -99;

    if (var::N_j_central30.truth() == 0 || var::N_lep.truth() > 0)
    { xs_nbjet = 0; }
    else if (bjets30_y25.size() == 0)
    { xs_nbjet = 1; }
    else if (bjets30_y25.size() == 1)
    { xs_nbjet = 2; }
    else
    { xs_nbjet = 3; }

    eventHandler()->storeTruthVar<char>("catXS_nbjet", xs_nbjet);

    eventHandler()->storeTruthVar<char>("catXS_nbjet", xs_nbjet);

    int xs_HiggsHF = -99;
    xAOD::TruthParticleContainer muonsPassing(SG::VIEW_ELEMENTS);
    // Apply muon requirements
    std::copy_if(muons.begin(), muons.end(), std::back_inserter(muonsPassing), [this](const xAOD::TruthParticle * muon) {
      return (muon->pt() >= 10.0 * HG::GeV);
    });

    xAOD::TruthParticleContainer electronsPassing(SG::VIEW_ELEMENTS);
    // Apply electron requirements
    std::copy_if(electrons.begin(), electrons.end(), std::back_inserter(electronsPassing), [this](const xAOD::TruthParticle * electron) {
      return (electron->pt() >= 10.0 * HG::GeV);
    });

    if ((muonsPassing.size() == 0) && (electronsPassing.size() == 0)) {

      int Njet_truth_central = 0;
      int n_bjets = 0;
      int n_cjets = 0;

      for (auto jet : jets) {
        if (fabs(jet->eta()) > 2.5  || jet->pt() * 0.001 < 30) {continue;}

        ++Njet_truth_central;

        if (jet->auxdata<int>("HadronConeExclTruthLabelID") == 5) {
          ++n_bjets;
        } else if (jet->auxdata<int>("HadronConeExclTruthLabelID") == 4) {
          ++n_cjets;
        }
      }

      if (Njet_truth_central > 0 && Njet_truth_central < 4) {
        if (n_bjets > 0) { xs_HiggsHF = 2; }
        else if (n_cjets > 0) { xs_HiggsHF = 1; }
        else { xs_HiggsHF = 0; }
      }
    }

    eventHandler()->storeTruthVar<char>("catXS_HiggsHF", xs_HiggsHF);


    double alldm_pt(0.);

    if (all_dms.size() == 2)  { alldm_pt = (all_dms[0]->p4() + all_dms[1]->p4()).Pt(); }

    eventHandler()->storeTruthVar<float>("alldm_pt", alldm_pt);

    eventHandler()->storeTruthVar<float>("met_NonInt", met["NonInt"]->met());   // MET from neutrinos
    eventHandler()->storeTruthVar<float>("sumet_Int", met["Int"   ]->sumet());    // SumET from hadrons, etc.
    eventHandler()->storeTruthVar<float>("met_NonHad", truthHandler()->getMissingET_NonHad());

    // High mass fiducial variables
    static SG::AuxElement::Accessor<float> etcone40("etcone40");
    static SG::AuxElement::Accessor<float> etcone20("etcone20");

    bool isFiducialLowMyy = false, isFiducialHighMyy = false;

    if (all_photons.size() > 1) {
      const xAOD::TruthParticle *gam1 = all_photons[0], *gam2 = all_photons[1];

      isFiducialLowMyy = isFiducialHighMyy = true;

      // Eta cut
      if (fabs(gam1->eta()) >= 2.37 || fabs(gam2->eta()) >= 2.37)
      { isFiducialLowMyy = isFiducialHighMyy = false; }

      // High-mass Isolation cut
      if (etcone40(*gam1) / (gam1->pt() + 120e3) >= 0.05 ||
          etcone40(*gam2) / (gam2->pt() + 120e3) >= 0.05)
      {  isFiducialHighMyy = false; }

      // Low-mass Isolation cut
      if (etcone20(*gam1) / (gam1->pt()) >= 0.065 ||
          etcone20(*gam2) / (gam2->pt()) >= 0.065)
      {  isFiducialLowMyy = false; }

      // Scalar relative pT cut
      if (gam1->pt() / var::m_yy.truth() < 0.3 || gam2->pt() / var::m_yy.truth() < 0.25)
      { isFiducialHighMyy = false; }

      // Low-mass pT cut
      if (gam1->pt() < 22.0 * HG::GeV || gam2->pt() < 22.0 * HG::GeV)
      { isFiducialLowMyy = false; }

    }

    eventHandler()->storeTruthVar<char>("isFiducialLowMyy", isFiducialLowMyy);
    eventHandler()->storeTruthVar<char>("isFiducialHighMyy", isFiducialHighMyy);

  }

  // Adds all event variables to the TEvent output stream
  ANA_CHECK(HG::VarHandler::getInstance()->writeTruth());

  return EL::StatusCode::SUCCESS;
}



TH1F *HGamCutflowAndMxAOD::makeCutFlowHisto(int id, TString suffix)
{
  int Ncuts = s_cutDescs.size();

  // create meaningful name of the cutflow histo
  TString name(Form("CutFlow_%s%d", HG::isData() ? "Run" : "MC", std::abs(id)));

  bool hasMCname = HG::isMC() && config()->isDefined(Form("SampleName.%d", std::abs(id)));

  if (hasMCname) {
    name = Form("CutFlow_%s", getMCSampleName(std::abs(id)).Data());
  }

  if (HG::isMC() && !hasMCname && config()->getStr("SampleName", "sample") != "sample")
  { name = "CutFlow_" + config()->getStr("SampleName"); }

  name += suffix;

  // maybe should make sure we don't switch directory?
  TDirectory *dir = gDirectory;
  TFile *file = wk()->getOutputFile("MxAOD");
  TH1F *h = new TH1F(name, name, Ncuts, 0, Ncuts);
  h->SetDirectory(file); // probably not needed

  for (int bin = 1; bin <= Ncuts; ++bin)
  { h->GetXaxis()->SetBinLabel(bin, s_cutDescs[bin - 1]); }

  dir->cd();
  return h;
}

void HGamCutflowAndMxAOD::fillCutFlow(CutEnum cut, double w)
{
  getCutFlowHisto()->Fill(cut);

  if (HG::isData()) { return; }

  getCutFlowWeightedHisto()->Fill(cut, w);

  if (m_isDalitz) { return; }

  getCutFlowHisto(false)->Fill(cut);
  getCutFlowWeightedHisto(false)->Fill(cut, w);
}


EL::StatusCode HGamCutflowAndMxAOD::finalize()
{
  printf("\nEvent selection cut flow:\n");
  printCutFlowHistos();

  // Write the output to file
  ANA_CHECK(HgammaAnalysis::finalize());

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode HGamCutflowAndMxAOD::fileExecute()
{
  ANA_CHECK(HgammaAnalysis::fileExecute());

  // Tell the code a new file has just been opened
  m_newFile = true;

  TTree *MetaData = dynamic_cast<TTree *>(wk()->inputFile()->Get("MetaData"));

  if (MetaData == nullptr)
  { HG::fatal("Couldn't find MetaData TTree in event, is this a proper xAOD file? Exiting."); }

  // The isDAOD flag set in HgammaAnalysis::changeInput is not available here, so we get it maually.
  bool tmp_isDAOD = false;

  for (auto branch : * MetaData->GetListOfBranches()) {
    if (TString(branch->GetName()).Contains("StreamDAOD")) {
      tmp_isDAOD = true;
      break;
    }
  }

  if (tmp_isDAOD) {
    // If we get here, this is a DxAOD

    // 1. Check if there if the incomplete book-keeper object has entreies (that would be bad!)
    const xAOD::CutBookkeeperContainer *incompleteCBC = nullptr;
    EL_CHECK("fileExecute()", wk()->xaodEvent()->retrieveMetaInput(incompleteCBC, "IncompleteCutBookkeepers"));

    if (incompleteCBC->size() != 0) {
      // fatal or error? let's start with a hard fatal!
      // HG::fatal("Issue with DxAOD book keeper. It's incomplete. File corrupted?");
      Warning("fileExecute()",
              "Issue with DxAOD book keeper. It's incomplete. File corrupted? %s %s",
              "If this is data, this is known to happen (but not understood).",
              "If this is MC, this is expected to happen, and can probably be ignored.");
    }

    // 2. now get the actual bookkeeper
    const xAOD::CutBookkeeperContainer *completeCBC = nullptr;
    EL_CHECK("fileExecute()", wk()->xaodEvent()->retrieveMetaInput(completeCBC, "CutBookkeepers"));

    int maxAcycle = -1, maxDcycle = -1;

    for (auto cbk : *completeCBC) {
      Info("fileExecute()", "  Book keeper name=%s, inputStream=%s, cycle=%d, nAcceptedEvents=%d", cbk->name().c_str(), cbk->inputStream().c_str(), cbk->cycle(), (int)cbk->nAcceptedEvents());

      if (cbk->name().empty()) { continue; }

      // Use the DxAOD numbers from the largest cycle
      if (TString(cbk->name()).Contains("HIGG1D1") && cbk->inputStream() == "StreamAOD" && cbk->cycle() > maxDcycle) {
        maxDcycle     = cbk->cycle();
        m_N_DxAOD     = cbk->nAcceptedEvents();
        m_sumw_DxAOD  = cbk->sumOfEventWeights();
        m_sumw2_DxAOD = cbk->sumOfEventWeightsSquared();
      }


      // Use the xAOD numbers from the largest cycle
      if (cbk->name() == "AllExecutedEvents" && cbk->inputStream() == "StreamAOD" && cbk->cycle() > maxAcycle) {
        maxAcycle    = cbk->cycle();
        m_N_xAOD     = cbk->nAcceptedEvents();
        m_sumw_xAOD  = cbk->sumOfEventWeights();
        m_sumw2_xAOD = cbk->sumOfEventWeightsSquared();
      }
    }

    Info("fileExecute()", "Book keeper anticipates %i events in current input file (%i in parent xAOD)", m_N_DxAOD, m_N_xAOD);
  }

  return EL::StatusCode::SUCCESS;
}

void HGamCutflowAndMxAOD::printCutFlowHistos()
{
  for (auto entry : m_cFlowHistos) {
    printf("\n%s %d cut-flow%s\n", HG::isMC() ? "MC sample" : "Data run",
           std::abs(entry.first), entry.first > 0 ? ", excluding Dalitz events" : "");
    printCutFlowHisto(entry.second, 0);
  }

  for (auto entry : m_cFlowHistosWeighted) {
    printf("\n%s %d cut-flow, weighted events%s\n", HG::isMC() ? "MC sample" : "Data run",
           std::abs(entry.first), entry.first > 0 ? ", excluding Dalitz events" : "");
    printCutFlowHisto(entry.second, 2);
  }

  printf("\n");
}

void HGamCutflowAndMxAOD::printCutFlowHisto(TH1F *h, int Ndecimals)
{
  TString format("  %-24s%10.");
  format += Ndecimals;
  format += "f%11.2f%%%11.2f%%\n";
  int all_bin = h->FindBin(ALLEVTS);
  printf("  %-24s%10s%12s%12s\n", "Event selection", "Nevents", "Cut rej.", "Tot. eff.");

  for (int bin = 1; bin <= h->GetNbinsX(); ++bin) {
    double ntot = h->GetBinContent(all_bin), n = h->GetBinContent(bin), nprev = h->GetBinContent(bin - 1);
    TString cutName(h->GetXaxis()->GetBinLabel(bin));
    cutName.ReplaceAll("#it{m}_{#gamma#gamma}", "m_yy");

    if (bin == 1 || nprev == 0 || n == nprev)
    { printf(format.Data(), cutName.Data(), n, -1e-10, n / ntot * 100); }
    else // if the cut does something, print more information
    { printf(format.Data(), cutName.Data(), n, (n - nprev) / nprev * 100, n / ntot * 100); }
  }
}
