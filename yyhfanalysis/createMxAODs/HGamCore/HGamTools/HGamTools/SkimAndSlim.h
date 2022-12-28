#ifndef HGamTools_SkimAndSlim_H
#define HGamTools_SkimAndSlim_H

#include <memory>

#include "HGamAnalysisFramework/HgammaAnalysis.h"

#include "AsgTools/AnaToolHandle.h"
#include "AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h"
#include "AsgAnalysisInterfaces/IPileupReweightingTool.h"



class SkimAndSlim : public HgammaAnalysis {
  // variables that don't get filled at submission time should be
  // protected from being sent from the submission node to the worker
  // node (done by the //!)
private:
  std::unique_ptr<xAOD::TEvent> m_outEvent; //!
  std::vector<std::string>      m_sysComps; //!
  std::vector<std::string>      m_contToSave; //!
  std::map<std::string, TH1 *>  m_cutflows; //!
  std::vector<int>              m_extraMCWeights; //!

  CP::SystematicSet            m_prwSysNom; //!
  CP::SystematicSet            m_prwSysUp; //!
  CP::SystematicSet            m_prwSysDown; //!

  bool m_applyGRL;
  asg::AnaToolHandle<IGoodRunsListSelectionTool> m_grlTool; //!

  bool m_removeDuplicates;
  std::map<unsigned int, std::set<unsigned int> > m_eventNumberSet; //!

  bool m_updatePRW;
  bool m_updateMu;
  double m_prwSF;
  asg::AnaToolHandle<CP::IPileupReweightingTool> m_prwTool; //!

  std::string m_cutFlowSkimName;
  int m_cutFlowSkimMin;



private:
  EL::StatusCode writeMetaData();
  EL::StatusCode addMCGenExtraWeights();
  EL::StatusCode updatePileupWeight(const std::string &name);
  EL::StatusCode updateMu(const std::string &name);

  template <class Container, class Object>
  EL::StatusCode
  recordContainer(std::string name);

  template <class T>
  EL::StatusCode
  recordInfo(std::string name);

  bool passGRL(const xAOD::EventInfo &eventInfo);
  bool passCutFlowSkim();
  bool isDuplicate(const xAOD::EventInfo &eventInfo);



public:
  // this is a standard constructor
  SkimAndSlim() { }
  SkimAndSlim(const char *name);
  virtual ~SkimAndSlim();

  // these are the functions inherited from HgammaAnalysis
  virtual EL::StatusCode fileExecute();
  virtual EL::StatusCode createOutput();
  virtual EL::StatusCode initialize();
  virtual EL::StatusCode execute();
  virtual EL::StatusCode finalize();

  // helper functions for user customization
  EL::StatusCode skipEvent(bool &skip);
  EL::StatusCode recordContainers();
  void           fillEvent();
  std::vector<std::string> getSystematicNames();
  std::vector<std::string> getContainersToSave();
 
  template <class Container>
  bool contains(const std::string &name);

  template <class Container>
  EL::StatusCode
  getContainer(Container *&cont, const std::string &name);

  template <class Container>
  EL::StatusCode
  getConstContainer(const Container *&cont, const std::string &name);

  // this is needed to distribute the algorithm to the workers
  ClassDef(SkimAndSlim, 1);
};

#include "HGamTools/SkimAndSlim.icc"

#endif // HGamTools_SkimAndSlim_H

