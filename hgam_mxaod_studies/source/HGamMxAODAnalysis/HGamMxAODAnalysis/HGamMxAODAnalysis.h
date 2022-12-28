#ifndef HGamMxAODAnalysis_MyxAODAnalysis_H
#define HGamMxAODAnalysis_MyxAODAnalysis_H
#include <EventLoop/Algorithm.h>

//#include "PATInterfaces/SystematicRegistry.h"
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
// #include <TH2F.h>
#include <TLorentzVector.h>
// #include <map>
// #include <iomanip>
#include <vector>
//mini-xAOD production
#include "EventLoop/OutputStream.h"
#include "xAODEventInfo/EventInfo.h"

/* #include "xAODTrigger/MuonRoIContainer.h" */

//Auxiliary container needed for deep copy
// #include "xAODTrigger/MuonRoIAuxContainer.h"

// //Truth
// #include "xAODTruth/TruthEventContainer.h"
// #include "xAODTruth/TruthParticleContainer.h"
// #include "xAODTruth/TruthVertexContainer.h"

// // Track Particle
// #include "xAODTracking/TrackParticleContainer.h"
// #include "xAODTracking/TrackParticleAuxContainer.h"

#include "xAODJet/JetContainer.h"
// #include "xAODTruth/TruthParticle.h"
// #include "xAODTracking/TrackParticle.h"

// namespace Trk {
//   class IResidualPullCalculator;
// }  

class HGamMxAODAnalysis : public EL::Algorithm
{


  // bool m_isMC; //!
  // bool truth_particle_baseline; //!

  // int m_eventNumber; //!
  // int m_runNumber; //!
  int m_mu; //!
  bool passed; //!
  float m_yy; //!
  // int m_lb; //!



  //Variables
  int m_eventCounter; //!
  int ptbins = 100; 
  int pt50min = 40; 
  int pt50max = 240;
  int pt30min = 20; 
  int pt30max = 220;
  int ybins = 100; 
  int ymin = 0; 
  int ymax = 5;

  // int ntopojetsperevent  = 0; //!
  // float leadingtopojetpt; //!
  // float leadingtopojetphi; //!
  // float leadingtopojeteta; //!
  // float leadingtopojetm; //!
  // float leadingtopojety; //!

  int npflow30jetsperevent  = 0; //!
  int npflow50jetsperevent  = 0; //!
  int npflow30jetsperevent_fJVT  = 0; //!
  int npflow50jetsperevent_fJVT  = 0; //!

  float leadingpflow50jetpt = 0; //!
  float leadingpflow50jeteta; //!
  float leadingpflow50jetphi; //!
  float leadingpflow50jetm; //!
  float leadingpflow50jety; //!

  float leadingpflow30jetpt = 0; //!
  float leadingpflow30jeteta; //!
  float leadingpflow30jetphi; //!
  float leadingpflow30jetm; //!
  float leadingpflow30jety; //!

  float leadingpflow30jetpt_fJVT; //!
  float leadingpflow30jeteta_fJVT; //!
  float leadingpflow30jetphi_fJVT; //!
  float leadingpflow30jetm_fJVT; //!
  float leadingpflow30jety_fJVT; //!

  float leadingpflow50jetpt_fJVT; //!
  float leadingpflow50jeteta_fJVT; //!
  float leadingpflow50jetphi_fJVT; //!
  float leadingpflow50jetm_fJVT; //!
  float leadingpflow50jety_fJVT; //!

  // TLorentzVector topoTLVec;  //!
  TLorentzVector pflow30TLVec_fJVT;  //!
  TLorentzVector pflow50TLVec_fJVT;  //!
  TLorentzVector pflow30TLVec;  //!
  TLorentzVector pflow50TLVec;  //!

  //Containers for global use
  const xAOD::EventInfo*              m_eventInfoCont; //!

  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
  public:
   std::string outputName; //!
   std::string outputxAODName; //!
   

   TTree* outputTree; //!

   bool isData;
   bool isMC;
   
   // int n_EventNumber; //!
   // int n_RunNumber;   //!

