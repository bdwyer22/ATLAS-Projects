#ifndef HGamTestAnalysis_MyxAODAnalysis_H
#define HGamTestAnalysis_MyxAODAnalysis_H
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

class HGamTestAnalysis : public EL::Algorithm
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
    bool isMCa;
    bool isMCd;
    bool isMCe;
    bool isMCde;


    // float btagbin_LeadMV2Jet;        //!

    // TH1F *hist_LeadMV2Jet_btagbin;    //!

    TH1F *cutflow_hist; //!
    float sum_weights;  //!
    float lumi_mc16;    //!
    float eventweight;  //!





    TTree *tree; //!

    // this is a standard constructor
    HGamTestAnalysis ();


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
  ClassDef(HGamTestAnalysis, 1);

};

#endif
// 

