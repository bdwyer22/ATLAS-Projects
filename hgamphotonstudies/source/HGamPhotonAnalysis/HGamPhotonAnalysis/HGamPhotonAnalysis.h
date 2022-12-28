#ifndef HGamPhotonAnalysis_MyPhotonAnalysis_H
#define HGamPhotonAnalysis_MyPhotonAnalysis_H
#include <EventLoop/Algorithm.h>

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TGraphAsymmErrors.h>
#include <TLorentzVector.h>

#include <vector>
#include "EventLoop/OutputStream.h"
#include "xAODEventInfo/EventInfo.h"
#include "ElectronPhotonSelectorTools/egammaPIDdefs.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODJet/JetContainer.h"

class HGamPhotonAnalysis : public EL::Algorithm
{


    // bool m_isMC; //!
    // bool truth_particle_baseline; //!

    // int m_eventNumber; //!
    // int m_runNumber; //!
    int m_mu; //!

    bool HGam_isPassed; //!
    bool isPassedTriggerMatch; //!
    bool isPassedRelPtCuts; //!
    bool isPassedMassCut; //!
    bool isPassedPreselection; //!

    float m_yy; //!

    int leading_photon; //!

    uint gam1_isEMTight; //!
    uint gam2_isEMTight; //!

    bool y1_tight; //!
    bool y2_tight; //!

    bool y1_IsIso; //!
    bool y2_IsIso; //!

    bool y1_IsIso_def; //!
    bool y2_IsIso_def; //!

    bool loose1; //!
    bool loose2; //!

    bool passed; //!

    float tmp_y1_phi; //!
    float tmp_y1_eta; //!
    float tmp_y1_pt; //!
    float tmp_y1_m; //!

    float tmp_y2_phi; //!
    float tmp_y2_eta; //!
    float tmp_y2_pt; //!
    float tmp_y2_m; //!

    int ptbins = 6; //!
    double ptedges[7] = {0, 30, 55, 75, 120, 350, 450};  //!
    // int ptmin = 20;  //!
    // int ptmax = 220; //!

    int ybins = 100;  //!
    int ymin = 0;  //!
    int ymax = 5; //!

    int mbins = 70;  //!
    int mmin = 100;  //!
    int mmax = 170; //!

    int mubins = 5;  //!
    double muedges[6] = {0, 10, 20, 30, 40, 60};  //!

    int etabins = 50;  //!
    float etamin = -4;  //!
    float etamax = 4; //!

    // int ptbins = 100;  //!
    int pt50min = 40;  //!
    int pt50max = 240; //!
    // int pt30min = 20;  //!
    // int pt30max = 220; //!

    int myybins = 55;  //!
    int myymin = 105;  //!
    int myymax = 160; //!

    // float pilelupWeight; //!


    int m_eventCounter; //!

    TLorentzVector y1TLVec;
    TLorentzVector y2TLVec; 
    TLorentzVector yyTLVec; 

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
    bool isMCa;
    bool isMCd;
    bool isMCe;
    bool isMCde;

    // int n_EventNumber; //!
    // int n_RunNumber;   //!
    double pt_value; //!
    double myy_value; //!
    double mu_value; //!
    double eta_value; //!

    double ptj1_purity_value_yy; //!
    double ptj1_purity_value_mc; //!
    double ptj1_purity_value_jj; //!
    double ptj1_purity_value_yj; //!
    float ptj1_purity_weight; //!
    float ptj1_purity_weight_mc; //!

    double myy_purity_value_yy; //!
    double myy_purity_value_jj; //!
    double myy_purity_value_mc; //!
    double myy_purity_value_yj; //!
    float myy_purity_weight; //!
    float myy_purity_weight_mc; //!

    double mu_purity_value_yy; //!
    double mu_purity_value_jj; //!
    double mu_purity_value_mc; //!
    double mu_purity_value_yj; //!
    float mu_purity_weight; //!
    float mu_purity_weight_mc; //!

    double etaj1_purity_value_yy; //!
    double etaj1_purity_value_jj; //!
    double etaj1_purity_value_mc; //!
    double etaj1_purity_value_yj; //!
    double etaj1_purity_value_jy; //!
    float etaj1_purity_weight; //!
    float etaj1_purity_weight_mc; //!

    int N_points_ptj1; //!
    int N_points_myy; //!
    int N_points_mu; //!

