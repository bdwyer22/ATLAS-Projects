#ifndef HGamMxAODAnalysis_MyxAODAnalysis_H
#define HGamMxAODAnalysis_MyxAODAnalysis_H
#include <EventLoop/Algorithm.h>

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TLorentzVector.h>
#include <vector>
#include "EventLoop/OutputStream.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"

class HGamMxAODAnalysis : public EL::Algorithm
{


  int m_mu;    //!
  bool passed; //!
  float m_yy;  //!

  //Variables
  int m_eventCounter; //!
  int ptbins = 50;    //!
  int ptmin = 20;     //!
  int ptmax = 220;    //!

  int ybins = 50;  //!
  int ymin = 0;     //!
  int ymax = 5;     //!

  int mbins = 70;  //!
  int mmin = 100;  //!
  int mmax = 170;  //!

  int etabins = 50;   //!
  float etamin = -4;  //!
  float etamax = 4;   //!


  int npflow30jetsperevent  = 0;      //!
  int npflow30jetsperevent_fJVT  = 0; //!

  float leadingpflow30jetpt = 0; //!
  float leadingpflow30jeteta;    //!
  float leadingpflow30jetphi;    //!
  float leadingpflow30jetm;      //!
  float leadingpflow30jety;      //!

  float leadingpflow30jetpt_fJVT;  //!
  float leadingpflow30jeteta_fJVT; //!
  float leadingpflow30jetphi_fJVT; //!
  float leadingpflow30jetm_fJVT;   //!
  float leadingpflow30jety_fJVT;   //!
  float alljet_y;   //!
  float alljet_y_fJVT;   //!


  // TLorentzVector topoTLVec;       //!
  TLorentzVector pflow30TLVec_fJVT;  //!
  TLorentzVector pflow30TLVec;       //!
  TLorentzVector alljetTLVec;        //!
  TLorentzVector alljetTLVec_fJVT;        //!

  //Containers for global use
  const xAOD::EventInfo*              m_eventInfoCont; //!

  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
  public:
    std::string outputName;     //!
    std::string outputxAODName; //!
    std::string cutflow;        //!


    TTree* outputTree; //!

    bool isData;
    bool isMCa;
    bool isMCd;
    bool isMCe;
    bool isMCde;
    bool isggh;
    bool isVBF;
    bool isSherpa;

    // int n_EventNumber; //!
    // int n_RunNumber;   //!
    int n_events;   //!

    float  pflow_fjvt_fail_eta;       //!
    float  pflow_fjvt_pass_eta;       //!

    float  pflow_j130_y_15;     //! 
    float  pflow_j130_y_1525;   //!
    float  pflow_j130_y_2535;   //!
    float  pflow_j130_y_3550;   //!
    float  pflow_j130_y_50;     //!

    float  pflow_j130_pt_15;     //! 
    float  pflow_j130_pt_1525;   //!
    float  pflow_j130_pt_2535;   //!
    float  pflow_j130_pt_3550;   //!
    float  pflow_j130_pt_50;     //!

    float  pflow_j130_pt;    //!
    float  pflow_j130_eta;   //!
    float  pflow_j130_phi;   //!
    float  pflow_j130_m;     //!
    float  pflow_j130_y;     //!

    float  pflow_j130_y_15_fJVT;     //! 
    float  pflow_j130_y_1525_fJVT;   //!
    float  pflow_j130_y_2535_fJVT;   //!
    float  pflow_j130_y_3550_fJVT;   //!
    float  pflow_j130_y_50_fJVT;     //!

    float  pflow_j130_pt_15_fJVT;     //! 
    float  pflow_j130_pt_1525_fJVT;   //!
    float  pflow_j130_pt_2535_fJVT;   //!
    float  pflow_j130_pt_3550_fJVT;   //!
    float  pflow_j130_pt_50_fJVT;     //!

    float  pflow_j130_pt_fJVT;    //!
    float  pflow_j130_eta_fJVT;   //!
    float  pflow_j130_phi_fJVT;   //!
    float  pflow_j130_m_fJVT;     //!
    float  pflow_j130_y_fJVT;     //!

    TH1F *hist_j130_pt_015;      //!
    TH1F *hist_j130_pt_1525;     //!
    TH1F *hist_j130_pt_2535;     //!
    TH1F *hist_j130_pt_3550;     //!
    TH1F *hist_j130_pt_50;       //!

    TH1F *hist_j130_y_015;     //!
    TH1F *hist_j130_y_1525;    //!
    TH1F *hist_j130_y_2535;    //!
    TH1F *hist_j130_y_3550;    //!
    TH1F *hist_j130_y_50;      //! 

    TH1F *hist_j130_pt_015_fJVT;     //!
    TH1F *hist_j130_pt_1525_fJVT;    //!
    TH1F *hist_j130_pt_2535_fJVT;    //!
    TH1F *hist_j130_pt_3550_fJVT;    //!
    TH1F *hist_j130_pt_50_fJVT;      //!

    TH1F *hist_j130_y_015_fJVT;     //!
    TH1F *hist_j130_y_1525_fJVT;    //!
    TH1F *hist_j130_y_2535_fJVT;    //!
    TH1F *hist_j130_y_3550_fJVT;    //!
    TH1F *hist_j130_y_50_fJVT;      //! 

