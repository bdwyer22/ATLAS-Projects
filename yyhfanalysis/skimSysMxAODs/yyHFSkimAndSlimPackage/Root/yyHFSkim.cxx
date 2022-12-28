#include <AsgTools/MessageCheck.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <yyHFSkim/yyHFSkim.h>
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/Message.h"
#include <typeinfo>
#include <TH1.h>


/// Heper macro for checking xAOD::TReturnCode return values
#define EL_RETURN_CHECK( CONTEXT, EXP )     \
  do {              \
    if( ! EXP.isSuccess() ) {       \
    Error( CONTEXT,                                     \
    XAOD_MESSAGE( "Failed to execute: %s" ),            \
     #EXP );                                      \
      return EL::StatusCode::FAILURE;     \
    }             \
  } while( false )

// this is needed to distribute the algorithm to the workers
ClassImp(yyHFSkim)


yyHFSkim :: yyHFSkim ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
m_mcType = mc16a;

}



EL::StatusCode yyHFSkim :: setupJob (EL::Job& job)
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



EL::StatusCode yyHFSkim :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // myclass = new TH1F(...);
  tree = new TTree("CollectionTree", "tree with yyHF variables per event");

// *****************************************************************************
// *************************** NOMINAL BRANCHES ********************************
// *****************************************************************************


tree->Branch("mu",     &m_mu);
tree->Branch("HGamWeight",     &HGamWeight);
tree->Branch("eventNumber",     &eventNumber);
tree->Branch("XSWeight",     &XSWeight);

tree->Branch("yyHF_leadjet_truthlabel",     &yyHF_leadjet_truthlabel);
tree->Branch("yyHF_subleadjet_truthlabel",     &yyHF_subleadjet_truthlabel);
tree->Branch("yyHF_leadjet_btagbin",     &yyHF_leadjet_btagbin);
tree->Branch("yyHF_subleadjet_btagbin",     &yyHF_subleadjet_btagbin);
tree->Branch("yyHF_Njet_central",     &yyHF_Njet_central);
tree->Branch("yyHFjj_weight",     &yyHFjj_weight);
tree->Branch("yyHFj_weight",     &yyHFj_weight);
tree->Branch("yyHF_met",     &yyHF_met);
tree->Branch("yyHF_nelectron",     &yyHF_nelectron);
tree->Branch("yyHF_nmuon",     &yyHF_nmuon);
tree->Branch("isPassed",     &isPassed);
tree->Branch("m_yy",     &m_yy);
tree->Branch("yyHF_cutFlow",     &yyHF_cutFlow);
tree->Branch("m_yyjj",     &m_yyjj);
tree->Branch("pT_yy",     &pT_yy);
tree->Branch("yyHF_subleadjet_pt",     &yyHF_subleadjet_pt);
tree->Branch("yyHF_subleadjet_phi",     &yyHF_subleadjet_phi);
tree->Branch("yyHF_subleadjet_m",     &yyHF_subleadjet_m);
tree->Branch("yyHF_subleadjet_eta",     &yyHF_subleadjet_eta);
tree->Branch("yyHF_leadjet_pt",     &yyHF_leadjet_pt);
tree->Branch("yyHF_leadjet_phi",     &yyHF_leadjet_phi);
tree->Branch("yyHF_leadjet_m",     &yyHF_leadjet_m);
tree->Branch("yyHF_leadjet_eta",     &yyHF_leadjet_eta);
tree->Branch("Truth_yyHF_N_bjets",     &Truth_yyHF_N_bjets);
tree->Branch("Truth_yyHF_N_cjets",     &Truth_yyHF_N_cjets);
tree->Branch("Truth_yyHF_Njet_central",     &Truth_yyHF_Njet_central);
tree->Branch("Truth_yyHF_cutFlow",     &Truth_yyHF_cutFlow);
tree->Branch("Truth_yyHF_jcat",     &Truth_yyHF_jcat);
tree->Branch("Truth_yyHF_jjcat",     &Truth_yyHF_jjcat);
tree->Branch("Truth_yyHF_met",     &Truth_yyHF_met);
tree->Branch("Truth_yyHF_nelectron",     &Truth_yyHF_nelectron);
tree->Branch("Truth_yyHF_nmuon",     &Truth_yyHF_nmuon);