    float     pflow_fjvt_fail_eta;       //!
    float     pflow_fjvt_pass_eta;       //!

    // float     pflow_j130_pt;     //! 
    // float     pflow_j130_eta;     //! 

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

    float     pflow_j130_pt_10;     //! 
    float     pflow_j130_pt_1020;   //!
    float     pflow_j130_pt_2030;   //!
    float     pflow_j130_pt_3040;   //!
    float     pflow_j130_pt_4060;   //!

    float     myy_15;     //! 
    float     myy_1525;   //!
    float     myy_2535;   //!
    float     myy_3550;   //!
    float     myy_50;     //!

    float     myy_10;     //! 
    float     myy_1020;   //!
    float     myy_2030;   //!
    float     myy_3040;   //!
    float     myy_4060;   //!

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


    float hgam_yy_pflowj1_pt = -999; //!
    float hgam_jj_pflowj1_pt = -999; //!
    float hgam_yj_pflowj1_pt = -999; //!
    float hgam_jy_pflowj1_pt = -999; //!

    float hgam_yy_pflowj1_eta = -999; //!
    float hgam_jj_pflowj1_eta = -999; //!
    float hgam_yj_pflowj1_eta = -999; //!
    float hgam_jy_pflowj1_eta = -999; //!

    float hgam_yy_y1_eta = -999; //!
    float hgam_yy_y1_pt = -999; //!
    float hgam_yy_y2_eta = -999; //!
    float hgam_yy_y2_pt = -999; //!

    float hgam_yy_pt = -999; //!
    float hgam_yy_eta = -999; //!
    float hgam_yy_m = -999; //!

    float hgam_jj_j1_pt = -999; //!
    float hgam_jj_j1_eta = -999; //!
    float hgam_jj_j2_pt = -999; //!
    float hgam_jj_j2_eta = -999; //!

    float hgam_yj_j_pt = -999; //!
    float hgam_yj_y_pt = -999; //!
    float hgam_yj_j_eta = -999; //!
    float hgam_yj_y_eta = -999; //!

    float hgam_jy_j_pt = -999; //!
    float hgam_jy_y_pt = -999; //!
    float hgam_jy_j_eta = -999; //!
    float hgam_jy_y_eta = -999; //!


    TH1F *hist_yy_pflowj1_pt;  //!
    TH1F *hist_jj_pflowj1_pt;  //!
    TH1F *hist_jy_pflowj1_pt;  //!
    TH1F *hist_yj_pflowj1_pt;  //!

    TH1F *hist_yy_pflowj1_pt_010;  //!
    TH1F *hist_jj_pflowj1_pt_010;  //!
    TH1F *hist_jy_pflowj1_pt_010;  //!
    TH1F *hist_yj_pflowj1_pt_010;  //!

    TH1F *hist_yy_pflowj1_pt_1020;  //!
    TH1F *hist_jj_pflowj1_pt_1020;  //!
    TH1F *hist_jy_pflowj1_pt_1020;  //!
    TH1F *hist_yj_pflowj1_pt_1020;  //!

    TH1F *hist_yy_pflowj1_pt_2030;  //!
    TH1F *hist_jj_pflowj1_pt_2030;  //!
    TH1F *hist_jy_pflowj1_pt_2030;  //!
    TH1F *hist_yj_pflowj1_pt_2030;  //!

    TH1F *hist_yy_pflowj1_pt_3040;  //!
    TH1F *hist_jj_pflowj1_pt_3040;  //!
    TH1F *hist_jy_pflowj1_pt_3040;  //!
    TH1F *hist_yj_pflowj1_pt_3040;  //!

    TH1F *hist_yy_pflowj1_pt_4060;  //!
    TH1F *hist_jj_pflowj1_pt_4060;  //!
    TH1F *hist_jy_pflowj1_pt_4060;  //!
    TH1F *hist_yj_pflowj1_pt_4060;  //!

    TH1F *hist_yy_myy;  //!
    TH1F *hist_jj_myy;  //!
    TH1F *hist_jy_myy;  //!
    TH1F *hist_yj_myy;  //!

    TH1F *hist_yy_myy_010;  //!
    TH1F *hist_jj_myy_010;  //!
    TH1F *hist_jy_myy_010;  //!
    TH1F *hist_yj_myy_010;  //!

    TH1F *hist_yy_myy_1020;  //!
    TH1F *hist_jj_myy_1020;  //!
    TH1F *hist_jy_myy_1020;  //!
    TH1F *hist_yj_myy_1020;  //!

