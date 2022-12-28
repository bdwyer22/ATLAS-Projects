#ifndef yyHFSkim_MyxAODAnalysis_H
#define yyHFSkim_MyxAODAnalysis_H
#include <EventLoop/Algorithm.h>

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <vector>
#include "EventLoop/OutputStream.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"

class yyHFSkim : public EL::Algorithm
{
 //Variables
  int m_eventCounter; //!

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
    enum mcTypeEnum {mc16a = 0, mc16d  = 1, mc16e = 2};
    int m_mu; //!



    // float btagbin_LeadMV2Jet;        //!

    // TH1F *hist_LeadMV2Jet_btagbin;    //!

    TH1F *cutflow_hist; //!
    TH1F *cutflow_hist_noDalitz; //!
    TH1F *cutflow_hist_weighted; //!
    TH1F *cutflow_hist_noDalitz_weighted; //!
    float lumi_mc16;    //!

ULong64_t eventNumber;    //!
float XSWeight;    //!

float HGamWeight; //!

int yyHF_leadjet_truthlabel; //!
int yyHF_subleadjet_truthlabel; //!
int yyHF_leadjet_btagbin; //!
int yyHF_subleadjet_btagbin; //!
int yyHF_Njet_central; //!
float yyHFjj_weight; //!
float yyHFj_weight; //!
float yyHF_met; //!
int yyHF_nelectron; //!
int yyHF_nmuon; //!
bool isPassed; //!
int yyHF_cutFlow; //!
float m_yy; //!
float m_yyjj; //!
float pT_yy; //!
float yyHF_subleadjet_pt; //!
float yyHF_subleadjet_phi; //!
float yyHF_subleadjet_m; //!
float yyHF_subleadjet_eta; //!
float yyHF_leadjet_pt; //!
float yyHF_leadjet_phi; //!
float yyHF_leadjet_m; //!
float yyHF_leadjet_eta; //!
int Truth_yyHF_Njet_central; //!
int Truth_yyHF_N_bjets; //!
int Truth_yyHF_N_cjets; //!
int Truth_yyHF_cutFlow; //!
int Truth_yyHF_jcat; //!
int Truth_yyHF_jjcat; //!
int Truth_yyHF_nelectron; //!
int Truth_yyHF_nmuon; //!
float Truth_yyHF_met; //!




float FT_EFF_Eigen_Light_0__1up_HGamWeight; //!
int FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_truthlabel; //!
int FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_truthlabel; //!
int FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_btagbin; //!
int FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_btagbin; //!
int FT_EFF_Eigen_Light_0__1up_yyHF_Njet_central; //!
float FT_EFF_Eigen_Light_0__1up_yyHFjj_weight; //!
float FT_EFF_Eigen_Light_0__1up_yyHFj_weight; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_met; //!
int FT_EFF_Eigen_Light_0__1up_yyHF_nelectron; //!
int FT_EFF_Eigen_Light_0__1up_yyHF_nmuon; //!
bool FT_EFF_Eigen_Light_0__1up_isPassed; //!
int FT_EFF_Eigen_Light_0__1up_yyHF_cutFlow; //!
float FT_EFF_Eigen_Light_0__1up_m_yy; //!
float FT_EFF_Eigen_Light_0__1up_m_yyjj; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_pt; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_phi; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_m; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_eta; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_pt; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_phi; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_m; //!
float FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_eta; //!
float FT_EFF_Eigen_Light_1__1up_HGamWeight; //!
int FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_truthlabel; //!
int FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_truthlabel; //!
int FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_btagbin; //!
int FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_btagbin; //!
int FT_EFF_Eigen_Light_1__1up_yyHF_Njet_central; //!
float FT_EFF_Eigen_Light_1__1up_yyHFjj_weight; //!
float FT_EFF_Eigen_Light_1__1up_yyHFj_weight; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_met; //!
int FT_EFF_Eigen_Light_1__1up_yyHF_nelectron; //!
int FT_EFF_Eigen_Light_1__1up_yyHF_nmuon; //!
bool FT_EFF_Eigen_Light_1__1up_isPassed; //!
int FT_EFF_Eigen_Light_1__1up_yyHF_cutFlow; //!
float FT_EFF_Eigen_Light_1__1up_m_yy; //!
float FT_EFF_Eigen_Light_1__1up_m_yyjj; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_pt; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_phi; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_m; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_eta; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_pt; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_phi; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_m; //!
float FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_eta; //!
float FT_EFF_Eigen_Light_2__1up_HGamWeight; //!
int FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_truthlabel; //!
int FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_truthlabel; //!
int FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_btagbin; //!
int FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_btagbin; //!
int FT_EFF_Eigen_Light_2__1up_yyHF_Njet_central; //!
float FT_EFF_Eigen_Light_2__1up_yyHFjj_weight; //!
float FT_EFF_Eigen_Light_2__1up_yyHFj_weight; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_met; //!
int FT_EFF_Eigen_Light_2__1up_yyHF_nelectron; //!
int FT_EFF_Eigen_Light_2__1up_yyHF_nmuon; //!
bool FT_EFF_Eigen_Light_2__1up_isPassed; //!
int FT_EFF_Eigen_Light_2__1up_yyHF_cutFlow; //!
float FT_EFF_Eigen_Light_2__1up_m_yy; //!
float FT_EFF_Eigen_Light_2__1up_m_yyjj; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_pt; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_phi; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_m; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_eta; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_pt; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_phi; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_m; //!
float FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_eta; //!
float FT_EFF_Eigen_Light_3__1up_HGamWeight; //!
int FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_truthlabel; //!
int FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_truthlabel; //!
int FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_btagbin; //!
int FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_btagbin; //!
int FT_EFF_Eigen_Light_3__1up_yyHF_Njet_central; //!
float FT_EFF_Eigen_Light_3__1up_yyHFjj_weight; //!
float FT_EFF_Eigen_Light_3__1up_yyHFj_weight; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_met; //!
int FT_EFF_Eigen_Light_3__1up_yyHF_nelectron; //!
int FT_EFF_Eigen_Light_3__1up_yyHF_nmuon; //!
bool FT_EFF_Eigen_Light_3__1up_isPassed; //!
int FT_EFF_Eigen_Light_3__1up_yyHF_cutFlow; //!
float FT_EFF_Eigen_Light_3__1up_m_yy; //!
float FT_EFF_Eigen_Light_3__1up_m_yyjj; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_pt; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_phi; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_m; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_eta; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_pt; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_phi; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_m; //!
float FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_eta; //!
float FT_EFF_Eigen_Light_4__1up_HGamWeight; //!
int FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_truthlabel; //!
int FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_truthlabel; //!
int FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_btagbin; //!
int FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_btagbin; //!
int FT_EFF_Eigen_Light_4__1up_yyHF_Njet_central; //!
float FT_EFF_Eigen_Light_4__1up_yyHFjj_weight; //!
float FT_EFF_Eigen_Light_4__1up_yyHFj_weight; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_met; //!
int FT_EFF_Eigen_Light_4__1up_yyHF_nelectron; //!
int FT_EFF_Eigen_Light_4__1up_yyHF_nmuon; //!
bool FT_EFF_Eigen_Light_4__1up_isPassed; //!
int FT_EFF_Eigen_Light_4__1up_yyHF_cutFlow; //!
float FT_EFF_Eigen_Light_4__1up_m_yy; //!
float FT_EFF_Eigen_Light_4__1up_m_yyjj; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_pt; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_phi; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_m; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_eta; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_pt; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_phi; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_m; //!
float FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_eta; //!

float FT_EFF_Eigen_Light_0__1up_pT_yy; //!
float FT_EFF_Eigen_Light_1__1up_pT_yy; //!
float FT_EFF_Eigen_Light_2__1up_pT_yy; //!
float FT_EFF_Eigen_Light_3__1up_pT_yy; //!
float FT_EFF_Eigen_Light_4__1up_pT_yy; //!

    TTree *tree; //!
    TH1D *hist_cutflow; //!
    TH1D *hist_cutflow_noDalitz; //!
    TH1D *hist_cutflow_weighted; //!
    TH1D *hist_cutflow_noDalitz_weighted; //!

    // this is a standard constructor
    yyHFSkim ();


    EL::StatusCode TrackSelection ();

    void ResetVariables();
    mcTypeEnum m_mcType;
    void SetPeriod(int period) { if(period == 0)       m_mcType = mc16a;
                                 else if (period == 1) m_mcType = mc16d;
                                 else if (period == 2) m_mcType = mc16e;}

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
  ClassDef(yyHFSkim, 1);

};

#endif
// 