// *****************************************************************************
// ************************* END NOMINAL BRANCHES ******************************
// *****************************************************************************



// *****************************************************************************
// ************************* SYSTEMATICS BRANCHES ******************************
// *****************************************************************************
tree->Branch("FT_EFF_Eigen_Light_0__1up_pT_yy",     &FT_EFF_Eigen_Light_0__1up_pT_yy);
tree->Branch("FT_EFF_Eigen_Light_1__1up_pT_yy",     &FT_EFF_Eigen_Light_1__1up_pT_yy);
tree->Branch("FT_EFF_Eigen_Light_2__1up_pT_yy",     &FT_EFF_Eigen_Light_2__1up_pT_yy);
tree->Branch("FT_EFF_Eigen_Light_3__1up_pT_yy",     &FT_EFF_Eigen_Light_3__1up_pT_yy);
tree->Branch("FT_EFF_Eigen_Light_4__1up_pT_yy",     &FT_EFF_Eigen_Light_4__1up_pT_yy);
tree->Branch("FT_EFF_Eigen_Light_0__1up_HGamWeight",     &FT_EFF_Eigen_Light_0__1up_HGamWeight);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_truthlabel",     &FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_btagbin",     &FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_Njet_central",     &FT_EFF_Eigen_Light_0__1up_yyHF_Njet_central);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHFjj_weight",     &FT_EFF_Eigen_Light_0__1up_yyHFjj_weight);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHFj_weight",     &FT_EFF_Eigen_Light_0__1up_yyHFj_weight);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_met",     &FT_EFF_Eigen_Light_0__1up_yyHF_met);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_nelectron",     &FT_EFF_Eigen_Light_0__1up_yyHF_nelectron);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_nmuon",     &FT_EFF_Eigen_Light_0__1up_yyHF_nmuon);
tree->Branch("FT_EFF_Eigen_Light_0__1up_isPassed",     &FT_EFF_Eigen_Light_0__1up_isPassed);
tree->Branch("FT_EFF_Eigen_Light_0__1up_m_yy",     &FT_EFF_Eigen_Light_0__1up_m_yy);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_cutFlow",     &FT_EFF_Eigen_Light_0__1up_yyHF_cutFlow);
tree->Branch("FT_EFF_Eigen_Light_0__1up_m_yyjj",     &FT_EFF_Eigen_Light_0__1up_m_yyjj);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_pt",     &FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_phi",     &FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_m",     &FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_m);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_eta",     &FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_pt",     &FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_phi",     &FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_m",     &FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_m);
tree->Branch("FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_eta",     &FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_1__1up_HGamWeight",     &FT_EFF_Eigen_Light_1__1up_HGamWeight);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_truthlabel",     &FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_btagbin",     &FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_Njet_central",     &FT_EFF_Eigen_Light_1__1up_yyHF_Njet_central);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHFjj_weight",     &FT_EFF_Eigen_Light_1__1up_yyHFjj_weight);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHFj_weight",     &FT_EFF_Eigen_Light_1__1up_yyHFj_weight);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_met",     &FT_EFF_Eigen_Light_1__1up_yyHF_met);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_nelectron",     &FT_EFF_Eigen_Light_1__1up_yyHF_nelectron);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_nmuon",     &FT_EFF_Eigen_Light_1__1up_yyHF_nmuon);
tree->Branch("FT_EFF_Eigen_Light_1__1up_isPassed",     &FT_EFF_Eigen_Light_1__1up_isPassed);
tree->Branch("FT_EFF_Eigen_Light_1__1up_m_yy",     &FT_EFF_Eigen_Light_1__1up_m_yy);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_cutFlow",     &FT_EFF_Eigen_Light_1__1up_yyHF_cutFlow);
tree->Branch("FT_EFF_Eigen_Light_1__1up_m_yyjj",     &FT_EFF_Eigen_Light_1__1up_m_yyjj);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_pt",     &FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_phi",     &FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_m",     &FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_m);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_eta",     &FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_pt",     &FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_phi",     &FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_m",     &FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_m);
tree->Branch("FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_eta",     &FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_2__1up_HGamWeight",     &FT_EFF_Eigen_Light_2__1up_HGamWeight);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_truthlabel",     &FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_btagbin",     &FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_Njet_central",     &FT_EFF_Eigen_Light_2__1up_yyHF_Njet_central);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHFjj_weight",     &FT_EFF_Eigen_Light_2__1up_yyHFjj_weight);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHFj_weight",     &FT_EFF_Eigen_Light_2__1up_yyHFj_weight);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_met",     &FT_EFF_Eigen_Light_2__1up_yyHF_met);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_nelectron",     &FT_EFF_Eigen_Light_2__1up_yyHF_nelectron);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_nmuon",     &FT_EFF_Eigen_Light_2__1up_yyHF_nmuon);
tree->Branch("FT_EFF_Eigen_Light_2__1up_isPassed",     &FT_EFF_Eigen_Light_2__1up_isPassed);
tree->Branch("FT_EFF_Eigen_Light_2__1up_m_yy",     &FT_EFF_Eigen_Light_2__1up_m_yy);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_cutFlow",     &FT_EFF_Eigen_Light_2__1up_yyHF_cutFlow);
tree->Branch("FT_EFF_Eigen_Light_2__1up_m_yyjj",     &FT_EFF_Eigen_Light_2__1up_m_yyjj);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_pt",     &FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_phi",     &FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_m",     &FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_m);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_eta",     &FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_pt",     &FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_phi",     &FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_m",     &FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_m);
tree->Branch("FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_eta",     &FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_3__1up_HGamWeight",     &FT_EFF_Eigen_Light_3__1up_HGamWeight);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_truthlabel",     &FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_btagbin",     &FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_Njet_central",     &FT_EFF_Eigen_Light_3__1up_yyHF_Njet_central);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHFjj_weight",     &FT_EFF_Eigen_Light_3__1up_yyHFjj_weight);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHFj_weight",     &FT_EFF_Eigen_Light_3__1up_yyHFj_weight);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_met",     &FT_EFF_Eigen_Light_3__1up_yyHF_met);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_nelectron",     &FT_EFF_Eigen_Light_3__1up_yyHF_nelectron);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_nmuon",     &FT_EFF_Eigen_Light_3__1up_yyHF_nmuon);
tree->Branch("FT_EFF_Eigen_Light_3__1up_isPassed",     &FT_EFF_Eigen_Light_3__1up_isPassed);
tree->Branch("FT_EFF_Eigen_Light_3__1up_m_yy",     &FT_EFF_Eigen_Light_3__1up_m_yy);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_cutFlow",     &FT_EFF_Eigen_Light_3__1up_yyHF_cutFlow);
tree->Branch("FT_EFF_Eigen_Light_3__1up_m_yyjj",     &FT_EFF_Eigen_Light_3__1up_m_yyjj);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_pt",     &FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_phi",     &FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_m",     &FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_m);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_eta",     &FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_pt",     &FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_phi",     &FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_m",     &FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_m);
tree->Branch("FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_eta",     &FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_4__1up_HGamWeight",     &FT_EFF_Eigen_Light_4__1up_HGamWeight);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_truthlabel",     &FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_truthlabel",     &FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_truthlabel);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_btagbin",     &FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_btagbin",     &FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_btagbin);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_Njet_central",     &FT_EFF_Eigen_Light_4__1up_yyHF_Njet_central);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHFjj_weight",     &FT_EFF_Eigen_Light_4__1up_yyHFjj_weight);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHFj_weight",     &FT_EFF_Eigen_Light_4__1up_yyHFj_weight);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_met",     &FT_EFF_Eigen_Light_4__1up_yyHF_met);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_nelectron",     &FT_EFF_Eigen_Light_4__1up_yyHF_nelectron);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_nmuon",     &FT_EFF_Eigen_Light_4__1up_yyHF_nmuon);
tree->Branch("FT_EFF_Eigen_Light_4__1up_isPassed",     &FT_EFF_Eigen_Light_4__1up_isPassed);
tree->Branch("FT_EFF_Eigen_Light_4__1up_m_yy",     &FT_EFF_Eigen_Light_4__1up_m_yy);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_cutFlow",     &FT_EFF_Eigen_Light_4__1up_yyHF_cutFlow);
tree->Branch("FT_EFF_Eigen_Light_4__1up_m_yyjj",     &FT_EFF_Eigen_Light_4__1up_m_yyjj);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_pt",     &FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_phi",     &FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_m",     &FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_m);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_eta",     &FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_eta);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_pt",     &FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_pt);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_phi",     &FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_phi);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_m",     &FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_m);
tree->Branch("FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_eta",     &FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_eta);