    TH1F *hist_yy_myy_2030;  //!
    TH1F *hist_jj_myy_2030;  //!
    TH1F *hist_jy_myy_2030;  //!
    TH1F *hist_yj_myy_2030;  //!

    TH1F *hist_yy_myy_3040;  //!
    TH1F *hist_jj_myy_3040;  //!
    TH1F *hist_jy_myy_3040;  //!
    TH1F *hist_yj_myy_3040;  //!

    TH1F *hist_yy_myy_4060;  //!
    TH1F *hist_jj_myy_4060;  //!
    TH1F *hist_jy_myy_4060;  //!
    TH1F *hist_yj_myy_4060;  //!
    
    TH1F *hist_yy_pflowj1_pt_ptj1_purityweight;  //!
    TH1F *hist_jj_pflowj1_pt_ptj1_purityweight;  //!
    TH1F *hist_jy_pflowj1_pt_ptj1_purityweight;  //!
    TH1F *hist_yj_pflowj1_pt_ptj1_purityweight;  //!

    TH1F *hist_yy_pflowj1_pt_010_ptj1_purityweight;  //!
    TH1F *hist_jj_pflowj1_pt_010_ptj1_purityweight;  //!
    TH1F *hist_jy_pflowj1_pt_010_ptj1_purityweight;  //!
    TH1F *hist_yj_pflowj1_pt_010_ptj1_purityweight;  //!

    TH1F *hist_yy_pflowj1_pt_1020_ptj1_purityweight;  //!
    TH1F *hist_jj_pflowj1_pt_1020_ptj1_purityweight;  //!
    TH1F *hist_jy_pflowj1_pt_1020_ptj1_purityweight;  //!
    TH1F *hist_yj_pflowj1_pt_1020_ptj1_purityweight;  //!

    TH1F *hist_yy_pflowj1_pt_2030_ptj1_purityweight;  //!
    TH1F *hist_jj_pflowj1_pt_2030_ptj1_purityweight;  //!
    TH1F *hist_jy_pflowj1_pt_2030_ptj1_purityweight;  //!
    TH1F *hist_yj_pflowj1_pt_2030_ptj1_purityweight;  //!

    TH1F *hist_yy_pflowj1_pt_3040_ptj1_purityweight;  //!
    TH1F *hist_jj_pflowj1_pt_3040_ptj1_purityweight;  //!
    TH1F *hist_jy_pflowj1_pt_3040_ptj1_purityweight;  //!
    TH1F *hist_yj_pflowj1_pt_3040_ptj1_purityweight;  //!

    TH1F *hist_yy_pflowj1_pt_4060_ptj1_purityweight;  //!
    TH1F *hist_jj_pflowj1_pt_4060_ptj1_purityweight;  //!
    TH1F *hist_jy_pflowj1_pt_4060_ptj1_purityweight;  //!
    TH1F *hist_yj_pflowj1_pt_4060_ptj1_purityweight;  //!

    TH1F *hist_yy_myy_myy_purityweight;  //!
    TH1F *hist_jj_myy_myy_purityweight;  //!
    TH1F *hist_jy_myy_myy_purityweight;  //!
    TH1F *hist_yj_myy_myy_purityweight;  //!

    TH1F *hist_yy_myy_010_myy_purityweight;  //!
    TH1F *hist_jj_myy_010_myy_purityweight;  //!
    TH1F *hist_jy_myy_010_myy_purityweight;  //!
    TH1F *hist_yj_myy_010_myy_purityweight;  //!

    TH1F *hist_yy_myy_1020_myy_purityweight;  //!
    TH1F *hist_jj_myy_1020_myy_purityweight;  //!
    TH1F *hist_jy_myy_1020_myy_purityweight;  //!
    TH1F *hist_yj_myy_1020_myy_purityweight;  //!

    TH1F *hist_yy_myy_2030_myy_purityweight;  //!
    TH1F *hist_jj_myy_2030_myy_purityweight;  //!
    TH1F *hist_jy_myy_2030_myy_purityweight;  //!
    TH1F *hist_yj_myy_2030_myy_purityweight;  //!

    TH1F *hist_yy_myy_3040_myy_purityweight;  //!
    TH1F *hist_jj_myy_3040_myy_purityweight;  //!
    TH1F *hist_jy_myy_3040_myy_purityweight;  //!
    TH1F *hist_yj_myy_3040_myy_purityweight;  //!

