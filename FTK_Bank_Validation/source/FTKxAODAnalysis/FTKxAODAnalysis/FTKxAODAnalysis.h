#ifndef FTKxAODAnalysis_MyxAODAnalysis_H
#define FTKxAODAnalysis_MyxAODAnalysis_H
#include <EventLoop/Algorithm.h>

//#include "PATInterfaces/SystematicRegistry.h"
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2F.h>
#include <TLorentzVector.h>
#include <map>
#include <iomanip>
#include <vector>
//mini-xAOD production
#include "EventLoop/OutputStream.h"
#include "xAODEventInfo/EventInfo.h"

/* #include "xAODTrigger/MuonRoIContainer.h" */

//Auxiliary container needed for deep copy
#include "xAODTrigger/MuonRoIAuxContainer.h"

//Truth
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertexContainer.h"

// Track Particle
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/TrackParticleAuxContainer.h"

#include "xAODJet/JetContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTracking/TrackParticle.h"

namespace Trk {
  class IResidualPullCalculator;
}  

class FTKxAODAnalysis : public EL::Algorithm
{

  // void Fill_Clusters(const xAOD::TrackParticleContainer *trackCollection,std::vector<float> *x_residual,std::vector<float> *y_residual,std::vector<float> *x_loc,std::vector<float> *y_loc,std::vector<bool> *is_Pixel,std::vector<bool> *is_Barrel,std::vector<bool> *is_SCT,std::vector<int> *Layer,std::vector<int> *resAssociatedTrack,std::vector<int> *clustID);

  bool m_isMC; //!
  bool truth_particle_baseline; //!

  int m_eventNumber; //!
  int m_runNumber; //!
  int m_mu; //!
  int m_lb; //!

  int nTrack; //!

  int ntracks_before_selection; //!
  int ntracks_after_selection; //!
  int ntracks_ev; //!

  float track_selection_efficiency; //!

  // TH1* histocoordmasketa_ftk = new TH2F("histocoordmasketa_ftk", "Track probability of using a coordinate;Coordinate bit;#eta;Prob." ,25,0,25, 50, -2.5, 2.5);  //!
  // TH1* histocoordmaskphi_ftk = new TH2F("histocoordmaskphi_ftk", "Track probability of using a coordinate;Coordinate bit;#phi;Prob." ,25,0,25, 50, -3.2, 3.2);  //!
  // TH1* histocoordmaskz0_ftk  = new TH2F("histocoordmaskz0_ftk",  "Track probability of using a coordinate;Coordinate bit;#z0;Prob."  ,25,0,25, 50, -110, 110);  //!



  //Variables
  int m_eventCounter; //!

  //Containers for global use
  const xAOD::EventInfo*              m_eventInfoCont; //!

  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
  public:
   std::string outputName; //!
   std::string outputxAODName; //!
   
   float GeV; //!

   TTree* outputTree; //!

   bool isAOD; 
   bool isData; 
   float dRval;


   int n_EventNumber; //!
   int n_RunNumber;   //!

   float dx; //!
   float dy; //!

   int truth_track_n;                //!
   int reco_accepted_track_n;        //!
   int reco_inclusive_track_n;       //!

   int ftk_accepted_track_n;            //!
   int ftk_inclusive_track_n;           //!
   int ftk_refit_accepted_track_n;      //!
   int ftk_refit_inclusive_track_n;     //!

   int reco_ftkMatch_track_n;        //!
   int reco_ftkrefitMatch_track_n;   //!
   int truth_recoMatch_track_n;      //!
   int truth_ftkMatch_track_n;       //!
   int truth_ftkrefitMatch_track_n;  //!

   std::vector<Float_t>     truth_track_pt;       //!
   std::vector<Float_t>     truth_track_eta;      //!
   std::vector<Float_t>     truth_track_phi;      //!
   std::vector<Float_t>     truth_track_m;        //!
   std::vector<Float_t>     truth_track_theta;    //!
   std::vector<Float_t>     truth_track_d0;       //!
   std::vector<Float_t>     truth_track_z0;       //!
   std::vector<Float_t>     truth_track_z0st;     //!
   std::vector<Float_t>     truth_track_qop;      //!
   std::vector<Float_t>     truth_track_chi2ndof; //!
   std::vector<Float_t>     truth_track_charge;   //!
   std::vector<Float_t>     truth_track_prod_perp;            //!
   std::vector<Float_t>     truth_track_reco_match_prob;      //!
   std::vector<Float_t>     truth_track_ftk_match_prob;       //!
   std::vector<Float_t>     truth_track_ftk_refit_match_prob; //!
   std::vector<Int_t>       truth_track_reco_match;           //!
   std::vector<Float_t>     truth_track_ftk_match;            //!
   std::vector<Float_t>     truth_track_ftk_refit_match;      //!
   std::vector<Int_t>       truth_track_pdgid;                //!
   std::vector<Int_t>       truth_track_parent_pdgid;         //!
   std::vector<Int_t>       truth_track_status;               //!
   std::vector<Int_t>       truth_track_barcode;              //!