// *****************************************************************************
// *********************** END SYSTEMATICS BRANCHES ****************************
// *****************************************************************************

  
  wk()->addOutput(tree);


const std::vector<TString> s_cutDescs = {
    "#it{N}_{xAOD}", "#it{N}_{DxAOD}", "All events", "No duplicates", "GRL", "Pass trigger", "Detector DQ", "Has PV",
    "2 loose photons", "e-#gamma ambiguity", "Trigger match", "tight ID", "isolation", "rel. #it{p}_{T} cuts",
    "#it{m}_{#gamma#gamma} #in [105,160] GeV"
  };


hist_cutflow = new TH1D("hist_cutflow", "hist_cutflow", 15, 0, 15);
hist_cutflow_noDalitz = new TH1D("hist_cutflow_noDalitz", "hist_cutflow_noDalitz", 15, 0, 15);
hist_cutflow_weighted = new TH1D("hist_cutflow_weighted", "hist_cutflow_weighted", 15, 0, 15);
hist_cutflow_noDalitz_weighted = new TH1D("hist_cutflow_noDalitz_weighted", "hist_cutflow_noDalitz_weighted", 15, 0, 15);

int Ncuts = s_cutDescs.size();
for (int bin = 1; bin <= Ncuts; ++bin)
  { 
    hist_cutflow->GetXaxis()->SetBinLabel(bin, s_cutDescs[bin - 1]); 
    hist_cutflow_noDalitz->GetXaxis()->SetBinLabel(bin, s_cutDescs[bin - 1]); 
    hist_cutflow_weighted->GetXaxis()->SetBinLabel(bin, s_cutDescs[bin - 1]); 
    hist_cutflow_noDalitz_weighted->GetXaxis()->SetBinLabel(bin, s_cutDescs[bin - 1]); 
  }

  wk()->addOutput(hist_cutflow);
  wk()->addOutput(hist_cutflow_noDalitz);
  wk()->addOutput(hist_cutflow_weighted);
  wk()->addOutput(hist_cutflow_noDalitz_weighted);


  return EL::StatusCode::SUCCESS;
}