    TH1F *hist_yy_myy_4060_myy_purityweight;  //!
    TH1F *hist_jj_myy_4060_myy_purityweight;  //!
    TH1F *hist_jy_myy_4060_myy_purityweight;  //!
    TH1F *hist_yj_myy_4060_myy_purityweight;  //!

    TH1F *hist_yy_mu_mu_purityweight;  //!
    TH1F *hist_jj_mu_mu_purityweight;  //!
    TH1F *hist_jy_mu_mu_purityweight;  //!
    TH1F *hist_yj_mu_mu_purityweight;  //!

    TH1F *hist_yy_mu;  //!
    TH1F *hist_jj_mu;  //!
    TH1F *hist_jy_mu;  //!
    TH1F *hist_yj_mu;  //!

    TH1F *hist_mu;  //!
    // TH1F *hist_mu_purityweight;  //!

    TH1F *hist_yy_pflowj1_eta;  //!
    TH1F *hist_jj_pflowj1_eta;  //!
    TH1F *hist_yj_pflowj1_eta;  //!
    TH1F *hist_jy_pflowj1_eta;  //!

    TH1F *hist_yy_pflowj1_eta_purityweight;  //!
    TH1F *hist_jj_pflowj1_eta_purityweight;  //!
    TH1F *hist_yj_pflowj1_eta_purityweight;  //!
    TH1F *hist_jy_pflowj1_eta_purityweight;  //!

    TH1F *hist_yy_m;  //!
    TH1F *hist_yy_pt;  //!
    TH1F *hist_yy_eta;  //!

    TH1F *hist_yy_y1_pt;  //!
    TH1F *hist_yy_y2_pt;  //!
    TH1F *hist_yy_y1_eta;  //!
    TH1F *hist_yy_y2_eta;  //!

    TH1F *hist_jj_j1_pt;  //!
    TH1F *hist_jj_j2_pt;  //!
    TH1F *hist_jj_j1_eta;  //!
    TH1F *hist_jj_j2_eta;  //!

    TH1F *hist_jy_j_pt;  //!
    TH1F *hist_jy_y_pt;  //!
    TH1F *hist_jy_j_eta;  //!
    TH1F *hist_jy_y_eta;  //!

    TH1F *hist_yj_j_pt;  //!
    TH1F *hist_yj_y_pt;  //!
    TH1F *hist_yj_j_eta;  //!
    TH1F *hist_yj_y_eta;  //!

    TH1F *hist_j130_pt;      //!
    TH1F *hist_j130_eta;      //!


    // TH1F *hist_mu;      //!
    TH1F *hist_myy;      //!
    TH1F *hist_myy_inclusive;      //!

    TH1F *hist_j130_pt_015;      //!
    TH1F *hist_j130_pt_1525;      //!
    TH1F *hist_j130_pt_2535;      //!
    TH1F *hist_j130_pt_3550;      //!
    TH1F *hist_j130_pt_50;       //!

    TH1F *hist_j130_pt_010;      //!
    TH1F *hist_j130_pt_1020;      //!
    TH1F *hist_j130_pt_2030;      //!
    TH1F *hist_j130_pt_3040;      //!
    TH1F *hist_j130_pt_4060;       //!

    TH1F *hist_myy_015;      //!
    TH1F *hist_myy_1525;      //!
    TH1F *hist_myy_2535;      //!
    TH1F *hist_myy_3550;      //!
    TH1F *hist_myy_50;       //!

    TH1F *hist_myy_010;      //!
    TH1F *hist_myy_1020;      //!
    TH1F *hist_myy_2030;      //!
    TH1F *hist_myy_3040;      //!
    TH1F *hist_myy_4060;       //!

    TH1F *hist_myy_010_inclusive;      //!
    TH1F *hist_myy_1020_inclusive;      //!
    TH1F *hist_myy_2030_inclusive;      //!
    TH1F *hist_myy_3040_inclusive;      //!
    TH1F *hist_myy_4060_inclusive;       //!

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

    TH1F *hist_j150_y_015_fJVT;      //!
    TH1F *hist_j150_y_1525_fJVT;      //!
    TH1F *hist_j150_y_2535_fJVT;      //!
    TH1F *hist_j150_y_3550_fJVT;      //!
    TH1F *hist_j150_y_50_fJVT;     //!