    TH1F *hist_pass_fJVT;     //!
    TH1F *hist_fail_fJVT;     //!
    TH1F *hist_n_jets;        //! 
    TH1F *hist_n_jets_fJVT;   //! 

    TH1F *hist_alljet_pt;       //!
    TH1F *hist_alljet_y;       //!
    TH1F *hist_alljet_y_fJVT;       //!
    TH1F *hist_alljet_pt_fJVT;  //!
    TH1F *hist_alljet_eta;      //!

    TH1F *hist_forward_jet_pt;  //!
    TH1F *hist_forward_jet_eta; //!
    TH1F *hist_central_jet_pt;  //!
    TH1F *hist_central_jet_eta; //!

    TH1F *hist_forward_jet_pt_fJVT;  //!
    TH1F *hist_forward_jet_eta_fJVT; //!
    TH1F *hist_central_jet_pt_fJVT;  //!
    TH1F *hist_central_jet_eta_fJVT; //!

    TH1F *hist_alljet_y_015;  //!
    TH1F *hist_alljet_y_1525;  //!
    TH1F *hist_alljet_y_2535;  //!
    TH1F *hist_alljet_y_3550;  //!
    TH1F *hist_alljet_y_50;  //!

    TH1F *hist_alljet_y_015_fJVT;  //!
    TH1F *hist_alljet_y_1525_fJVT;  //!
    TH1F *hist_alljet_y_2535_fJVT;  //!
    TH1F *hist_alljet_y_3550_fJVT;  //!
    TH1F *hist_alljet_y_50_fJVT;  //!

    TH1F *hist_alljet_pt_015;  //!
    TH1F *hist_alljet_pt_1525;  //!
    TH1F *hist_alljet_pt_2535;  //!
    TH1F *hist_alljet_pt_3550;  //!
    TH1F *hist_alljet_pt_50;  //!

    TH1F *hist_alljet_pt_015_fJVT;  //!
    TH1F *hist_alljet_pt_1525_fJVT;  //!
    TH1F *hist_alljet_pt_2535_fJVT;  //!
    TH1F *hist_alljet_pt_3550_fJVT;  //!
    TH1F *hist_alljet_pt_50_fJVT;  //!

    // TH1F *hist_pass_fJVT_HS;     //!
    // TH1F *hist_fail_fJVT_HS;     //!
    // TH1F *hist_n_jets_HS;        //! 
    // TH1F *hist_n_jets_fJVT_HS;   //! 

    // TH1F *hist_pass_fJVT_notHS;     //!
    // TH1F *hist_fail_fJVT_notHS;     //!
    // TH1F *hist_n_jets_notHS;        //! 
    // TH1F *hist_n_jets_fJVT_notHS;   //! 

    // TH1F *hist_alljet_pt_HS;       //!
    // TH1F *hist_alljet_pt_fJVT_HS;  //!
    // TH1F *hist_alljet_eta_HS;      //!

    // TH1F *hist_forward_jet_pt_HS;  //!
    // TH1F *hist_forward_jet_eta_HS; //!
    // TH1F *hist_central_jet_pt_HS;  //!
    // TH1F *hist_central_jet_eta_HS; //!

    // TH1F *hist_forward_jet_pt_fJVT_HS;  //!
    // TH1F *hist_forward_jet_eta_fJVT_HS; //!
    // TH1F *hist_central_jet_pt_fJVT_HS;  //!
    // TH1F *hist_central_jet_eta_fJVT_HS; //!

    // TH1F *hist_alljet_pt_notHS;       //!
    // TH1F *hist_alljet_pt_fJVT_notHS;  //!
    // TH1F *hist_alljet_eta_notHS;      //!

    // TH1F *hist_forward_jet_pt_notHS;  //!
    // TH1F *hist_forward_jet_eta_notHS; //!
    // TH1F *hist_central_jet_pt_notHS;  //!
    // TH1F *hist_central_jet_eta_notHS; //!

    // TH1F *hist_forward_jet_pt_fJVT_notHS;  //!
    // TH1F *hist_forward_jet_eta_fJVT_notHS; //!
    // TH1F *hist_central_jet_pt_fJVT_notHS;  //!
    // TH1F *hist_central_jet_eta_fJVT_notHS; //!

    TH1F *cutflow_hist; //!
    float sum_weights;  //!
    float lumi_mc16;    //!
    float eventweight;  //!





    TTree *tree; //!

    // this is a standard constructor
    HGamMxAODAnalysis ();

    // these are the functions inherited from Algorithm
    // tomoya add
    EL::StatusCode TrackSelection ();

    void ResetVariables();

    // void SetCutflow(std::string cutflow_flag) {cutflow = cutflow_flag;}
    // std::cout<<"SetCutflow:  " << SetCutflow << std::endl;

    void SetIsMCa(bool mca_flag) {isMCa = mca_flag;}
    void SetIsMCd(bool mcd_flag) {isMCd = mcd_flag;}
    void SetIsMCe(bool mce_flag) {isMCe = mce_flag;}
    void SetIsMCde(bool mcde_flag) {isMCde = mcde_flag;}
    void SetIsData(bool data_flag) {isData = data_flag;}
    void SetIsggh(bool ggh_flag) {isggh = ggh_flag;}
    void SetIsVBF(bool vbf_flag) {isVBF = vbf_flag;}
    void SetIsSherpa(bool sherpa_flag) {isSherpa = sherpa_flag;}

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