EL::StatusCode yyHFSkim :: fileExecute ()
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
        std::cerr << "cutflow_hist_noDalitz_weighted name:  " << histname << std::endl;
        cutflow_hist_noDalitz_weighted = (TH1F*)key->ReadObj();
      }
      else if (histname.Contains("weighted")){
        std::cerr << "cutflow_hist_weighted name:  " << histname << std::endl;
        cutflow_hist_weighted = (TH1F*)key->ReadObj();
      }
      else if (histname.Contains("noDalitz")){
        std::cerr << "cutflow_hist_noDalitz name:  " << histname << std::endl;
        cutflow_hist_noDalitz = (TH1F*)key->ReadObj();
      }
      else {
        std::cerr << "cutflow name:  " << histname << std::endl;
        cutflow_hist = (TH1F*)key->ReadObj();
      }
    }

    // sum_weights = ((cutflow_hist->GetBinContent(1) / cutflow_hist->GetBinContent(2)) * cutflow_hist->GetBinContent(3));
    std::cout << cutflow_hist_noDalitz_weighted->GetName() << std::endl;
   hist_cutflow_noDalitz_weighted->Add(cutflow_hist_noDalitz_weighted);
   hist_cutflow_weighted->Add(cutflow_hist_weighted);
   hist_cutflow_noDalitz->Add(cutflow_hist_noDalitz);
   hist_cutflow->Add(cutflow_hist);
  }

  // std::cout << "Sum_weights = " << sum_weights << std::endl;

  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode yyHFSkim :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode yyHFSkim :: initialize ()
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