    TH1F *hist_pass_fJVT;     //!
    TH1F *hist_fail_fJVT;     //!

    TH1F *cutflow;      //!

    TH1F *hist_j130_pt_central;  //!
    TH1F *hist_j130_eta_central;  //!

    TH1F *hist_myy_010_central;  //!
    TH1F *hist_myy_1020_central;  //!
    TH1F *hist_myy_2030_central;  //!
    TH1F *hist_myy_3040_central;  //!
    TH1F *hist_myy_4060_central;  //!

    TH1F *hist_j130_pt_010_central;  //!
    TH1F *hist_j130_pt_1020_central;  //!
    TH1F *hist_j130_pt_2030_central;  //!
    TH1F *hist_j130_pt_3040_central;  //!
    TH1F *hist_j130_pt_4060_central;  //!

    TH1F *hist_yy_myy_central;  //!
    TH1F *hist_jj_myy_central;  //!
    TH1F *hist_jy_myy_central;  //!
    TH1F *hist_yj_myy_central;  //!

    TH1F *hist_yy_myy_myy_purityweight_central;  //!
    TH1F *hist_jj_myy_myy_purityweight_central;  //!
    TH1F *hist_jy_myy_myy_purityweight_central;  //!
    TH1F *hist_yj_myy_myy_purityweight_central;  //!

    TH1F *hist_yy_pflowj1_pt_010_central;  //!
    TH1F *hist_jj_pflowj1_pt_010_central;  //!
    TH1F *hist_yj_pflowj1_pt_010_central;  //!
    TH1F *hist_jy_pflowj1_pt_010_central;  //!

    TH1F *hist_yy_pflowj1_pt_1020_central;  //!
    TH1F *hist_jj_pflowj1_pt_1020_central;  //!
    TH1F *hist_yj_pflowj1_pt_1020_central;  //!
    TH1F *hist_jy_pflowj1_pt_1020_central;  //!

    TH1F *hist_yy_pflowj1_pt_2030_central;  //!
    TH1F *hist_jj_pflowj1_pt_2030_central;  //!
    TH1F *hist_yj_pflowj1_pt_2030_central;  //!
    TH1F *hist_jy_pflowj1_pt_2030_central;  //!

    TH1F *hist_yy_pflowj1_pt_3040_central;  //!
    TH1F *hist_jj_pflowj1_pt_3040_central;  //!
    TH1F *hist_yj_pflowj1_pt_3040_central;  //!
    TH1F *hist_jy_pflowj1_pt_3040_central;  //!

    TH1F *hist_yy_pflowj1_pt_4060_central;  //!
    TH1F *hist_jj_pflowj1_pt_4060_central;  //!
    TH1F *hist_yj_pflowj1_pt_4060_central;  //!
    TH1F *hist_jy_pflowj1_pt_4060_central;  //!

    TH1F *hist_jj_pflowj1_pt_010_ptj1_purityweight_central;  //!
    TH1F *hist_yj_pflowj1_pt_010_ptj1_purityweight_central;  //!
    TH1F *hist_jy_pflowj1_pt_010_ptj1_purityweight_central;  //!

    TH1F *hist_jj_pflowj1_pt_1020_ptj1_purityweight_central;  //!
    TH1F *hist_yj_pflowj1_pt_1020_ptj1_purityweight_central;  //!
    TH1F *hist_jy_pflowj1_pt_1020_ptj1_purityweight_central;  //!

    TH1F *hist_jj_pflowj1_pt_2030_ptj1_purityweight_central;  //!
    TH1F *hist_yj_pflowj1_pt_2030_ptj1_purityweight_central;  //!
    TH1F *hist_jy_pflowj1_pt_2030_ptj1_purityweight_central;  //!

    TH1F *hist_jj_pflowj1_pt_3040_ptj1_purityweight_central;  //!
    TH1F *hist_yj_pflowj1_pt_3040_ptj1_purityweight_central;  //!
    TH1F *hist_jy_pflowj1_pt_3040_ptj1_purityweight_central;  //!

    TH1F *hist_jj_pflowj1_pt_4060_ptj1_purityweight_central;  //!
    TH1F *hist_yj_pflowj1_pt_4060_ptj1_purityweight_central;  //!
    TH1F *hist_jy_pflowj1_pt_4060_ptj1_purityweight_central;  //!