   // std::vector<Float_t>     muonRoI_eta;         //!
   // std::vector<Float_t>     muonRoI_phi;         //!
   // std::vector<Float_t>     muonRoI_roiWord;     //!
   // std::vector<Float_t>     muonRoI_thrValue;    //!

   std::vector<Float_t>     reco_accepted_track_pt;          //!
   std::vector<Float_t>     reco_accepted_track_eta;         //!
   std::vector<Float_t>     reco_accepted_track_eta_barrel;         //!
   std::vector<Float_t>     reco_accepted_track_eta_endcap;         //!
   std::vector<Float_t>     reco_accepted_track_phi;         //!
   std::vector<Float_t>     reco_accepted_track_m;           //!
   std::vector<Float_t>     reco_accepted_track_theta;       //!
   std::vector<Float_t>     reco_accepted_track_d0;          //!
   std::vector<Float_t>     reco_accepted_track_z0;          //!
   std::vector<Float_t>     reco_accepted_track_qop;         //!
   std::vector<Float_t>     reco_accepted_track_chi2ndof;    //!
   std::vector<Float_t>     reco_accepted_track_chi2;        //!
   std::vector<Float_t>     reco_accepted_track_charge;      //!
   std::vector<Float_t>     reco_accepted_track_hitPattern;  //!

   std::vector<Float_t>     reco_inclusive_track_pt;          //!
   std::vector<Float_t>     reco_inclusive_track_eta;         //!
   std::vector<Float_t>     reco_inclusive_track_phi;         //!
   std::vector<Float_t>     reco_inclusive_track_m;           //!
   std::vector<Float_t>     reco_inclusive_track_theta;       //!
   std::vector<Float_t>     reco_inclusive_track_d0;          //!
   std::vector<Float_t>     reco_inclusive_track_z0;          //!
   std::vector<Float_t>     reco_inclusive_track_qop;         //!
   std::vector<Float_t>     reco_inclusive_track_chi2ndof;    //!
   std::vector<Float_t>     reco_inclusive_track_chi2;        //!
   std::vector<Float_t>     reco_inclusive_track_charge;      //!
   std::vector<Float_t>     reco_inclusive_track_hitPattern;  //!


   std::vector<Float_t>     ftk_accepted_track_pt;            //!
   std::vector<Float_t>     ftk_accepted_track_eta;           //!
   std::vector<Float_t>     ftk_accepted_track_eta_barrel;           //!
   std::vector<Float_t>     ftk_accepted_track_eta_endcap;           //!
   std::vector<Float_t>     ftk_accepted_track_phi;           //!
   std::vector<Float_t>     ftk_accepted_track_m;             //!
   std::vector<Float_t>     ftk_accepted_track_theta;         //!
   std::vector<Float_t>     ftk_accepted_track_d0;            //!
   std::vector<Float_t>     ftk_accepted_track_corrected_d0;  //!
   std::vector<Float_t>     ftk_accepted_track_z0;            //!
   std::vector<Float_t>     ftk_accepted_track_qop;           //!
   std::vector<Float_t>     ftk_accepted_track_chi2ndof;      //!
   std::vector<Float_t>     ftk_accepted_track_chi2;          //!
   std::vector<Float_t>     ftk_accepted_track_charge;        //!
   std::vector<Float_t>     ftk_accepted_track_hitPattern;    //!

   std::vector<Float_t>     ftk_inclusive_track_pt;           //!
   std::vector<Float_t>     ftk_inclusive_track_eta;          //!
   std::vector<Float_t>     ftk_inclusive_track_phi;          //!
   std::vector<Float_t>     ftk_inclusive_track_m;            //!
   std::vector<Float_t>     ftk_inclusive_track_theta;        //!
   std::vector<Float_t>     ftk_inclusive_track_d0;           //!
   std::vector<Float_t>     ftk_inclusive_track_corrected_d0; //!
   std::vector<Float_t>     ftk_inclusive_track_z0;           //!
   std::vector<Float_t>     ftk_inclusive_track_qop;          //!
   std::vector<Float_t>     ftk_inclusive_track_chi2ndof;     //!
   std::vector<Float_t>     ftk_inclusive_track_chi2;         //!
   std::vector<Float_t>     ftk_inclusive_track_charge;       //!
   std::vector<Float_t>     ftk_inclusive_track_hitPattern;   //!