   float     pflow_fjvt_fail_eta;       //!
   float     pflow_fjvt_pass_eta;       //!

   float     pflow_j150_pt_15;     //! 
   float     pflow_j150_pt_1525;   //!
   float     pflow_j150_pt_2535;   //!
   float     pflow_j150_pt_3550;   //!
   float     pflow_j150_pt_50;     //!

   float     pflow_j150_pt_15_fJVT;     //! 
   float     pflow_j150_pt_1525_fJVT;   //!
   float     pflow_j150_pt_2535_fJVT;   //!
   float     pflow_j150_pt_3550_fJVT;   //!
   float     pflow_j150_pt_50_fJVT;     //!

   float     pflow_j150_pt_15_loweta;     //! 
   float     pflow_j150_pt_1525_loweta;   //!
   float     pflow_j150_pt_2535_loweta;   //!
   float     pflow_j150_pt_3550_loweta;   //!
   float     pflow_j150_pt_50_loweta;     //!

   float     pflow_j150_pt_15_higheta;     //! 
   float     pflow_j150_pt_1525_higheta;   //!
   float     pflow_j150_pt_2535_higheta;   //!
   float     pflow_j150_pt_3550_higheta;   //!
   float     pflow_j150_pt_50_higheta;     //!

   float     pflow_j150_pt_15_loweta_fJVT;     //! 
   float     pflow_j150_pt_1525_loweta_fJVT;   //!
   float     pflow_j150_pt_2535_loweta_fJVT;   //!
   float     pflow_j150_pt_3550_loweta_fJVT;   //!
   float     pflow_j150_pt_50_loweta_fJVT;     //!

   float     pflow_j150_pt_15_higheta_fJVT;     //! 
   float     pflow_j150_pt_1525_higheta_fJVT;   //!
   float     pflow_j150_pt_2535_higheta_fJVT;   //!
   float     pflow_j150_pt_3550_higheta_fJVT;   //!
   float     pflow_j150_pt_50_higheta_fJVT;     //!

   float     pflow_j150_y_15;     //! 
   float     pflow_j150_y_1525;   //!
   float     pflow_j150_y_2535;   //!
   float     pflow_j150_y_3550;   //!
   float     pflow_j150_y_50;     //!

   float     pflow_j150_y_15_fJVT;     //! 
   float     pflow_j150_y_1525_fJVT;   //!
   float     pflow_j150_y_2535_fJVT;   //!
   float     pflow_j150_y_3550_fJVT;   //!
   float     pflow_j150_y_50_fJVT;     //!

   float     pflow_j150_pt;     //!
   float     pflow_j150_eta;     //!
   float     pflow_j150_phi;     //!
   float     pflow_j150_m;     //!
   float     pflow_j150_y;     //!

   float     pflow_j150_pt_fJVT;     //!
   float     pflow_j150_eta_fJVT;     //!
   float     pflow_j150_phi_fJVT;     //!
   float     pflow_j150_m_fJVT;     //!
   float     pflow_j150_y_fJVT;     //!

   float     pflow_j130_pt_15_loweta;     //! 
   float     pflow_j130_pt_1525_loweta;   //!
   float     pflow_j130_pt_2535_loweta;   //!
   float     pflow_j130_pt_3550_loweta;   //!
   float     pflow_j130_pt_50_loweta;     //!

   float     pflow_j130_pt_15_higheta;     //! 
   float     pflow_j130_pt_1525_higheta;   //!
   float     pflow_j130_pt_2535_higheta;   //!
   float     pflow_j130_pt_3550_higheta;   //!
   float     pflow_j130_pt_50_higheta;     //!

   float     pflow_j130_pt_15_loweta_fJVT;     //! 
   float     pflow_j130_pt_1525_loweta_fJVT;   //!
   float     pflow_j130_pt_2535_loweta_fJVT;   //!
   float     pflow_j130_pt_3550_loweta_fJVT;   //!
   float     pflow_j130_pt_50_loweta_fJVT;     //!