EL::StatusCode yyHFSkim :: execute ()
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
  
  const xAOD::EventInfo *EventInfo = NULL;
  if (! event->retrieve(EventInfo, "EventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve EventInfo. Exiting.");
    return EL::StatusCode::FAILURE;
  }

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

// *****************************************************************************
// ************************* SYSTEMATICS BRANCHES ******************************
// *****************************************************************************


  const xAOD::EventInfo *HGamEventInfo_FT_EFF_Eigen_Light_0__1up = NULL;
  if (! event->retrieve(HGamEventInfo_FT_EFF_Eigen_Light_0__1up, "HGamEventInfo_FT_EFF_Eigen_Light_0__1up").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo_FT_EFF_Eigen_Light_0__1up. Exiting.");
    return EL::StatusCode::FAILURE;
  }
  const xAOD::EventInfo *HGamEventInfo_FT_EFF_Eigen_Light_1__1up = NULL;
  if (! event->retrieve(HGamEventInfo_FT_EFF_Eigen_Light_1__1up, "HGamEventInfo_FT_EFF_Eigen_Light_1__1up").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo_FT_EFF_Eigen_Light_1__1up. Exiting.");
    return EL::StatusCode::FAILURE;
  }
  const xAOD::EventInfo *HGamEventInfo_FT_EFF_Eigen_Light_2__1up = NULL;
  if (! event->retrieve(HGamEventInfo_FT_EFF_Eigen_Light_2__1up, "HGamEventInfo_FT_EFF_Eigen_Light_2__1up").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo_FT_EFF_Eigen_Light_2__1up. Exiting.");
    return EL::StatusCode::FAILURE;
  }
  const xAOD::EventInfo *HGamEventInfo_FT_EFF_Eigen_Light_3__1up = NULL;
  if (! event->retrieve(HGamEventInfo_FT_EFF_Eigen_Light_3__1up, "HGamEventInfo_FT_EFF_Eigen_Light_3__1up").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo_FT_EFF_Eigen_Light_3__1up. Exiting.");
    return EL::StatusCode::FAILURE;
  }
  const xAOD::EventInfo *HGamEventInfo_FT_EFF_Eigen_Light_4__1up = NULL;
  if (! event->retrieve(HGamEventInfo_FT_EFF_Eigen_Light_4__1up, "HGamEventInfo_FT_EFF_Eigen_Light_4__1up").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo_FT_EFF_Eigen_Light_4__1up. Exiting.");
    return EL::StatusCode::FAILURE;
  }

// *****************************************************************************
// *********************** END SYSTEMATICS BRANCHES ****************************
// *****************************************************************************


  if (m_mcType == mc16a){lumi_mc16 = 36209.04;}// sum_weights = 104724945.164;}
  else if (m_mcType == mc16d){lumi_mc16 = 44385.7;}// sum_weights = 131279689.835;}
  else if (m_mcType == mc16e){lumi_mc16 = 58450.1;}// sum_weights = 35667314.9538;}
  else {lumi_mc16 = 0; Error("execute()", "No period set. Exiting.");}

  
  // eventweight = ((
  //         *  
  //         * HGamEventInfo->auxdataConst<float>("weightJvt")
  //         * lumi_mc16)
  //         / sum_weights);

    eventNumber = EventInfo->auxdataConst<ULong64_t>("eventNumber");
    XSWeight = HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") ;