   std::vector<Float_t>     ftk_refit_accepted_track_pt;            //!
   std::vector<Float_t>     ftk_refit_accepted_track_eta;           //!
   std::vector<Float_t>     ftk_refit_accepted_track_eta_barrel;           //!
   std::vector<Float_t>     ftk_refit_accepted_track_eta_endcap;           //!
   std::vector<Float_t>     ftk_refit_accepted_track_phi;           //!
   std::vector<Float_t>     ftk_refit_accepted_track_m;             //!
   std::vector<Float_t>     ftk_refit_accepted_track_theta;         //!
   std::vector<Float_t>     ftk_refit_accepted_track_d0;            //!
   std::vector<Float_t>     ftk_refit_accepted_track_z0;            //!
   std::vector<Float_t>     ftk_refit_accepted_track_qop;           //!
   std::vector<Float_t>     ftk_refit_accepted_track_chi2;          //!
   std::vector<Float_t>     ftk_refit_accepted_track_chi2ndof;      //!
   std::vector<Float_t>     ftk_refit_accepted_track_charge;        //!
   std::vector<Float_t>     ftk_refit_accepted_track_hitPattern;    //!

   std::vector<Float_t>     ftk_refit_inclusive_track_pt;            //!
   std::vector<Float_t>     ftk_refit_inclusive_track_eta;           //!
   std::vector<Float_t>     ftk_refit_inclusive_track_phi;           //!
   std::vector<Float_t>     ftk_refit_inclusive_track_m;             //!
   std::vector<Float_t>     ftk_refit_inclusive_track_theta;         //!
   std::vector<Float_t>     ftk_refit_inclusive_track_d0;            //!
   std::vector<Float_t>     ftk_refit_inclusive_track_z0;            //!
   std::vector<Float_t>     ftk_refit_inclusive_track_qop;           //!
   std::vector<Float_t>     ftk_refit_inclusive_track_chi2;          //!
   std::vector<Float_t>     ftk_refit_inclusive_track_chi2ndof;      //!
   std::vector<Float_t>     ftk_refit_inclusive_track_charge;        //!
   std::vector<Float_t>     ftk_refit_inclusive_track_hitPattern;    //!


   std::vector<Float_t>     ftk_reco_deltaR;            //!
   std::vector<Float_t>     truth_reco_deltaR;          //!
   std::vector<Float_t>     ftk_refit_truth_deltaR;     //!
   std::vector<Float_t>     ftk_refit_reco_deltaR;      //!
   std::vector<Float_t>     ftk_truth_deltaR;           //!

   std::vector<Float_t>     truth_reco_pt_bias;         //!
   std::vector<Float_t>     truth_reco_eta_bias;        //!
   std::vector<Float_t>     truth_reco_phi_bias;        //!
   std::vector<Float_t>     truth_reco_d0_bias;         //!

   std::vector<Float_t>     ftk_refit_reco_pt_bias;     //!
   std::vector<Float_t>     ftk_refit_reco_eta_bias;    //!
   std::vector<Float_t>     ftk_refit_reco_phi_bias;    //!
   std::vector<Float_t>     ftk_refit_reco_d0_bias;     //!

   std::vector<Float_t>     ftk_truth_pt_bias;          //!
   std::vector<Float_t>     ftk_truth_eta_bias;         //!
   std::vector<Float_t>     ftk_truth_phi_bias;         //!
   std::vector<Float_t>     ftk_truth_d0_bias;          //!
   std::vector<Float_t>     ftk_truth_corrected_d0_bias;          //!

   std::vector<Float_t>     ftk_reco_pt_bias;           //!
   std::vector<Float_t>     ftk_reco_eta_bias;          //!
   std::vector<Float_t>     ftk_reco_phi_bias;          //!
   std::vector<Float_t>     ftk_reco_d0_bias;           //!
   std::vector<Float_t>     ftk_reco_corrected_d0_bias;           //!

   std::vector<Float_t>     ftk_refit_truth_pt_bias;    //!
   std::vector<Float_t>     ftk_refit_truth_eta_bias;   //!
   std::vector<Float_t>     ftk_refit_truth_phi_bias;   //!
   std::vector<Float_t>     ftk_refit_truth_d0_bias;    //!


   std::vector<Float_t>     ftk_refit_recoMatch_track_pt;   //!
   std::vector<Float_t>     reco_ftkrefitMatch_track_pt;    //!
   std::vector<Float_t>     ftk_refit_recoMatch_track_eta;  //!
   std::vector<Float_t>     ftk_refit_recoMatch_track_phi;  //!
   std::vector<Float_t>     reco_ftkrefitMatch_track_eta;   //!
   std::vector<Float_t>     reco_ftkrefitMatch_track_phi;   //!
   std::vector<Float_t>     reco_ftkrefitMatch_track_d0;    //!
   std::vector<Float_t>     reco_ftkrefitMatch_track_z0;    //!