   float     pflow_j130_pt_15_higheta_fJVT;     //! 
   float     pflow_j130_pt_1525_higheta_fJVT;   //!
   float     pflow_j130_pt_2535_higheta_fJVT;   //!
   float     pflow_j130_pt_3550_higheta_fJVT;   //!
   float     pflow_j130_pt_50_higheta_fJVT;     //!

   float     pflow_j130_y_15;     //! 
   float     pflow_j130_y_1525;   //!
   float     pflow_j130_y_2535;   //!
   float     pflow_j130_y_3550;   //!
   float     pflow_j130_y_50;     //!

   float     pflow_j130_pt_15;     //! 
   float     pflow_j130_pt_1525;   //!
   float     pflow_j130_pt_2535;   //!
   float     pflow_j130_pt_3550;   //!
   float     pflow_j130_pt_50;     //!

   float     pflow_j130_pt;     //!
   float     pflow_j130_eta;     //!
   float     pflow_j130_phi;     //!
   float     pflow_j130_m;     //!
   float     pflow_j130_y;     //!

   float     pflow_j130_y_15_fJVT;     //! 
   float     pflow_j130_y_1525_fJVT;   //!
   float     pflow_j130_y_2535_fJVT;   //!
   float     pflow_j130_y_3550_fJVT;   //!
   float     pflow_j130_y_50_fJVT;     //!

   float     pflow_j130_pt_15_fJVT;     //! 
   float     pflow_j130_pt_1525_fJVT;   //!
   float     pflow_j130_pt_2535_fJVT;   //!
   float     pflow_j130_pt_3550_fJVT;   //!
   float     pflow_j130_pt_50_fJVT;     //!

   float     pflow_j130_pt_fJVT;     //!
   float     pflow_j130_eta_fJVT;     //!
   float     pflow_j130_phi_fJVT;     //!
   float     pflow_j130_m_fJVT;     //!
   float     pflow_j130_y_fJVT;     //!

   TH1F *hist_j130_pt_015;      //!
   TH1F *hist_j130_pt_1525;      //!
   TH1F *hist_j130_pt_2535;      //!
   TH1F *hist_j130_pt_3550;      //!
   TH1F *hist_j130_pt_50;       //!

   TH1F *hist_j130_pt_015_loweta;      //!
   TH1F *hist_j130_pt_1525_loweta;      //!
   TH1F *hist_j130_pt_2535_loweta;      //!
   TH1F *hist_j130_pt_3550_loweta;      //!
   TH1F *hist_j130_pt_50_loweta;       //!
 
   TH1F *hist_j130_pt_015_higheta;      //!
   TH1F *hist_j130_pt_1525_higheta;      //!
   TH1F *hist_j130_pt_2535_higheta;      //!
   TH1F *hist_j130_pt_3550_higheta;      //!
   TH1F *hist_j130_pt_50_higheta;       //!
 
   TH1F *hist_j130_y_015;      //!
   TH1F *hist_j130_y_1525;      //!
   TH1F *hist_j130_y_2535;      //!
   TH1F *hist_j130_y_3550;      //!
   TH1F *hist_j130_y_50;      //! 

   TH1F *hist_j150_pt_015;      //!
   TH1F *hist_j150_pt_1525;      //!
   TH1F *hist_j150_pt_2535;      //!
   TH1F *hist_j150_pt_3550;      //!
   TH1F *hist_j150_pt_50;       //!

   TH1F *hist_j150_pt_015_loweta;      //!
   TH1F *hist_j150_pt_1525_loweta;      //!
   TH1F *hist_j150_pt_2535_loweta;     //!
   TH1F *hist_j150_pt_3550_loweta;      //!
   TH1F *hist_j150_pt_50_loweta;      //!

   TH1F *hist_j150_pt_015_higheta;      //!
   TH1F *hist_j150_pt_1525_higheta;      //!
   TH1F *hist_j150_pt_2535_higheta;      //!
   TH1F *hist_j150_pt_3550_higheta;      //!
   TH1F *hist_j150_pt_50_higheta;       //!