    TH1F *hist_yy_myy_010_central;  //!
    TH1F *hist_jj_myy_010_central;  //!
    TH1F *hist_yj_myy_010_central;  //!
    TH1F *hist_jy_myy_010_central;  //!

    TH1F *hist_yy_myy_1020_central;  //!
    TH1F *hist_jj_myy_1020_central;  //!
    TH1F *hist_yj_myy_1020_central;  //!
    TH1F *hist_jy_myy_1020_central;  //!

    TH1F *hist_yy_myy_2030_central;  //!
    TH1F *hist_jj_myy_2030_central;  //!
    TH1F *hist_yj_myy_2030_central;  //!
    TH1F *hist_jy_myy_2030_central;  //!

    TH1F *hist_yy_myy_3040_central;  //!
    TH1F *hist_jj_myy_3040_central;  //!
    TH1F *hist_yj_myy_3040_central;  //!
    TH1F *hist_jy_myy_3040_central;  //!

    TH1F *hist_yy_myy_4060_central;  //!
    TH1F *hist_jj_myy_4060_central;  //!
    TH1F *hist_yj_myy_4060_central;  //!
    TH1F *hist_jy_myy_4060_central;  //!

    TH1F *hist_jj_myy_010_myy_purityweight_central;  //!
    TH1F *hist_yj_myy_010_myy_purityweight_central;  //!
    TH1F *hist_jy_myy_010_myy_purityweight_central;  //!

    TH1F *hist_jj_myy_1020_myy_purityweight_central;  //!
    TH1F *hist_yj_myy_1020_myy_purityweight_central;  //!
    TH1F *hist_jy_myy_1020_myy_purityweight_central;  //!

    TH1F *hist_jj_myy_2030_myy_purityweight_central;  //!
    TH1F *hist_yj_myy_2030_myy_purityweight_central;  //!
    TH1F *hist_jy_myy_2030_myy_purityweight_central;  //!

    TH1F *hist_jj_myy_3040_myy_purityweight_central;  //!
    TH1F *hist_yj_myy_3040_myy_purityweight_central;  //!
    TH1F *hist_jy_myy_3040_myy_purityweight_central;  //!

    TH1F *hist_jj_myy_4060_myy_purityweight_central;  //!
    TH1F *hist_yj_myy_4060_myy_purityweight_central;  //!
    TH1F *hist_jy_myy_4060_myy_purityweight_central;  //!

    TH1F *hist_yy_myy_inclusive;  //!
    TH1F *hist_jj_myy_inclusive;  //!
    TH1F *hist_jy_myy_inclusive;  //!
    TH1F *hist_yj_myy_inclusive;  //!

    TH1F *hist_yy_myy_010_inclusive;  //!
    TH1F *hist_jj_myy_010_inclusive;  //!
    TH1F *hist_jy_myy_010_inclusive;  //!
    TH1F *hist_yj_myy_010_inclusive;  //!

    TH1F *hist_yy_myy_1020_inclusive;  //!
    TH1F *hist_jj_myy_1020_inclusive;  //!
    TH1F *hist_jy_myy_1020_inclusive;  //!
    TH1F *hist_yj_myy_1020_inclusive;  //!

    TH1F *hist_yy_myy_2030_inclusive;  //!
    TH1F *hist_jj_myy_2030_inclusive;  //!
    TH1F *hist_jy_myy_2030_inclusive;  //!
    TH1F *hist_yj_myy_2030_inclusive;  //!

    TH1F *hist_yy_myy_3040_inclusive;  //!
    TH1F *hist_jj_myy_3040_inclusive;  //!
    TH1F *hist_jy_myy_3040_inclusive;  //!
    TH1F *hist_yj_myy_3040_inclusive;  //!

    TH1F *hist_yy_myy_4060_inclusive;  //!
    TH1F *hist_jj_myy_4060_inclusive;  //!
    TH1F *hist_jy_myy_4060_inclusive;  //!
    TH1F *hist_yj_myy_4060_inclusive;  //!


    TH1F *hist_yy_myy_myy_purityweight_inclusive;  //!
    TH1F *hist_jj_myy_myy_purityweight_inclusive;  //!
    TH1F *hist_jy_myy_myy_purityweight_inclusive;  //!
    TH1F *hist_yj_myy_myy_purityweight_inclusive;  //!

    TH1F *hist_yy_myy_010_myy_purityweight_inclusive;  //!
    TH1F *hist_jj_myy_010_myy_purityweight_inclusive;  //!
    TH1F *hist_jy_myy_010_myy_purityweight_inclusive;  //!
    TH1F *hist_yj_myy_010_myy_purityweight_inclusive;  //!