// VaryPerEvent:
HGamWeight = HGamEventInfo->auxdataConst<float>("weight");
m_mu   = static_cast<int>(m_eventInfoCont->actualInteractionsPerCrossing());
pT_yy = HGamEventInfo->auxdata<float>("pT_yy");
yyHF_leadjet_truthlabel = HGamEventInfo->auxdata<int>("yyHF_leadjet_truthlabel");
yyHF_subleadjet_truthlabel = HGamEventInfo->auxdata<int>("yyHF_subleadjet_truthlabel");
yyHF_leadjet_btagbin = HGamEventInfo->auxdata<int>("yyHF_leadjet_btagbin");
yyHF_subleadjet_btagbin = HGamEventInfo->auxdata<int>("yyHF_subleadjet_btagbin");
yyHF_Njet_central = HGamEventInfo->auxdata<int>("yyHF_Njet_central");
yyHFjj_weight = HGamEventInfo->auxdata<float>("yyHFjj_weight");
yyHFj_weight = HGamEventInfo->auxdata<float>("yyHFj_weight");
yyHF_met = HGamEventInfo->auxdata<float>("yyHF_met");
yyHF_nelectron = HGamEventInfo->auxdata<int>("yyHF_nelectron");
yyHF_nmuon = HGamEventInfo->auxdata<int>("yyHF_nmuon");
isPassed = HGamEventInfo->auxdata<char>("isPassed");
yyHF_cutFlow = HGamEventInfo->auxdata<int>("yyHF_cutFlow");
m_yy = HGamEventInfo->auxdata<float>("m_yy");
m_yyjj = HGamEventInfo->auxdata<float>("m_yyjj");
yyHF_subleadjet_pt = HGamEventInfo->auxdata<float>("yyHF_subleadjet_pt");
yyHF_subleadjet_phi = HGamEventInfo->auxdata<float>("yyHF_subleadjet_phi");
yyHF_subleadjet_m = HGamEventInfo->auxdata<float>("yyHF_subleadjet_m");
yyHF_subleadjet_eta = HGamEventInfo->auxdata<float>("yyHF_subleadjet_eta");
yyHF_leadjet_pt = HGamEventInfo->auxdata<float>("yyHF_leadjet_pt");
yyHF_leadjet_phi = HGamEventInfo->auxdata<float>("yyHF_leadjet_phi");
yyHF_leadjet_m = HGamEventInfo->auxdata<float>("yyHF_leadjet_m");
yyHF_leadjet_eta = HGamEventInfo->auxdata<float>("yyHF_leadjet_eta");

Truth_yyHF_Njet_central = HGamTruthEventInfo->auxdata<int>("yyHF_Njet_central");
Truth_yyHF_N_bjets = HGamTruthEventInfo->auxdata<int>("yyHF_N_bjets");
Truth_yyHF_N_cjets = HGamTruthEventInfo->auxdata<int>("yyHF_N_cjets");
Truth_yyHF_cutFlow = HGamTruthEventInfo->auxdata<int>("yyHF_cutFlow");
Truth_yyHF_jcat = HGamTruthEventInfo->auxdata<int>("yyHF_jcat");
Truth_yyHF_jjcat = HGamTruthEventInfo->auxdata<int>("yyHF_jjcat");
Truth_yyHF_nelectron = HGamTruthEventInfo->auxdata<int>("yyHF_nelectron");
Truth_yyHF_nmuon = HGamTruthEventInfo->auxdata<int>("yyHF_nmuon");
Truth_yyHF_met = HGamTruthEventInfo->auxdata<float>("yyHF_met");

