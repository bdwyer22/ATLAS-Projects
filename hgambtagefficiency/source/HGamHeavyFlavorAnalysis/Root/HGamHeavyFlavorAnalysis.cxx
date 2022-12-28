#include <AsgTools/MessageCheck.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <HGamHeavyFlavorAnalysis/HGamHeavyFlavorAnalysis.h>
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/Message.h"
#include <typeinfo>
#include <TH1.h>


/// Heper macro for checking xAOD::TReturnCode return values
#define EL_RETURN_CHECK( CONTEXT, EXP )			\
  do {							\
    if( ! EXP.isSuccess() ) {				\
    Error( CONTEXT,                                     \
    XAOD_MESSAGE( "Failed to execute: %s" ),            \
	   #EXP );                                      \
      return EL::StatusCode::FAILURE;			\
    }							\
  } while( false )

// this is needed to distribute the algorithm to the workers
ClassImp(HGamHeavyFlavorAnalysis)


HGamHeavyFlavorAnalysis :: HGamHeavyFlavorAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().


}



EL::StatusCode HGamHeavyFlavorAnalysis :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  job.useXAOD ();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamHeavyFlavorAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // myclass = new TH1F(...);
  tree = new TTree("hgamvariables", "tree with hgam variables per event");
  
  tree->Branch("Truth_bjets_hard_to_hgam_z",     &Truth_bjets_hard_to_hgam_z);
  tree->Branch("Truth_bjets_hard_to_truth_z",    &Truth_bjets_hard_to_truth_z);
  tree->Branch("Truth_bjets_hgam_to_truth_z",    &Truth_bjets_hgam_to_truth_z);

  tree->Branch("HF_bjets_hard_to_hgam_z",     &HF_bjets_hard_to_hgam_z);
  tree->Branch("HF_bjets_hard_to_truth_z",    &HF_bjets_hard_to_truth_z);
  tree->Branch("HF_bjets_hgam_to_truth_z",    &HF_bjets_hgam_to_truth_z);

  tree->Branch("passed_first_cuts", &passed_first_cuts);
  tree->Branch("passed_first_cuts_event", &passed_first_cuts_event);
  tree->Branch("passed_second_cuts", &passed_second_cuts);
  tree->Branch("passed_second_cuts_event", &passed_second_cuts_event);

  tree->Branch("sameIDyyNN",  &sameIDyyNN);
  tree->Branch("sameIDyyNN_good",  &sameIDyyNN_good);
  tree->Branch("sameIDyyNN_wrong",  &sameIDyyNN_wrong);
  tree->Branch("diffIDyyNN",  &diffIDyyNN);
  tree->Branch("diffIDyyNN_yyNNgood",  &diffIDyyNN_yyNNgood);
  tree->Branch("diffIDyyNN_IDgood",  &diffIDyyNN_IDgood);
  tree->Branch("diffIDyyNN_wrong",  &diffIDyyNN_wrong);

  // tree->Branch("dz_samewrong_IDtruth" , &dz_samewrong_IDtruth);
  tree->Branch("dz_samewrong_yytruth" , &dz_samewrong_yytruth);
  tree->Branch("dz_samegood_yytruth" , &dz_samegood_yytruth);
  tree->Branch("dz_diffIDgood_yytruth" , &dz_diffIDgood_yytruth);
  tree->Branch("dz_diffyyNNgood_yytruth" , &dz_diffyyNNgood_yytruth);
  tree->Branch("dz_diffwrong_yytruth" , &dz_diffwrong_yytruth);


  hist_cutflow = new TH1I("hist_cutflow", "hist_cutflow", 6, 0, 6);

  hist_cutflow->GetXaxis()->SetBinLabel(1, "photons");
  hist_cutflow->GetXaxis()->SetBinLabel(2, "isolate");
  hist_cutflow->GetXaxis()->SetBinLabel(3, "tight");
  hist_cutflow->GetXaxis()->SetBinLabel(4, "relpt");
  hist_cutflow->GetXaxis()->SetBinLabel(5, "bjet");
  hist_cutflow->GetXaxis()->SetBinLabel(6, "pass");

  // hist_samegood_alljets = new TH2F("hist_samegood_alljets", "hist_samegood_alljets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // hist_samewrong_alljets = new TH2F("hist_samewrong_alljets", "hist_samewrong_alljets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // hist_diff_IDgood_alljets = new TH2F("hist_diff_IDgood_alljets", "hist_diff_IDgood_alljets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // hist_diff_yyNNgood_alljets = new TH2F("hist_diff_yyNNgood_alljets", "hist_diff_yyNNgood_alljets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // hist_diffwrong_alljets = new TH2F("hist_diffwrong_alljets", "hist_diffwrong_alljets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);

  // hist_samegood_btaggedjets = new TH2F("hist_samegood_btaggedjets", "hist_samegood_btaggedjets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // hist_samewrong_btaggedjets = new TH2F("hist_samewrong_btaggedjets", "hist_samewrong_btaggedjets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // hist_diff_IDgood_btaggedjets = new TH2F("hist_diff_IDgood_btaggedjets", "hist_diff_IDgood_btaggedjets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // hist_diff_yyNNgood_btaggedjets = new TH2F("hist_diff_yyNNgood_btaggedjets", "hist_diff_yyNNgood_btaggedjets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // hist_diffwrong_btaggedjets = new TH2F("hist_diffwrong_btaggedjets", "hist_diffwrong_btaggedjets;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  
  hist_samegood_alljets = new TH2F("hist_samegood_alljets", "hist_samegood_alljets;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_alljets = new TH2F("hist_samewrong_alljets", "hist_samewrong_alljets;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_alljets = new TH2F("hist_diff_IDgood_alljets", "hist_diff_IDgood_alljets;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_alljets = new TH2F("hist_diff_yyNNgood_alljets", "hist_diff_yyNNgood_alljets;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_alljets = new TH2F("hist_diffwrong_alljets", "hist_diffwrong_alljets;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);

  hist_samegood_alljets_multijet = new TH2F("hist_samegood_alljets_multijet", "hist_samegood_alljets_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_alljets_multijet = new TH2F("hist_samewrong_alljets_multijet", "hist_samewrong_alljets_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_alljets_multijet = new TH2F("hist_diff_IDgood_alljets_multijet", "hist_diff_IDgood_alljets_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_alljets_multijet = new TH2F("hist_diff_yyNNgood_alljets_multijet", "hist_diff_yyNNgood_alljets_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_alljets_multijet = new TH2F("hist_diffwrong_alljets_multijet", "hist_diffwrong_alljets_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);

  hist_samegood_alljets_singlejet = new TH2F("hist_samegood_alljets_singlejet", "hist_samegood_alljets_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_alljets_singlejet = new TH2F("hist_samewrong_alljets_singlejet", "hist_samewrong_alljets_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_alljets_singlejet = new TH2F("hist_diff_IDgood_alljets_singlejet", "hist_diff_IDgood_alljets_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_alljets_singlejet = new TH2F("hist_diff_yyNNgood_alljets_singlejet", "hist_diff_yyNNgood_alljets_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_alljets_singlejet = new TH2F("hist_diffwrong_alljets_singlejet", "hist_diffwrong_alljets_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);

  hist_samegood_btaggedjets_70 = new TH2F("hist_samegood_btaggedjets_70", "hist_samegood_btaggedjets_70;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_btaggedjets_70 = new TH2F("hist_samewrong_btaggedjets_70", "hist_samewrong_btaggedjets_70;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_btaggedjets_70 = new TH2F("hist_diff_IDgood_btaggedjets_70", "hist_diff_IDgood_btaggedjets_70;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_btaggedjets_70 = new TH2F("hist_diff_yyNNgood_btaggedjets_70", "hist_diff_yyNNgood_btaggedjets_70;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_btaggedjets_70 = new TH2F("hist_diffwrong_btaggedjets_70", "hist_diffwrong_btaggedjets_70;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  
  hist_samegood_btaggedjets_70_singlejet = new TH2F("hist_samegood_btaggedjets_70_singlejet", "hist_samegood_btaggedjets_70_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_btaggedjets_70_singlejet = new TH2F("hist_samewrong_btaggedjets_70_singlejet", "hist_samewrong_btaggedjets_70_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_btaggedjets_70_singlejet = new TH2F("hist_diff_IDgood_btaggedjets_70_singlejet", "hist_diff_IDgood_btaggedjets_70_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_btaggedjets_70_singlejet = new TH2F("hist_diff_yyNNgood_btaggedjets_70_singlejet", "hist_diff_yyNNgood_btaggedjets_70_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_btaggedjets_70_singlejet = new TH2F("hist_diffwrong_btaggedjets_70_singlejet", "hist_diffwrong_btaggedjets_70_singlejet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);

  hist_samegood_btaggedjets_70_multijet = new TH2F("hist_samegood_btaggedjets_70_multijet", "hist_samegood_btaggedjets_70_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_btaggedjets_70_multijet = new TH2F("hist_samewrong_btaggedjets_70_multijet", "hist_samewrong_btaggedjets_70_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_btaggedjets_70_multijet = new TH2F("hist_diff_IDgood_btaggedjets_70_multijet", "hist_diff_IDgood_btaggedjets_70_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_btaggedjets_70_multijet = new TH2F("hist_diff_yyNNgood_btaggedjets_70_multijet", "hist_diff_yyNNgood_btaggedjets_70_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_btaggedjets_70_multijet = new TH2F("hist_diffwrong_btaggedjets_70_multijet", "hist_diffwrong_btaggedjets_70_multijet;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);

  hist_samegood_btaggedjets_77 = new TH2F("hist_samegood_btaggedjets_77", "hist_samegood_btaggedjets_77;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_btaggedjets_77 = new TH2F("hist_samewrong_btaggedjets_77", "hist_samewrong_btaggedjets_77;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_btaggedjets_77 = new TH2F("hist_diff_IDgood_btaggedjets_77", "hist_diff_IDgood_btaggedjets_77;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_btaggedjets_77 = new TH2F("hist_diff_yyNNgood_btaggedjets_77", "hist_diff_yyNNgood_btaggedjets_77;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_btaggedjets_77 = new TH2F("hist_diffwrong_btaggedjets_77", "hist_diffwrong_btaggedjets_77;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);


  hist_samegood_btaggedjets_85 = new TH2F("hist_samegood_btaggedjets_85", "hist_samegood_btaggedjets_85;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_btaggedjets_85 = new TH2F("hist_samewrong_btaggedjets_85", "hist_samewrong_btaggedjets_85;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_btaggedjets_85 = new TH2F("hist_diff_IDgood_btaggedjets_85", "hist_diff_IDgood_btaggedjets_85;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_btaggedjets_85 = new TH2F("hist_diff_yyNNgood_btaggedjets_85", "hist_diff_yyNNgood_btaggedjets_85;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_btaggedjets_85 = new TH2F("hist_diffwrong_btaggedjets_85", "hist_diffwrong_btaggedjets_85;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);


  hist_samegood_btaggedjets_60 = new TH2F("hist_samegood_btaggedjets_60", "hist_samegood_btaggedjets_60;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_samewrong_btaggedjets_60 = new TH2F("hist_samewrong_btaggedjets_60", "hist_samewrong_btaggedjets_60;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_IDgood_btaggedjets_60 = new TH2F("hist_diff_IDgood_btaggedjets_60", "hist_diff_IDgood_btaggedjets_60;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diff_yyNNgood_btaggedjets_60 = new TH2F("hist_diff_yyNNgood_btaggedjets_60", "hist_diff_yyNNgood_btaggedjets_60;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);
  hist_diffwrong_btaggedjets_60 = new TH2F("hist_diffwrong_btaggedjets_60", "hist_diffwrong_btaggedjets_60;p_{T} [GeV];|#eta|", ptbins, ptedges, etabins, etaedges);


  eff_samegood = new TEfficiency("eff_samegood","my eff_samegood;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  eff_samewrong = new TEfficiency("eff_samewrong","my eff_samewrong;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);

  eff_diff_IDgood = new TEfficiency("eff_diff_IDgood","my eff_diff_IDgood;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  eff_diff_yyNNgood = new TEfficiency("eff_diff_yyNNgood","my eff_diff_yyNNgood;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  eff_diff_wrong = new TEfficiency("eff_diff_wrong","my eff_diff_wrong;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);

  // eff_samegood = new TH2F("eff_samegood","my eff_samegood;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // eff_samewrong = new TH2F("eff_samewrong","my eff_samewrong;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);

  // eff_diff_IDgood = new TH2F("eff_diff_IDgood","my eff_diff_IDgood;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // eff_diff_yyNNgood = new TH2F("eff_diff_yyNNgood","my eff_diff_yyNNgood;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);
  // eff_diff_wrong = new TH2F("eff_diff_wrong","my eff_diff_wrong;p_{T} [GeV];|#eta|", 9, 25, 250, 2, 0, 2.5);



  wk()->addOutput(tree);
  wk()->addOutput(hist_cutflow);
  
  wk()->addOutput(hist_samegood_alljets);
  wk()->addOutput(hist_samewrong_alljets);
  wk()->addOutput(hist_diff_IDgood_alljets);
  wk()->addOutput(hist_diff_yyNNgood_alljets);
  wk()->addOutput(hist_diffwrong_alljets);  

  wk()->addOutput(hist_samegood_alljets_multijet);
  wk()->addOutput(hist_samewrong_alljets_multijet);
  wk()->addOutput(hist_diff_IDgood_alljets_multijet);
  wk()->addOutput(hist_diff_yyNNgood_alljets_multijet);
  wk()->addOutput(hist_diffwrong_alljets_multijet);  
  
  wk()->addOutput(hist_samegood_alljets_singlejet);
  wk()->addOutput(hist_samewrong_alljets_singlejet);
  wk()->addOutput(hist_diff_IDgood_alljets_singlejet);
  wk()->addOutput(hist_diff_yyNNgood_alljets_singlejet);
  wk()->addOutput(hist_diffwrong_alljets_singlejet);  
  
  wk()->addOutput(hist_samegood_btaggedjets_77);
  wk()->addOutput(hist_samewrong_btaggedjets_77);
  wk()->addOutput(hist_diff_IDgood_btaggedjets_77);
  wk()->addOutput(hist_diff_yyNNgood_btaggedjets_77);
  wk()->addOutput(hist_diffwrong_btaggedjets_77);

  wk()->addOutput(hist_samegood_btaggedjets_70);
  wk()->addOutput(hist_samewrong_btaggedjets_70);
  wk()->addOutput(hist_diff_IDgood_btaggedjets_70);
  wk()->addOutput(hist_diff_yyNNgood_btaggedjets_70);
  wk()->addOutput(hist_diffwrong_btaggedjets_70);

  wk()->addOutput(hist_samegood_btaggedjets_70_singlejet);
  wk()->addOutput(hist_samewrong_btaggedjets_70_singlejet);
  wk()->addOutput(hist_diff_IDgood_btaggedjets_70_singlejet);
  wk()->addOutput(hist_diff_yyNNgood_btaggedjets_70_singlejet);
  wk()->addOutput(hist_diffwrong_btaggedjets_70_singlejet);

  wk()->addOutput(hist_samegood_btaggedjets_70_multijet);
  wk()->addOutput(hist_samewrong_btaggedjets_70_multijet);
  wk()->addOutput(hist_diff_IDgood_btaggedjets_70_multijet);
  wk()->addOutput(hist_diff_yyNNgood_btaggedjets_70_multijet);
  wk()->addOutput(hist_diffwrong_btaggedjets_70_multijet);

  wk()->addOutput(hist_samegood_btaggedjets_85);
  wk()->addOutput(hist_samewrong_btaggedjets_85);
  wk()->addOutput(hist_diff_IDgood_btaggedjets_85);
  wk()->addOutput(hist_diff_yyNNgood_btaggedjets_85);
  wk()->addOutput(hist_diffwrong_btaggedjets_85);

  wk()->addOutput(hist_samegood_btaggedjets_60);
  wk()->addOutput(hist_samewrong_btaggedjets_60);
  wk()->addOutput(hist_diff_IDgood_btaggedjets_60);
  wk()->addOutput(hist_diff_yyNNgood_btaggedjets_60);
  wk()->addOutput(hist_diffwrong_btaggedjets_60);

  wk()->addOutput(eff_samegood);
  wk()->addOutput(eff_samewrong);
  wk()->addOutput(eff_diff_IDgood);
  wk()->addOutput(eff_diff_yyNNgood);
  wk()->addOutput(eff_diff_wrong);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamHeavyFlavorAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  if (isData != true){

    TIter keyList(wk()->inputFile()->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)keyList())) {
      TH1 *h = (TH1*)key->ReadObj();
      TString histname(h->GetName());
      // std::cerr << "all histname " << histname << std::endl;
      if (histname.Contains("noDalitz_weighted")){
        std::cerr << "cutflow name:  " << histname << std::endl;
        cutflow_hist = (TH1F*)key->ReadObj();
      }

    }

    sum_weights = ((cutflow_hist->GetBinContent(1) / cutflow_hist->GetBinContent(2)) * cutflow_hist->GetBinContent(3));
    std::cout << cutflow_hist->GetName() << std::endl;
  }

  std::cout << "Sum_weights = " << sum_weights << std::endl;

  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamHeavyFlavorAnalysis :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamHeavyFlavorAnalysis :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  xAOD::TEvent* event = wk()->xaodEvent();
  m_eventCounter = 0;
  // GeV = 0.001;

  // as a check, let's see the number of events in our xAOD
  Warning("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamHeavyFlavorAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  xAOD::TEvent* event = wk()->xaodEvent();
  m_eventCounter++;
  ResetVariables();

  m_eventInfoCont =0;
  EL_RETURN_CHECK("execute()",event->retrieve( m_eventInfoCont, "EventInfo"));
  
  // const xAOD::JetContainer* pflowjets = NULL;
  // if (!event->retrieve(pflowjets, "HGamAntiKt4EMTopoJets").isSuccess()) {
  //   Error("execute()", "Failed to retrieve pflowjets. Exiting.");
  //   return EL::StatusCode::FAILURE;
  // }

  const xAOD::EventInfo *HGamEventInfo = NULL;
  if (! event->retrieve(HGamEventInfo, "HGamEventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::EventInfo *HGamTruthEventInfo = NULL;
  if (! event->retrieve(HGamTruthEventInfo, "HGamTruthEventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamTruthEventInfo. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::JetContainer *TruthJets = NULL;
  if (! event->retrieve(TruthJets, "HGamAntiKt4TruthWZJets").isSuccess()) {
    Error("execute()", "Failed to retrieve TruthJets. Exiting.");
    return EL::StatusCode::FAILURE;
  }
  const xAOD::MuonContainer *HGamMuons = NULL;
  if (! event->retrieve(HGamMuons, "HGamMuons").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamMuons. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::ElectronContainer *HGamElectrons = NULL;
  if (! event->retrieve(HGamElectrons, "HGamElectrons").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamElectrons. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::PhotonContainer* HGamPhotons = NULL;
  if (! event->retrieve(HGamPhotons, "HGamPhotons").isSuccess()) {
    Error("execute()", "Failed to retrieve HgamPhotons. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::JetContainer *topojets = NULL;
  if (! event->retrieve(topojets, "HGamAntiKt4EMTopoJets").isSuccess()) {
    Error("execute()", "Failed to retrieve topojets. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  if (isMCa == true){lumi_mc16 = 36205.26;}// sum_weights = 104724945.164;}
  if (isMCd == true){lumi_mc16 = 44307.4;}// sum_weights = 131279689.835;}
  if (isMCe == true){lumi_mc16 = 58450.1;}// sum_weights = 35667314.9538;}
  // if (isMCde == true){lumi_mc16 = 44307.4 + 58450.1;}
  
  eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
          * HGamEventInfo->auxdataConst<float>("weight") 
          * HGamEventInfo->auxdataConst<float>("weightJvt")
          * lumi_mc16)
          / sum_weights);

  if (isData == true){eventweight = 1;}

  float m_yy = HGamEventInfo->auxdata<float>("m_yy");

  hgam_vertex_z = HGamEventInfo->auxdataConst<float>("selectedVertexZ");
  truth_vertex_z = HGamTruthEventInfo->auxdataConst<float>("vertexZ");
  hardest_vertex_z = HGamEventInfo->auxdataConst<float>("hardestVertexZ");

  int HiggsHF_N_bjets = HGamTruthEventInfo->auxdataConst<int>("HiggsHF_N_bjets");

  if (HiggsHF_N_bjets > 0){
    HF_bjets_hard_to_hgam_z = (abs(hardest_vertex_z - hgam_vertex_z));
    HF_bjets_hard_to_truth_z = (abs(hardest_vertex_z - truth_vertex_z));
    HF_bjets_hgam_to_truth_z = (abs(hgam_vertex_z - truth_vertex_z));
  }

  isPassedPID = HGamEventInfo->auxdata<char>("isPassedPID");
  isPassedRelPtCuts = HGamEventInfo->auxdata<char>("isPassedRelPtCuts");
  isPassedIsolation = HGamEventInfo->auxdata<char>("isPassedIsolation");
  isPassedPreselection = HGamEventInfo->auxdata<char>("isPassedPreselection");
  isPassedTriggerMatch = HGamEventInfo->auxdata<char>("isPassedTriggerMatch");
  isPassed = HGamEventInfo->auxdata<char>("isPassed");

  // bool truthjet_b = false;
  int n_iso_photons = 0;
  int n_tight = 0;
  int n_iso = 0;
// std::cout << "BLS Start event" << std::endl;
  if (HGamPhotons->size() >= 2){
    for (auto photon: *HGamPhotons){
      if (photon->auxdataConst<char>("isIsoFixedCutLoose")){++n_iso;}
      if (photon->auxdataConst<char>("isTight")){++n_tight;}

      if (photon->auxdataConst<char>("isIsoFixedCutLoose") && photon->auxdataConst<char>("isTight")){
        ++n_iso_photons;
        // std::cout << "isotight photon" << std::endl;

        if (leading_photon == 0){
          leading_photon = 1;
          // std::cout << "leading" << std::endl;

          float lead_pt = photon->auxdataConst<float>("pt");
          float rel_pt = 0.35 * m_yy;
          // std::cout << lead_pt << " > "  << rel_pt << std::endl;

          if (lead_pt > rel_pt){
            passlead = true;
            // std::cout << "passlead" << std::endl;
          }
          else {passlead = false;}
        }
        else if (leading_photon == 1 && subleading_photon == 0 && passlead == true){
          subleading_photon = 1;
          // std::cout << "subleading" << std::endl;

          float sublead_pt = photon->auxdataConst<float>("pt");
          float rel_pt = 0.25 * m_yy;
          // std::cout << sublead_pt << " > "  << rel_pt << std::endl;
          if (sublead_pt > rel_pt){
            passsublead = true;
            // std::cout << "passsublead" << std::endl;
          }
          else {passsublead = false;}
        }
      }
    }
  }

  // else{std::cout << "no photons" << std::endl;}
  // std::cout << "n_iso_photons: " << n_iso_photons  << " out of " << HGamPhotons->size() << " total photons" << std::endl;
  // std::cout << "passlead && passsublead: " << passlead << " && " << passsublead << std::endl;

  // if ((HGamPhotons->size() >= 2) && (HGamElectrons->size() == 0) && (HGamMuons->size() == 0 )){
  //   for (auto jet : *TruthJets) {
  //     if (fabs(jet->eta()) > 2.5  || jet->pt() * 0.001 < 30){continue;}
  //     if (jet->auxdata<int>("HadronConeExclTruthLabelID") == 5){truthjet_b = true;}
  //   }
  // }
  int Njets = 0;
  for (auto jet : *topojets){
    if (fabs(jet->eta()) > 2.5  || jet->pt() * 0.001 < 30){continue;}
    ++Njets;
  }

  for (auto jet : *TruthJets) {
    if (fabs(jet->eta()) > 2.5  || jet->pt() * 0.001 < 30){continue;}
    if (jet->auxdata<int>("HadronConeExclTruthLabelID") == 5){passtruth = true;}
  }
  
  if (HGamPhotons->size() < 2){hist_cutflow->Fill(0);}
  else if (n_iso < 2){hist_cutflow->Fill(1);}
  else if (n_tight < 2){hist_cutflow->Fill(2);}
  else if (!passlead && !passsublead){hist_cutflow->Fill(3);}
  else if (!passtruth){hist_cutflow->Fill(4);}
  else {hist_cutflow->Fill(5);}

  if (passtruth){
    Truth_bjets_hard_to_hgam_z = (abs(hardest_vertex_z - hgam_vertex_z));
    Truth_bjets_hard_to_truth_z = (abs(hardest_vertex_z - truth_vertex_z));
    Truth_bjets_hgam_to_truth_z = (abs(hgam_vertex_z - truth_vertex_z));
  }

  // if ((HGamPhotons->size() >= 2) && n_iso_photons >= 2 && passlead && passsublead){passed_first_cuts = 2; 
  // std::cout << "passed_first_cuts? "  << passed_first_cuts<< std::endl;
  // } // 19207

  if (isPassedPID && isPassedRelPtCuts && isPassedIsolation && isPassedPreselection && isPassedTriggerMatch && isPassed) {passed_first_cuts_event = 1;}
  else {passed_first_cuts_event =0;}

  if (passlead && passsublead){passed_first_cuts = 1;} //2711481
  else {passed_first_cuts = 0;}

  if (passed_first_cuts==1 && passtruth == true){passed_second_cuts = 1;}
  else{passed_second_cuts = 0;} //40599
  
  if (passed_first_cuts_event==1 && passtruth == true){passed_second_cuts_event = 1;}
  else{passed_second_cuts_event = 0;} //40326

  // hgam_vertex_z = yyNN
  // truth_vertex_z = true
  // hardest_vertex_z = ID

if (passed_second_cuts == 1){
  if (hgam_vertex_z == hardest_vertex_z){
    sameIDyyNN = 1;
    if (fabs(hgam_vertex_z - truth_vertex_z) <= 0.3){
      bool pass;
      sameIDyyNN_good = 1;
      dz_samegood_yytruth = fabs(hgam_vertex_z - truth_vertex_z);
      for (auto jet: *topojets){
        if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 5){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 4 || jet->auxdata<int>("HadronConeExclTruthLabelID") == 5){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") == 4 || jet->auxdata<int>("HadronConeExclTruthLabelID") == 5){continue;}
        hist_samegood_alljets->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        if (Njets > 1){hist_samegood_alljets_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        else if (Njets == 1){hist_samegood_alljets_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_60")){
          hist_samegood_btaggedjets_60->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          pass = true;
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_70")){
          hist_samegood_btaggedjets_70->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          if (Njets > 1){hist_samegood_btaggedjets_70_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
          else if (Njets == 1){hist_samegood_btaggedjets_70_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_77")){
          hist_samegood_btaggedjets_77->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_85")){
          hist_samegood_btaggedjets_85->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        eff_samegood->Fill(pass, jet->pt() * 0.001, fabs(jet->eta()), eventweight);
      }
    }
    else{
      bool pass;
      sameIDyyNN_wrong = 1;
      dz_samewrong_yytruth = fabs(hgam_vertex_z - truth_vertex_z);
      dz_samewrong_IDtruth = fabs(hardest_vertex_z - truth_vertex_z);
      for (auto jet: *topojets){
        if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 5){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 4){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") == 4 || jet->auxdata<int>("HadronConeExclTruthLabelID") == 5){continue;}
        hist_samewrong_alljets->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        if (Njets > 1){hist_samewrong_alljets_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        else if (Njets == 1){hist_samewrong_alljets_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_60")){
          hist_samewrong_btaggedjets_60->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          pass = true;
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_70")){
          hist_samewrong_btaggedjets_70->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          if (Njets > 1){hist_samewrong_btaggedjets_70_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
          else if (Njets == 1){hist_samewrong_btaggedjets_70_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_77")){
          hist_samewrong_btaggedjets_77->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_85")){
          hist_samewrong_btaggedjets_85->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        eff_samewrong->Fill(pass, jet->pt() * 0.001, fabs(jet->eta()), eventweight);
      }
    }
  }

  else{
    diffIDyyNN = 1;
    if (fabs(hgam_vertex_z - truth_vertex_z) <= 0.3){
      diffIDyyNN_yyNNgood = 1;
      dz_diffyyNNgood_yytruth = fabs(hgam_vertex_z - truth_vertex_z);
      bool pass;
      for (auto jet: *topojets){
        if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 5){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 4){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") == 4 || jet->auxdata<int>("HadronConeExclTruthLabelID") == 5){continue;}
        hist_diff_yyNNgood_alljets->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        if (Njets > 1){hist_diff_yyNNgood_alljets_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        else if (Njets == 1){hist_diff_yyNNgood_alljets_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}

        if (jet->auxdata<char>("MV2c10_FixedCutBEff_60")){
          hist_diff_yyNNgood_btaggedjets_60->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          pass = true;
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_70")){
          hist_diff_yyNNgood_btaggedjets_70->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          if (Njets > 1){hist_diff_yyNNgood_btaggedjets_70_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
          else if (Njets == 1){hist_diff_yyNNgood_btaggedjets_70_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_77")){
          hist_diff_yyNNgood_btaggedjets_77->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_85")){
          hist_diff_yyNNgood_btaggedjets_85->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        eff_diff_yyNNgood->Fill(pass, jet->pt() * 0.001, fabs(jet->eta()), eventweight);
      }
    }
    else if (fabs(hardest_vertex_z - truth_vertex_z) <= 0.3){
      diffIDyyNN_IDgood = 1;
      dz_diffIDgood_yytruth = fabs(hgam_vertex_z - truth_vertex_z);
      bool pass;
      for (auto jet: *topojets){
        if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 5){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 4){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") == 4 || jet->auxdata<int>("HadronConeExclTruthLabelID") == 5){continue;}
        hist_diff_IDgood_alljets->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        if (Njets > 1){hist_diff_IDgood_alljets_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        else if (Njets == 1){hist_diff_IDgood_alljets_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}

        if (jet->auxdata<char>("MV2c10_FixedCutBEff_60")){
          hist_diff_IDgood_btaggedjets_60->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          pass = true;
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_70")){
          hist_diff_IDgood_btaggedjets_70->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          if (Njets > 1){hist_diff_IDgood_btaggedjets_70_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
          else if (Njets == 1){hist_diff_IDgood_btaggedjets_70_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_77")){
          hist_diff_IDgood_btaggedjets_77->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_85")){
          hist_diff_IDgood_btaggedjets_85->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        eff_diff_IDgood->Fill(pass, jet->pt() * 0.001, fabs(jet->eta()), eventweight);
      }
    }
    else{
      diffIDyyNN_wrong = 1;
      dz_diffwrong_yytruth = fabs(hgam_vertex_z - truth_vertex_z);
      bool pass;
      for (auto jet: *topojets){
        if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 5){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") != 4){continue;}
        // if (jet->pt() * 0.001 < 30 || !jet->auxdata<char>("passFJVT") || jet->auxdata<int>("HadronConeExclTruthLabelID") == 4 || jet->auxdata<int>("HadronConeExclTruthLabelID") == 5){continue;}
        hist_diffwrong_alljets->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        if (Njets > 1){hist_diffwrong_alljets_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        else if (Njets == 1){hist_diffwrong_alljets_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}

        if (jet->auxdata<char>("MV2c10_FixedCutBEff_60")){
          hist_diffwrong_btaggedjets_60->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          pass = true;
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_70")){
          hist_diffwrong_btaggedjets_70->Fill(jet->pt() * 0.001, fabs(jet->eta()));
          if (Njets > 1){hist_diffwrong_btaggedjets_70_multijet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
          else if (Njets == 1){hist_diffwrong_btaggedjets_70_singlejet->Fill(jet->pt() * 0.001, fabs(jet->eta()));}
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_77")){
          hist_diffwrong_btaggedjets_77->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        if (jet->auxdata<char>("MV2c10_FixedCutBEff_85")){
          hist_diffwrong_btaggedjets_85->Fill(jet->pt() * 0.001, fabs(jet->eta()));
        }
        eff_diff_wrong->Fill(pass, jet->pt() * 0.001, fabs(jet->eta()), eventweight);
      }
    }
  }
}


  tree->Fill();


  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamHeavyFlavorAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamHeavyFlavorAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  return EL::StatusCode::SUCCESS;
}


void HGamHeavyFlavorAnalysis::ResetVariables()
{
  Truth_bjets_hard_to_hgam_z = -999;
  Truth_bjets_hard_to_truth_z = -999;
  Truth_bjets_hgam_to_truth_z = -999;

  HF_bjets_hard_to_hgam_z = -999;
  HF_bjets_hard_to_truth_z = -999;
  HF_bjets_hgam_to_truth_z = -999;

  dz_samewrong_yytruth = -999;
  dz_samegood_yytruth = -999;
  dz_diffwrong_yytruth = -999;
  dz_diffIDgood_yytruth = -999;
  dz_diffyyNNgood_yytruth = -999;
  dz_samewrong_IDtruth = -999;
  
  passlead = false;
  passsublead = false;
  passtruth = false;
  leading_photon = 0;
  subleading_photon = 0;

  passed_second_cuts = 0;
  passed_second_cuts_event = 0;
  passed_first_cuts = 0;
  passed_first_cuts_event = 0;

  sameIDyyNN = 0;
  sameIDyyNN_good = 0;
  sameIDyyNN_wrong = 0;
  diffIDyyNN = 0;
  diffIDyyNN_yyNNgood = 0;
  diffIDyyNN_IDgood = 0;
  diffIDyyNN_wrong = 0;

}

EL::StatusCode HGamHeavyFlavorAnalysis :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.

  // eff_samegood->Fill(hist_samegood_btaggedjets, hist_samegood_alljets);
  // eff_samewrong->Fill(hist_samewrong_btaggedjets, hist_samewrong_alljets);
  // eff_diff_IDgood->Fill(hist_diff_IDgood_btaggedjets, hist_diff_IDgood_alljets);
  // eff_diff_yyNNgood->Fill(hist_diff_yyNNgood_btaggedjets, hist_diff_yyNNgood_alljets);
  // eff_diff_wrong->Fill(hist_diffwrong_btaggedjets, hist_diffwrong_alljets);

  // eff_samegood = new TEfficiency(hist_samegood_btaggedjets, hist_samegood_alljets);
  // eff_samewrong = new TEfficiency(hist_samewrong_btaggedjets, hist_samewrong_alljets);
  // eff_diff_IDgood = new TEfficiency(hist_diff_IDgood_btaggedjets, hist_diff_IDgood_alljets);
  // eff_diff_yyNNgood = new TEfficiency(hist_diff_yyNNgood_btaggedjets, hist_diff_yyNNgood_alljets);
  // eff_diff_wrong = new TEfficiency(hist_diffwrong_btaggedjets, hist_diffwrong_alljets);
  // wk()->addOutput(eff_samegood);
  // wk()->addOutput(eff_samewrong);
  // wk()->addOutput(eff_diff_IDgood);
  // wk()->addOutput(eff_diff_yyNNgood);
  // wk()->addOutput(eff_diff_wrong);

  hist_samegood_btaggedjets_77->Sumw2();       hist_samegood_btaggedjets_77->Divide(hist_samegood_alljets);
  hist_samewrong_btaggedjets_77->Sumw2();      hist_samewrong_btaggedjets_77->Divide(hist_samewrong_alljets);
  hist_diff_IDgood_btaggedjets_77->Sumw2();    hist_diff_IDgood_btaggedjets_77->Divide(hist_diff_IDgood_alljets);
  hist_diff_yyNNgood_btaggedjets_77->Sumw2();  hist_diff_yyNNgood_btaggedjets_77->Divide(hist_diff_yyNNgood_alljets);
  hist_diffwrong_btaggedjets_77->Sumw2();      hist_diffwrong_btaggedjets_77->Divide(hist_diffwrong_alljets);


  hist_samegood_btaggedjets_77->SetMaximum(1);      hist_samegood_btaggedjets_77->SetMinimum(0);
  hist_samewrong_btaggedjets_77->SetMaximum(1);     hist_samewrong_btaggedjets_77->SetMinimum(0);
  hist_diff_IDgood_btaggedjets_77->SetMaximum(1);   hist_diff_IDgood_btaggedjets_77->SetMinimum(0);
  hist_diff_yyNNgood_btaggedjets_77->SetMaximum(1); hist_diff_yyNNgood_btaggedjets_77->SetMinimum(0);
  hist_diffwrong_btaggedjets_77->SetMaximum(1);     hist_diffwrong_btaggedjets_77->SetMinimum(0);

  hist_samegood_btaggedjets_70->Sumw2();       hist_samegood_btaggedjets_70->Divide(hist_samegood_alljets);
  hist_samewrong_btaggedjets_70->Sumw2();      hist_samewrong_btaggedjets_70->Divide(hist_samewrong_alljets);
  hist_diff_IDgood_btaggedjets_70->Sumw2();    hist_diff_IDgood_btaggedjets_70->Divide(hist_diff_IDgood_alljets);
  hist_diff_yyNNgood_btaggedjets_70->Sumw2();  hist_diff_yyNNgood_btaggedjets_70->Divide(hist_diff_yyNNgood_alljets);
  hist_diffwrong_btaggedjets_70->Sumw2();      hist_diffwrong_btaggedjets_70->Divide(hist_diffwrong_alljets);

  hist_samegood_btaggedjets_70->SetMaximum(1);      hist_samegood_btaggedjets_70->SetMinimum(0);
  hist_samewrong_btaggedjets_70->SetMaximum(1);     hist_samewrong_btaggedjets_70->SetMinimum(0);
  hist_diff_IDgood_btaggedjets_70->SetMaximum(1);   hist_diff_IDgood_btaggedjets_70->SetMinimum(0);
  hist_diff_yyNNgood_btaggedjets_70->SetMaximum(1); hist_diff_yyNNgood_btaggedjets_70->SetMinimum(0);
  hist_diffwrong_btaggedjets_70->SetMaximum(1);     hist_diffwrong_btaggedjets_70->SetMinimum(0);

  hist_samegood_btaggedjets_70_singlejet->Sumw2();       hist_samegood_btaggedjets_70_singlejet->Divide(hist_samegood_alljets);
  hist_samewrong_btaggedjets_70_singlejet->Sumw2();      hist_samewrong_btaggedjets_70_singlejet->Divide(hist_samewrong_alljets);
  hist_diff_IDgood_btaggedjets_70_singlejet->Sumw2();    hist_diff_IDgood_btaggedjets_70_singlejet->Divide(hist_diff_IDgood_alljets);
  hist_diff_yyNNgood_btaggedjets_70_singlejet->Sumw2();  hist_diff_yyNNgood_btaggedjets_70_singlejet->Divide(hist_diff_yyNNgood_alljets);
  hist_diffwrong_btaggedjets_70_singlejet->Sumw2();      hist_diffwrong_btaggedjets_70_singlejet->Divide(hist_diffwrong_alljets);

  hist_samegood_btaggedjets_70_singlejet->SetMaximum(1);      hist_samegood_btaggedjets_70_singlejet->SetMinimum(0);
  hist_samewrong_btaggedjets_70_singlejet->SetMaximum(1);     hist_samewrong_btaggedjets_70_singlejet->SetMinimum(0);
  hist_diff_IDgood_btaggedjets_70_singlejet->SetMaximum(1);   hist_diff_IDgood_btaggedjets_70_singlejet->SetMinimum(0);
  hist_diff_yyNNgood_btaggedjets_70_singlejet->SetMaximum(1); hist_diff_yyNNgood_btaggedjets_70_singlejet->SetMinimum(0);
  hist_diffwrong_btaggedjets_70_singlejet->SetMaximum(1);     hist_diffwrong_btaggedjets_70_singlejet->SetMinimum(0);

  hist_samegood_btaggedjets_70_multijet->Sumw2();       hist_samegood_btaggedjets_70_multijet->Divide(hist_samegood_alljets);
  hist_samewrong_btaggedjets_70_multijet->Sumw2();      hist_samewrong_btaggedjets_70_multijet->Divide(hist_samewrong_alljets);
  hist_diff_IDgood_btaggedjets_70_multijet->Sumw2();    hist_diff_IDgood_btaggedjets_70_multijet->Divide(hist_diff_IDgood_alljets);
  hist_diff_yyNNgood_btaggedjets_70_multijet->Sumw2();  hist_diff_yyNNgood_btaggedjets_70_multijet->Divide(hist_diff_yyNNgood_alljets);
  hist_diffwrong_btaggedjets_70_multijet->Sumw2();      hist_diffwrong_btaggedjets_70_multijet->Divide(hist_diffwrong_alljets);

  hist_samegood_btaggedjets_70_multijet->SetMaximum(1);      hist_samegood_btaggedjets_70_multijet->SetMinimum(0);
  hist_samewrong_btaggedjets_70_multijet->SetMaximum(1);     hist_samewrong_btaggedjets_70_multijet->SetMinimum(0);
  hist_diff_IDgood_btaggedjets_70_multijet->SetMaximum(1);   hist_diff_IDgood_btaggedjets_70_multijet->SetMinimum(0);
  hist_diff_yyNNgood_btaggedjets_70_multijet->SetMaximum(1); hist_diff_yyNNgood_btaggedjets_70_multijet->SetMinimum(0);
  hist_diffwrong_btaggedjets_70_multijet->SetMaximum(1);     hist_diffwrong_btaggedjets_70_multijet->SetMinimum(0);

  hist_samegood_btaggedjets_60->Sumw2();       hist_samegood_btaggedjets_60->Divide(hist_samegood_alljets);
  hist_samewrong_btaggedjets_60->Sumw2();      hist_samewrong_btaggedjets_60->Divide(hist_samewrong_alljets);
  hist_diff_IDgood_btaggedjets_60->Sumw2();    hist_diff_IDgood_btaggedjets_60->Divide(hist_diff_IDgood_alljets);
  hist_diff_yyNNgood_btaggedjets_60->Sumw2();  hist_diff_yyNNgood_btaggedjets_60->Divide(hist_diff_yyNNgood_alljets);
  hist_diffwrong_btaggedjets_60->Sumw2();      hist_diffwrong_btaggedjets_60->Divide(hist_diffwrong_alljets);


  hist_samegood_btaggedjets_60->SetMaximum(1);      hist_samegood_btaggedjets_60->SetMinimum(0);
  hist_samewrong_btaggedjets_60->SetMaximum(1);     hist_samewrong_btaggedjets_60->SetMinimum(0);
  hist_diff_IDgood_btaggedjets_60->SetMaximum(1);   hist_diff_IDgood_btaggedjets_60->SetMinimum(0);
  hist_diff_yyNNgood_btaggedjets_60->SetMaximum(1); hist_diff_yyNNgood_btaggedjets_60->SetMinimum(0);
  hist_diffwrong_btaggedjets_60->SetMaximum(1);     hist_diffwrong_btaggedjets_60->SetMinimum(0);

  hist_samegood_btaggedjets_85->Sumw2();       hist_samegood_btaggedjets_85->Divide(hist_samegood_alljets);
  hist_samewrong_btaggedjets_85->Sumw2();      hist_samewrong_btaggedjets_85->Divide(hist_samewrong_alljets);
  hist_diff_IDgood_btaggedjets_85->Sumw2();    hist_diff_IDgood_btaggedjets_85->Divide(hist_diff_IDgood_alljets);
  hist_diff_yyNNgood_btaggedjets_85->Sumw2();  hist_diff_yyNNgood_btaggedjets_85->Divide(hist_diff_yyNNgood_alljets);
  hist_diffwrong_btaggedjets_85->Sumw2();      hist_diffwrong_btaggedjets_85->Divide(hist_diffwrong_alljets);


  hist_samegood_btaggedjets_85->SetMaximum(1);      hist_samegood_btaggedjets_85->SetMinimum(0);
  hist_samewrong_btaggedjets_85->SetMaximum(1);     hist_samewrong_btaggedjets_85->SetMinimum(0);
  hist_diff_IDgood_btaggedjets_85->SetMaximum(1);   hist_diff_IDgood_btaggedjets_85->SetMinimum(0);
  hist_diff_yyNNgood_btaggedjets_85->SetMaximum(1); hist_diff_yyNNgood_btaggedjets_85->SetMinimum(0);
  hist_diffwrong_btaggedjets_85->SetMaximum(1);     hist_diffwrong_btaggedjets_85->SetMinimum(0);



  return EL::StatusCode::SUCCESS;
}






