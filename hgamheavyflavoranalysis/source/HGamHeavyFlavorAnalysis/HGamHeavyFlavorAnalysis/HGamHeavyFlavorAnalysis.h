#ifndef HGamHeavyFlavorAnalysis_MyxAODAnalysis_H
#define HGamHeavyFlavorAnalysis_MyxAODAnalysis_H
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
#include "xAODTruth/TruthParticleContainer.h"

class HGamHeavyFlavorAnalysis : public EL::Algorithm
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

  // int mbins = 70;  //!
  // int mmin = 100;  //!
  // int mmax = 170;  //!

  int etabins = 50;   //!
  float etamin = -4;  //!
  float etamax = 4;   //!


  // int npflow30jetsperevent  = 0;      //!
  // int npflow30jetsperevent_fJVT  = 0; //!

  // float leadingpflow30jetpt = 0; //!



  // TLorentzVector topoTLVec;       //!
  // TLorentzVector pflow30TLVec_fJVT;  //!
  // TLorentzVector pflow30TLVec;       //!
  // TLorentzVector alljetTLVec;        //!

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
    bool isPassed; //!
    // bool isPowhegPy8EG_NNPDF30_VBFH125;
    // bool isPowhegPy8_NNLOPS_ggH125;
    // bool isPowhegPy8_WmH125J;
    // bool isPowhegPy8_WpH125J;
    // bool isPowhegPy8_ZH125J;
    // bool isPowhegPy8_ggZH125;
    // bool isPowhegPy8_bbH125;
    // bool isPowhegPy8_ttH125;
    // bool isaMCnloHwpp_tWH125_yt_plus1;

    // int n_EventNumber; //!
    // int n_RunNumber;   //!
    // int n_events;   //!

    float btagbin_LeadDL1Jet;        //!
    float truthlabel_LeadDL1Jet;     //!
    float event_weight;  //!
    float btag_weight;  //!

    int n_btag_0;   //!
    int n_btag_1;   //!
    int n_btag_2;   //!
    int n_btag_3;   //!
    int n_btag_4;   //!
    int n_btag_none;   //!

    int n_truthjet_b;   //!
    int n_truthjet_c;   //!
    int n_truthjet_l;   //!
    int n_truthjet_none;   //! 

    int n_truthevent_b;   //!
    int n_truthevent_c;   //!
    int n_truthevent_l;   //!
    int n_truthevent_none;   //! 

    int ncdisagree; //!
    int nbdisagree; //!

    int Njets_central; //!

    int n_cjets; //!
    int n_bjets; //! 
    int n_HFcjets; //!
    int n_HFbjets; //!
    // TString *truth_event_label; //!

    bool isb_event; //!
    bool isc_event; //!
    bool isnone_event; //!

    bool ispassed; //!

    bool pass_centralmax; //!
    bool pass_nphotons; //!
    bool pass_nelectrons; //!
    bool pass_nmuons; //!

    bool pass_truth_photons; //!
    bool pass_truth_electrons; //!
    bool pass_truth_muons; //!

    TH1F *hist_LeadDL1Jet_btagbin;    //!
    TH1F *hist_LeadDL1Jet_truthlabel; //!
    TH2F *hist_btagbin_truthjet;    //!
    TH2F *hist_btagbin_truthevent;    //!
    TH2F *hist_HFTool_btagbin_truthjet;    //!
    TH2F *hist_HFTool_btagbin_truthevent;    //!

    TH1I *hist_truth_cutflow; //!
    TH1I *hist_reco_cutflow; //!
    TH1I *hist_mismatch_b_cutflow; //!
    TH1I *hist_mismatch_c_cutflow; //!

    TH1F *cutflow_hist; //!
    TH1F *cutflow_hist_unweighted; //!
    TH1F *my_cutflow_hist; //!
    TH1F *my_cutflow_hist_unweighted; //!
    float sum_weights;  //!
    float lumi_mc16;    //!
    float eventweight;  //!
    float btag_eventweight; //!

    float weight_crossSectionBRfilterEff ; //!
    float weight_HGamEventInfoWeight ; //!
    float weight_weightJvt ; //!
    float weight_lumi ; //!
    float weight_sumweights ; //!
    float weight_totalweight ; //!
    float y1_pt; //!
    float y2_pt; //!
    float y1_eta; //!
    float y2_eta; //!
    float y1_phi; //!
    float y2_phi; //!
    int   PythiaHerwigMatch; //!

    TH2F *hist_nbjets; //!


    TTree *tree; //!

    // this is a standard constructor
    HGamHeavyFlavorAnalysis ();


    EL::StatusCode TrackSelection ();

    void ResetVariables();

    // void SetCutflow(std::string cutflow_flag) {cutflow = cutflow_flag;}
    // std::cout<<"SetCutflow:  " << SetCutflow << std::endl;

    void SetIsMCa(bool mca_flag) {isMCa = mca_flag;}
    void SetIsMCd(bool mcd_flag) {isMCd = mcd_flag;}
    void SetIsMCe(bool mce_flag) {isMCe = mce_flag;}
    void SetIsMCde(bool mcde_flag) {isMCde = mcde_flag;}
    void SetIsData(bool data_flag) {isData = data_flag;}

    // void SetIs_PowhegPy8EG_NNPDF30_VBFH125(bool PowhegPy8EG_NNPDF30_VBFH125_flag){ isPowhegPy8EG_NNPDF30_VBFH125 = PowhegPy8EG_NNPDF30_VBFH125_flag;}
    // void SetIs_PowhegPy8_NNLOPS_ggH125(bool PowhegPy8_NNLOPS_ggH125_flag){ isPowhegPy8_NNLOPS_ggH125 = PowhegPy8_NNLOPS_ggH125_flag;}
    // void SetIs_PowhegPy8_WmH125J(bool PowhegPy8_WmH125J_flag){ isPowhegPy8_WmH125J = PowhegPy8_WmH125J_flag;}
    // void SetIs_PowhegPy8_WpH125J(bool PowhegPy8_WpH125J_flag){ isPowhegPy8_WpH125J =PowhegPy8_WpH125J_flag;}
    // void SetIs_PowhegPy8_ZH125J(bool PowhegPy8_ZH125J_flag){ isPowhegPy8_ZH125J = PowhegPy8_ZH125J_flag;}
    // void SetIs_PowhegPy8_ggZH125(bool PowhegPy8_ggZH125_flag){ isPowhegPy8_ggZH125 = PowhegPy8_ggZH125_flag;}
    // void SetIs_PowhegPy8_bbH125(bool PowhegPy8_bbH125_flag){ isPowhegPy8_bbH125 = PowhegPy8_bbH125_flag;}
    // void SetIs_PowhegPy8_ttH125(bool PowhegPy8_ttH125_flag){ isPowhegPy8_ttH125 = PowhegPy8_ttH125_flag;}
    // void SetIs_aMCnloHwpp_tWH125_yt_plus1(bool aMCnloHwpp_tWH125_yt_plus1_flag){ isaMCnloHwpp_tWH125_yt_plus1 = aMCnloHwpp_tWH125_yt_plus1_flag;}

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

  // private:

  // const AtlasDetectorID* m_idHelper;
  // const PixelID* m_pixelId;  
  // const SCT_ID* m_sctId;  
  // const InDetDD::SiDetectorManager*  m_PIX_mgr;
  // const InDetDD::SiDetectorManager*  m_SCT_mgr;
};

#endif
// 

