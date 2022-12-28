#pragma once

// EDM include(s)
#ifndef __CINT__
  #include "EventLoop/Algorithm.h"
  #include "EventLoop/Worker.h"
  #include "xAODMetaDataCnv/FileMetaDataTool.h"
  #include "xAODTruthCnv/TruthMetaDataTool.h"
  #include "PhotonVertexSelection/PhotonVertexSelectionTool.h"
#endif

// ROOT include(s):
#include "TRegexp.h"

// Local include(s)
#include "HGamAnalysisFramework/Config.h"
#include "HGamAnalysisFramework/HistogramStore.h"
#ifndef __CINT__
  #include "HGamAnalysisFramework/ElectronHandler.h"
  #include "HGamAnalysisFramework/ETmissHandler.h"
  #include "HGamAnalysisFramework/EventHandler.h"
  #include "HGamAnalysisFramework/FCNCTool.h"
  #include "HGamAnalysisFramework/HGamCategoryTool.h"
  #include "HGamAnalysisFramework/HGamHiggsHFTool.h"
  #include "HGamAnalysisFramework/HGamMETCatTool.h"
  #include "HGamAnalysisFramework/HGamVLQTool.h"
  #include "HGamAnalysisFramework/HHyybbTool.h"
  #include "HGamAnalysisFramework/JetHandler.h"
  #include "HGamAnalysisFramework/TauHandler.h"
  #include "HGamAnalysisFramework/MuonHandler.h"
  #include "HGamAnalysisFramework/OverlapRemovalHandler.h"
  #include "HGamAnalysisFramework/PhotonHandler.h"
  #include "HGamAnalysisFramework/TruthHandler.h"
  #include "HGamAnalysisFramework/yyHFTool.h"
  #include "HGamAnalysisFramework/GammaORTool.h"
  #include "HGamAnalysisFramework/HcgamgamTool.h"
#endif

class HgammaAnalysis : public EL::Algorithm {
  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:

  // Init
  //  EL::StatusCode initTools();

  //! \brief event counter
  int m_eventCounter;//!
  //! \brief start time (used to calculate the processing rate)
  long m_startTime; //!

private:
  HG::Config m_config;

  xAOD::TEvent *m_event; //!
  xAOD::TStore *m_store; //!
  xAODMaker::FileMetaDataTool *m_metaDataTool; //!
  xAODMaker::TruthMetaDataTool *m_truthDataTool; //!
  //! \brief histogram store
  HistogramStore *m_histoStore; //!
  //! \brief configuration file
  std::vector<CP::SystematicSet> m_sysList; //!
  std::vector<TRegexp> m_uncComps; //!
  std::vector<TRegexp> m_ignoreUncComps; //!
  TString m_name;
#ifndef __CINT__
  CP::PhotonVertexSelectionTool *m_vertexTool; //!
  asg::AnaToolHandle<CP::IPhotonPointingTool> m_tpoint; //!
  HG::PhotonHandler *m_photonHandler; //!
  HG::ElectronHandler *m_electronHandler; //!
  HG::JetHandler *m_jetHandler; //!
  HG::JetHandler *m_jetHandlerPFlow; //!
  HG::TauHandler *m_tauHandler; //!
  HG::MuonHandler *m_muonHandler; //!
  HG::EventHandler *m_eventHandler; //!
  HG::TruthHandler *m_truthHandler; //!
  HG::OverlapRemovalHandler *m_overlapHandler; //!
  HG::ETmissHandler *m_etmissHandler; //!
  HG::ETmissHandler *m_etmissHandlerPFlow; //!
  HG::HGamCategoryTool *m_catTool; //!
  HG::HHyybbTool *m_yybbTool; //!
  HG::yyHFTool *m_yyHFTool; //!
  HG::GammaORTool *m_GammaORTool; //!
  HG::HGamVLQTool *m_HGamVLQTool; //!
  HG::HGamHiggsHFTool *m_HGamHiggsHFTool; //!
  HG::HGamMETCatTool *m_metCatTool; //!
  HG::FCNCTool *m_fcncTool; //!
  HG::HcgamgamTool *m_hcTool; //!
#endif // __CINT__
  bool   m_newFile;
  bool   m_isInit;
  bool   m_doPileupWeight;
  bool   m_doVertexWeight;
  bool   m_markPhotonCand;
  bool   m_doAnaTrig, m_doRelPtCut, m_doMyyCut;
  bool   m_doTwoGoodPhotonsCut;
  double m_relPtCut1;
  double m_relPtCut2;
  double m_myyLow, m_myyHigh;
  bool   m_doVertex;
  bool   m_doHardPV;
  bool   m_doJetClean;
  HG::StrV   m_anaTrigs;
  std::map<TString, int> m_trigYear;
  std::map<int, double>  m_crossSections, m_genEffs, m_kFactors, m_NevtsInitial;
  std::map<int, double>  m_skimmingEff, m_weightXsec, m_higgsMass, m_crossSectionBRfilterEff;
  std::map<int, TString> m_mcNames;
  std::map<int, int> m_nTotEvents;
  //Fake photons
  bool   m_useFakePhotons;
  TFile *m_PhotonFakeRateFile = 0;
  TH2F  *m_PhotonFakes2DHist = 0;

protected:
  virtual const std::vector<CP::SystematicSet> &getSystematics() { return m_sysList; }
  virtual bool isSystematicAvailable(const CP::SystematicSet &sys);
  virtual CP::SystematicCode applySystematicVariation(const CP::SystematicSet &sys);
  virtual void fillSystematicsList();