    TH1F *hist_yy_myy_1020_myy_purityweight_inclusive;  //!
    TH1F *hist_jj_myy_1020_myy_purityweight_inclusive;  //!
    TH1F *hist_jy_myy_1020_myy_purityweight_inclusive;  //!
    TH1F *hist_yj_myy_1020_myy_purityweight_inclusive;  //!

    TH1F *hist_yy_myy_2030_myy_purityweight_inclusive;  //!
    TH1F *hist_jj_myy_2030_myy_purityweight_inclusive;  //!
    TH1F *hist_jy_myy_2030_myy_purityweight_inclusive;  //!
    TH1F *hist_yj_myy_2030_myy_purityweight_inclusive;  //!

    TH1F *hist_yy_myy_3040_myy_purityweight_inclusive;  //!
    TH1F *hist_jj_myy_3040_myy_purityweight_inclusive;  //!
    TH1F *hist_jy_myy_3040_myy_purityweight_inclusive;  //!
    TH1F *hist_yj_myy_3040_myy_purityweight_inclusive;  //!

    TH1F *hist_yy_myy_4060_myy_purityweight_inclusive;  //!
    TH1F *hist_jj_myy_4060_myy_purityweight_inclusive;  //!
    TH1F *hist_jy_myy_4060_myy_purityweight_inclusive;  //!
    TH1F *hist_yj_myy_4060_myy_purityweight_inclusive;  //!

    TGraphAsymmErrors *gr_inclusive_gg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_inclusive_gjjg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_inclusive_jj_purity_TotErr;  //!

    TGraphAsymmErrors *gr_m_yy_gg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_m_yy_gjjg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_m_yy_jj_purity_TotErr;  //!

    TGraphAsymmErrors *gr_mu_gg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_mu_gjjg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_mu_jj_purity_TotErr;  //!

    TGraphAsymmErrors *gr_pT_j1_30_gg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_pT_j1_30_gjjg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_pT_j1_30_jj_purity_TotErr;  //!

    TGraphAsymmErrors *gr_eta_j1_30_gg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_eta_j1_30_gjjg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_eta_j1_30_jj_purity_TotErr;  //!

    TGraphAsymmErrors *gr_abs_eta_j1_30_gg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_abs_eta_j1_30_gjjg_purity_TotErr;  //!
    TGraphAsymmErrors *gr_abs_eta_j1_30_jj_purity_TotErr;  //!


    TH1F *hist_mc_pt_ptj1_purityweight;   //!
    TH1F *hist_mc_myy_myy_purityweight;   //!
    TH1F *hist_mc_mu_mu_purityweight;   //!
    TH1F *hist_mc_myy_myy_purityweight_inclusive;   //!

    TH1F *hist_mc_myy_010_myy_purityweight;   //!
    TH1F *hist_mc_myy_1020_myy_purityweight;   //!
    TH1F *hist_mc_myy_2030_myy_purityweight;   //!
    TH1F *hist_mc_myy_3040_myy_purityweight;   //!
    TH1F *hist_mc_myy_4060_myy_purityweight;   //!


    TH1F *hist_mc_pt_010_ptj1_purityweight;   //!
    TH1F *hist_mc_pt_1020_ptj1_purityweight;   //!
    TH1F *hist_mc_pt_2030_ptj1_purityweight;   //!
    TH1F *hist_mc_pt_3040_ptj1_purityweight;   //!
    TH1F *hist_mc_pt_4060_ptj1_purityweight;   //!



    float sum_weights;      //!
    float lumi_mc16;      //!
    float eventweight;      //!





    TTree *tree; //!
    TFile *purity_file; //!


   // this is a standard constructor
   HGamPhotonAnalysis ();

   // these are the functions inherited from Algorithm
   // tomoya add
   EL::StatusCode TrackSelection ();

    void ResetVariables();

    void SetIsMCa(bool mca_flag) {isMCa = mca_flag;}
    void SetIsMCd(bool mcd_flag) {isMCd = mcd_flag;}
    void SetIsMCe(bool mce_flag) {isMCe = mce_flag;}
    void SetIsMCde(bool mcde_flag) {isMCde = mcde_flag;}
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
  ClassDef(HGamPhotonAnalysis, 1);

};

#endif
// 