   TH1F *hist_j150_y_015;      //!
   TH1F *hist_j150_y_1525;      //!
   TH1F *hist_j150_y_2535;      //!
   TH1F *hist_j150_y_3550;      //!
   TH1F *hist_j150_y_50;     //!



   TH1F *hist_j130_pt_015_fJVT;      //!
   TH1F *hist_j130_pt_1525_fJVT;      //!
   TH1F *hist_j130_pt_2535_fJVT;      //!
   TH1F *hist_j130_pt_3550_fJVT;      //!
   TH1F *hist_j130_pt_50_fJVT;       //!

   TH1F *hist_j130_pt_015_loweta_fJVT;      //!
   TH1F *hist_j130_pt_1525_loweta_fJVT;      //!
   TH1F *hist_j130_pt_2535_loweta_fJVT;      //!
   TH1F *hist_j130_pt_3550_loweta_fJVT;      //!
   TH1F *hist_j130_pt_50_loweta_fJVT;       //!
 
   TH1F *hist_j130_pt_015_higheta_fJVT;      //!
   TH1F *hist_j130_pt_1525_higheta_fJVT;      //!
   TH1F *hist_j130_pt_2535_higheta_fJVT;      //!
   TH1F *hist_j130_pt_3550_higheta_fJVT;      //!
   TH1F *hist_j130_pt_50_higheta_fJVT;       //!
 
   TH1F *hist_j130_y_015_fJVT;      //!
   TH1F *hist_j130_y_1525_fJVT;      //!
   TH1F *hist_j130_y_2535_fJVT;      //!
   TH1F *hist_j130_y_3550_fJVT;      //!
   TH1F *hist_j130_y_50_fJVT;      //! 

   TH1F *hist_j150_pt_015_fJVT;      //!
   TH1F *hist_j150_pt_1525_fJVT;      //!
   TH1F *hist_j150_pt_2535_fJVT;      //!
   TH1F *hist_j150_pt_3550_fJVT;      //!
   TH1F *hist_j150_pt_50_fJVT;       //!

   TH1F *hist_j150_pt_015_loweta_fJVT;      //!
   TH1F *hist_j150_pt_1525_loweta_fJVT;      //!
   TH1F *hist_j150_pt_2535_loweta_fJVT;     //!
   TH1F *hist_j150_pt_3550_loweta_fJVT;      //!
   TH1F *hist_j150_pt_50_loweta_fJVT;      //!

   TH1F *hist_j150_pt_015_higheta_fJVT;      //!
   TH1F *hist_j150_pt_1525_higheta_fJVT;      //!
   TH1F *hist_j150_pt_2535_higheta_fJVT;      //!
   TH1F *hist_j150_pt_3550_higheta_fJVT;      //!
   TH1F *hist_j150_pt_50_higheta_fJVT;       //!

   TH1F *hist_j150_y_015_fJVT;      //!
   TH1F *hist_j150_y_1525_fJVT;      //!
   TH1F *hist_j150_y_2535_fJVT;      //!
   TH1F *hist_j150_y_3550_fJVT;      //!
   TH1F *hist_j150_y_50_fJVT;     //!

   TH1F *hist_pass_fJVT;     //!
   TH1F *hist_fail_fJVT;     //!

   TH1F *cutflow;      //!
   float sum_weights;      //!
   float lumi_mc16;      //!
   float eventweight;      //!




   
   TTree *tree; //!

   // this is a standard constructor
   HGamMxAODAnalysis ();

   // these are the functions inherited from Algorithm
   // tomoya add
   EL::StatusCode TrackSelection ();

   void ResetVariables();

void SetIsMC(bool mc_flag) {isMC = mc_flag;}
void SetIsData(bool data_flag) {isData = data_flag;}
  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();



  // this is needed to distribute the algorithm to the workers
  ClassDef(HGamMxAODAnalysis, 1);

  // private:

  // const AtlasDetectorID* m_idHelper;
  // const PixelID* m_pixelId;  
  // const SCT_ID* m_sctId;  
  // const InDetDD::SiDetectorManager*  m_PIX_mgr;
  // const InDetDD::SiDetectorManager*  m_SCT_mgr;
};

#endif
// 