  // access to useful pointers
  inline virtual xAOD::TEvent      *event() { return m_event; }
  inline virtual xAOD::TStore      *store() { return m_store; }
  inline virtual const xAOD::EventInfo  *eventInfo();

  inline virtual HistogramStore      *histoStore()      { return m_histoStore; }
  inline virtual HG::Config          *config()          { return &m_config; }
  inline virtual HG::PhotonHandler   *photonHandler()   { return m_photonHandler; }
  inline virtual HG::ElectronHandler *electronHandler() { return m_electronHandler; }
  inline virtual HG::JetHandler      *jetHandler()      { return m_jetHandler; }
  inline virtual HG::JetHandler      *jetHandlerPFlow() { return m_jetHandlerPFlow; }
  inline virtual HG::TauHandler      *tauHandler()      { return m_tauHandler; }
  inline virtual HG::MuonHandler     *muonHandler()     { return m_muonHandler; }
  inline virtual HG::EventHandler    *eventHandler()    { return m_eventHandler; }
  inline virtual HG::TruthHandler    *truthHandler()    { return m_truthHandler; }
  inline virtual HG::OverlapRemovalHandler *overlapHandler() { return m_overlapHandler; }
  inline virtual HG::ETmissHandler   *etmissHandler()   { return m_etmissHandler; }
  inline virtual HG::ETmissHandler   *etmissHandlerPFlow() { return m_etmissHandlerPFlow; }
  inline virtual HG::HHyybbTool      *yybbTool()        { return m_yybbTool; }
  inline virtual HG::yyHFTool        *yyHFTool()        { return m_yyHFTool; }
  inline virtual HG::GammaORTool     *GammaORTool()     { return m_GammaORTool; }
  inline virtual HG::HGamVLQTool     *HGamVLQTool()     { return m_HGamVLQTool; }
  inline virtual HG::HGamHiggsHFTool *HGamHiggsHFTool() { return m_HGamHiggsHFTool; }
  inline virtual HG::HGamMETCatTool  *metCatTool()      { return m_metCatTool; }
  inline virtual HG::FCNCTool        *fcncTool()        { return m_fcncTool; }
  inline virtual HG::HGamCategoryTool *catTool()        { return m_catTool; }
  inline virtual HG::HcgamgamTool    *hcTool()          { return m_hcTool; }


  virtual void setWeightInitial();

  virtual double weight();
  virtual double weightInitial();
  inline virtual double weightFinal();

  TString getMCSampleName(int mcChannelNumber = -1);
  int getNtotalEvents(int mcChannelNumber = -1);
  TH1F *getCutFlowHistogram(int mcID, TString suffix = "");
  virtual double getCrossSection(int mcChannelNumber = -1);
  virtual double getGeneratorEfficiency(int mcChannelNumber = -1);
  virtual double getGeneratorHiggsMass(int mcChannelNumber = -1);
  virtual double getKFactor(int mcChannelNumber = -1);
  virtual double getIntialSumOfWeights(int mcChannelNumber = -1);
  virtual double getSumOfWeights(int mcChannelNumber = -1);
  virtual double crossSectionBRfilterEff(int mcChannelNumber = -1);

  /// \brief get intL * sigma / Ninitial
  double lumiXsecWeight(double intLumiPbInv = -1, int mcChannelNumber = -1, bool printFirst = true);

  virtual void selectVertex();

  void addTruthLinks(xAOD::IParticleContainer *recoCont, xAOD::TruthParticleContainer *truthCont);
  void addTruthLinks(std::string recoName, std::string truthName);

  //Fake Photon Functions
  xAOD::PhotonContainer getFakePhotons(double &photonFakeWeight);
  std::vector<std::pair<xAOD::PhotonContainer, double>> getPhotonCombinations(xAOD::PhotonContainer &realPhotons, xAOD::PhotonContainer &fakePhotons);
  std::pair<xAOD::PhotonContainer, double> chooseRandomComb(std::vector<std::pair<xAOD::PhotonContainer, double>> &fakeCombos);
  double getFPprob(xAOD::Photon *photon);