   std::vector<Float_t>     ftk_recoMatch_track_eta; //!
   std::vector<Float_t>     ftk_recoMatch_track_phi; //!
   std::vector<Float_t>     reco_ftkMatch_track_eta; //!
   std::vector<Float_t>     reco_ftkMatch_track_phi; //!
   std::vector<Float_t>     reco_ftkMatch_track_d0;  //!
   // std::vector<Float_t>     reco_ftkMatch_track_corrected_d0;  //!
   std::vector<Float_t>     reco_ftkMatch_track_z0;  //!
   std::vector<Float_t>     ftk_recoMatch_track_pt;  //!
   std::vector<Float_t>     reco_ftkMatch_track_pt;  //!

   std::vector<Float_t>     reco_truthMatch_track_eta; //!
   std::vector<Float_t>     reco_truthMatch_track_phi; //!
   std::vector<Float_t>     truth_recoMatch_track_eta; //!
   std::vector<Float_t>     truth_recoMatch_track_phi; //!
   std::vector<Float_t>     truth_recoMatch_track_pt;  //!
   std::vector<Float_t>     reco_truthMatch_track_pt;  //!
   std::vector<Float_t>     truth_recoMatch_track_z0;  //!
   std::vector<Float_t>     truth_recoMatch_track_d0;  //!

   std::vector<Float_t>     truth_ftkMatch_track_phi; //!
   std::vector<Float_t>     truth_ftkMatch_track_eta; //!
   std::vector<Float_t>     ftk_truthMatch_track_phi; //!
   std::vector<Float_t>     ftk_truthMatch_track_eta; //!
   std::vector<Float_t>     truth_ftkMatch_track_pt;  //!
   std::vector<Float_t>     ftk_truthMatch_track_pt;  //!
   std::vector<Float_t>     truth_ftkMatch_track_d0;  //!
   std::vector<Float_t>     truth_ftkMatch_track_z0;  //!

   std::vector<Float_t>     truth_ftkrefitMatch_track_phi;  //!
   std::vector<Float_t>     truth_ftkrefitMatch_track_eta;  //!
   std::vector<Float_t>     ftk_refit_truthMatch_track_phi; //!
   std::vector<Float_t>     ftk_refit_truthMatch_track_eta; //!
   std::vector<Float_t>     truth_ftkrefitMatch_track_pt;   //!
   std::vector<Float_t>     ftk_refit_truthMatch_track_pt;  //!
   std::vector<Float_t>     truth_ftkrefitMatch_track_d0;   //!
   std::vector<Float_t>     truth_ftkrefitMatch_track_z0;   //!


   std::vector<Int_t>       truth_accepted;        //!
   std::vector<Int_t>       reco_accepted;         //!
   std::vector<Int_t>       reco_muon_accepted;    //!
   std::vector<Int_t>       reco_accepted_FTKTDR;  //!
   std::vector<Int_t>       ftk_accepted;          //!
   std::vector<Int_t>       ftk_refit_accepted;    //!

   std::vector<Int_t>       reco_ftk_fiducial;     //!




   TTree *tree; //!

   // this is a standard constructor
   FTKxAODAnalysis ();

   // these are the functions inherited from Algorithm
   // tomoya add
   EL::StatusCode TrackSelection ();

   bool isAcceptedTruth(const xAOD::TruthParticle* tp);
   bool isAcceptedReco(const xAOD::TrackParticle* recp);
   bool isAcceptedReco_FTKTDR(const xAOD::TrackParticle* recp);
   bool isAcceptedReco_muon(const xAOD::TrackParticle* recp);
   bool isAcceptedFTKfiducial(const xAOD::TrackParticle* recp);

   void ResetVariables();
   Float_t calc_delta_R(Float_t eta1, Float_t eta2, Float_t phi1, Float_t phi2);

  void SetIsAOD(bool aod_flag) {isAOD = aod_flag;}
  // std::cerr << "BRI TEST isAOD 1 is equal to " << value << std::endl;
  // std::cerr << "BRI TEST isAOD 3 is equal to " << isAOD << std::endl;
  void SetDeltaR(float value) {dRval = value;}

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
  ClassDef(FTKxAODAnalysis, 1);

  // private:

  // const AtlasDetectorID* m_idHelper;
  // const PixelID* m_pixelId;  
  // const SCT_ID* m_sctId;  
  // const InDetDD::SiDetectorManager*  m_PIX_mgr;
  // const InDetDD::SiDetectorManager*  m_SCT_mgr;
};

#endif
