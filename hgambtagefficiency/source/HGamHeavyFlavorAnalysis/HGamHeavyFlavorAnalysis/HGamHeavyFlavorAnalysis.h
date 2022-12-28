#ifndef HGamHeavyFlavorAnalysis_MyxAODAnalysis_H
#define HGamHeavyFlavorAnalysis_MyxAODAnalysis_H
#include <EventLoop/Algorithm.h>

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TEfficiency.h>
#include <vector>
#include "EventLoop/OutputStream.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"

class HGamHeavyFlavorAnalysis : public EL::Algorithm
{


  int m_mu;    //!
  bool passed; //!
  float m_yy;  //!

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
    bool isMCa;
    bool isMCd;
    bool isMCe;
    bool isMCde;

    float Truth_bjets_hard_to_hgam_z;   //!
    float Truth_bjets_hard_to_truth_z;   //!
    float Truth_bjets_hgam_to_truth_z;   //!

    float HF_bjets_hard_to_hgam_z;   //!
    float HF_bjets_hard_to_truth_z;   //!
    float HF_bjets_hgam_to_truth_z;   //!

    float hgam_vertex_z; //!
    float truth_vertex_z; //!
    float hardest_vertex_z; //!

    TH1F *cutflow_hist; //!
    float sum_weights;  //!
    float lumi_mc16;    //!
    float eventweight;  //!

    bool passlead; //!
    bool passsublead; //!
    bool passtruth; //!


    bool isPassedPID; //!
    bool isPassedRelPtCuts; //!
    bool isPassedIsolation; //!
    bool isPassedTriggerMatch; //!
    bool isPassedPreselection; //!
    bool isPassed; //!


    int leading_photon; //!
    int subleading_photon; //!

    int passed_first_cuts; //!
    int passed_first_cuts_event; //!
    int passed_second_cuts; //!
    int passed_second_cuts_event; //!

    int sameIDyyNN; //!
    int sameIDyyNN_good; //!
    int sameIDyyNN_wrong; //!
    int diffIDyyNN; //!
    int diffIDyyNN_yyNNgood; //!
    int diffIDyyNN_IDgood; //!
    int diffIDyyNN_wrong; //!

    TTree *tree; //!
    TH1I *hist_cutflow; //!

    TH2F *hist_samegood_alljets; //!
    TH2F *hist_samewrong_alljets; //!
    TH2F *hist_diff_IDgood_alljets; //!
    TH2F *hist_diff_yyNNgood_alljets; //!
    TH2F *hist_diffwrong_alljets; //!

    TH2F *hist_samegood_alljets_multijet; //!
    TH2F *hist_samewrong_alljets_multijet; //!
    TH2F *hist_diff_IDgood_alljets_multijet; //!
    TH2F *hist_diff_yyNNgood_alljets_multijet; //!
    TH2F *hist_diffwrong_alljets_multijet; //!
    
    TH2F *hist_samegood_alljets_singlejet; //!
    TH2F *hist_samewrong_alljets_singlejet; //!
    TH2F *hist_diff_IDgood_alljets_singlejet; //!
    TH2F *hist_diff_yyNNgood_alljets_singlejet; //!
    TH2F *hist_diffwrong_alljets_singlejet; //!
    
    TH2F *hist_samegood_btaggedjets_70; //!
    TH2F *hist_samewrong_btaggedjets_70; //!
    TH2F *hist_diff_IDgood_btaggedjets_70; //!
    TH2F *hist_diff_yyNNgood_btaggedjets_70; //!
    TH2F *hist_diffwrong_btaggedjets_70; //!

    TH2F *hist_samegood_btaggedjets_70_singlejet; //!
    TH2F *hist_samewrong_btaggedjets_70_singlejet; //!
    TH2F *hist_diff_IDgood_btaggedjets_70_singlejet; //!
    TH2F *hist_diff_yyNNgood_btaggedjets_70_singlejet; //!
    TH2F *hist_diffwrong_btaggedjets_70_singlejet; //!

    TH2F *hist_samegood_btaggedjets_70_multijet; //!
    TH2F *hist_samewrong_btaggedjets_70_multijet; //!
    TH2F *hist_diff_IDgood_btaggedjets_70_multijet; //!
    TH2F *hist_diff_yyNNgood_btaggedjets_70_multijet; //!
    TH2F *hist_diffwrong_btaggedjets_70_multijet; //!

    TH2F *hist_samegood_btaggedjets_60; //!
    TH2F *hist_samewrong_btaggedjets_60; //!
    TH2F *hist_diff_IDgood_btaggedjets_60; //!
    TH2F *hist_diff_yyNNgood_btaggedjets_60; //!
    TH2F *hist_diffwrong_btaggedjets_60; //!

    TH2F *hist_samegood_btaggedjets_85; //!
    TH2F *hist_samewrong_btaggedjets_85; //!
    TH2F *hist_diff_IDgood_btaggedjets_85; //!
    TH2F *hist_diff_yyNNgood_btaggedjets_85; //!
    TH2F *hist_diffwrong_btaggedjets_85; //!

    TH2F *hist_samegood_btaggedjets_77; //!
    TH2F *hist_samewrong_btaggedjets_77; //!
    TH2F *hist_diff_IDgood_btaggedjets_77; //!
    TH2F *hist_diff_yyNNgood_btaggedjets_77; //!
    TH2F *hist_diffwrong_btaggedjets_77; //!

    TEfficiency *eff_samegood; //!
    TEfficiency *eff_samewrong; //!

    TEfficiency *eff_diff_IDgood; //!
    TEfficiency *eff_diff_yyNNgood; //!
    TEfficiency *eff_diff_wrong; //!

    double etaedges[3] = {0, 1.5, 2.5}; //!
    int etabins = 2; //!

    double ptedges[9] = {25, 50, 75, 100, 125, 150, 175, 200, 250}; //!
    int ptbins = 8; //!

    float dz_samewrong_yytruth; //!
    float dz_samewrong_IDtruth; //!
    float dz_samegood_yytruth; //!
    float dz_diffIDgood_yytruth; //!
    float dz_diffyyNNgood_yytruth; //!
    float dz_diffwrong_yytruth; //!

    // TH2F *eff_samegood; //!
    // TH2F *eff_samewrong; //!

    // TH2F *eff_diff_IDgood; //!
    // TH2F *eff_diff_yyNNgood; //!
    // TH2F *eff_diff_wrong; //!


    // this is a standard constructor
    HGamHeavyFlavorAnalysis ();


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
  ClassDef(HGamHeavyFlavorAnalysis, 1);
};

#endif
// 