  virtual void setSelectedTruthObjects(const xAOD::TruthParticleContainer *photons   = nullptr,
                                       const xAOD::TruthParticleContainer *electrons = nullptr,
                                       const xAOD::TruthParticleContainer *muons     = nullptr,
                                       const xAOD::TruthParticleContainer *taus     = nullptr,
                                       const xAOD::JetContainer           *jets      = nullptr,
                                       const xAOD::MissingETContainer     *mets      = nullptr);

  virtual void setSelectedObjects(const xAOD::PhotonContainer    *photons   = nullptr,
                                  const xAOD::ElectronContainer  *electrons = nullptr,
                                  const xAOD::MuonContainer      *muons     = nullptr,
                                  const xAOD::TauJetContainer      *taus     = nullptr,
                                  const xAOD::JetContainer       *jets      = nullptr,
                                  const xAOD::MissingETContainer *met       = nullptr,
                                  const xAOD::JetContainer       *jetsNoJvt = nullptr);

  virtual bool pass(const xAOD::PhotonContainer *photons = nullptr,
                    const xAOD::ElectronContainer *electrons = nullptr,
                    const xAOD::MuonContainer *muons = nullptr,
                    const xAOD::JetContainer *jets = nullptr);

  virtual bool passTwoGoodPhotonsCut(const xAOD::PhotonContainer &photons);
  virtual bool passRelativePtCuts(const xAOD::PhotonContainer &photons);
  virtual bool passMyyWindowCut(const xAOD::PhotonContainer &photons);
  virtual bool passJetEventCleaning();
  virtual bool passCrackVetoCleaning(const xAOD::PhotonContainer &photons, const xAOD::ElectronContainer &electrons);
  virtual bool passTriggerMatch(const xAOD::PhotonContainer *photons,
                                const xAOD::ElectronContainer *electrons = nullptr,
                                const xAOD::MuonContainer *muons = nullptr,
                                const xAOD::JetContainer *jets = nullptr);
  virtual bool passTriggerMatch(const TString &trig,
                                const xAOD::PhotonContainer *photons,
                                const xAOD::ElectronContainer *electrons = nullptr,
                                const xAOD::MuonContainer *muons = nullptr,
                                const xAOD::JetContainer *jets = nullptr);

  inline bool isAOD();
  inline bool isDAOD();
  inline bool isMAOD();
  inline bool isMC();
  inline bool isData();

public:

  // this is a standard constructor/destructor
  HgammaAnalysis() : m_name() { }
  HgammaAnalysis(const char *name);
  virtual ~HgammaAnalysis() { }

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob(EL::Job &job);
  virtual EL::StatusCode fileExecute();
  virtual EL::StatusCode histInitialize();
  virtual EL::StatusCode changeInput(bool firstFile);
  virtual EL::StatusCode initialize();
  virtual EL::StatusCode execute();
  virtual EL::StatusCode postExecute();
  virtual EL::StatusCode finalize();
  virtual EL::StatusCode histFinalize();

  virtual EL::StatusCode createOutput();

  inline virtual void setConfig(const HG::Config &config);

  // this is needed to distribute the algorithm to the workers
  ClassDef(HgammaAnalysis, 1);
};

inline
void HgammaAnalysis::setConfig(const HG::Config &config)
{
  m_config = config;
}

inline
bool HgammaAnalysis::isAOD()
{
  HG::fatal("Error - HgammaAnalysis::isAOD() is depracated. Use HG::isAOD() instead.");
  return HG::isAOD();
}

inline
bool HgammaAnalysis::isDAOD()
{
  HG::fatal("Error - HgammaAnalysis::isDAOD() is depracated. Use HG::isDAOD() instead.");
  return HG::isDAOD();
}

inline
bool HgammaAnalysis::isMAOD()
{
  HG::fatal("Error - HgammaAnalysis::isMAOD() is depracated. Use HG::isMAOD() instead.");
  return HG::isMAOD();
}

inline
bool HgammaAnalysis::isMC()
{
  HG::fatal("Error - HgammaAnalysis::isMC() is depracated. Use HG::isMC() instead.");
  return HG::isMC();
}

inline
bool HgammaAnalysis::isData()
{
  HG::fatal("Error - HgammaAnalysis::isData() is depracated. Use HG::isData() instead.");
  return HG::isData();
}

inline double HgammaAnalysis::weightFinal() { return lumiXsecWeight() * weight(); }

inline
const xAOD::EventInfo *HgammaAnalysis::eventInfo()
{
  const xAOD::EventInfo *eventinfo = 0;

  if (wk()->xaodEvent()->retrieve(eventinfo, "EventInfo").isFailure()) {
    HG::fatal("Cannot access EventInfo");
  }

  return eventinfo;
}
