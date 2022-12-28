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


  hist_j130_pt_015 = new TH1F("hist_j130_pt_015", "hist_j130_pt_015;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_1525 = new TH1F("hist_j130_pt_1525", "hist_j130_pt_1525;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_2535 = new TH1F("hist_j130_pt_2535", "hist_j130_pt_2535;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_3550 = new TH1F("hist_j130_pt_3550", "hist_j130_pt_3550;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_50  = new TH1F("hist_j130_pt_50", "hist_j130_pt_50;p_{T};Events", ptbins, pt30min, pt30max);

  hist_j130_pt_015_loweta = new TH1F("hist_j130_pt_015_loweta", "hist_j130_pt_015;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_1525_loweta = new TH1F("hist_j130_pt_1525_loweta", "hist_j130_pt_1525;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_2535_loweta = new TH1F("hist_j130_pt_2535_loweta", "hist_j130_pt_2535;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_3550_loweta = new TH1F("hist_j130_pt_3550_loweta", "hist_j130_pt_3550;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_50_loweta  = new TH1F("hist_j130_pt_50_loweta", "hist_j130_pt_50;p_{T};Events", ptbins, pt30min, pt30max);

  hist_j130_pt_015_higheta = new TH1F("hist_j130_pt_015_higheta", "hist_j130_pt_015;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_1525_higheta = new TH1F("hist_j130_pt_1525_higheta", "hist_j130_pt_1525;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_2535_higheta = new TH1F("hist_j130_pt_2535_higheta", "hist_j130_pt_2535;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_3550_higheta = new TH1F("hist_j130_pt_3550_higheta", "hist_j130_pt_3550;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_50_higheta  = new TH1F("hist_j130_pt_50_higheta", "hist_j130_pt_50;p_{T};Events", ptbins, pt30min, pt30max);

  hist_j130_y_015 = new TH1F("hist_j130_y_015", "hist_j130_y_015;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_1525 = new TH1F("hist_j130_y_1525", "hist_j130_y_1525;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_2535 = new TH1F("hist_j130_y_2535", "hist_j130_y_2535;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_3550 = new TH1F("hist_j130_y_3550", "hist_j130_y_3550;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_50  = new TH1F("hist_j130_y_50", "hist_j130_y_50;Rapidity;Events", ybins, ymin, ymax);


  hist_j150_pt_015 = new TH1F("hist_j150_pt_015", "hist_j150_pt_015;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_1525 = new TH1F("hist_j150_pt_1525", "hist_j150_pt_1525;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_2535 = new TH1F("hist_j150_pt_2535", "hist_j150_pt_2535;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_3550 = new TH1F("hist_j150_pt_3550", "hist_j150_pt_3550;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_50  = new TH1F("hist_j150_pt_50", "hist_j150_pt_50;p_{T};Events", ptbins, pt50min, pt50max);

  hist_j150_pt_015_loweta = new TH1F("hist_j150_pt_015_loweta", "hist_j150_pt_015;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_1525_loweta = new TH1F("hist_j150_pt_1525_loweta", "hist_j150_pt_1525;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_2535_loweta = new TH1F("hist_j150_pt_2535_loweta", "hist_j150_pt_2535;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_3550_loweta = new TH1F("hist_j150_pt_3550_loweta", "hist_j150_pt_3550;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_50_loweta  = new TH1F("hist_j150_pt_50_loweta", "hist_j150_pt_50;p_{T};Events", ptbins, pt50min, pt50max);

  hist_j150_pt_015_higheta = new TH1F("hist_j150_pt_015_higheta", "hist_j150_pt_015;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_1525_higheta = new TH1F("hist_j150_pt_1525_higheta", "hist_j150_pt_1525;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_2535_higheta = new TH1F("hist_j150_pt_2535_higheta", "hist_j150_pt_2535;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_3550_higheta = new TH1F("hist_j150_pt_3550_higheta", "hist_j150_pt_3550;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_50_higheta  = new TH1F("hist_j150_pt_50_higheta", "hist_j150_pt_50;p_{T};Events", ptbins, pt50min, pt50max);

  hist_j150_y_015 = new TH1F("hist_j150_y_015", "hist_j150_y_015;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_1525 = new TH1F("hist_j150_y_1525", "hist_j150_y_1525;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_2535 = new TH1F("hist_j150_y_2535", "hist_j150_y_2535;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_3550 = new TH1F("hist_j150_y_3550", "hist_j150_y_3550;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_50 = new TH1F("hist_j150_y_50", "hist_j150_y_50;Rapidity;Events", ybins, ymin, ymax);

  hist_j130_pt_015_fJVT = new TH1F("hist_j130_pt_015_fJVT", "hist_j130_pt_015_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_1525_fJVT = new TH1F("hist_j130_pt_1525_fJVT", "hist_j130_pt_1525_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_2535_fJVT = new TH1F("hist_j130_pt_2535_fJVT", "hist_j130_pt_2535_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_3550_fJVT = new TH1F("hist_j130_pt_3550_fJVT", "hist_j130_pt_3550_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_50_fJVT = new TH1F("hist_j130_pt_50_fJVT", "hist_j130_pt_50_fJVT;p_{T};Events", ptbins, pt30min, pt30max);

  hist_j130_pt_015_loweta_fJVT = new TH1F("hist_j130_pt_015_loweta_fJVT", "hist_j130_pt_015_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_1525_loweta_fJVT = new TH1F("hist_j130_pt_1525_loweta_fJVT", "hist_j130_pt_1525_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_2535_loweta_fJVT = new TH1F("hist_j130_pt_2535_loweta_fJVT", "hist_j130_pt_2535_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_3550_loweta_fJVT = new TH1F("hist_j130_pt_3550_loweta_fJVT", "hist_j130_pt_3550_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_50_loweta_fJVT = new TH1F("hist_j130_pt_50_loweta_fJVT", "hist_j130_pt_50_fJVT;p_{T};Events", ptbins, pt30min, pt30max);

  hist_j130_pt_015_higheta_fJVT = new TH1F("hist_j130_pt_015_higheta_fJVT", "hist_j130_pt_015_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_1525_higheta_fJVT = new TH1F("hist_j130_pt_1525_higheta_fJVT", "hist_j130_pt_1525_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_2535_higheta_fJVT = new TH1F("hist_j130_pt_2535_higheta_fJVT", "hist_j130_pt_2535_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_3550_higheta_fJVT = new TH1F("hist_j130_pt_3550_higheta_fJVT", "hist_j130_pt_3550_fJVT;p_{T};Events", ptbins, pt30min, pt30max);
  hist_j130_pt_50_higheta_fJVT = new TH1F("hist_j130_pt_50_higheta_fJVT", "hist_j130_pt_50_fJVT;p_{T};Events", ptbins, pt30min, pt30max);

  hist_j130_y_015_fJVT = new TH1F("hist_j130_y_015_fJVT", "hist_j130_y_015_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_1525_fJVT = new TH1F("hist_j130_y_1525_fJVT", "hist_j130_y_1525_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_2535_fJVT = new TH1F("hist_j130_y_2535_fJVT", "hist_j130_y_2535_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_3550_fJVT = new TH1F("hist_j130_y_3550_fJVT", "hist_j130_y_3550_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j130_y_50_fJVT = new TH1F("hist_j130_y_50_fJVT", "hist_j130_y_50_fJVT;Rapidity;Events", ybins, ymin, ymax);


  hist_j150_pt_015_fJVT = new TH1F("hist_j150_pt_015_fJVT", "hist_j150_pt_015_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_1525_fJVT = new TH1F("hist_j150_pt_1525_fJVT", "hist_j150_pt_1525_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_2535_fJVT = new TH1F("hist_j150_pt_2535_fJVT", "hist_j150_pt_2535_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_3550_fJVT = new TH1F("hist_j150_pt_3550_fJVT", "hist_j150_pt_3550_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_50_fJVT = new TH1F("hist_j150_pt_50_fJVT", "hist_j150_pt_50_fJVT;p_{T};Events", ptbins, pt50min, pt50max);

  hist_j150_pt_015_loweta_fJVT = new TH1F("hist_j150_pt_015_loweta_fJVT", "hist_j150_pt_015_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_1525_loweta_fJVT = new TH1F("hist_j150_pt_1525_loweta_fJVT", "hist_j150_pt_1525_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_2535_loweta_fJVT = new TH1F("hist_j150_pt_2535_loweta_fJVT", "hist_j150_pt_2535_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_3550_loweta_fJVT = new TH1F("hist_j150_pt_3550_loweta_fJVT", "hist_j150_pt_3550_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_50_loweta_fJVT = new TH1F("hist_j150_pt_50_loweta_fJVT", "hist_j150_pt_50_fJVT;p_{T};Events", ptbins, pt50min, pt50max);

  hist_j150_pt_015_higheta_fJVT = new TH1F("hist_j150_pt_015_higheta_fJVT", "hist_j150_pt_015_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_1525_higheta_fJVT = new TH1F("hist_j150_pt_1525_higheta_fJVT", "hist_j150_pt_1525_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_2535_higheta_fJVT = new TH1F("hist_j150_pt_2535_higheta_fJVT", "hist_j150_pt_2535_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_3550_higheta_fJVT = new TH1F("hist_j150_pt_3550_higheta_fJVT", "hist_j150_pt_3550_fJVT;p_{T};Events", ptbins, pt50min, pt50max);
  hist_j150_pt_50_higheta_fJVT = new TH1F("hist_j150_pt_50_higheta_fJVT", "hist_j150_pt_50_fJVT;p_{T};Events", ptbins, pt50min, pt50max);

  hist_j150_y_015_fJVT = new TH1F("hist_j150_y_015_fJVT", "hist_j150_y_015_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_1525_fJVT = new TH1F("hist_j150_y_1525_fJVT", "hist_j150_y_1525_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_2535_fJVT = new TH1F("hist_j150_y_2535_fJVT", "hist_j150_y_2535_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_3550_fJVT = new TH1F("hist_j150_y_3550_fJVT", "hist_j150_y_3550_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_50_fJVT = new TH1F("hist_j150_y_50_fJVT", "hist_j150_y_50_fJVT;Rapidity;Events", ybins, ymin, ymax);

  hist_pass_fJVT = new TH1F("hist_pass_fJVT", "hist_pass_fJVT;#eta;Events", 40, -4.0, 4.0);
  hist_fail_fJVT = new TH1F("hist_fail_fJVT", "hist_fail_fJVT;#eta;Events", 40, -4.0, 4.0);



  // tree->Branch("event_number", &m_eventNumber, "event_number/I");
  // tree->Branch("run_number",   &m_runNumber,   "run_number/I");
  // tree->Branch("mu",   &m_mu,   "mu/I");
  // tree->Branch("lumiblock",   &m_lb,   "lumiblock/I");

  tree->Branch("pflow_j130_pt_15",     &pflow_j130_pt_15);
  tree->Branch("pflow_j130_pt_1525",   &pflow_j130_pt_1525);
  tree->Branch("pflow_j130_pt_2535",   &pflow_j130_pt_2535);
  tree->Branch("pflow_j130_pt_3550",   &pflow_j130_pt_3550);
  tree->Branch("pflow_j130_pt_50",     &pflow_j130_pt_50);

  tree->Branch("pflow_j130_pt_15_loweta",     &pflow_j130_pt_15_loweta);
  tree->Branch("pflow_j130_pt_1525_loweta",   &pflow_j130_pt_1525_loweta);
  tree->Branch("pflow_j130_pt_2535_loweta",   &pflow_j130_pt_2535_loweta);
  tree->Branch("pflow_j130_pt_3550_loweta",   &pflow_j130_pt_3550_loweta);
  tree->Branch("pflow_j130_pt_50_loweta",     &pflow_j130_pt_50_loweta);

  tree->Branch("pflow_j130_pt_15_higheta",     &pflow_j130_pt_15_higheta);
  tree->Branch("pflow_j130_pt_1525_higheta",   &pflow_j130_pt_1525_higheta);
  tree->Branch("pflow_j130_pt_2535_higheta",   &pflow_j130_pt_2535_higheta);
  tree->Branch("pflow_j130_pt_3550_higheta",   &pflow_j130_pt_3550_higheta);
  tree->Branch("pflow_j130_pt_50_higheta",     &pflow_j130_pt_50_higheta);


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

  tree->Branch("pflow_j150_pt_15",     &pflow_j150_pt_15);
  tree->Branch("pflow_j150_pt_1525",   &pflow_j150_pt_1525);
  tree->Branch("pflow_j150_pt_2535",   &pflow_j150_pt_2535);
  tree->Branch("pflow_j150_pt_3550",   &pflow_j150_pt_3550);
  tree->Branch("pflow_j150_pt_50",     &pflow_j150_pt_50);

  tree->Branch("pflow_j150_pt_15_loweta",     &pflow_j150_pt_15_loweta);
  tree->Branch("pflow_j150_pt_1525_loweta",   &pflow_j150_pt_1525_loweta);
  tree->Branch("pflow_j150_pt_2535_loweta",   &pflow_j150_pt_2535_loweta);
  tree->Branch("pflow_j150_pt_3550_loweta",   &pflow_j150_pt_3550_loweta);
  tree->Branch("pflow_j150_pt_50_loweta",     &pflow_j150_pt_50_loweta);

  tree->Branch("pflow_j150_pt_15_higheta",     &pflow_j150_pt_15_higheta);
  tree->Branch("pflow_j150_pt_1525_higheta",   &pflow_j150_pt_1525_higheta);
  tree->Branch("pflow_j150_pt_2535_higheta",   &pflow_j150_pt_2535_higheta);
  tree->Branch("pflow_j150_pt_3550_higheta",   &pflow_j150_pt_3550_higheta);
  tree->Branch("pflow_j150_pt_50_higheta",     &pflow_j150_pt_50_higheta);


  tree->Branch("pflow_j150_y_15",     &pflow_j150_y_15);
  tree->Branch("pflow_j150_y_1525",   &pflow_j150_y_1525);
  tree->Branch("pflow_j150_y_2535",   &pflow_j150_y_2535);
  tree->Branch("pflow_j150_y_3550",   &pflow_j150_y_3550);
  tree->Branch("pflow_j150_y_50",     &pflow_j150_y_50);


  tree->Branch("pflow_j150_pt",     &pflow_j150_pt);
  tree->Branch("pflow_j150_eta",    &pflow_j150_eta);
  tree->Branch("pflow_j150_phi",    &pflow_j150_phi);
  tree->Branch("pflow_j150_m",      &pflow_j150_m);
  tree->Branch("pflow_j150_y",      &pflow_j150_y);


  // tree->Branch("pflow_fjvt_fail_eta",  &pflow_fjvt_fail_eta);
  // tree->Branch("pflow_fjvt_pass_eta",  &pflow_fjvt_pass_eta);

  // tree->Branch("pflow_j150_pt_15_nofJVT",     &pflow_j150_pt_15_nofJVT);
  // tree->Branch("pflow_j150_pt_1525_nofJVT",   &pflow_j150_pt_1525_nofJVT);
  // tree->Branch("pflow_j150_pt_2535_nofJVT",   &pflow_j150_pt_2535_nofJVT);
  // tree->Branch("pflow_j150_pt_3550_nofJVT",   &pflow_j150_pt_3550_nofJVT);
  // tree->Branch("pflow_j150_pt_50_nofJVT",     &pflow_j150_pt_50_nofJVT);

  // tree->Branch("pflow_j150_pt_15_nofJVT_loweta",     &pflow_j150_pt_15_nofJVT_loweta);
  // tree->Branch("pflow_j150_pt_1525_nofJVT_loweta",   &pflow_j150_pt_1525_nofJVT_loweta);
  // tree->Branch("pflow_j150_pt_2535_nofJVT_loweta",   &pflow_j150_pt_2535_nofJVT_loweta);
  // tree->Branch("pflow_j150_pt_3550_nofJVT_loweta",   &pflow_j150_pt_3550_nofJVT_loweta);
  // tree->Branch("pflow_j150_pt_50_nofJVT_loweta",     &pflow_j150_pt_50_nofJVT_loweta);

  // tree->Branch("pflow_j150_pt_15_nofJVT_higheta",     &pflow_j150_pt_15_nofJVT_higheta);
  // tree->Branch("pflow_j150_pt_1525_nofJVT_higheta",   &pflow_j150_pt_1525_nofJVT_higheta);
  // tree->Branch("pflow_j150_pt_2535_nofJVT_higheta",   &pflow_j150_pt_2535_nofJVT_higheta);
  // tree->Branch("pflow_j150_pt_3550_nofJVT_higheta",   &pflow_j150_pt_3550_nofJVT_higheta);
  // tree->Branch("pflow_j150_pt_50_nofJVT_higheta",     &pflow_j150_pt_50_nofJVT_higheta);

  // tree->Branch("pflow_j150_y_15_nofJVT",     &pflow_j150_y_15_nofJVT);
  // tree->Branch("pflow_j150_y_1525_nofJVT",   &pflow_j150_y_1525_nofJVT);
  // tree->Branch("pflow_j150_y_2535_nofJVT",   &pflow_j150_y_2535_nofJVT);
  // tree->Branch("pflow_j150_y_3550_nofJVT",   &pflow_j150_y_3550_nofJVT);
  // tree->Branch("pflow_j150_y_50_nofJVT",     &pflow_j150_y_50_nofJVT);

  // tree->Branch("pflow_j150_pt_nofJVT",     &pflow_j150_pt_nofJVT);
  // tree->Branch("pflow_j150_eta_nofJVT",    &pflow_j150_eta_nofJVT);
  // tree->Branch("pflow_j150_phi_nofJVT",    &pflow_j150_phi_nofJVT);
  // tree->Branch("pflow_j150_m_nofJVT",      &pflow_j150_m_nofJVT);
  // tree->Branch("pflow_j150_y_nofJVT",      &pflow_j150_y_nofJVT);

  wk()->addOutput(tree);
  wk()->addOutput(hist_j130_pt_015);
  wk()->addOutput(hist_j130_pt_1525);
  wk()->addOutput(hist_j130_pt_2535);
  wk()->addOutput(hist_j130_pt_3550);
  wk()->addOutput(hist_j130_pt_50 );

  wk()->addOutput(hist_j130_pt_015_loweta);
  wk()->addOutput(hist_j130_pt_1525_loweta);
  wk()->addOutput(hist_j130_pt_2535_loweta);
  wk()->addOutput(hist_j130_pt_3550_loweta);
  wk()->addOutput(hist_j130_pt_50_loweta );

  wk()->addOutput(hist_j130_pt_015_higheta);
  wk()->addOutput(hist_j130_pt_1525_higheta);
  wk()->addOutput(hist_j130_pt_2535_higheta);
  wk()->addOutput(hist_j130_pt_3550_higheta);
  wk()->addOutput(hist_j130_pt_50_higheta );

  wk()->addOutput(hist_j130_y_015);
  wk()->addOutput(hist_j130_y_1525);
  wk()->addOutput(hist_j130_y_2535);
  wk()->addOutput(hist_j130_y_3550);
  wk()->addOutput(hist_j130_y_50 );


  wk()->addOutput(hist_j150_pt_015);
  wk()->addOutput(hist_j150_pt_1525);
  wk()->addOutput(hist_j150_pt_2535);
  wk()->addOutput(hist_j150_pt_3550);
  wk()->addOutput(hist_j150_pt_50 );

  wk()->addOutput(hist_j150_pt_015_loweta);
  wk()->addOutput(hist_j150_pt_1525_loweta);
  wk()->addOutput(hist_j150_pt_2535_loweta);
  wk()->addOutput(hist_j150_pt_3550_loweta);
  wk()->addOutput(hist_j150_pt_50_loweta );

  wk()->addOutput(hist_j150_pt_015_higheta);
  wk()->addOutput(hist_j150_pt_1525_higheta);
  wk()->addOutput(hist_j150_pt_2535_higheta);
  wk()->addOutput(hist_j150_pt_3550_higheta);
  wk()->addOutput(hist_j150_pt_50_higheta );

  wk()->addOutput(hist_j150_y_015);
  wk()->addOutput(hist_j150_y_1525);
  wk()->addOutput(hist_j150_y_2535);
  wk()->addOutput(hist_j150_y_3550);
  wk()->addOutput(hist_j150_y_50);

  wk()->addOutput(hist_j130_pt_015_fJVT);
  wk()->addOutput(hist_j130_pt_1525_fJVT);
  wk()->addOutput(hist_j130_pt_2535_fJVT);
  wk()->addOutput(hist_j130_pt_3550_fJVT);
  wk()->addOutput(hist_j130_pt_50_fJVT);

  wk()->addOutput(hist_j130_pt_015_loweta_fJVT);
  wk()->addOutput(hist_j130_pt_1525_loweta_fJVT);
  wk()->addOutput(hist_j130_pt_2535_loweta_fJVT);
  wk()->addOutput(hist_j130_pt_3550_loweta_fJVT);
  wk()->addOutput(hist_j130_pt_50_loweta_fJVT);

  wk()->addOutput(hist_j130_pt_015_higheta_fJVT);
  wk()->addOutput(hist_j130_pt_1525_higheta_fJVT);
  wk()->addOutput(hist_j130_pt_2535_higheta_fJVT);
  wk()->addOutput(hist_j130_pt_3550_higheta_fJVT);
  wk()->addOutput(hist_j130_pt_50_higheta_fJVT);

  wk()->addOutput(hist_j130_y_015_fJVT);
  wk()->addOutput(hist_j130_y_1525_fJVT);
  wk()->addOutput(hist_j130_y_2535_fJVT);
  wk()->addOutput(hist_j130_y_3550_fJVT);
  wk()->addOutput(hist_j130_y_50_fJVT);

  wk()->addOutput(hist_j150_pt_015_fJVT);
  wk()->addOutput(hist_j150_pt_1525_fJVT);
  wk()->addOutput(hist_j150_pt_2535_fJVT);
  wk()->addOutput(hist_j150_pt_3550_fJVT);
  wk()->addOutput(hist_j150_pt_50_fJVT);

  wk()->addOutput(hist_j150_pt_015_loweta_fJVT);
  wk()->addOutput(hist_j150_pt_1525_loweta_fJVT);
  wk()->addOutput(hist_j150_pt_2535_loweta_fJVT);
  wk()->addOutput(hist_j150_pt_3550_loweta_fJVT);
  wk()->addOutput(hist_j150_pt_50_loweta_fJVT);

  wk()->addOutput(hist_j150_pt_015_higheta_fJVT);
  wk()->addOutput(hist_j150_pt_1525_higheta_fJVT);
  wk()->addOutput(hist_j150_pt_2535_higheta_fJVT);
  wk()->addOutput(hist_j150_pt_3550_higheta_fJVT);
  wk()->addOutput(hist_j150_pt_50_higheta_fJVT);

  wk()->addOutput(hist_j150_y_015_fJVT);
  wk()->addOutput(hist_j150_y_1525_fJVT);
  wk()->addOutput(hist_j150_y_2535_fJVT);
  wk()->addOutput(hist_j150_y_3550_fJVT);
  wk()->addOutput(hist_j150_y_50_fJVT);

  wk()->addOutput(hist_pass_fJVT);
  wk()->addOutput(hist_fail_fJVT);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamMxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed

  // cutflow = new TH1F();
  std::cout << "IS MC?: " << isMC << std::endl;
  std::cout << "IS DATA?: " << isData << std::endl;
  if (isMC == true){
    cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_100_160_noDalitz");
    sum_weights = ((cutflow->GetBinContent(1) / cutflow->GetBinContent(2)) * cutflow->GetBinContent(3));
  }
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
  // std::cout << "isData type " << typeid(isData).name() << std::endl;
  // std::cout << "evt number " << n_EventNumber << std::endl;
  // //  bool isData = false;


  // std::cerr << "tjb data: " << isData << std::endl;
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
  // std::cerr << "deltaR val is " << dRval >> std::endl;

  // if( (m_eventCounter % 1000) ==0 ){Info("execute()", "Event number = %i", m_eventCounter );}
  // Info("execute()", "Event number = %i", m_eventCounter );
  // cnt_total++;
  m_eventCounter++;


  // if (m_eventCounter < 500){


  // initialize variable
  ResetVariables();

  m_eventInfoCont =0;
  // m_muonRoICont  =0;
  // m_muonsCont    =0;

  EL_RETURN_CHECK("execute()",event->retrieve( m_eventInfoCont, "EventInfo"));
  // EL_RETURN_CHECK("execute()",event->retrieve( m_muonsCont,     "Muons" ));
  // EL_RETURN_CHECK("execute()",event->retrieve( m_electronsCont, "ElectronCollection" )); // DC14
  // EL_RETURN_CHECK("execute()",event->retrieve( m_electronsCont, "Electrons" )); // MC15
  

  
  const xAOD::JetContainer* pflowjets = NULL;
  if (!event->retrieve(pflowjets, "HGamAntiKt4EMPFlowJets").isSuccess()) {
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

  if (isMC == true){
    lumi_mc16 = 36215.0;
    eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
              * HGamEventInfo->auxdataConst<float>("weight") 
              //* HGamEventInfo->auxdataConst<float>("yybb_discreteMV2c10pT_weight")
              * lumi_mc16)
              / sum_weights);
  }

  if (isData == true){eventweight = 1;}

  passed = HGamEventInfo->auxdata<char>("isPassed");
  m_yy = HGamEventInfo->auxdata<float>("m_yy")*0.001;

  m_mu   = static_cast<int>(m_eventInfoCont->actualInteractionsPerCrossing());


  // m_eventNumber = static_cast<int>(m_eventInfoCont->eventNumber());
  // m_runNumber   = static_cast<int>(m_eventInfoCont->runNumber());
  // m_mu   = static_cast<int>(m_eventInfoCont->actualInteractionsPerCrossing());
  // m_lb = static_cast<int>(m_eventInfoCont->lumiBlock());

  // m_isMC = m_eventInfoCont->eventType( xAOD::EventInfo::IS_SIMULATION );

  npflow30jetsperevent  = 0;
  npflow50jetsperevent  = 0;

  npflow30jetsperevent_fJVT  = 0;
  npflow50jetsperevent_fJVT  = 0;


  leadingpflow30jetpt = 0;
  leadingpflow50jetpt = 0;

  leadingpflow30jetpt_fJVT = 0;
  leadingpflow50jetpt_fJVT = 0;


  // 
  //  Begin loop over particle flow jets comparing leading jet pt thresholds
  //
if (passed){
if (( m_yy > 120 ) && ( m_yy < 130 )) {}
else{
for (auto jet: *pflowjets){
    // std::cerr << "execute(): pflow jet pt = " << (jet->pt() * 0.001) << " GeV" << std::endl;
    
    // 
    //  Compare to distributions with fJVT cut
    //
if (jet->auxdata<char>("passFJVT") == 1) {
  pflow_fjvt_pass_eta = jet->eta();
    if (npflow30jetsperevent_fJVT == 0){
      ++npflow30jetsperevent_fJVT;

      if ((jet->pt() * 0.001)>30){
          // std::cerr << "pass GeV cut of 30 with pT of " << (jet->pt() * 0.001) << std::endl;
          leadingpflow30jetpt_fJVT = (jet->pt() * 0.001);
          leadingpflow30jeteta_fJVT = (jet->eta());
          leadingpflow30jetphi_fJVT = (jet->phi());
          leadingpflow30jetm_fJVT  = (jet->m());
              //  Using TLorentzVector to find rapidity
          pflow30TLVec_fJVT.SetPtEtaPhiM((leadingpflow30jetpt_fJVT/0.001), leadingpflow30jeteta_fJVT, leadingpflow30jetphi_fJVT, leadingpflow30jetm_fJVT);
          leadingpflow30jety_fJVT = pflow30TLVec_fJVT.Rapidity();
          pflow_j130_pt_fJVT = (leadingpflow30jetpt_fJVT);
          pflow_j130_eta_fJVT = (leadingpflow30jeteta_fJVT);
          pflow_j130_phi_fJVT = (leadingpflow30jetphi_fJVT);
          pflow_j130_y_fJVT = (leadingpflow30jety_fJVT);
          pflow_j130_m_fJVT = (leadingpflow30jetm_fJVT);
      }
      else{
        npflow30jetsperevent_fJVT=0;
      }
    }

    if (npflow50jetsperevent_fJVT == 0){
      ++npflow50jetsperevent_fJVT;
      if ((jet->pt() * 0.001)>50){
          // std::cerr << "pass GeV cut of 30 with pT of " << (jet->pt() * 0.001) << std::endl;
          leadingpflow50jetpt_fJVT = (jet->pt() * 0.001);
          leadingpflow50jeteta_fJVT = (jet->eta());
          leadingpflow50jetphi_fJVT = (jet->phi());
          leadingpflow50jetm_fJVT  = (jet->m());
              //  Using TLorentzVector to find rapidity
          pflow50TLVec_fJVT.SetPtEtaPhiM((leadingpflow50jetpt_fJVT/0.001), leadingpflow50jeteta_fJVT, leadingpflow50jetphi_fJVT, leadingpflow50jetm_fJVT);
          leadingpflow50jety_fJVT = pflow50TLVec_fJVT.Rapidity();
          pflow_j150_pt_fJVT = (leadingpflow50jetpt_fJVT);
          pflow_j150_eta_fJVT = (leadingpflow50jeteta_fJVT);
          pflow_j150_phi_fJVT = (leadingpflow50jetphi_fJVT);
          pflow_j150_y_fJVT = (leadingpflow50jety_fJVT);
          pflow_j150_m_fJVT = (leadingpflow50jetm_fJVT);
      }
      else{
        npflow50jetsperevent_fJVT=0;
      }
    }
}
if (jet->auxdata<char>("passFJVT") != 1){pflow_fjvt_fail_eta = jet->eta();}

//
// comparing without fJVT cut
//
    if (npflow30jetsperevent == 0){
      ++npflow30jetsperevent;
      if ((jet->pt() * 0.001)>30){
          // std::cerr << "pass GeV cut of 30 with pT of " << (jet->pt() * 0.001) << std::endl;
          leadingpflow30jetpt = (jet->pt() * 0.001);
          leadingpflow30jeteta = (jet->eta());
          leadingpflow30jetphi = (jet->phi());
          leadingpflow30jetm  = (jet->m());
              //  Using TLorentzVector to find rapidity
          pflow30TLVec.SetPtEtaPhiM((leadingpflow30jetpt/0.001), leadingpflow30jeteta, leadingpflow30jetphi, leadingpflow30jetm);
          leadingpflow30jety = pflow30TLVec.Rapidity();
          pflow_j130_pt = (leadingpflow30jetpt);
          pflow_j130_eta = (leadingpflow30jeteta);
          pflow_j130_phi = (leadingpflow30jetphi);
          pflow_j130_y = (leadingpflow30jety);
          pflow_j130_m = (leadingpflow30jetm);
      }
      else{
        npflow30jetsperevent=0;
      }
    }

    if (npflow50jetsperevent == 0){
      ++npflow50jetsperevent;
      if ((jet->pt() * 0.001)>50){
          // std::cerr << "pass GeV cut of 30 with pT of " << (jet->pt() * 0.001) << std::endl;
          leadingpflow50jetpt = (jet->pt() * 0.001);
          leadingpflow50jeteta = (jet->eta());
          leadingpflow50jetphi = (jet->phi());
          leadingpflow50jetm  = (jet->m());
              //  Using TLorentzVector to find rapidity
          pflow50TLVec.SetPtEtaPhiM((leadingpflow50jetpt/0.001), leadingpflow50jeteta, leadingpflow50jetphi, leadingpflow50jetm);
          leadingpflow50jety = pflow50TLVec.Rapidity();
          pflow_j150_pt = (leadingpflow50jetpt);
          pflow_j150_eta = (leadingpflow50jeteta);
          pflow_j150_phi = (leadingpflow50jetphi);
          pflow_j150_y = (leadingpflow50jety);
          pflow_j150_m = (leadingpflow50jetm);
      }
      else{
        npflow50jetsperevent=0;
      }
    }

      // }
    // else {
      // pflow_fjvt_fail_eta = (jet->eta());
      // std::cerr<<"did not pass fjvt"<<std::endl;
    // }
    
  hist_pass_fJVT->Fill(pflow_fjvt_pass_eta, eventweight);
  hist_fail_fJVT->Fill(pflow_fjvt_fail_eta, eventweight);

  } //end of jet loop
} //end of m_yy requirement
} //end of HGam passed 

// std::cerr << "leading jet pt: " << leadingpflowjetpt << std::endl;
// std::cerr << "leading jet eta: " << leadingpflowjeteta << std::endl;

if (npflow30jetsperevent > 0){
    // 
    //  npflowjetsperevent > 0 to make sure we have one jet
    //  shouldn't matter if >1, leading values stay the same
    //
  // if (( leadingpflow30jetpt > 120 ) && ( leadingpflow30jetpt < 130 )) {}
  // else{
      if (m_mu < 15){
        pflow_j130_pt_15 = (leadingpflow30jetpt);
        hist_j130_pt_015->Fill(leadingpflow30jetpt, eventweight);
        // pflow_j130_pt_15_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_15 = (leadingpflow30jety);
        hist_j130_y_015->Fill(leadingpflow30jety, eventweight);
        
        // pflow_j130_y_15_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow30jeteta) > 2.5){
          pflow_j130_pt_15_loweta = leadingpflow30jetpt;
          hist_j130_pt_015_loweta->Fill(leadingpflow30jetpt, eventweight);
        }
        if (abs(leadingpflow30jeteta) < 2.5){
          pflow_j130_pt_15_higheta = leadingpflow30jetpt;
          hist_j130_pt_015_higheta->Fill(leadingpflow30jetpt, eventweight);
        }
      }
      else if (m_mu < 25){
        pflow_j130_pt_1525 = (leadingpflow30jetpt);
        hist_j130_pt_1525->Fill(leadingpflow30jetpt, eventweight);
        // pflow_j130_pt_1525_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_1525 = (leadingpflow30jety);
        hist_j130_y_1525->Fill(leadingpflow30jety, eventweight);
        // pflow_j130_y_1525_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow30jeteta) > 2.5){
          pflow_j130_pt_1525_loweta = leadingpflow30jetpt;
          hist_j130_pt_1525_loweta->Fill(leadingpflow30jetpt, eventweight);
        }
        if (abs(leadingpflow30jeteta) < 2.5){
          pflow_j130_pt_1525_higheta = leadingpflow30jetpt;
          hist_j130_pt_1525_higheta->Fill(leadingpflow30jetpt, eventweight);
        }
      }
      else if (m_mu < 35){
        pflow_j130_pt_2535 = (leadingpflow30jetpt);
        hist_j130_pt_2535->Fill(leadingpflow30jetpt, eventweight);
        // pflow_j130_pt_2535_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_2535 = (leadingpflow30jety);
        hist_j130_y_2535->Fill(leadingpflow30jety, eventweight);
        // pflow_j130_y_2535_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow30jeteta) > 2.5){
          pflow_j130_pt_2535_loweta = leadingpflow30jetpt;
          hist_j130_pt_2535_loweta->Fill(leadingpflow30jetpt, eventweight);
        }
            if (abs(leadingpflow30jeteta) < 2.5){
          pflow_j130_pt_2535_higheta = leadingpflow30jetpt;
          hist_j130_pt_2535_higheta->Fill(leadingpflow30jetpt, eventweight);
        }
      }
      else if (m_mu < 50){
        pflow_j130_pt_3550 = (leadingpflow30jetpt);
        hist_j130_pt_3550->Fill(leadingpflow30jetpt, eventweight);
        // pflow_j130_pt_3550_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_3550 = (leadingpflow30jety);
        hist_j130_y_3550->Fill(leadingpflow30jety, eventweight);
        // pflow_j130_y_3550_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow30jeteta) > 2.5){
          pflow_j130_pt_3550_loweta = leadingpflow30jetpt;
          hist_j130_pt_3550_loweta->Fill(leadingpflow30jetpt, eventweight);
        }
        if (abs(leadingpflow30jeteta) < 2.5){
          pflow_j130_pt_3550_higheta = leadingpflow30jetpt;
          hist_j130_pt_3550_higheta->Fill(leadingpflow30jetpt, eventweight);
        }
      }
      else if (m_mu > 50){
        pflow_j130_pt_50 = (leadingpflow30jetpt);
        hist_j130_pt_50->Fill(leadingpflow30jetpt, eventweight);
        // pflow_j130_pt_50_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_50 = (leadingpflow30jety);
        hist_j130_y_50->Fill(leadingpflow30jety, eventweight);
        // pflow_j130_y_50_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow30jeteta) > 2.5){
          pflow_j130_pt_50_loweta = leadingpflow30jetpt;
          hist_j130_pt_50_loweta->Fill(leadingpflow30jetpt, eventweight);
        }
        if (abs(leadingpflow30jeteta) < 2.5){
          pflow_j130_pt_50_higheta = leadingpflow30jetpt;
          hist_j130_pt_50_higheta->Fill(leadingpflow30jetpt, eventweight);
        }
      }
    // }
  }


if (npflow50jetsperevent > 0){
  // std::cout << npflow50jetsperevent << std::endl;
  // std::cout << leadingpflow50jetpt << std::endl;
    // 
    //  npflowjetsperevent > 0 to make sure we have one jet
    //  shouldn't matter if >1, leading values stay the same
    // if (m_yy > 120 and m_yy < 130): continue
  // if (( leadingpflow50jetpt > 120 ) && ( leadingpflow50jetpt < 130 )) {}
    
  // else {
      // std::cout << "entered if 130" << std::endl;
      if (m_mu < 15){
        pflow_j150_pt_15 = (leadingpflow50jetpt);
        hist_j150_pt_015->Fill(leadingpflow50jetpt, eventweight);
        // pflow_j150_pt_15_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_15 = (leadingpflow50jety);
        hist_j150_y_015->Fill(leadingpflow50jety, eventweight);
        
        // pflow_j150_y_15_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow50jeteta) > 2.5){
          pflow_j150_pt_15_loweta = leadingpflow50jetpt;
          hist_j150_pt_015_loweta->Fill(leadingpflow50jetpt, eventweight);
        }
        if (abs(leadingpflow50jeteta) < 2.5){
          pflow_j150_pt_15_higheta = leadingpflow50jetpt;
          hist_j150_pt_015_higheta->Fill(leadingpflow50jetpt, eventweight);
        }
      }
      else if (m_mu < 25){
        pflow_j150_pt_1525 = (leadingpflow50jetpt);
        hist_j150_pt_1525->Fill(leadingpflow50jetpt, eventweight);
        // pflow_j150_pt_1525_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_1525 = (leadingpflow50jety);
        hist_j150_y_1525->Fill(leadingpflow50jety, eventweight);
        // pflow_j150_y_1525_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow50jeteta) > 2.5){
          pflow_j150_pt_1525_loweta = leadingpflow50jetpt;
          hist_j150_pt_1525_loweta->Fill(leadingpflow50jetpt, eventweight);
        }
        if (abs(leadingpflow50jeteta) < 2.5){
          pflow_j150_pt_1525_higheta = leadingpflow50jetpt;
          hist_j150_pt_1525_higheta->Fill(leadingpflow50jetpt, eventweight);
        }
      }
      else if (m_mu < 35){
        pflow_j150_pt_2535 = (leadingpflow50jetpt);
        hist_j150_pt_2535->Fill(leadingpflow50jetpt, eventweight);
        // pflow_j150_pt_2535_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_2535 = (leadingpflow50jety);
        hist_j150_y_2535->Fill(leadingpflow50jety, eventweight);
        // pflow_j150_y_2535_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow50jeteta) > 2.5){
          pflow_j150_pt_2535_loweta = leadingpflow50jetpt;
          hist_j150_pt_2535_loweta->Fill(leadingpflow50jetpt, eventweight);
        }
            if (abs(leadingpflow50jeteta) < 2.5){
          pflow_j150_pt_2535_higheta = leadingpflow50jetpt;
          hist_j150_pt_2535_higheta->Fill(leadingpflow50jetpt, eventweight);
        }
      }
      else if (m_mu < 50){
        pflow_j150_pt_3550 = (leadingpflow50jetpt);
        hist_j150_pt_3550->Fill(leadingpflow50jetpt, eventweight);
        // pflow_j150_pt_3550_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_3550 = (leadingpflow50jety);
        hist_j150_y_3550->Fill(leadingpflow50jety, eventweight);
        // pflow_j150_y_3550_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow50jeteta) > 2.5){
          pflow_j150_pt_3550_loweta = leadingpflow50jetpt;
          hist_j150_pt_3550_loweta->Fill(leadingpflow50jetpt, eventweight);
        }
        if (abs(leadingpflow50jeteta) < 2.5){
          pflow_j150_pt_3550_higheta = leadingpflow50jetpt;
          hist_j150_pt_3550_higheta->Fill(leadingpflow50jetpt, eventweight);
        }
      }
      else if (m_mu > 50){
        pflow_j150_pt_50 = (leadingpflow50jetpt);
        hist_j150_pt_50->Fill(leadingpflow50jetpt, eventweight);
        // pflow_j150_pt_50_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_50 = (leadingpflow50jety);
        hist_j150_y_50->Fill(leadingpflow50jety, eventweight);
        // pflow_j150_y_50_nofJVT = (leadingpflowjety_nofJVT);
        if (abs(leadingpflow50jeteta) > 2.5){
          pflow_j150_pt_50_loweta = leadingpflow50jetpt;
          hist_j150_pt_50_loweta->Fill(leadingpflow50jetpt, eventweight);
        }
        if (abs(leadingpflow50jeteta) < 2.5){
          pflow_j150_pt_50_higheta = leadingpflow50jetpt;
          hist_j150_pt_50_higheta->Fill(leadingpflow50jetpt, eventweight);
        }
      }
    // }
  }


if (npflow30jetsperevent_fJVT > 0){
    // 
    //  npflowjetsperevent > 0 to make sure we have one jet
    //  shouldn't matter if >1, leading values stay the same
    //
  // if (( leadingpflow30jetpt_fJVT > 120 ) && ( leadingpflow30jetpt_fJVT < 130 )) {}
  // else{
    if (m_mu < 15){
      pflow_j130_pt_15_fJVT = (leadingpflow30jetpt_fJVT);
      hist_j130_pt_015_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      // pflow_j130_pt_15_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j130_y_15_fJVT = (leadingpflow30jety_fJVT);
      hist_j130_y_015_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
      
      // pflow_j130_y_15_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow30jeteta_fJVT) > 2.5){
        pflow_j130_pt_15_loweta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_015_loweta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
      if (abs(leadingpflow30jeteta_fJVT) < 2.5){
        pflow_j130_pt_15_higheta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_015_higheta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
    }
    else if (m_mu < 25){
      pflow_j130_pt_1525_fJVT = (leadingpflow30jetpt_fJVT);
      hist_j130_pt_1525_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      // pflow_j130_pt_1525_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j130_y_1525_fJVT = (leadingpflow30jety_fJVT);
      hist_j130_y_1525_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
      // pflow_j130_y_1525_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow30jeteta_fJVT) > 2.5){
        pflow_j130_pt_1525_loweta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_1525_loweta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
      if (abs(leadingpflow30jeteta_fJVT) < 2.5){
        pflow_j130_pt_1525_higheta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_1525_higheta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
    }
    else if (m_mu < 35){
      pflow_j130_pt_2535_fJVT = (leadingpflow30jetpt_fJVT);
      hist_j130_pt_2535_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      // pflow_j130_pt_2535_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j130_y_2535_fJVT = (leadingpflow30jety_fJVT);
      hist_j130_y_2535_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
      // pflow_j130_y_2535_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow30jeteta_fJVT) > 2.5){
        pflow_j130_pt_2535_loweta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_2535_loweta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
          if (abs(leadingpflow30jeteta_fJVT) < 2.5){
        pflow_j130_pt_2535_higheta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_2535_higheta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
    }
    else if (m_mu < 50){
      pflow_j130_pt_3550_fJVT = (leadingpflow30jetpt_fJVT);
      hist_j130_pt_3550_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      // pflow_j130_pt_3550_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j130_y_3550_fJVT = (leadingpflow30jety_fJVT);
      hist_j130_y_3550_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
      // pflow_j130_y_3550_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow30jeteta_fJVT) > 2.5){
        pflow_j130_pt_3550_loweta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_3550_loweta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
      if (abs(leadingpflow30jeteta_fJVT) < 2.5){
        pflow_j130_pt_3550_higheta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_3550_higheta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
    }
    else if (m_mu > 50){
      pflow_j130_pt_50_fJVT = (leadingpflow30jetpt_fJVT);
      hist_j130_pt_50_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      // pflow_j130_pt_50_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j130_y_50_fJVT = (leadingpflow30jety_fJVT);
      hist_j130_y_50_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
      // pflow_j130_y_50_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow30jeteta_fJVT) > 2.5){
        pflow_j130_pt_50_loweta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_50_loweta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
      if (abs(leadingpflow30jeteta_fJVT) < 2.5){
        pflow_j130_pt_50_higheta_fJVT = leadingpflow30jetpt_fJVT;
        hist_j130_pt_50_higheta_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
      }
    }
  // }
}

if (npflow50jetsperevent_fJVT > 0){
    // 
    //  npflowjetsperevent > 0 to make sure we have one jet
    //  shouldn't matter if >1, leading values stay the same
    //
  // if (( leadingpflow50jetpt_fJVT > 120 ) && ( leadingpflow50jetpt_fJVT < 130 )) {}
  // else {
    if (m_mu < 15){
      pflow_j150_pt_15_fJVT = (leadingpflow50jetpt_fJVT);
      hist_j150_pt_015_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      // pflow_j150_pt_15_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j150_y_15_fJVT = (leadingpflow50jety_fJVT);
      hist_j150_y_015_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
      
      // pflow_j150_y_15_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow50jeteta_fJVT) > 2.5){
        pflow_j150_pt_15_loweta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_015_loweta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
      if (abs(leadingpflow50jeteta_fJVT) < 2.5){
        pflow_j150_pt_15_higheta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_015_higheta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
    }
    else if (m_mu < 25){
      pflow_j150_pt_1525_fJVT = (leadingpflow50jetpt_fJVT);
      hist_j150_pt_1525_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      // pflow_j150_pt_1525_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j150_y_1525_fJVT = (leadingpflow50jety_fJVT);
      hist_j150_y_1525_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
      // pflow_j150_y_1525_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow50jeteta_fJVT) > 2.5){
        pflow_j150_pt_1525_loweta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_1525_loweta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
      if (abs(leadingpflow50jeteta_fJVT) < 2.5){
        pflow_j150_pt_1525_higheta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_1525_higheta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
    }
    else if (m_mu < 35){
      pflow_j150_pt_2535_fJVT = (leadingpflow50jetpt_fJVT);
      hist_j150_pt_2535_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      // pflow_j150_pt_2535_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j150_y_2535_fJVT = (leadingpflow50jety_fJVT);
      hist_j150_y_2535_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
      // pflow_j150_y_2535_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow50jeteta_fJVT) > 2.5){
        pflow_j150_pt_2535_loweta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_2535_loweta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
          if (abs(leadingpflow50jeteta_fJVT) < 2.5){
        pflow_j150_pt_2535_higheta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_2535_higheta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
    }
    else if (m_mu < 50){
      pflow_j150_pt_3550_fJVT = (leadingpflow50jetpt_fJVT);
      hist_j150_pt_3550_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      // pflow_j150_pt_3550_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j150_y_3550_fJVT = (leadingpflow50jety_fJVT);
      hist_j150_y_3550_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
      // pflow_j150_y_3550_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow50jeteta_fJVT) > 2.5){
        pflow_j150_pt_3550_loweta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_3550_loweta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
      if (abs(leadingpflow50jeteta_fJVT) < 2.5){
        pflow_j150_pt_3550_higheta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_3550_higheta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
    }
    else if (m_mu > 50){
      pflow_j150_pt_50_fJVT = (leadingpflow50jetpt_fJVT);
      hist_j150_pt_50_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      // pflow_j150_pt_50_nofJVT = (leadingpflowjetpt_nofJVT);
      pflow_j150_y_50_fJVT = (leadingpflow50jety_fJVT);
      hist_j150_y_50_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
      // pflow_j150_y_50_nofJVT = (leadingpflowjety_nofJVT);
      if (abs(leadingpflow50jeteta_fJVT) > 2.5){
        pflow_j150_pt_50_loweta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_50_loweta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
      if (abs(leadingpflow50jeteta_fJVT) < 2.5){
        pflow_j150_pt_50_higheta_fJVT = leadingpflow50jetpt_fJVT;
        hist_j150_pt_50_higheta_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
      }
    }
  // }
}



  tree->Fill();
  return EL::StatusCode::SUCCESS;
// };
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
  // std::cout<<"BLS 3 finished finalize"<<std::endl;

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


  pflow_j150_pt_15 = 0;
  pflow_j150_pt_1525 = 0;
  pflow_j150_pt_2535 = 0;
  pflow_j150_pt_3550 = 0;
  pflow_j150_pt_50 = 0;

  pflow_j150_y_15 = -999;
  pflow_j150_y_1525 = -999;
  pflow_j150_y_2535 = -999;
  pflow_j150_y_3550 = -999;
  pflow_j150_y_50 = -999;

  pflow_j150_pt = 0;
  pflow_j150_eta = -999;
  pflow_j150_phi = -999;
  pflow_j150_m = -999;
  pflow_j150_y = -999;

  pflow_j150_pt_15_higheta = 0;
  pflow_j150_pt_1525_higheta = 0;
  pflow_j150_pt_2535_higheta = 0;
  pflow_j150_pt_3550_higheta = 0;
  pflow_j150_pt_50_higheta = 0;

  pflow_j150_pt_15_loweta = 0;
  pflow_j150_pt_1525_loweta = 0;
  pflow_j150_pt_2535_loweta = 0;
  pflow_j150_pt_3550_loweta = 0;
  pflow_j150_pt_50_loweta = 0;

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

  pflow_j130_pt_15_higheta = 0;
  pflow_j130_pt_1525_higheta = 0;
  pflow_j130_pt_2535_higheta = 0;
  pflow_j130_pt_3550_higheta = 0;
  pflow_j130_pt_50_higheta = 0;

  pflow_j130_pt_15_loweta = 0;
  pflow_j130_pt_1525_loweta = 0;
  pflow_j130_pt_2535_loweta = 0;
  pflow_j130_pt_3550_loweta = 0;
  pflow_j130_pt_50_loweta = 0;

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

  pflow_j130_pt_15_higheta_fJVT = 0;
  pflow_j130_pt_1525_higheta_fJVT = 0;
  pflow_j130_pt_2535_higheta_fJVT = 0;
  pflow_j130_pt_3550_higheta_fJVT = 0;
  pflow_j130_pt_50_higheta_fJVT = 0;

  pflow_j130_pt_15_loweta_fJVT = 0;
  pflow_j130_pt_1525_loweta_fJVT = 0;
  pflow_j130_pt_2535_loweta_fJVT = 0;
  pflow_j130_pt_3550_loweta_fJVT = 0;
  pflow_j130_pt_50_loweta_fJVT = 0;


  pflow_j150_pt_15_fJVT = 0;
  pflow_j150_pt_1525_fJVT = 0;
  pflow_j150_pt_2535_fJVT = 0;
  pflow_j150_pt_3550_fJVT = 0;
  pflow_j150_pt_50_fJVT = 0;

  pflow_j150_y_15_fJVT = -999;
  pflow_j150_y_1525_fJVT = -999;
  pflow_j150_y_2535_fJVT = -999;
  pflow_j150_y_3550_fJVT = -999;
  pflow_j150_y_50_fJVT = -999;

  pflow_j150_pt_fJVT = 0;
  pflow_j150_eta_fJVT = -999;
  pflow_j150_phi_fJVT = -999;
  pflow_j150_m_fJVT = -999;
  pflow_j150_y_fJVT = -999;

  pflow_j150_pt_15_higheta_fJVT = 0;
  pflow_j150_pt_1525_higheta_fJVT = 0;
  pflow_j150_pt_2535_higheta_fJVT = 0;
  pflow_j150_pt_3550_higheta_fJVT = 0;
  pflow_j150_pt_50_higheta_fJVT = 0;

  pflow_j150_pt_15_loweta_fJVT = 0;
  pflow_j150_pt_1525_loweta_fJVT = 0;
  pflow_j150_pt_2535_loweta_fJVT = 0;
  pflow_j150_pt_3550_loweta_fJVT = 0;
  pflow_j150_pt_50_loweta_fJVT = 0;

}

EL::StatusCode HGamMxAODAnalysis :: histFinalize ()
{
    // EL_RETURN_CHECK("BLS 4 finished event processing -- histFinalize", "");
  // std::cout<<"BLS 4 finished histFinalize"<<std::endl;

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