FT_EFF_Eigen_Light_0__1up_HGamWeight = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdataConst<float>("weight");
FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<int>("yyHF_leadjet_truthlabel");
FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<int>("yyHF_subleadjet_truthlabel");
FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<int>("yyHF_leadjet_btagbin");
FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<int>("yyHF_subleadjet_btagbin");
FT_EFF_Eigen_Light_0__1up_yyHF_Njet_central = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<int>("yyHF_Njet_central");
FT_EFF_Eigen_Light_0__1up_yyHFjj_weight = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHFjj_weight");
FT_EFF_Eigen_Light_0__1up_yyHFj_weight = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHFj_weight");
FT_EFF_Eigen_Light_0__1up_yyHF_met = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_met");
FT_EFF_Eigen_Light_0__1up_yyHF_nelectron = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<int>("yyHF_nelectron");
FT_EFF_Eigen_Light_0__1up_yyHF_nmuon = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<int>("yyHF_nmuon");
FT_EFF_Eigen_Light_0__1up_isPassed = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<char>("isPassed");
FT_EFF_Eigen_Light_0__1up_yyHF_cutFlow = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<int>("yyHF_cutFlow");
FT_EFF_Eigen_Light_0__1up_m_yy = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("m_yy");
FT_EFF_Eigen_Light_0__1up_m_yyjj = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("m_yyjj");
FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_subleadjet_pt");
FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_subleadjet_phi");
FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_subleadjet_m");
FT_EFF_Eigen_Light_0__1up_yyHF_subleadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_subleadjet_eta");
FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_leadjet_pt");
FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_leadjet_phi");
FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_leadjet_m");
FT_EFF_Eigen_Light_0__1up_yyHF_leadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("yyHF_leadjet_eta");
FT_EFF_Eigen_Light_1__1up_HGamWeight = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdataConst<float>("weight");
FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<int>("yyHF_leadjet_truthlabel");
FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<int>("yyHF_subleadjet_truthlabel");
FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<int>("yyHF_leadjet_btagbin");
FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<int>("yyHF_subleadjet_btagbin");
FT_EFF_Eigen_Light_1__1up_yyHF_Njet_central = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<int>("yyHF_Njet_central");
FT_EFF_Eigen_Light_1__1up_yyHFjj_weight = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHFjj_weight");
FT_EFF_Eigen_Light_1__1up_yyHFj_weight = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHFj_weight");
FT_EFF_Eigen_Light_1__1up_yyHF_met = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_met");
FT_EFF_Eigen_Light_1__1up_yyHF_nelectron = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<int>("yyHF_nelectron");
FT_EFF_Eigen_Light_1__1up_yyHF_nmuon = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<int>("yyHF_nmuon");
FT_EFF_Eigen_Light_1__1up_isPassed = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<char>("isPassed");
FT_EFF_Eigen_Light_1__1up_yyHF_cutFlow = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<int>("yyHF_cutFlow");
FT_EFF_Eigen_Light_1__1up_m_yy = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("m_yy");
FT_EFF_Eigen_Light_1__1up_m_yyjj = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("m_yyjj");
FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_subleadjet_pt");
FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_subleadjet_phi");
FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_subleadjet_m");
FT_EFF_Eigen_Light_1__1up_yyHF_subleadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_subleadjet_eta");
FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_leadjet_pt");
FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_leadjet_phi");
FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_leadjet_m");
FT_EFF_Eigen_Light_1__1up_yyHF_leadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("yyHF_leadjet_eta");
FT_EFF_Eigen_Light_2__1up_HGamWeight = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdataConst<float>("weight");
FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<int>("yyHF_leadjet_truthlabel");
FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<int>("yyHF_subleadjet_truthlabel");
FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<int>("yyHF_leadjet_btagbin");
FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<int>("yyHF_subleadjet_btagbin");
FT_EFF_Eigen_Light_2__1up_yyHF_Njet_central = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<int>("yyHF_Njet_central");
FT_EFF_Eigen_Light_2__1up_yyHFjj_weight = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHFjj_weight");
FT_EFF_Eigen_Light_2__1up_yyHFj_weight = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHFj_weight");
FT_EFF_Eigen_Light_2__1up_yyHF_met = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_met");
FT_EFF_Eigen_Light_2__1up_yyHF_nelectron = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<int>("yyHF_nelectron");
FT_EFF_Eigen_Light_2__1up_yyHF_nmuon = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<int>("yyHF_nmuon");
FT_EFF_Eigen_Light_2__1up_isPassed = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<char>("isPassed");
FT_EFF_Eigen_Light_2__1up_yyHF_cutFlow = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<int>("yyHF_cutFlow");
FT_EFF_Eigen_Light_2__1up_m_yy = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("m_yy");
FT_EFF_Eigen_Light_2__1up_m_yyjj = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("m_yyjj");
FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_subleadjet_pt");
FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_subleadjet_phi");
FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_subleadjet_m");
FT_EFF_Eigen_Light_2__1up_yyHF_subleadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_subleadjet_eta");
FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_leadjet_pt");
FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_leadjet_phi");
FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_leadjet_m");
FT_EFF_Eigen_Light_2__1up_yyHF_leadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("yyHF_leadjet_eta");
FT_EFF_Eigen_Light_3__1up_HGamWeight = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdataConst<float>("weight");
FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<int>("yyHF_leadjet_truthlabel");
FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<int>("yyHF_subleadjet_truthlabel");
FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<int>("yyHF_leadjet_btagbin");
FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<int>("yyHF_subleadjet_btagbin");
FT_EFF_Eigen_Light_3__1up_yyHF_Njet_central = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<int>("yyHF_Njet_central");
FT_EFF_Eigen_Light_3__1up_yyHFjj_weight = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHFjj_weight");
FT_EFF_Eigen_Light_3__1up_yyHFj_weight = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHFj_weight");
FT_EFF_Eigen_Light_3__1up_yyHF_met = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_met");
FT_EFF_Eigen_Light_3__1up_yyHF_nelectron = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<int>("yyHF_nelectron");
FT_EFF_Eigen_Light_3__1up_yyHF_nmuon = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<int>("yyHF_nmuon");
FT_EFF_Eigen_Light_3__1up_isPassed = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<char>("isPassed");
FT_EFF_Eigen_Light_3__1up_yyHF_cutFlow = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<int>("yyHF_cutFlow");
FT_EFF_Eigen_Light_3__1up_m_yy = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("m_yy");
FT_EFF_Eigen_Light_3__1up_m_yyjj = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("m_yyjj");
FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_subleadjet_pt");
FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_subleadjet_phi");
FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_subleadjet_m");
FT_EFF_Eigen_Light_3__1up_yyHF_subleadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_subleadjet_eta");
FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_leadjet_pt");
FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_leadjet_phi");
FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_leadjet_m");
FT_EFF_Eigen_Light_3__1up_yyHF_leadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("yyHF_leadjet_eta");
FT_EFF_Eigen_Light_4__1up_HGamWeight = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdataConst<float>("weight");
FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<int>("yyHF_leadjet_truthlabel");
FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_truthlabel = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<int>("yyHF_subleadjet_truthlabel");
FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<int>("yyHF_leadjet_btagbin");
FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_btagbin = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<int>("yyHF_subleadjet_btagbin");
FT_EFF_Eigen_Light_4__1up_yyHF_Njet_central = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<int>("yyHF_Njet_central");
FT_EFF_Eigen_Light_4__1up_yyHFjj_weight = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHFjj_weight");
FT_EFF_Eigen_Light_4__1up_yyHFj_weight = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHFj_weight");
FT_EFF_Eigen_Light_4__1up_yyHF_met = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_met");
FT_EFF_Eigen_Light_4__1up_yyHF_nelectron = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<int>("yyHF_nelectron");
FT_EFF_Eigen_Light_4__1up_yyHF_nmuon = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<int>("yyHF_nmuon");
FT_EFF_Eigen_Light_4__1up_isPassed = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<char>("isPassed");
FT_EFF_Eigen_Light_4__1up_yyHF_cutFlow = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<int>("yyHF_cutFlow");
FT_EFF_Eigen_Light_4__1up_m_yy = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("m_yy");
FT_EFF_Eigen_Light_4__1up_m_yyjj = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("m_yyjj");
FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_subleadjet_pt");
FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_subleadjet_phi");
FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_subleadjet_m");
FT_EFF_Eigen_Light_4__1up_yyHF_subleadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_subleadjet_eta");
FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_pt = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_leadjet_pt");
FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_phi = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_leadjet_phi");
FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_m = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_leadjet_m");
FT_EFF_Eigen_Light_4__1up_yyHF_leadjet_eta = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("yyHF_leadjet_eta");


FT_EFF_Eigen_Light_0__1up_pT_yy = HGamEventInfo_FT_EFF_Eigen_Light_0__1up->auxdata<float>("pT_yy");
FT_EFF_Eigen_Light_1__1up_pT_yy = HGamEventInfo_FT_EFF_Eigen_Light_1__1up->auxdata<float>("pT_yy");
FT_EFF_Eigen_Light_2__1up_pT_yy = HGamEventInfo_FT_EFF_Eigen_Light_2__1up->auxdata<float>("pT_yy");
FT_EFF_Eigen_Light_3__1up_pT_yy = HGamEventInfo_FT_EFF_Eigen_Light_3__1up->auxdata<float>("pT_yy");
FT_EFF_Eigen_Light_4__1up_pT_yy = HGamEventInfo_FT_EFF_Eigen_Light_4__1up->auxdata<float>("pT_yy");

  tree->Fill();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode yyHFSkim :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode yyHFSkim :: finalize ()
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


void yyHFSkim::ResetVariables()
{

}

EL::StatusCode yyHFSkim :: histFinalize ()
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






