#include <AsgTools/MessageCheck.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <HGamMxAODAnalysis/HGamMxAODAnalysis.h>
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
ClassImp(HGamMxAODAnalysis)


HGamMxAODAnalysis :: HGamMxAODAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().


}



EL::StatusCode HGamMxAODAnalysis :: setupJob (EL::Job& job)
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



EL::StatusCode HGamMxAODAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // myclass = new TH1F(...);
  tree = new TTree("hgamvariables", "tree with hgam variables per event");


  hist_j130_pt_015 = new TH1F("hist_j130_pt_015", "hist_j130_pt_015;p_{T};Events", ptbins, ptmin, ptmax);
  hist_j130_pt_1525 = new TH1F("hist_j130_pt_1525", "hist_j130_pt_1525;p_{T};Events", ptbins, ptmin, ptmax);
  hist_j130_pt_2535 = new TH1F("hist_j130_pt_2535", "hist_j130_pt_2535;p_{T};Events", ptbins, ptmin, ptmax);
  hist_j130_pt_3550 = new TH1F("hist_j130_pt_3550", "hist_j130_pt_3550;p_{T};Events", ptbins, ptmin, ptmax);
  hist_j130_pt_50  = new TH1F("hist_j130_pt_50", "hist_j130_pt_50;p_{T};Events", ptbins, ptmin, ptmax);

  hist_j130_y_015 = new TH1F("hist_j130_y_015", "hist_j130_y_015;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_1525 = new TH1F("hist_j130_y_1525", "hist_j130_y_1525;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_2535 = new TH1F("hist_j130_y_2535", "hist_j130_y_2535;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_3550 = new TH1F("hist_j130_y_3550", "hist_j130_y_3550;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_50  = new TH1F("hist_j130_y_50", "hist_j130_y_50;Rapidity;Events", ybins, ymin, ymax);

  hist_j130_pt_015_fJVT = new TH1F("hist_j130_pt_015_fJVT", "hist_j130_pt_015_fJVT;p_{T};Events", ptbins, ptmin, ptmax);
  hist_j130_pt_1525_fJVT = new TH1F("hist_j130_pt_1525_fJVT", "hist_j130_pt_1525_fJVT;p_{T};Events", ptbins, ptmin, ptmax);
  hist_j130_pt_2535_fJVT = new TH1F("hist_j130_pt_2535_fJVT", "hist_j130_pt_2535_fJVT;p_{T};Events", ptbins, ptmin, ptmax);
  hist_j130_pt_3550_fJVT = new TH1F("hist_j130_pt_3550_fJVT", "hist_j130_pt_3550_fJVT;p_{T};Events", ptbins, ptmin, ptmax);
  hist_j130_pt_50_fJVT = new TH1F("hist_j130_pt_50_fJVT", "hist_j130_pt_50_fJVT;p_{T};Events", ptbins, ptmin, ptmax);

  hist_j130_y_015_fJVT = new TH1F("hist_j130_y_015_fJVT", "hist_j130_y_015_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_1525_fJVT = new TH1F("hist_j130_y_1525_fJVT", "hist_j130_y_1525_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_2535_fJVT = new TH1F("hist_j130_y_2535_fJVT", "hist_j130_y_2535_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_3550_fJVT = new TH1F("hist_j130_y_3550_fJVT", "hist_j130_y_3550_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_50_fJVT = new TH1F("hist_j130_y_50_fJVT", "hist_j130_y_50_fJVT;Rapidity;Events", ybins, ymin, ymax);

  hist_pass_fJVT = new TH1F("hist_pass_fJVT", "hist_pass_fJVT;#eta;Events", 40, -4.0, 4.0);
  hist_fail_fJVT = new TH1F("hist_fail_fJVT", "hist_fail_fJVT;#eta;Events", 40, -4.0, 4.0);

  hist_alljet_pt = new TH1F("hist_alljet_pt", "hist_alljet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  hist_alljet_pt_fJVT = new TH1F("hist_alljet_p_fJVTt", "hist_alljet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  hist_alljet_eta = new TH1F("hist_alljet_eta", "hist_alljet_eta;Jet #eta;Events", etabins, etamin, etamax);
  hist_alljet_y = new TH1F("hist_alljet_y", "hist_alljet_y;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_fJVT = new TH1F("hist_alljet_y_fJVT", "hist_alljet_y_fJVT;Jet Rapidity;Events", ybins, ymin, ymax);

  hist_alljet_y_015 = new TH1F("hist_alljet_y_015", "hist_alljet_y_015;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_1525 = new TH1F("hist_alljet_y_1525", "hist_alljet_y_1525;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_2535 = new TH1F("hist_alljet_y_2535", "hist_alljet_y_2535;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_3550 = new TH1F("hist_alljet_y_3550", "hist_alljet_y_3550;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_50 = new TH1F("hist_alljet_y_50", "hist_alljet_y_50;Jet Rapidity;Events", ybins, ymin, ymax);

  hist_alljet_y_015_fJVT = new TH1F("hist_alljet_y_015_fJVT", "hist_alljet_y_015_fJVT;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_1525_fJVT = new TH1F("hist_alljet_y_1525_fJVT", "hist_alljet_y_1525_fJVT;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_2535_fJVT = new TH1F("hist_alljet_y_2535_fJVT", "hist_alljet_y_2535_fJVT;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_3550_fJVT = new TH1F("hist_alljet_y_3550_fJVT", "hist_alljet_y_3550_fJVT;Jet Rapidity;Events", ybins, ymin, ymax);
  hist_alljet_y_50_fJVT = new TH1F("hist_alljet_y_50_fJVT", "hist_alljet_y_50_fJVT;Jet Rapidity;Events", ybins, ymin, ymax);

  hist_alljet_pt_015 = new TH1F("hist_alljet_pt_015", "hist_alljet_pt_015;Jet p_{T};Events", ptbins, ptmin, ptmax);
  hist_alljet_pt_1525 = new TH1F("hist_alljet_pt_1525", "hist_alljet_pt_1525;Jet p_{T};Events", ptbins, ptmin, ptmax);
  hist_alljet_pt_2535 = new TH1F("hist_alljet_pt_2535", "hist_alljet_pt_2535;Jet p_{T};Events", ptbins, ptmin, ptmax);
  hist_alljet_pt_3550 = new TH1F("hist_alljet_pt_3550", "hist_alljet_pt_3550;Jet p_{T};Events", ptbins, ptmin, ptmax);
  hist_alljet_pt_50 = new TH1F("hist_alljet_pt_50", "hist_alljet_pt_50;Jet p_{T};Events", ptbins, ptmin, ptmax);

  hist_alljet_pt_015_fJVT = new TH1F("hist_alljet_pt_015_fJVT", "hist_alljet_pt_015_fJVT;Jet p_{T};Events", ptbins, ptmin, ptmax);
  hist_alljet_pt_1525_fJVT = new TH1F("hist_alljet_pt_1525_fJVT", "hist_alljet_pt_1525_fJVT;Jet p_{T};Events", ptbins, ptmin, ptmax);
  hist_alljet_pt_2535_fJVT = new TH1F("hist_alljet_pt_2535_fJVT", "hist_alljet_pt_2535_fJVT;Jet p_{T};Events", ptbins, ptmin, ptmax);
  hist_alljet_pt_3550_fJVT = new TH1F("hist_alljet_pt_3550_fJVT", "hist_alljet_pt_3550_fJVT;Jet p_{T};Events", ptbins, ptmin, ptmax);
  hist_alljet_pt_50_fJVT = new TH1F("hist_alljet_pt_50_fJVT", "hist_alljet_pt_50_fJVT;Jet p_{T};Events", ptbins, ptmin, ptmax);

  hist_forward_jet_pt = new TH1F("hist_forward_jet_pt", "hist_forward_jet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  hist_forward_jet_eta = new TH1F("hist_forward_jet_eta", "hist_forward_jet_eta;Jet #eta;Events", 28, 2.2, 5);
  hist_central_jet_pt = new TH1F("hist_central_jet_pt", "hist_central_jet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  hist_central_jet_eta = new TH1F("hist_central_jet_eta", "hist_central_jet_eta;Jet #eta;Events", etabins, etamin, etamax);

  hist_forward_jet_pt_fJVT = new TH1F("hist_forward_jet_pt_fJVT", "hist_forward_jet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  hist_forward_jet_eta_fJVT = new TH1F("hist_forward_jet_eta_fJVT", "hist_forward_jet_eta_fJVT;Jet #eta;Events", 28, 2.2, 5);
  hist_central_jet_pt_fJVT = new TH1F("hist_central_jet_pt_fJVT", "hist_central_jet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  hist_central_jet_eta_fJVT = new TH1F("hist_central_jet_eta_fJVT", "hist_central_jet_eta_fJVT;Jet #eta;Events", etabins, etamin, etamax);

  hist_n_jets = new TH1F("hist_n_jets", "hist_n_jets;Number of jets;Events", 7, 0, 7);
  hist_n_jets_fJVT = new TH1F("hist_n_jets_fJVT", "hist_n_jets_fJVT;Number of jets;Events", 7, 0, 7);

  // hist_pass_fJVT_HS = new TH1F("hist_pass_fJVT_HS", "hist_pass_fJVT;#eta;Events", 40, -4.0, 4.0);
  // hist_fail_fJVT_HS = new TH1F("hist_fail_fJVT_HS", "hist_fail_fJVT;#eta;Events", 40, -4.0, 4.0);

  // hist_pass_fJVT_notHS = new TH1F("hist_pass_fJVT_notHS", "hist_pass_fJVT;#eta;Events", 40, -4.0, 4.0);
  // hist_fail_fJVT_notHS = new TH1F("hist_fail_fJVT_notHS", "hist_fail_fJVT;#eta;Events", 40, -4.0, 4.0);

  // hist_alljet_pt_HS = new TH1F("hist_alljet_pt_HS", "hist_alljet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_alljet_pt_fJVT_HS = new TH1F("hist_alljet_pt_fJVT_HS  ", "hist_alljet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_alljet_eta_HS = new TH1F("hist_alljet_eta_HS", "hist_alljet_eta;Jet #eta;Events", etabins, etamin, etamax);

  // hist_forward_jet_pt_HS = new TH1F("hist_forward_jet_pt_HS", "hist_forward_jet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_forward_jet_eta_HS = new TH1F("hist_forward_jet_eta_HS", "hist_forward_jet_eta;Jet #eta;Events", 28, 2.2, 5);
  // hist_central_jet_pt_HS = new TH1F("hist_central_jet_pt_HS", "hist_central_jet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_central_jet_eta_HS = new TH1F("hist_central_jet_eta_HS", "hist_central_jet_eta;Jet #eta;Events", etabins, etamin, etamax);

  // hist_forward_jet_pt_fJVT_HS = new TH1F("hist_forward_jet_pt_fJVT_HS", "hist_forward_jet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_forward_jet_eta_fJVT_HS = new TH1F("hist_forward_jet_eta_fJVT_HS", "hist_forward_jet_eta_fJVT;Jet #eta;Events", 28, 2.2, 5);
  // hist_central_jet_pt_fJVT_HS = new TH1F("hist_central_jet_pt_fJVT_HS", "hist_central_jet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_central_jet_eta_fJVT_HS = new TH1F("hist_central_jet_eta_fJVT_HS", "hist_central_jet_eta_fJVT;Jet #eta;Events", etabins, etamin, etamax);

  // hist_alljet_pt_notHS = new TH1F("hist_alljet_pt_notHS", "hist_alljet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_alljet_pt_fJVT_notHS = new TH1F("hist_alljet_pt_fJVT_notHS  ", "hist_alljet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_alljet_eta_notHS = new TH1F("hist_alljet_eta_notHS", "hist_alljet_eta;Jet #eta;Events", etabins, etamin, etamax);

  // hist_forward_jet_pt_notHS = new TH1F("hist_forward_jet_pt_notHS", "hist_forward_jet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_forward_jet_eta_notHS = new TH1F("hist_forward_jet_eta_notHS", "hist_forward_jet_eta;Jet #eta;Events", 28, 2.2, 5);
  // hist_central_jet_pt_notHS = new TH1F("hist_central_jet_pt_notHS", "hist_central_jet_pt;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_central_jet_eta_notHS = new TH1F("hist_central_jet_eta_notHS", "hist_central_jet_eta;Jet #eta;Events", etabins, etamin, etamax);

  // hist_forward_jet_pt_fJVT_notHS = new TH1F("hist_forward_jet_pt_fJVT_notHS", "hist_forward_jet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_forward_jet_eta_fJVT_notHS = new TH1F("hist_forward_jet_eta_fJVT_notHS", "hist_forward_jet_eta_fJVT;Jet #eta;Events", 28, 2.2, 5);
  // hist_central_jet_pt_fJVT_notHS = new TH1F("hist_central_jet_pt_fJVT_notHS", "hist_central_jet_pt_fJVT;Jet p_{T};Events",ptbins, ptmin, ptmax);
  // hist_central_jet_eta_fJVT_notHS = new TH1F("hist_central_jet_eta_fJVT_notHS", "hist_central_jet_eta_fJVT;Jet #eta;Events", etabins, etamin, etamax);

  // hist_n_jets_HS = new TH1F("hist_n_jets_HS", "hist_n_jets;Number of jets;Events", 7, 0, 7);
  // hist_n_jets_fJVT_HS = new TH1F("hist_n_jets_fJVT_HS", "hist_n_jets_fJVT;Number of jets;Events", 7, 0, 7);

  // hist_n_jets_notHS = new TH1F("hist_n_jets_notHS", "hist_n_jets;Number of jets;Events", 7, 0, 7);
  // hist_n_jets_fJVT_notHS = new TH1F("hist_n_jets_fJVT_notHS", "hist_n_jets_fJVT;Number of jets;Events", 7, 0, 7);

  // hist_mu = TH1F("hist_mu", "hist_mu;#mu;Events;", 6, 0, 60);
  
  tree->Branch("pflow_j130_pt_15",     &pflow_j130_pt_15);
  tree->Branch("pflow_j130_pt_1525",   &pflow_j130_pt_1525);
  tree->Branch("pflow_j130_pt_2535",   &pflow_j130_pt_2535);
  tree->Branch("pflow_j130_pt_3550",   &pflow_j130_pt_3550);
  tree->Branch("pflow_j130_pt_50",     &pflow_j130_pt_50);

  tree->Branch("pflow_j130_y_15",     &pflow_j130_y_15);
  tree->Branch("pflow_j130_y_1525",   &pflow_j130_y_1525);
  tree->Branch("pflow_j130_y_2535",   &pflow_j130_y_2535);
  tree->Branch("pflow_j130_y_3550",   &pflow_j130_y_3550);
  tree->Branch("pflow_j130_y_50",     &pflow_j130_y_50);

  tree->Branch("pflow_j130_pt",     &pflow_j130_pt);
  tree->Branch("pflow_j130_eta",    &pflow_j130_eta);
  tree->Branch("pflow_j130_phi",    &pflow_j130_phi);
  tree->Branch("pflow_j130_m",      &pflow_j130_m);
  tree->Branch("pflow_j130_y",      &pflow_j130_y);

  tree->Branch("pflow_fjvt_fail_eta",  &pflow_fjvt_fail_eta);
  tree->Branch("pflow_fjvt_pass_eta",  &pflow_fjvt_pass_eta);

  tree->Branch("n_events",  &n_events);

  wk()->addOutput(tree);
  wk()->addOutput(hist_j130_pt_015);
  wk()->addOutput(hist_j130_pt_1525);
  wk()->addOutput(hist_j130_pt_2535);
  wk()->addOutput(hist_j130_pt_3550);
  wk()->addOutput(hist_j130_pt_50 );

  wk()->addOutput(hist_j130_y_015);
  wk()->addOutput(hist_j130_y_1525);
  wk()->addOutput(hist_j130_y_2535);
  wk()->addOutput(hist_j130_y_3550);
  wk()->addOutput(hist_j130_y_50 );

  wk()->addOutput(hist_j130_pt_015_fJVT);
  wk()->addOutput(hist_j130_pt_1525_fJVT);
  wk()->addOutput(hist_j130_pt_2535_fJVT);
  wk()->addOutput(hist_j130_pt_3550_fJVT);
  wk()->addOutput(hist_j130_pt_50_fJVT);

  wk()->addOutput(hist_j130_y_015_fJVT);
  wk()->addOutput(hist_j130_y_1525_fJVT);
  wk()->addOutput(hist_j130_y_2535_fJVT);
  wk()->addOutput(hist_j130_y_3550_fJVT);
  wk()->addOutput(hist_j130_y_50_fJVT);

  wk()->addOutput(hist_pass_fJVT);
  wk()->addOutput(hist_fail_fJVT);

  wk()->addOutput(hist_forward_jet_pt);
  wk()->addOutput(hist_forward_jet_eta);
  wk()->addOutput(hist_central_jet_pt);
  wk()->addOutput(hist_central_jet_eta);

  wk()->addOutput(hist_alljet_pt_fJVT);
  wk()->addOutput(hist_alljet_pt);
  wk()->addOutput(hist_alljet_eta);

  wk()->addOutput(hist_forward_jet_pt_fJVT);
  wk()->addOutput(hist_forward_jet_eta_fJVT);
  wk()->addOutput(hist_central_jet_pt_fJVT);
  wk()->addOutput(hist_central_jet_eta_fJVT);

  wk()->addOutput(hist_n_jets);
  wk()->addOutput(hist_n_jets_fJVT);

  wk()->addOutput(hist_alljet_y_015);
  wk()->addOutput(hist_alljet_y_1525);
  wk()->addOutput(hist_alljet_y_2535);
  wk()->addOutput(hist_alljet_y_3550);
  wk()->addOutput(hist_alljet_y_50);

  wk()->addOutput(hist_alljet_y_015_fJVT);
  wk()->addOutput(hist_alljet_y_1525_fJVT);
  wk()->addOutput(hist_alljet_y_2535_fJVT);
  wk()->addOutput(hist_alljet_y_3550_fJVT);
  wk()->addOutput(hist_alljet_y_50_fJVT);

  wk()->addOutput(hist_alljet_pt_015);
  wk()->addOutput(hist_alljet_pt_1525);
  wk()->addOutput(hist_alljet_pt_2535);
  wk()->addOutput(hist_alljet_pt_3550);
  wk()->addOutput(hist_alljet_pt_50);

  wk()->addOutput(hist_alljet_pt_015_fJVT);
  wk()->addOutput(hist_alljet_pt_1525_fJVT);
  wk()->addOutput(hist_alljet_pt_2535_fJVT);
  wk()->addOutput(hist_alljet_pt_3550_fJVT);
  wk()->addOutput(hist_alljet_pt_50_fJVT);

  // wk()->addOutput(hist_pass_fJVT_HS);
  // wk()->addOutput(hist_fail_fJVT_HS);

  // wk()->addOutput(hist_pass_fJVT_notHS);
  // wk()->addOutput(hist_fail_fJVT_notHS);

  // wk()->addOutput(hist_alljet_pt_HS);
  // wk()->addOutput(hist_alljet_pt_fJVT_HS);
  // wk()->addOutput(hist_alljet_eta_HS);

  // wk()->addOutput(hist_forward_jet_pt_HS);
  // wk()->addOutput(hist_forward_jet_eta_HS);

  // wk()->addOutput(hist_central_jet_pt_HS);
  // wk()->addOutput(hist_central_jet_eta_HS);

  // wk()->addOutput(hist_forward_jet_pt_fJVT_HS);
  // wk()->addOutput(hist_forward_jet_eta_fJVT_HS);

  // wk()->addOutput(hist_central_jet_pt_fJVT_HS);
  // wk()->addOutput(hist_central_jet_eta_fJVT_HS);

  // wk()->addOutput(hist_alljet_pt_notHS);
  // wk()->addOutput(hist_alljet_pt_fJVT_notHS);
  // wk()->addOutput(hist_alljet_eta_notHS);

  // wk()->addOutput(hist_forward_jet_pt_notHS);
  // wk()->addOutput(hist_forward_jet_eta_notHS);

  // wk()->addOutput(hist_central_jet_pt_notHS);
  // wk()->addOutput(hist_central_jet_eta_notHS);

  // wk()->addOutput(hist_forward_jet_pt_fJVT_notHS);
  // wk()->addOutput(hist_forward_jet_eta_fJVT_notHS);

  // wk()->addOutput(hist_central_jet_pt_fJVT_notHS);
  // wk()->addOutput(hist_central_jet_eta_fJVT_notHS);

  // wk()->addOutput(hist_n_jets_HS);
  // wk()->addOutput(hist_n_jets_fJVT_HS);

  // wk()->addOutput(hist_n_jets_notHS);
  // wk()->addOutput(hist_n_jets_fJVT_notHS);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamMxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  std::cout.precision(23);
  std::cout << "IS mc16a?: " << isMCa << std::endl;
  std::cout << "IS mc16d?: " << isMCd << std::endl;
  std::cout << "IS mc16e?: " << isMCe << std::endl;
  std::cout << "IS mc16de?: " << isMCde << std::endl;
  std::cout << "IS data?: " << isData << std::endl;
  std::cout<<  "Cutflow ggh: " << isggh << std::endl;
  std::cout<<  "Cutflow VBF: " << isVBF << std::endl;
  std::cout<<  "Cutflow Sherpa: " << isSherpa << std::endl;

  if (isData != true){
    if (isggh == true){cutflow_hist = (TH1F*)wk()->inputFile()->Get("CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted");sum_weights = 206557808;}
    if (isVBF == true){cutflow_hist = (TH1F*)wk()->inputFile()->Get("CutFlow_PowhegPy8_NNPDF30_VBFH125_noDalitz_weighted");sum_weights = 7073270;}
    if (isSherpa == true){cutflow_hist = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa2_myy_90_175_noDalitz_weighted");}
    // sum_weights = ((cutflow_hist->GetBinContent(1) / cutflow_hist->GetBinContent(2)) * cutflow_hist->GetBinContent(3));
  }
  //   cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_100_160_noDalitz_weighted");
  //   cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted");
  //   cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_160_250_noDalitz_weighted");
  //   cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa2_myy_90_175_noDalitz_weighted");
  //   // sum_weights = 104724945.164;

  std::cout << "Sum_weights = " << sum_weights << std::endl;

  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamMxAODAnalysis :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamMxAODAnalysis :: initialize ()
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



EL::StatusCode HGamMxAODAnalysis :: execute ()
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
  
  const xAOD::JetContainer* pflowjets = NULL;
  if (!event->retrieve(pflowjets, "HGamAntiKt4EMTopoJets").isSuccess()) {
    Error("execute()", "Failed to retrieve pflowjets. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  // const xAOD::JetContainer* topojets = NULL;
  // if (!event->retrieve(topojets, "HGamAntiKt4EMTopoJets").isSuccess()) {
  //   Error("execute()", "Failed to retrieve topojets. Exiting.");
  //   return EL::StatusCode::FAILURE;
  // }
  const xAOD::EventInfo *HGamEventInfo = NULL;
  if (! event->retrieve(HGamEventInfo, "HGamEventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  if (isMCa == true){lumi_mc16 = 36205.26;}
  if (isMCd == true){lumi_mc16 = 44307.4;}
  if (isMCe == true){lumi_mc16 = 58450.1;}

  if (isMCde == true){lumi_mc16 = 44307.4 + 58450.1;}
  
  eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
          * HGamEventInfo->auxdataConst<float>("weight") 
          * lumi_mc16)
          / sum_weights);

  if (isData == true){eventweight = 1;}
  // std::cout << "Event weight = " << eventweight << std::endl;

  passed = HGamEventInfo->auxdata<char>("isPassed");
  m_yy = HGamEventInfo->auxdata<float>("m_yy")*0.001;

  m_mu   = static_cast<int>(m_eventInfoCont->actualInteractionsPerCrossing());

  n_events = 1;

  if (passed){
    if (pflowjets->size() > 0){
      auto leadingjet = (*pflowjets)[0];
      if (leadingjet->pt() * 0.001 > 30){
        leadingpflow30jetpt = (leadingjet->pt() * 0.001);
        leadingpflow30jeteta = (leadingjet->eta());
        leadingpflow30jetphi = (leadingjet->phi());
        leadingpflow30jetm  = (leadingjet->m());
        //  Using TLorentzVector to find rapidity
        pflow30TLVec.SetPtEtaPhiM((leadingpflow30jetpt/0.001), leadingpflow30jeteta, leadingpflow30jetphi, leadingpflow30jetm);
        leadingpflow30jety = abs(pflow30TLVec.Rapidity());
        // std::cout<<"rapidity: "<<leadingpflow30jety<<std::endl;
        pflow_j130_pt = (leadingpflow30jetpt);
        pflow_j130_eta = (leadingpflow30jeteta);
        pflow_j130_phi = (leadingpflow30jetphi);
        pflow_j130_y = (leadingpflow30jety);
        pflow_j130_m = (leadingpflow30jetm);
        if (m_mu < 15){
          pflow_j130_pt_15 = (leadingpflow30jetpt);
          hist_j130_pt_015->Fill(leadingpflow30jetpt, eventweight);
          pflow_j130_y_15 = (leadingpflow30jety);
          hist_j130_y_015->Fill(leadingpflow30jety, eventweight);
        }
        else if (m_mu < 25){
          pflow_j130_pt_1525 = (leadingpflow30jetpt);
          hist_j130_pt_1525->Fill(leadingpflow30jetpt, eventweight);
          pflow_j130_y_1525 = (leadingpflow30jety);
          hist_j130_y_1525->Fill(leadingpflow30jety, eventweight);
        }
        else if (m_mu < 35){
          pflow_j130_pt_2535 = (leadingpflow30jetpt);
          hist_j130_pt_2535->Fill(leadingpflow30jetpt, eventweight);
          pflow_j130_y_2535 = (leadingpflow30jety);
          hist_j130_y_2535->Fill(leadingpflow30jety, eventweight);
        }
        else if (m_mu < 50){
          pflow_j130_pt_3550 = (leadingpflow30jetpt);
          hist_j130_pt_3550->Fill(leadingpflow30jetpt, eventweight);
          pflow_j130_y_3550 = (leadingpflow30jety);
          hist_j130_y_3550->Fill(leadingpflow30jety, eventweight);
        }
        else if (m_mu > 50){
          pflow_j130_pt_50 = (leadingpflow30jetpt);
          hist_j130_pt_50->Fill(leadingpflow30jetpt, eventweight);
          pflow_j130_y_50 = (leadingpflow30jety);
          hist_j130_y_50->Fill(leadingpflow30jety, eventweight);
        }
        if (leadingjet->auxdata<char>("passFJVT") == 1){
          leadingpflow30jetpt_fJVT = (leadingjet->pt() * 0.001);
          leadingpflow30jeteta_fJVT = (leadingjet->eta());
          leadingpflow30jetphi_fJVT = (leadingjet->phi());
          leadingpflow30jetm_fJVT  = (leadingjet->m());
          //  Using TLorentzVector to find rapidity
          pflow30TLVec_fJVT.SetPtEtaPhiM((leadingpflow30jetpt_fJVT/0.001), leadingpflow30jeteta_fJVT, leadingpflow30jetphi_fJVT, leadingpflow30jetm_fJVT);
          leadingpflow30jety_fJVT = abs(pflow30TLVec_fJVT.Rapidity());
          pflow_j130_pt_fJVT = (leadingpflow30jetpt_fJVT);
          pflow_j130_eta_fJVT = (leadingpflow30jeteta_fJVT);
          pflow_j130_phi_fJVT = (leadingpflow30jetphi_fJVT);
          pflow_j130_y_fJVT = (leadingpflow30jety_fJVT);
          pflow_j130_m_fJVT = (leadingpflow30jetm_fJVT);
          if (m_mu < 15){
            pflow_j130_pt_15_fJVT = (leadingpflow30jetpt_fJVT);
            hist_j130_pt_015_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
            pflow_j130_y_15_fJVT = (leadingpflow30jety_fJVT);
            hist_j130_y_015_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
          }
          else if (m_mu < 25){
            pflow_j130_pt_1525_fJVT = (leadingpflow30jetpt_fJVT);
            hist_j130_pt_1525_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
            pflow_j130_y_1525_fJVT = (leadingpflow30jety_fJVT);
            hist_j130_y_1525_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
          }
          else if (m_mu < 35){
            pflow_j130_pt_2535_fJVT = (leadingpflow30jetpt_fJVT);
            hist_j130_pt_2535_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
            pflow_j130_y_2535_fJVT = (leadingpflow30jety_fJVT);
            hist_j130_y_2535_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
          }
          else if (m_mu < 50){
            pflow_j130_pt_3550_fJVT = (leadingpflow30jetpt_fJVT);
            hist_j130_pt_3550_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
            pflow_j130_y_3550_fJVT = (leadingpflow30jety_fJVT);
            hist_j130_y_3550_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
          }
          else if (m_mu > 50){
            pflow_j130_pt_50_fJVT = (leadingpflow30jetpt_fJVT);
            hist_j130_pt_50_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
            pflow_j130_y_50_fJVT = (leadingpflow30jety_fJVT);
            hist_j130_y_50_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
          }
        }
      }
      int number_of_fjvt_jets = 0;
      // int number_of_fjvt_jets_HS = 0;
      // int number_of_fjvt_jets_notHS = 0;
      // int number_of_jets_HS = 0;
      // int number_of_jets_notHS = 0;
      for (auto jet: *pflowjets){
        alljetTLVec.SetPtEtaPhiM(jet->pt(), jet->eta(), jet->phi(), jet->m());
        alljet_y = abs(alljetTLVec.Rapidity());
        hist_alljet_pt->Fill(jet->pt() * 0.001, eventweight);
        hist_alljet_eta->Fill(jet->eta(), eventweight);
        hist_alljet_y->Fill(alljet_y, eventweight);

          if (m_mu < 15){
            hist_alljet_pt_015->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_015->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }
          else if (m_mu < 25){
            hist_alljet_pt_1525->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_1525->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }
          else if (m_mu < 35){
            hist_alljet_pt_2535->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_2535->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }
          else if (m_mu < 50){
            hist_alljet_pt_3550->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_3550->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }
          else if (m_mu > 50){
            hist_alljet_pt_50->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_50->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }

        // std::cout<<
        if (abs(jet->eta()) > 2.5){
          hist_forward_jet_pt->Fill(jet->pt() * 0.001, eventweight);
          hist_forward_jet_eta->Fill(abs(jet->eta()), eventweight);
        }
        if (abs(jet->eta()) < 2.5){
          hist_central_jet_pt->Fill(jet->pt() * 0.001, eventweight);
          hist_central_jet_eta->Fill(jet->eta(), eventweight);
        }

        if (jet->auxdata<char>("passFJVT") == 1) {
          number_of_fjvt_jets++;
          hist_pass_fJVT->Fill(jet->eta(), eventweight);
          // alljetTLVec_fJVT.SetPtEtaPhiM(jet->pt(), jet->eta(), jet->phi(), jet->m());
          // alljet_y_fJVT = abs(alljetTLVec_fJVT.Rapidity());

          hist_alljet_pt_fJVT->Fill(jet->pt() * 0.001, eventweight);
          // hist_alljet_y_fJVT->Fill(alljet_y_fJVT, eventweight);
          
          if (m_mu < 15){
            hist_alljet_pt_015_fJVT->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_015_fJVT->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }
          else if (m_mu < 25){
            hist_alljet_pt_1525_fJVT->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_1525_fJVT->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }
          else if (m_mu < 35){
            hist_alljet_pt_2535_fJVT->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_2535_fJVT->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }
          else if (m_mu < 50){
            hist_alljet_pt_3550_fJVT->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_3550_fJVT->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }
          else if (m_mu > 50){
            hist_alljet_pt_50_fJVT->Fill(jet->pt() * 0.001, eventweight);
            hist_alljet_y_50_fJVT->Fill(abs(alljetTLVec.Rapidity()), eventweight);
          }

          if (abs(jet->eta()) > 2.5){
            // std::cout << "forward jet jvt" << std::endl;
            hist_forward_jet_pt_fJVT->Fill(jet->pt() * 0.001, eventweight);
            hist_forward_jet_eta_fJVT->Fill(abs(jet->eta()), eventweight);
          }
          if (abs(jet->eta()) < 2.5){
            hist_central_jet_pt_fJVT->Fill(jet->pt() * 0.001, eventweight);
            hist_central_jet_eta_fJVT->Fill(jet->eta(), eventweight);
          }

        }
        if (jet->auxdata<char>("passFJVT") != 1){
          hist_fail_fJVT->Fill(jet->eta(), eventweight);
        }

        // if (jet->auxdata<char>("isJvtHS") == 1){
        //   number_of_jets_HS++;
        //   hist_alljet_pt_HS->Fill(jet->pt() * 0.001, eventweight);
        //   hist_alljet_eta_HS->Fill(jet->eta(), eventweight);
        //   // std::cout<<
        //   if (abs(jet->eta()) > 2.5){
        //     hist_forward_jet_pt_HS->Fill(jet->pt() * 0.001, eventweight);
        //     hist_forward_jet_eta_HS->Fill(abs(jet->eta()), eventweight);
        //   }
        //   if (abs(jet->eta()) < 2.5){
        //     hist_central_jet_pt_HS->Fill(jet->pt() * 0.001, eventweight);
        //     hist_central_jet_eta_HS->Fill(jet->eta(), eventweight);
        //   }

        //   if (jet->auxdata<char>("passFJVT") == 1) {
        //     number_of_fjvt_jets_HS++;
        //     hist_pass_fJVT_HS->Fill(jet->eta(), eventweight);
        //     hist_alljet_pt_fJVT_HS->Fill(jet->pt() * 0.001, eventweight);
        //     if (abs(jet->eta()) > 2.5){
        //       // std::cout << "forward jet jvt" << std::endl;
        //       hist_forward_jet_pt_fJVT_HS->Fill(jet->pt() * 0.001, eventweight);
        //       hist_forward_jet_eta_fJVT_HS->Fill(abs(jet->eta()), eventweight);
        //     }
        //     if (abs(jet->eta()) < 2.5){
        //       hist_central_jet_pt_fJVT_HS->Fill(jet->pt() * 0.001, eventweight);
        //       hist_central_jet_eta_fJVT_HS->Fill(jet->eta(), eventweight);
        //     }
        //   }
        //   if (jet->auxdata<char>("passFJVT") != 1){
        //     hist_fail_fJVT_HS->Fill(jet->eta(), eventweight);
        //   }
        // }
        // if (jet->auxdata<char>("isJvtHS") != 1){
        //   number_of_jets_notHS++;
        //   hist_alljet_pt_notHS->Fill(jet->pt() * 0.001, eventweight);
        //   hist_alljet_eta_notHS->Fill(jet->eta(), eventweight);
        //   // std::cout<<
        //   if (abs(jet->eta()) > 2.5){
        //     hist_forward_jet_pt_notHS->Fill(jet->pt() * 0.001, eventweight);
        //     hist_forward_jet_eta_notHS->Fill(abs(jet->eta()), eventweight);
        //   }
        //   if (abs(jet->eta()) < 2.5){
        //     hist_central_jet_pt_notHS->Fill(jet->pt() * 0.001, eventweight);
        //     hist_central_jet_eta_notHS->Fill(jet->eta(), eventweight);
        //   }

        //   if (jet->auxdata<char>("passFJVT") == 1) {
        //     number_of_fjvt_jets_notHS++;
        //     hist_pass_fJVT_notHS->Fill(jet->eta(), eventweight);
        //     hist_alljet_pt_fJVT_notHS->Fill(jet->pt() * 0.001, eventweight);
        //     if (abs(jet->eta()) > 2.5){
        //       // std::cout << "forward jet jvt" << std::endl;
        //       hist_forward_jet_pt_fJVT_notHS->Fill(jet->pt() * 0.001, eventweight);
        //       hist_forward_jet_eta_fJVT_notHS->Fill(abs(jet->eta()), eventweight);
        //     }
        //     if (abs(jet->eta()) < 2.5){
        //       hist_central_jet_pt_fJVT_notHS->Fill(jet->pt() * 0.001, eventweight);
        //       hist_central_jet_eta_fJVT_notHS->Fill(jet->eta(), eventweight);
        //     }
        //   }
        //   if (jet->auxdata<char>("passFJVT") != 1){
        //     hist_fail_fJVT_notHS->Fill(jet->eta(), eventweight);
        //   }
        // }
      } //end of jet loop
      hist_n_jets->Fill(pflowjets->size());
      if (number_of_fjvt_jets > 0){hist_n_jets_fJVT->Fill(number_of_fjvt_jets);}
      // if (number_of_jets_HS > 0){hist_n_jets_HS->Fill(number_of_jets_HS);}
      // if (number_of_fjvt_jets_HS > 0){hist_n_jets_fJVT_HS->Fill(number_of_fjvt_jets_HS);}
      // if (number_of_fjvt_jets_notHS > 0){hist_n_jets_fJVT_notHS->Fill(number_of_fjvt_jets_notHS);}
      // if (number_of_jets_notHS > 0){hist_n_jets_notHS->Fill(number_of_jets_notHS);}
    } // end of 1 jet requirement
  } //end of HGam passed 


  tree->Fill();
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamMxAODAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamMxAODAnalysis :: finalize ()
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


void HGamMxAODAnalysis::ResetVariables()
{
  pflow_j130_pt_15 = 0;
  pflow_j130_pt_1525 = 0;
  pflow_j130_pt_2535 = 0;
  pflow_j130_pt_3550 = 0;
  pflow_j130_pt_50 = 0;

  pflow_j130_y_15 = -999;
  pflow_j130_y_1525 = -999;
  pflow_j130_y_2535 = -999;
  pflow_j130_y_3550 = -999;
  pflow_j130_y_50 = -999;

  pflow_j130_pt = 0;
  pflow_j130_eta = -999;
  pflow_j130_phi = -999;
  pflow_j130_m = -999;
  pflow_j130_y = -999;

  pflow_fjvt_fail_eta = -999;
  pflow_fjvt_pass_eta = -999;

  pflow_j130_pt_15_fJVT = 0;
  pflow_j130_pt_1525_fJVT = 0;
  pflow_j130_pt_2535_fJVT = 0;
  pflow_j130_pt_3550_fJVT = 0;
  pflow_j130_pt_50_fJVT = 0;

  pflow_j130_y_15_fJVT = -999;
  pflow_j130_y_1525_fJVT = -999;
  pflow_j130_y_2535_fJVT = -999;
  pflow_j130_y_3550_fJVT = -999;
  pflow_j130_y_50_fJVT = -999;

  pflow_j130_pt_fJVT = 0;
  pflow_j130_eta_fJVT = -999;
  pflow_j130_phi_fJVT = -999;
  pflow_j130_m_fJVT = -999;
  pflow_j130_y_fJVT = -999;

}

EL::StatusCode HGamMxAODAnalysis :: histFinalize ()
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
  return EL::StatusCode::SUCCESS;
}





