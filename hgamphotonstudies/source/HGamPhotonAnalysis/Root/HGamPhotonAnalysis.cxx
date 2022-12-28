#include <AsgTools/MessageCheck.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <HGamPhotonAnalysis/HGamPhotonAnalysis.h>
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
ClassImp(HGamPhotonAnalysis)


HGamPhotonAnalysis :: HGamPhotonAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode HGamPhotonAnalysis :: setupJob (EL::Job& job)
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



EL::StatusCode HGamPhotonAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  tree = new TTree("hgamvariables", "tree with hgam variables per event");

  TFile *purity_file = new TFile("/home/bstamas/HGam_13TeV_2x2DBkgDComp_SherpaAF2_139.0ifb_XSection.root");
  // TFile *purity_file = new TFile("/home/bstamas/CONF_HGam_13TeV_2x2DBkgDComp_SherpaAF2_139.0ifb_XSection.root");
  // TFile *purity_file = new TFile("/afs/cern.ch/user/b/bstamas/HGam_13TeV_2x2DBkgDComp_SherpaAF2_139.0ifb_XSection.root");

  gr_inclusive_gg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_inclusive_gg_purity_TotErr");
  gr_inclusive_gjjg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_inclusive_gjjg_purity_TotErr");
  gr_inclusive_jj_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_inclusive_jj_purity_TotErr");

  gr_m_yy_gg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_m_yy_gg_purity_TotErr");
  gr_m_yy_gjjg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_m_yy_gjjg_purity_TotErr");
  gr_m_yy_jj_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_m_yy_jj_purity_TotErr");

  gr_mu_gg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_mu_gg_purity_TotErr");
  gr_mu_gjjg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_mu_gjjg_purity_TotErr");
  gr_mu_jj_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_mu_jj_purity_TotErr");

  gr_pT_j1_30_gg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_pT_j1_30_gg_purity_TotErr");
  gr_pT_j1_30_gjjg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_pT_j1_30_gjjg_purity_TotErr");
  gr_pT_j1_30_jj_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_pT_j1_30_jj_purity_TotErr");

  gr_eta_j1_30_gg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_eta_j1_30_gg_purity_TotErr");
  gr_eta_j1_30_gjjg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_eta_j1_30_gjjg_purity_TotErr");
  gr_eta_j1_30_jj_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_eta_j1_30_jj_purity_TotErr");

  gr_abs_eta_j1_30_gg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_abs_eta_j1_30_gg_purity_TotErr");
  gr_abs_eta_j1_30_gjjg_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_abs_eta_j1_30_gjjg_purity_TotErr");
  gr_abs_eta_j1_30_jj_purity_TotErr = (TGraphAsymmErrors*)purity_file->Get("gr_abs_eta_j1_30_jj_purity_TotErr");

  hist_yy_pflowj1_pt_ptj1_purityweight = new TH1F("hist_yy_pflowj1_pt_ptj1_purityweight", "hist_yy_pflowj1_pt_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_ptj1_purityweight = new TH1F("hist_jj_pflowj1_pt_ptj1_purityweight", "hist_jj_pflowj1_pt_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_ptj1_purityweight = new TH1F("hist_yj_pflowj1_pt_ptj1_purityweight", "hist_yj_pflowj1_pt_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_ptj1_purityweight = new TH1F("hist_jy_pflowj1_pt_ptj1_purityweight", "hist_jy_pflowj1_pt_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_010_ptj1_purityweight = new TH1F("hist_yy_pflowj1_pt_010_ptj1_purityweight", "hist_yy_pflowj1_pt_010_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_010_ptj1_purityweight = new TH1F("hist_jj_pflowj1_pt_010_ptj1_purityweight", "hist_jj_pflowj1_pt_010_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_010_ptj1_purityweight = new TH1F("hist_yj_pflowj1_pt_010_ptj1_purityweight", "hist_yj_pflowj1_pt_010_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_010_ptj1_purityweight = new TH1F("hist_jy_pflowj1_pt_010_ptj1_purityweight", "hist_jy_pflowj1_pt_010_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_1020_ptj1_purityweight = new TH1F("hist_yy_pflowj1_pt_1020_ptj1_purityweight", "hist_yy_pflowj1_pt_1020_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_1020_ptj1_purityweight = new TH1F("hist_jj_pflowj1_pt_1020_ptj1_purityweight", "hist_jj_pflowj1_pt_1020_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_1020_ptj1_purityweight = new TH1F("hist_yj_pflowj1_pt_1020_ptj1_purityweight", "hist_yj_pflowj1_pt_1020_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_1020_ptj1_purityweight = new TH1F("hist_jy_pflowj1_pt_1020_ptj1_purityweight", "hist_jy_pflowj1_pt_1020_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_2030_ptj1_purityweight = new TH1F("hist_yy_pflowj1_pt_2030_ptj1_purityweight", "hist_yy_pflowj1_pt_2030_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_2030_ptj1_purityweight = new TH1F("hist_jj_pflowj1_pt_2030_ptj1_purityweight", "hist_jj_pflowj1_pt_2030_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_2030_ptj1_purityweight = new TH1F("hist_yj_pflowj1_pt_2030_ptj1_purityweight", "hist_yj_pflowj1_pt_2030_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_2030_ptj1_purityweight = new TH1F("hist_jy_pflowj1_pt_2030_ptj1_purityweight", "hist_jy_pflowj1_pt_2030_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_3040_ptj1_purityweight = new TH1F("hist_yy_pflowj1_pt_3040_ptj1_purityweight", "hist_yy_pflowj1_pt_3040_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_3040_ptj1_purityweight = new TH1F("hist_jj_pflowj1_pt_3040_ptj1_purityweight", "hist_jj_pflowj1_pt_3040_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_3040_ptj1_purityweight = new TH1F("hist_yj_pflowj1_pt_3040_ptj1_purityweight", "hist_yj_pflowj1_pt_3040_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_3040_ptj1_purityweight = new TH1F("hist_jy_pflowj1_pt_3040_ptj1_purityweight", "hist_jy_pflowj1_pt_3040_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_4060_ptj1_purityweight = new TH1F("hist_yy_pflowj1_pt_4060_ptj1_purityweight", "hist_yy_pflowj1_pt_4060_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_4060_ptj1_purityweight = new TH1F("hist_jj_pflowj1_pt_4060_ptj1_purityweight", "hist_jj_pflowj1_pt_4060_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_4060_ptj1_purityweight = new TH1F("hist_yj_pflowj1_pt_4060_ptj1_purityweight", "hist_yj_pflowj1_pt_4060_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_4060_ptj1_purityweight = new TH1F("hist_jy_pflowj1_pt_4060_ptj1_purityweight", "hist_jy_pflowj1_pt_4060_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_myy_myy_purityweight = new TH1F("hist_yy_myy_myy_purityweight", "hist_yy_myy_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_myy_purityweight = new TH1F("hist_jj_myy_myy_purityweight", "hist_jj_myy_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_myy_purityweight = new TH1F("hist_yj_myy_myy_purityweight", "hist_yj_myy_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_myy_purityweight = new TH1F("hist_jy_myy_myy_purityweight", "hist_jy_myy_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_010_myy_purityweight = new TH1F("hist_yy_myy_010_myy_purityweight", "hist_yy_myy_010_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_010_myy_purityweight = new TH1F("hist_jj_myy_010_myy_purityweight", "hist_jj_myy_010_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_010_myy_purityweight = new TH1F("hist_yj_myy_010_myy_purityweight", "hist_yj_myy_010_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_010_myy_purityweight = new TH1F("hist_jy_myy_010_myy_purityweight", "hist_jy_myy_010_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_1020_myy_purityweight = new TH1F("hist_yy_myy_1020_myy_purityweight", "hist_yy_myy_1020_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_1020_myy_purityweight = new TH1F("hist_jj_myy_1020_myy_purityweight", "hist_jj_myy_1020_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_1020_myy_purityweight = new TH1F("hist_yj_myy_1020_myy_purityweight", "hist_yj_myy_1020_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_1020_myy_purityweight = new TH1F("hist_jy_myy_1020_myy_purityweight", "hist_jy_myy_1020_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_2030_myy_purityweight = new TH1F("hist_yy_myy_2030_myy_purityweight", "hist_yy_myy_2030_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_2030_myy_purityweight = new TH1F("hist_jj_myy_2030_myy_purityweight", "hist_jj_myy_2030_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_2030_myy_purityweight = new TH1F("hist_yj_myy_2030_myy_purityweight", "hist_yj_myy_2030_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_2030_myy_purityweight = new TH1F("hist_jy_myy_2030_myy_purityweight", "hist_jy_myy_2030_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_3040_myy_purityweight = new TH1F("hist_yy_myy_3040_myy_purityweight", "hist_yy_myy_3040_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_3040_myy_purityweight = new TH1F("hist_jj_myy_3040_myy_purityweight", "hist_jj_myy_3040_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_3040_myy_purityweight = new TH1F("hist_yj_myy_3040_myy_purityweight", "hist_yj_myy_3040_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_3040_myy_purityweight = new TH1F("hist_jy_myy_3040_myy_purityweight", "hist_jy_myy_3040_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_4060_myy_purityweight = new TH1F("hist_yy_myy_4060_myy_purityweight", "hist_yy_myy_4060_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_4060_myy_purityweight = new TH1F("hist_jj_myy_4060_myy_purityweight", "hist_jj_myy_4060_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_4060_myy_purityweight = new TH1F("hist_yj_myy_4060_myy_purityweight", "hist_yj_myy_4060_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_4060_myy_purityweight = new TH1F("hist_jy_myy_4060_myy_purityweight", "hist_jy_myy_4060_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_pflowj1_pt = new TH1F("hist_yy_pflowj1_pt", "hist_yy_pflowj1_pt;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt = new TH1F("hist_jj_pflowj1_pt", "hist_jj_pflowj1_pt;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt = new TH1F("hist_yj_pflowj1_pt", "hist_yj_pflowj1_pt;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt = new TH1F("hist_jy_pflowj1_pt", "hist_jy_pflowj1_pt;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_010 = new TH1F("hist_yy_pflowj1_pt_010", "hist_yy_pflowj1_pt_010;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_010 = new TH1F("hist_jj_pflowj1_pt_010", "hist_jj_pflowj1_pt_010;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_010 = new TH1F("hist_yj_pflowj1_pt_010", "hist_yj_pflowj1_pt_010;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_010 = new TH1F("hist_jy_pflowj1_pt_010", "hist_jy_pflowj1_pt_010;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_1020 = new TH1F("hist_yy_pflowj1_pt_1020", "hist_yy_pflowj1_pt_1020;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_1020 = new TH1F("hist_jj_pflowj1_pt_1020", "hist_jj_pflowj1_pt_1020;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_1020 = new TH1F("hist_yj_pflowj1_pt_1020", "hist_yj_pflowj1_pt_1020;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_1020 = new TH1F("hist_jy_pflowj1_pt_1020", "hist_jy_pflowj1_pt_1020;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_2030 = new TH1F("hist_yy_pflowj1_pt_2030", "hist_yy_pflowj1_pt_2030;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_2030 = new TH1F("hist_jj_pflowj1_pt_2030", "hist_jj_pflowj1_pt_2030;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_2030 = new TH1F("hist_yj_pflowj1_pt_2030", "hist_yj_pflowj1_pt_2030;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_2030 = new TH1F("hist_jy_pflowj1_pt_2030", "hist_jy_pflowj1_pt_2030;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_3040 = new TH1F("hist_yy_pflowj1_pt_3040", "hist_yy_pflowj1_pt_3040;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_3040 = new TH1F("hist_jj_pflowj1_pt_3040", "hist_jj_pflowj1_pt_3040;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_3040 = new TH1F("hist_yj_pflowj1_pt_3040", "hist_yj_pflowj1_pt_3040;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_3040 = new TH1F("hist_jy_pflowj1_pt_3040", "hist_jy_pflowj1_pt_3040;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_4060 = new TH1F("hist_yy_pflowj1_pt_4060", "hist_yy_pflowj1_pt_4060;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_4060 = new TH1F("hist_jj_pflowj1_pt_4060", "hist_jj_pflowj1_pt_4060;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_4060 = new TH1F("hist_yj_pflowj1_pt_4060", "hist_yj_pflowj1_pt_4060;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_4060 = new TH1F("hist_jy_pflowj1_pt_4060", "hist_jy_pflowj1_pt_4060;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_myy = new TH1F("hist_yy_myy", "hist_yy_myy;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy = new TH1F("hist_jj_myy", "hist_jj_myy;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy = new TH1F("hist_yj_myy", "hist_yj_myy;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy = new TH1F("hist_jy_myy", "hist_jy_myy;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_010 = new TH1F("hist_yy_myy_010", "hist_yy_myy_010;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_010 = new TH1F("hist_jj_myy_010", "hist_jj_myy_010;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_010 = new TH1F("hist_yj_myy_010", "hist_yj_myy_010;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_010 = new TH1F("hist_jy_myy_010", "hist_jy_myy_010;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_1020 = new TH1F("hist_yy_myy_1020", "hist_yy_myy_1020;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_1020 = new TH1F("hist_jj_myy_1020", "hist_jj_myy_1020;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_1020 = new TH1F("hist_yj_myy_1020", "hist_yj_myy_1020;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_1020 = new TH1F("hist_jy_myy_1020", "hist_jy_myy_1020;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_2030 = new TH1F("hist_yy_myy_2030", "hist_yy_myy_2030;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_2030 = new TH1F("hist_jj_myy_2030", "hist_jj_myy_2030;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_2030 = new TH1F("hist_yj_myy_2030", "hist_yj_myy_2030;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_2030 = new TH1F("hist_jy_myy_2030", "hist_jy_myy_2030;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_3040 = new TH1F("hist_yy_myy_3040", "hist_yy_myy_3040;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_3040 = new TH1F("hist_jj_myy_3040", "hist_jj_myy_3040;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_3040 = new TH1F("hist_yj_myy_3040", "hist_yj_myy_3040;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_3040 = new TH1F("hist_jy_myy_3040", "hist_jy_myy_3040;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_4060 = new TH1F("hist_yy_myy_4060", "hist_yy_myy_4060;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_4060 = new TH1F("hist_jj_myy_4060", "hist_jj_myy_4060;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_4060 = new TH1F("hist_yj_myy_4060", "hist_yj_myy_4060;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_4060 = new TH1F("hist_jy_myy_4060", "hist_jy_myy_4060;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_pflowj1_eta = new TH1F("hist_yy_pflowj1_eta", "hist_yy_pflowj1_eta;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_yj_pflowj1_eta = new TH1F("hist_yj_pflowj1_eta", "hist_yj_pflowj1_eta;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_jy_pflowj1_eta = new TH1F("hist_jy_pflowj1_eta", "hist_jy_pflowj1_eta;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_jj_pflowj1_eta = new TH1F("hist_jj_pflowj1_eta", "hist_jj_pflowj1_eta;Leading jet #eta [GeV];Events", etabins, etamin, etamax);

  hist_yy_pflowj1_eta_purityweight = new TH1F("hist_yy_pflowj1_eta_purityweight", "hist_yy_pflowj1_eta_purityweight;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_yj_pflowj1_eta_purityweight = new TH1F("hist_yj_pflowj1_eta_purityweight", "hist_yj_pflowj1_eta_purityweight;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_jy_pflowj1_eta_purityweight = new TH1F("hist_jy_pflowj1_eta_purityweight", "hist_jy_pflowj1_eta_purityweight;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_jj_pflowj1_eta_purityweight = new TH1F("hist_jj_pflowj1_eta_purityweight", "hist_jj_pflowj1_eta_purityweight;Leading jet #eta [GeV];Events", etabins, etamin, etamax);

  hist_jj_j1_pt = new TH1F("hist_jj_j1_pt", "hist_jj_j1_pt;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_j1_eta = new TH1F("hist_jj_j1_eta", "hist_jj_j1_eta;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_jj_j2_pt = new TH1F("hist_jj_j2_pt", "hist_jj_j2_pt;Subleading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_j2_eta = new TH1F("hist_jj_j2_eta", "hist_jj_j2_eta;Subleading jet #eta;Events", etabins, etamin, etamax);

  hist_yj_j_pt = new TH1F("hist_yj_j_pt", "hist_yj_j_pt;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_j_eta = new TH1F("hist_yj_j_eta", "hist_yj_j_eta;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_yj_y_pt = new TH1F("hist_yj_y_pt", "hist_yj_y_pt;Leading #gamma p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_y_eta = new TH1F("hist_yj_y_eta", "hist_yj_y_eta;Leading #gamma #eta;Events", etabins, etamin, etamax);

  hist_jy_j_pt = new TH1F("hist_jy_j_pt", "hist_jy_j_pt;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_j_eta = new TH1F("hist_jy_j_eta", "hist_jy_j_eta;Leading jet #eta;Events", etabins, etamin, etamax);
  hist_jy_y_pt = new TH1F("hist_jy_y_pt", "hist_jy_y_pt;Leading #gamma p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_y_eta = new TH1F("hist_jy_y_eta", "hist_jy_y_eta;Leading #gamma #eta;Events", etabins, etamin, etamax);

  hist_yy_y1_pt = new TH1F("hist_yy_y1_pt", "hist_yy_y1_pt;Leading #gamma p_{T} [GeV];Events", ptbins, ptedges);
  hist_yy_y2_pt = new TH1F("hist_yy_y2_pt", "hist_yy_y2_pt;Leading #gamma p_{T} [GeV];Events", ptbins, ptedges);
  hist_yy_y1_eta = new TH1F("hist_yy_y1_eta", "hist_yy_y1_eta;Leading #gamma #eta;Events", etabins, etamin, etamax);
  hist_yy_y2_eta = new TH1F("hist_yy_y2_eta", "hist_yy_y2_eta;Leading #gamma #eta;Events", etabins, etamin, etamax);
  
  hist_yy_eta = new TH1F("hist_yy_eta", "hist_yy_eta;#eta_{#gamma#gamma};Events", etabins, etamin, etamax);
  hist_yy_pt = new TH1F("hist_yy_pt", "hist_yy_pt;p_{T}^{#gamma#gamma} [GeV];Events", ptbins, ptedges);
  hist_yy_m = new TH1F("hist_yy_m", "hist_yy_m;Mass_{#gamma#gamma} [GeV];Events", mbins, mmin, mmax);

  hist_mu = new TH1F("hist_mu", "hist_mu;#mu;Events", mubins, muedges);

  hist_yy_mu_mu_purityweight= new TH1F("hist_yy_mu_mu_purityweight", "hist_yy_mu_mu_purityweight;#mu;Events", mubins, muedges);
  hist_jj_mu_mu_purityweight= new TH1F("hist_jj_mu_mu_purityweight", "hist_jj_mu_mu_purityweight;#mu;Events", mubins, muedges);
  hist_yj_mu_mu_purityweight= new TH1F("hist_yj_mu_mu_purityweight", "hist_yj_mu_mu_purityweight;#mu;Events", mubins, muedges);
  hist_jy_mu_mu_purityweight= new TH1F("hist_jy_mu_mu_purityweight", "hist_jy_mu_mu_purityweight;#mu;Events", mubins, muedges);

  hist_yy_mu= new TH1F("hist_yy_mu", "hist_yy_mu;#mu;Events", mubins, muedges);
  hist_jj_mu= new TH1F("hist_jj_mu", "hist_jj_mu;#mu;Events", mubins, muedges);
  hist_yj_mu= new TH1F("hist_yj_mu", "hist_yj_mu;#mu;Events", mubins, muedges);
  hist_jy_mu= new TH1F("hist_jy_mu", "hist_jy_mu;#mu;Events", mubins, muedges);

  hist_j130_pt = new TH1F("hist_j130_pt", "hist_j130_pt;p_{T};Events", ptbins, ptedges);
  hist_j130_eta = new TH1F("hist_j130_eta", "hist_j130_eta;#eta;Events", etabins, etamin, etamax);

  hist_j130_pt_015 = new TH1F("hist_j130_pt_015", "hist_j130_pt_015;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_1525 = new TH1F("hist_j130_pt_1525", "hist_j130_pt_1525;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_2535 = new TH1F("hist_j130_pt_2535", "hist_j130_pt_2535;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_3550 = new TH1F("hist_j130_pt_3550", "hist_j130_pt_3550;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_50  = new TH1F("hist_j130_pt_50", "hist_j130_pt_50;p_{T};Events", ptbins, ptedges);

  hist_j130_pt_010 = new TH1F("hist_j130_pt_010", "hist_j130_pt_010;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_1020 = new TH1F("hist_j130_pt_1020", "hist_j130_pt_1020;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_2030 = new TH1F("hist_j130_pt_2030", "hist_j130_pt_2030;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_3040 = new TH1F("hist_j130_pt_3040", "hist_j130_pt_3040;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_4060 = new TH1F("hist_j130_pt_4060", "hist_j130_pt_4060;p_{T};Events", ptbins, ptedges);

  hist_myy = new TH1F("hist_myy", "hist_myy;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_inclusive = new TH1F("hist_myy_inclusive", "hist_myy_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_myy_010 = new TH1F("hist_myy_010", "hist_myy_010;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_1020 = new TH1F("hist_myy_1020", "hist_myy_1020;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_2030 = new TH1F("hist_myy_2030", "hist_myy_2030;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_3040 = new TH1F("hist_myy_3040", "hist_myy_3040;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_4060 = new TH1F("hist_myy_4060", "hist_myy_4060;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_myy_010_inclusive = new TH1F("hist_myy_010_inclusive", "hist_myy_010_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_1020_inclusive = new TH1F("hist_myy_1020_inclusive", "hist_myy_1020_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_2030_inclusive = new TH1F("hist_myy_2030_inclusive", "hist_myy_2030_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_3040_inclusive = new TH1F("hist_myy_3040_inclusive", "hist_myy_3040_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_4060_inclusive = new TH1F("hist_myy_4060_inclusive", "hist_myy_4060_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_myy_015 = new TH1F("hist_myy_015", "hist_myy_015;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_1525 = new TH1F("hist_myy_1525", "hist_myy_1525;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_2535 = new TH1F("hist_myy_2535", "hist_myy_2535;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_3550 = new TH1F("hist_myy_3550", "hist_myy_3550;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_50 = new TH1F("hist_myy_50", "hist_myy_50;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

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

  hist_j150_y_015 = new TH1F("hist_j150_y_015", "hist_j150_y_015;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_1525 = new TH1F("hist_j150_y_1525", "hist_j150_y_1525;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_2535 = new TH1F("hist_j150_y_2535", "hist_j150_y_2535;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_3550 = new TH1F("hist_j150_y_3550", "hist_j150_y_3550;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_50 = new TH1F("hist_j150_y_50", "hist_j150_y_50;Rapidity;Events", ybins, ymin, ymax);

  hist_j130_pt_015_fJVT = new TH1F("hist_j130_pt_015_fJVT", "hist_j130_pt_015_fJVT;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_1525_fJVT = new TH1F("hist_j130_pt_1525_fJVT", "hist_j130_pt_1525_fJVT;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_2535_fJVT = new TH1F("hist_j130_pt_2535_fJVT", "hist_j130_pt_2535_fJVT;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_3550_fJVT = new TH1F("hist_j130_pt_3550_fJVT", "hist_j130_pt_3550_fJVT;p_{T};Events", ptbins, ptedges);
  hist_j130_pt_50_fJVT = new TH1F("hist_j130_pt_50_fJVT", "hist_j130_pt_50_fJVT;p_{T};Events", ptbins, ptedges);

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

  hist_j150_y_015_fJVT = new TH1F("hist_j150_y_015_fJVT", "hist_j150_y_015_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_1525_fJVT = new TH1F("hist_j150_y_1525_fJVT", "hist_j150_y_1525_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_2535_fJVT = new TH1F("hist_j150_y_2535_fJVT", "hist_j150_y_2535_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_3550_fJVT = new TH1F("hist_j150_y_3550_fJVT", "hist_j150_y_3550_fJVT;Rapidity;Events", ybins, ymin, ymax);
  hist_j150_y_50_fJVT = new TH1F("hist_j150_y_50_fJVT", "hist_j150_y_50_fJVT;Rapidity;Events", ybins, ymin, ymax);

  hist_pass_fJVT = new TH1F("hist_pass_fJVT", "hist_pass_fJVT;#eta;Events", 40, -4.0, 4.0);
  hist_fail_fJVT = new TH1F("hist_fail_fJVT", "hist_fail_fJVT;#eta;Events", 40, -4.0, 4.0);

  hist_yy_myy_inclusive = new TH1F("hist_yy_myy_inclusive", "hist_yy_myy_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_inclusive = new TH1F("hist_jj_myy_inclusive", "hist_jj_myy_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_inclusive = new TH1F("hist_yj_myy_inclusive", "hist_yj_myy_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_inclusive = new TH1F("hist_jy_myy_inclusive", "hist_jy_myy_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_010_inclusive = new TH1F("hist_yy_myy_010_inclusive", "hist_yy_myy_010_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_010_inclusive = new TH1F("hist_jj_myy_010_inclusive", "hist_jj_myy_010_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_010_inclusive = new TH1F("hist_yj_myy_010_inclusive", "hist_yj_myy_010_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_010_inclusive = new TH1F("hist_jy_myy_010_inclusive", "hist_jy_myy_010_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_1020_inclusive = new TH1F("hist_yy_myy_1020_inclusive", "hist_yy_myy_1020_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_1020_inclusive = new TH1F("hist_jj_myy_1020_inclusive", "hist_jj_myy_1020_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_1020_inclusive = new TH1F("hist_yj_myy_1020_inclusive", "hist_yj_myy_1020_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_1020_inclusive = new TH1F("hist_jy_myy_1020_inclusive", "hist_jy_myy_1020_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_2030_inclusive = new TH1F("hist_yy_myy_2030_inclusive", "hist_yy_myy_2030_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_2030_inclusive = new TH1F("hist_jj_myy_2030_inclusive", "hist_jj_myy_2030_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_2030_inclusive = new TH1F("hist_yj_myy_2030_inclusive", "hist_yj_myy_2030_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_2030_inclusive = new TH1F("hist_jy_myy_2030_inclusive", "hist_jy_myy_2030_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_3040_inclusive = new TH1F("hist_yy_myy_3040_inclusive", "hist_yy_myy_3040_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_3040_inclusive = new TH1F("hist_jj_myy_3040_inclusive", "hist_jj_myy_3040_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_3040_inclusive = new TH1F("hist_yj_myy_3040_inclusive", "hist_yj_myy_3040_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_3040_inclusive = new TH1F("hist_jy_myy_3040_inclusive", "hist_jy_myy_3040_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_4060_inclusive = new TH1F("hist_yy_myy_4060_inclusive", "hist_yy_myy_4060_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_4060_inclusive = new TH1F("hist_jj_myy_4060_inclusive", "hist_jj_myy_4060_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_4060_inclusive = new TH1F("hist_yj_myy_4060_inclusive", "hist_yj_myy_4060_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_4060_inclusive = new TH1F("hist_jy_myy_4060_inclusive", "hist_jy_myy_4060_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_myy_purityweight_inclusive = new TH1F("hist_yy_myy_myy_purityweight_inclusive", "hist_yy_myy_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_myy_purityweight_inclusive = new TH1F("hist_jj_myy_myy_purityweight_inclusive", "hist_jj_myy_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_myy_purityweight_inclusive = new TH1F("hist_yj_myy_myy_purityweight_inclusive", "hist_yj_myy_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_myy_purityweight_inclusive = new TH1F("hist_jy_myy_myy_purityweight_inclusive", "hist_jy_myy_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_010_myy_purityweight_inclusive = new TH1F("hist_yy_myy_010_myy_purityweight_inclusive", "hist_yy_myy_010_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_010_myy_purityweight_inclusive = new TH1F("hist_jj_myy_010_myy_purityweight_inclusive", "hist_jj_myy_010_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_010_myy_purityweight_inclusive = new TH1F("hist_yj_myy_010_myy_purityweight_inclusive", "hist_yj_myy_010_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_010_myy_purityweight_inclusive = new TH1F("hist_jy_myy_010_myy_purityweight_inclusive", "hist_jy_myy_010_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_1020_myy_purityweight_inclusive = new TH1F("hist_yy_myy_1020_myy_purityweight_inclusive", "hist_yy_myy_1020_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_1020_myy_purityweight_inclusive = new TH1F("hist_jj_myy_1020_myy_purityweight_inclusive", "hist_jj_myy_1020_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_1020_myy_purityweight_inclusive = new TH1F("hist_yj_myy_1020_myy_purityweight_inclusive", "hist_yj_myy_1020_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_1020_myy_purityweight_inclusive = new TH1F("hist_jy_myy_1020_myy_purityweight_inclusive", "hist_jy_myy_1020_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_2030_myy_purityweight_inclusive = new TH1F("hist_yy_myy_2030_myy_purityweight_inclusive", "hist_yy_myy_2030_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_2030_myy_purityweight_inclusive = new TH1F("hist_jj_myy_2030_myy_purityweight_inclusive", "hist_jj_myy_2030_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_2030_myy_purityweight_inclusive = new TH1F("hist_yj_myy_2030_myy_purityweight_inclusive", "hist_yj_myy_2030_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_2030_myy_purityweight_inclusive = new TH1F("hist_jy_myy_2030_myy_purityweight_inclusive", "hist_jy_myy_2030_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_3040_myy_purityweight_inclusive = new TH1F("hist_yy_myy_3040_myy_purityweight_inclusive", "hist_yy_myy_3040_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_3040_myy_purityweight_inclusive = new TH1F("hist_jj_myy_3040_myy_purityweight_inclusive", "hist_jj_myy_3040_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_3040_myy_purityweight_inclusive = new TH1F("hist_yj_myy_3040_myy_purityweight_inclusive", "hist_yj_myy_3040_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_3040_myy_purityweight_inclusive = new TH1F("hist_jy_myy_3040_myy_purityweight_inclusive", "hist_jy_myy_3040_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_4060_myy_purityweight_inclusive = new TH1F("hist_yy_myy_4060_myy_purityweight_inclusive", "hist_yy_myy_4060_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_4060_myy_purityweight_inclusive = new TH1F("hist_jj_myy_4060_myy_purityweight_inclusive", "hist_jj_myy_4060_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_4060_myy_purityweight_inclusive = new TH1F("hist_yj_myy_4060_myy_purityweight_inclusive", "hist_yj_myy_4060_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_4060_myy_purityweight_inclusive = new TH1F("hist_jy_myy_4060_myy_purityweight_inclusive", "hist_jy_myy_4060_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_j130_pt_central = new TH1F("hist_j130_pt_central", "hist_j130_pt_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_j130_eta_central = new TH1F("hist_j130_eta_central", "hist_j130_eta_central;#eta;Events", etabins, etamin, etamax);

  hist_myy_010_central = new TH1F("hist_myy_010_central", "hist_myy_010_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_1020_central = new TH1F("hist_myy_1020_central", "hist_myy_1020_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_2030_central = new TH1F("hist_myy_2030_central", "hist_myy_2030_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_3040_central = new TH1F("hist_myy_3040_central", "hist_myy_3040_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_myy_4060_central = new TH1F("hist_myy_4060_central", "hist_myy_4060_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_j130_pt_010_central = new TH1F("hist_j130_pt_010_central", "hist_j130_pt_010_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_j130_pt_1020_central = new TH1F("hist_j130_pt_1020_central", "hist_j130_pt_1020_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_j130_pt_2030_central = new TH1F("hist_j130_pt_2030_central", "hist_j130_pt_2030_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_j130_pt_3040_central = new TH1F("hist_j130_pt_3040_central", "hist_j130_pt_3040_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_j130_pt_4060_central = new TH1F("hist_j130_pt_4060_central", "hist_j130_pt_4060_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_myy_central = new TH1F("hist_yy_myy_central", "hist_yy_myy_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_central = new TH1F("hist_jj_myy_central", "hist_jj_myy_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_central = new TH1F("hist_jy_myy_central", "hist_jy_myy_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_central = new TH1F("hist_yj_myy_central", "hist_yj_myy_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_pflowj1_pt_010_central = new TH1F("hist_yy_pflowj1_pt_010_central", "hist_yy_pflowj1_pt_010_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_010_central = new TH1F("hist_jj_pflowj1_pt_010_central", "hist_jj_pflowj1_pt_010_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_010_central = new TH1F("hist_yj_pflowj1_pt_010_central", "hist_yj_pflowj1_pt_010_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_010_central = new TH1F("hist_jy_pflowj1_pt_010_central", "hist_jy_pflowj1_pt_010_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_1020_central = new TH1F("hist_yy_pflowj1_pt_1020_central", "hist_yy_pflowj1_pt_1020_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_1020_central = new TH1F("hist_jj_pflowj1_pt_1020_central", "hist_jj_pflowj1_pt_1020_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_1020_central = new TH1F("hist_yj_pflowj1_pt_1020_central", "hist_yj_pflowj1_pt_1020_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_1020_central = new TH1F("hist_jy_pflowj1_pt_1020_central", "hist_jy_pflowj1_pt_1020_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_2030_central = new TH1F("hist_yy_pflowj1_pt_2030_central", "hist_yy_pflowj1_pt_2030_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_2030_central = new TH1F("hist_jj_pflowj1_pt_2030_central", "hist_jj_pflowj1_pt_2030_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_2030_central = new TH1F("hist_yj_pflowj1_pt_2030_central", "hist_yj_pflowj1_pt_2030_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_2030_central = new TH1F("hist_jy_pflowj1_pt_2030_central", "hist_jy_pflowj1_pt_2030_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_3040_central = new TH1F("hist_yy_pflowj1_pt_3040_central", "hist_yy_pflowj1_pt_3040_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_3040_central = new TH1F("hist_jj_pflowj1_pt_3040_central", "hist_jj_pflowj1_pt_3040_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_3040_central = new TH1F("hist_yj_pflowj1_pt_3040_central", "hist_yj_pflowj1_pt_3040_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_3040_central = new TH1F("hist_jy_pflowj1_pt_3040_central", "hist_jy_pflowj1_pt_3040_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_pflowj1_pt_4060_central = new TH1F("hist_yy_pflowj1_pt_4060_central", "hist_yy_pflowj1_pt_4060_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jj_pflowj1_pt_4060_central = new TH1F("hist_jj_pflowj1_pt_4060_central", "hist_jj_pflowj1_pt_4060_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_4060_central = new TH1F("hist_yj_pflowj1_pt_4060_central", "hist_yj_pflowj1_pt_4060_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_4060_central = new TH1F("hist_jy_pflowj1_pt_4060_central", "hist_jy_pflowj1_pt_4060_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_jj_pflowj1_pt_010_ptj1_purityweight_central = new TH1F("hist_jj_pflowj1_pt_010_ptj1_purityweight_central", "hist_jj_pflowj1_pt_010_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_010_ptj1_purityweight_central = new TH1F("hist_yj_pflowj1_pt_010_ptj1_purityweight_central", "hist_yj_pflowj1_pt_010_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_010_ptj1_purityweight_central = new TH1F("hist_jy_pflowj1_pt_010_ptj1_purityweight_central", "hist_jy_pflowj1_pt_010_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_jj_pflowj1_pt_1020_ptj1_purityweight_central = new TH1F("hist_jj_pflowj1_pt_1020_ptj1_purityweight_central", "hist_jj_pflowj1_pt_1020_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_1020_ptj1_purityweight_central = new TH1F("hist_yj_pflowj1_pt_1020_ptj1_purityweight_central", "hist_yj_pflowj1_pt_1020_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_1020_ptj1_purityweight_central = new TH1F("hist_jy_pflowj1_pt_1020_ptj1_purityweight_central", "hist_jy_pflowj1_pt_1020_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_jj_pflowj1_pt_2030_ptj1_purityweight_central = new TH1F("hist_jj_pflowj1_pt_2030_ptj1_purityweight_central", "hist_jj_pflowj1_pt_2030_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_2030_ptj1_purityweight_central = new TH1F("hist_yj_pflowj1_pt_2030_ptj1_purityweight_central", "hist_yj_pflowj1_pt_2030_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_2030_ptj1_purityweight_central = new TH1F("hist_jy_pflowj1_pt_2030_ptj1_purityweight_central", "hist_jy_pflowj1_pt_2030_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_jj_pflowj1_pt_3040_ptj1_purityweight_central = new TH1F("hist_jj_pflowj1_pt_3040_ptj1_purityweight_central", "hist_jj_pflowj1_pt_3040_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_3040_ptj1_purityweight_central = new TH1F("hist_yj_pflowj1_pt_3040_ptj1_purityweight_central", "hist_yj_pflowj1_pt_3040_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_3040_ptj1_purityweight_central = new TH1F("hist_jy_pflowj1_pt_3040_ptj1_purityweight_central", "hist_jy_pflowj1_pt_3040_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_jj_pflowj1_pt_4060_ptj1_purityweight_central = new TH1F("hist_jj_pflowj1_pt_4060_ptj1_purityweight_central", "hist_jj_pflowj1_pt_4060_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_yj_pflowj1_pt_4060_ptj1_purityweight_central = new TH1F("hist_yj_pflowj1_pt_4060_ptj1_purityweight_central", "hist_yj_pflowj1_pt_4060_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_jy_pflowj1_pt_4060_ptj1_purityweight_central = new TH1F("hist_jy_pflowj1_pt_4060_ptj1_purityweight_central", "hist_jy_pflowj1_pt_4060_ptj1_purityweight_central;Leading jet p_{T} [GeV];Events", ptbins, ptedges);

  hist_yy_myy_myy_purityweight_central = new TH1F("hist_yy_myy_myy_purityweight_central", "hist_yy_myy_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_myy_purityweight_central = new TH1F("hist_jj_myy_myy_purityweight_central", "hist_jj_myy_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_myy_purityweight_central = new TH1F("hist_jy_myy_myy_purityweight_central", "hist_jy_myy_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_myy_purityweight_central = new TH1F("hist_yj_myy_myy_purityweight_central", "hist_yj_myy_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_010_central = new TH1F("hist_yy_myy_010_central", "hist_yy_myy_010_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_010_central = new TH1F("hist_jj_myy_010_central", "hist_jj_myy_010_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_010_central = new TH1F("hist_yj_myy_010_central", "hist_yj_myy_010_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_010_central = new TH1F("hist_jy_myy_010_central", "hist_jy_myy_010_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_1020_central = new TH1F("hist_yy_myy_1020_central", "hist_yy_myy_1020_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_1020_central = new TH1F("hist_jj_myy_1020_central", "hist_jj_myy_1020_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_1020_central = new TH1F("hist_yj_myy_1020_central", "hist_yj_myy_1020_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_1020_central = new TH1F("hist_jy_myy_1020_central", "hist_jy_myy_1020_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_2030_central = new TH1F("hist_yy_myy_2030_central", "hist_yy_myy_2030_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_2030_central = new TH1F("hist_jj_myy_2030_central", "hist_jj_myy_2030_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_2030_central = new TH1F("hist_yj_myy_2030_central", "hist_yj_myy_2030_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_2030_central = new TH1F("hist_jy_myy_2030_central", "hist_jy_myy_2030_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_3040_central = new TH1F("hist_yy_myy_3040_central", "hist_yy_myy_3040_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_3040_central = new TH1F("hist_jj_myy_3040_central", "hist_jj_myy_3040_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_3040_central = new TH1F("hist_yj_myy_3040_central", "hist_yj_myy_3040_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_3040_central = new TH1F("hist_jy_myy_3040_central", "hist_jy_myy_3040_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_yy_myy_4060_central = new TH1F("hist_yy_myy_4060_central", "hist_yy_myy_4060_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jj_myy_4060_central = new TH1F("hist_jj_myy_4060_central", "hist_jj_myy_4060_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_4060_central = new TH1F("hist_yj_myy_4060_central", "hist_yj_myy_4060_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_4060_central = new TH1F("hist_jy_myy_4060_central", "hist_jy_myy_4060_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_jj_myy_010_myy_purityweight_central = new TH1F("hist_jj_myy_010_myy_purityweight_central", "hist_jj_myy_010_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_010_myy_purityweight_central = new TH1F("hist_yj_myy_010_myy_purityweight_central", "hist_yj_myy_010_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_010_myy_purityweight_central = new TH1F("hist_jy_myy_010_myy_purityweight_central", "hist_jy_myy_010_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_jj_myy_1020_myy_purityweight_central = new TH1F("hist_jj_myy_1020_myy_purityweight_central", "hist_jj_myy_1020_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_1020_myy_purityweight_central = new TH1F("hist_yj_myy_1020_myy_purityweight_central", "hist_yj_myy_1020_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_1020_myy_purityweight_central = new TH1F("hist_jy_myy_1020_myy_purityweight_central", "hist_jy_myy_1020_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_jj_myy_2030_myy_purityweight_central = new TH1F("hist_jj_myy_2030_myy_purityweight_central", "hist_jj_myy_2030_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_2030_myy_purityweight_central = new TH1F("hist_yj_myy_2030_myy_purityweight_central", "hist_yj_myy_2030_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_2030_myy_purityweight_central = new TH1F("hist_jy_myy_2030_myy_purityweight_central", "hist_jy_myy_2030_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_jj_myy_3040_myy_purityweight_central = new TH1F("hist_jj_myy_3040_myy_purityweight_central", "hist_jj_myy_3040_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_3040_myy_purityweight_central = new TH1F("hist_yj_myy_3040_myy_purityweight_central", "hist_yj_myy_3040_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_3040_myy_purityweight_central = new TH1F("hist_jy_myy_3040_myy_purityweight_central", "hist_jy_myy_3040_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_jj_myy_4060_myy_purityweight_central = new TH1F("hist_jj_myy_4060_myy_purityweight_central", "hist_jj_myy_4060_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_yj_myy_4060_myy_purityweight_central = new TH1F("hist_yj_myy_4060_myy_purityweight_central", "hist_yj_myy_4060_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_jy_myy_4060_myy_purityweight_central = new TH1F("hist_jy_myy_4060_myy_purityweight_central", "hist_jy_myy_4060_myy_purityweight_central;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_mc_pt_ptj1_purityweight = new TH1F("hist_mc_pt_ptj1_purityweight", "hist_mc_pt_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_mc_myy_myy_purityweight = new TH1F("hist_mc_myy_myy_purityweight", "hist_mc_myy_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_mc_mu_mu_purityweight = new TH1F("hist_mc_mu_mu_purityweight", "hist_mc_mu_mu_purityweight;#mu;Events", mubins, muedges);
  hist_mc_myy_myy_purityweight_inclusive = new TH1F("hist_mc_myy_myy_purityweight_inclusive", "hist_mc_myy_myy_purityweight_inclusive;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);

  hist_mc_myy_010_myy_purityweight = new TH1F("hist_mc_myy_010_myy_purityweight", "hist_mc_myy_010_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_mc_myy_1020_myy_purityweight = new TH1F("hist_mc_myy_1020_myy_purityweight", "hist_mc_myy_1020_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_mc_myy_2030_myy_purityweight = new TH1F("hist_mc_myy_2030_myy_purityweight", "hist_mc_myy_2030_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_mc_myy_3040_myy_purityweight = new TH1F("hist_mc_myy_3040_myy_purityweight", "hist_mc_myy_3040_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);
  hist_mc_myy_4060_myy_purityweight = new TH1F("hist_mc_myy_4060_myy_purityweight", "hist_mc_myy_4060_myy_purityweight;m_{#gamma#gamma} [GeV];Events", myybins, myymin, myymax);


  hist_mc_pt_010_ptj1_purityweight = new TH1F("hist_mc_pt_010_ptj1_purityweight", "hist_mc_pt_010_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_mc_pt_1020_ptj1_purityweight = new TH1F("hist_mc_pt_1020_ptj1_purityweight", "hist_mc_pt_1020_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_mc_pt_2030_ptj1_purityweight = new TH1F("hist_mc_pt_2030_ptj1_purityweight", "hist_mc_pt_2030_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_mc_pt_3040_ptj1_purityweight = new TH1F("hist_mc_pt_3040_ptj1_purityweight", "hist_mc_pt_3040_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);
  hist_mc_pt_4060_ptj1_purityweight = new TH1F("hist_mc_pt_4060_ptj1_purityweight", "hist_mc_pt_4060_ptj1_purityweight;Leading jet p_{T} [GeV];Events", ptbins, ptedges);


  tree->Branch("hgam_yy_pflowj1_pt",     &hgam_yy_pflowj1_pt);
  tree->Branch("hgam_jj_pflowj1_pt",     &hgam_jj_pflowj1_pt);
  tree->Branch("hgam_yj_pflowj1_pt",     &hgam_yj_pflowj1_pt);
  tree->Branch("hgam_jy_pflowj1_pt",     &hgam_jy_pflowj1_pt);
  
  tree->Branch("hgam_yy_pflowj1_eta",     &hgam_yy_pflowj1_eta);
  tree->Branch("hgam_jj_pflowj1_eta",     &hgam_jj_pflowj1_eta);
  tree->Branch("hgam_yj_pflowj1_eta",     &hgam_yj_pflowj1_eta);
  tree->Branch("hgam_jy_pflowj1_eta",     &hgam_jy_pflowj1_eta);

  tree->Branch("hgam_yy_y1_eta",    &hgam_yy_y1_eta);
  tree->Branch("hgam_yy_y1_pt",     &hgam_yy_y1_pt);
  tree->Branch("hgam_yy_y2_eta",    &hgam_yy_y2_eta);
  tree->Branch("hgam_yy_y2_pt",     &hgam_yy_y2_pt);

  tree->Branch("hgam_yy_pt",      &hgam_yy_pt);
  tree->Branch("hgam_yy_eta",     &hgam_yy_eta);
  tree->Branch("hgam_yy_m",       &hgam_yy_m);

  tree->Branch("hgam_jj_j1_pt",      &hgam_jj_j1_pt);
  tree->Branch("hgam_jj_j1_eta",     &hgam_jj_j1_eta);
  tree->Branch("hgam_jj_j2_pt",      &hgam_jj_j2_pt);
  tree->Branch("hgam_jj_j2_eta",     &hgam_jj_j2_eta);

  tree->Branch("hgam_yj_j_pt",      &hgam_yj_j_pt);
  tree->Branch("hgam_yj_y_pt",      &hgam_yj_y_pt);
  tree->Branch("hgam_yj_j_eta",     &hgam_yj_j_eta);
  tree->Branch("hgam_yj_y_eta",     &hgam_yj_y_eta);
  
  tree->Branch("hgam_jy_j_pt",      &hgam_jy_j_pt);
  tree->Branch("hgam_jy_y_pt",      &hgam_jy_y_pt);
  tree->Branch("hgam_jy_j_eta",     &hgam_jy_j_eta);
  tree->Branch("hgam_jy_y_eta",     &hgam_jy_y_eta);
  
  tree->Branch("pflow_j130_pt",     &pflow_j130_pt);

  tree->Branch("pflow_j130_pt_15",     &pflow_j130_pt_15);
  tree->Branch("pflow_j130_pt_1525",   &pflow_j130_pt_1525);
  tree->Branch("pflow_j130_pt_2535",   &pflow_j130_pt_2535);
  tree->Branch("pflow_j130_pt_3550",   &pflow_j130_pt_3550);
  tree->Branch("pflow_j130_pt_50",     &pflow_j130_pt_50);

  tree->Branch("pflow_j130_pt_10",     &pflow_j130_pt_10);
  tree->Branch("pflow_j130_pt_1020",   &pflow_j130_pt_1020);
  tree->Branch("pflow_j130_pt_2030",   &pflow_j130_pt_2030);
  tree->Branch("pflow_j130_pt_3040",   &pflow_j130_pt_3040);
  tree->Branch("pflow_j130_pt_4060",     &pflow_j130_pt_4060);

  tree->Branch("myy_15",     &myy_15);
  tree->Branch("myy_1525",   &myy_1525);
  tree->Branch("myy_2535",   &myy_2535);
  tree->Branch("myy_3550",   &myy_3550);
  tree->Branch("myy_50",     &myy_50);

  tree->Branch("myy_10",     &myy_10);
  tree->Branch("myy_1020",   &myy_1020);
  tree->Branch("myy_2030",   &myy_2030);
  tree->Branch("myy_3040",   &myy_3040);
  tree->Branch("myy_4060",   &myy_4060);

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

  wk()->addOutput(tree);
  wk()->addOutput(hist_j130_pt);
  wk()->addOutput(hist_j130_eta);

  wk()->addOutput(hist_j130_pt_010);
  wk()->addOutput(hist_j130_pt_1020);
  wk()->addOutput(hist_j130_pt_2030);
  wk()->addOutput(hist_j130_pt_3040);
  wk()->addOutput(hist_j130_pt_4060);

  wk()->addOutput(hist_myy);
  wk()->addOutput(hist_myy_010);
  wk()->addOutput(hist_myy_1020);
  wk()->addOutput(hist_myy_2030);
  wk()->addOutput(hist_myy_3040);
  wk()->addOutput(hist_myy_4060);

  wk()->addOutput(hist_myy_inclusive);
  wk()->addOutput(hist_myy_010_inclusive);
  wk()->addOutput(hist_myy_1020_inclusive);
  wk()->addOutput(hist_myy_2030_inclusive);
  wk()->addOutput(hist_myy_3040_inclusive);
  wk()->addOutput(hist_myy_4060_inclusive);

  wk()->addOutput(hist_pass_fJVT);
  wk()->addOutput(hist_fail_fJVT);

  wk()->addOutput(hist_yy_pflowj1_pt);
  wk()->addOutput(hist_jj_pflowj1_pt);
  wk()->addOutput(hist_jy_pflowj1_pt);
  wk()->addOutput(hist_yj_pflowj1_pt);

  wk()->addOutput(hist_yy_pflowj1_pt_010);
  wk()->addOutput(hist_jj_pflowj1_pt_010);
  wk()->addOutput(hist_yj_pflowj1_pt_010);
  wk()->addOutput(hist_jy_pflowj1_pt_010);

  wk()->addOutput(hist_yy_pflowj1_pt_1020);
  wk()->addOutput(hist_jj_pflowj1_pt_1020);
  wk()->addOutput(hist_jy_pflowj1_pt_1020);
  wk()->addOutput(hist_yj_pflowj1_pt_1020);

  wk()->addOutput(hist_yy_pflowj1_pt_2030);
  wk()->addOutput(hist_jj_pflowj1_pt_2030);
  wk()->addOutput(hist_jy_pflowj1_pt_2030);
  wk()->addOutput(hist_yj_pflowj1_pt_2030);

  wk()->addOutput(hist_yy_pflowj1_pt_3040);
  wk()->addOutput(hist_jj_pflowj1_pt_3040);
  wk()->addOutput(hist_jy_pflowj1_pt_3040);
  wk()->addOutput(hist_yj_pflowj1_pt_3040);

  wk()->addOutput(hist_yy_pflowj1_pt_4060);
  wk()->addOutput(hist_jj_pflowj1_pt_4060);
  wk()->addOutput(hist_jy_pflowj1_pt_4060);
  wk()->addOutput(hist_yj_pflowj1_pt_4060);

  wk()->addOutput(hist_yy_myy_010);
  wk()->addOutput(hist_jj_myy_010);
  wk()->addOutput(hist_yj_myy_010);
  wk()->addOutput(hist_jy_myy_010);

  wk()->addOutput(hist_yy_myy_1020);
  wk()->addOutput(hist_jj_myy_1020);
  wk()->addOutput(hist_jy_myy_1020);
  wk()->addOutput(hist_yj_myy_1020);

  wk()->addOutput(hist_yy_myy_2030);
  wk()->addOutput(hist_jj_myy_2030);
  wk()->addOutput(hist_jy_myy_2030);
  wk()->addOutput(hist_yj_myy_2030);

  wk()->addOutput(hist_yy_myy_3040);
  wk()->addOutput(hist_jj_myy_3040);
  wk()->addOutput(hist_jy_myy_3040);
  wk()->addOutput(hist_yj_myy_3040);

  wk()->addOutput(hist_yy_myy_4060);
  wk()->addOutput(hist_jj_myy_4060);
  wk()->addOutput(hist_jy_myy_4060);
  wk()->addOutput(hist_yj_myy_4060);

  wk()->addOutput(hist_yy_pflowj1_eta);
  wk()->addOutput(hist_jj_pflowj1_eta);
  wk()->addOutput(hist_yj_pflowj1_eta);
  wk()->addOutput(hist_jy_pflowj1_eta);

  wk()->addOutput(hist_yy_pflowj1_eta_purityweight);
  wk()->addOutput(hist_jj_pflowj1_eta_purityweight);
  wk()->addOutput(hist_yj_pflowj1_eta_purityweight);
  wk()->addOutput(hist_jy_pflowj1_eta_purityweight);

  wk()->addOutput(hist_yy_m);
  wk()->addOutput(hist_yy_pt);
  wk()->addOutput(hist_yy_eta);

  wk()->addOutput(hist_yy_y1_pt);
  wk()->addOutput(hist_yy_y2_pt);
  wk()->addOutput(hist_yy_y1_eta);
  wk()->addOutput(hist_yy_y2_eta);

  wk()->addOutput(hist_jj_j1_pt);
  wk()->addOutput(hist_jj_j2_pt);
  wk()->addOutput(hist_jj_j1_eta);
  wk()->addOutput(hist_jj_j2_eta);

  wk()->addOutput(hist_jy_j_pt);
  wk()->addOutput(hist_jy_y_pt);
  wk()->addOutput(hist_jy_j_eta);
  wk()->addOutput(hist_jy_y_eta);
 
  wk()->addOutput(hist_yj_j_pt);
  wk()->addOutput(hist_yj_y_pt);
  wk()->addOutput(hist_yj_j_eta);
  wk()->addOutput(hist_yj_y_eta);
 
  wk()->addOutput(hist_yy_myy);
  wk()->addOutput(hist_jj_myy);
  wk()->addOutput(hist_yj_myy);
  wk()->addOutput(hist_jy_myy);

  wk()->addOutput(hist_yy_myy_myy_purityweight);
  wk()->addOutput(hist_jj_myy_myy_purityweight);
  wk()->addOutput(hist_yj_myy_myy_purityweight);
  wk()->addOutput(hist_jy_myy_myy_purityweight);

  wk()->addOutput(hist_yy_myy_010_myy_purityweight);
  wk()->addOutput(hist_jj_myy_010_myy_purityweight);
  wk()->addOutput(hist_yj_myy_010_myy_purityweight);
  wk()->addOutput(hist_jy_myy_010_myy_purityweight);

  wk()->addOutput(hist_yy_myy_1020_myy_purityweight);
  wk()->addOutput(hist_jj_myy_1020_myy_purityweight);
  wk()->addOutput(hist_jy_myy_1020_myy_purityweight);
  wk()->addOutput(hist_yj_myy_1020_myy_purityweight);

  wk()->addOutput(hist_yy_myy_2030_myy_purityweight);
  wk()->addOutput(hist_jj_myy_2030_myy_purityweight);
  wk()->addOutput(hist_jy_myy_2030_myy_purityweight);
  wk()->addOutput(hist_yj_myy_2030_myy_purityweight);

  wk()->addOutput(hist_yy_myy_3040_myy_purityweight);
  wk()->addOutput(hist_jj_myy_3040_myy_purityweight);
  wk()->addOutput(hist_jy_myy_3040_myy_purityweight);
  wk()->addOutput(hist_yj_myy_3040_myy_purityweight);

  wk()->addOutput(hist_yy_myy_4060_myy_purityweight);
  wk()->addOutput(hist_jj_myy_4060_myy_purityweight);
  wk()->addOutput(hist_jy_myy_4060_myy_purityweight);
  wk()->addOutput(hist_yj_myy_4060_myy_purityweight);

  wk()->addOutput(hist_yy_mu_mu_purityweight);
  wk()->addOutput(hist_jj_mu_mu_purityweight);
  wk()->addOutput(hist_yj_mu_mu_purityweight);
  wk()->addOutput(hist_jy_mu_mu_purityweight);

  wk()->addOutput(hist_yy_mu);
  wk()->addOutput(hist_jj_mu);
  wk()->addOutput(hist_yj_mu);
  wk()->addOutput(hist_jy_mu);

  wk()->addOutput(hist_mu);

  wk()->addOutput(hist_yy_pflowj1_pt_ptj1_purityweight);
  wk()->addOutput(hist_jj_pflowj1_pt_ptj1_purityweight);
  wk()->addOutput(hist_jy_pflowj1_pt_ptj1_purityweight);
  wk()->addOutput(hist_yj_pflowj1_pt_ptj1_purityweight);

  wk()->addOutput(hist_yy_pflowj1_pt_010_ptj1_purityweight);
  wk()->addOutput(hist_jj_pflowj1_pt_010_ptj1_purityweight);
  wk()->addOutput(hist_yj_pflowj1_pt_010_ptj1_purityweight);
  wk()->addOutput(hist_jy_pflowj1_pt_010_ptj1_purityweight);

  wk()->addOutput(hist_yy_pflowj1_pt_1020_ptj1_purityweight);
  wk()->addOutput(hist_jj_pflowj1_pt_1020_ptj1_purityweight);
  wk()->addOutput(hist_jy_pflowj1_pt_1020_ptj1_purityweight);
  wk()->addOutput(hist_yj_pflowj1_pt_1020_ptj1_purityweight);

  wk()->addOutput(hist_yy_pflowj1_pt_2030_ptj1_purityweight);
  wk()->addOutput(hist_jj_pflowj1_pt_2030_ptj1_purityweight);
  wk()->addOutput(hist_jy_pflowj1_pt_2030_ptj1_purityweight);
  wk()->addOutput(hist_yj_pflowj1_pt_2030_ptj1_purityweight);

  wk()->addOutput(hist_yy_pflowj1_pt_3040_ptj1_purityweight);
  wk()->addOutput(hist_jj_pflowj1_pt_3040_ptj1_purityweight);
  wk()->addOutput(hist_jy_pflowj1_pt_3040_ptj1_purityweight);
  wk()->addOutput(hist_yj_pflowj1_pt_3040_ptj1_purityweight);

  wk()->addOutput(hist_yy_pflowj1_pt_4060_ptj1_purityweight);
  wk()->addOutput(hist_jj_pflowj1_pt_4060_ptj1_purityweight);
  wk()->addOutput(hist_jy_pflowj1_pt_4060_ptj1_purityweight);
  wk()->addOutput(hist_yj_pflowj1_pt_4060_ptj1_purityweight);

  wk()->addOutput(hist_yy_myy_inclusive);
  wk()->addOutput(hist_jj_myy_inclusive);
  wk()->addOutput(hist_yj_myy_inclusive);
  wk()->addOutput(hist_jy_myy_inclusive);

  wk()->addOutput(hist_yy_myy_010_inclusive);
  wk()->addOutput(hist_jj_myy_010_inclusive);
  wk()->addOutput(hist_yj_myy_010_inclusive);
  wk()->addOutput(hist_jy_myy_010_inclusive);

  wk()->addOutput(hist_yy_myy_1020_inclusive);
  wk()->addOutput(hist_jj_myy_1020_inclusive);
  wk()->addOutput(hist_jy_myy_1020_inclusive);
  wk()->addOutput(hist_yj_myy_1020_inclusive);

  wk()->addOutput(hist_yy_myy_2030_inclusive);
  wk()->addOutput(hist_jj_myy_2030_inclusive);
  wk()->addOutput(hist_jy_myy_2030_inclusive);
  wk()->addOutput(hist_yj_myy_2030_inclusive);

  wk()->addOutput(hist_yy_myy_3040_inclusive);
  wk()->addOutput(hist_jj_myy_3040_inclusive);
  wk()->addOutput(hist_jy_myy_3040_inclusive);
  wk()->addOutput(hist_yj_myy_3040_inclusive);

  wk()->addOutput(hist_yy_myy_4060_inclusive);
  wk()->addOutput(hist_jj_myy_4060_inclusive);
  wk()->addOutput(hist_jy_myy_4060_inclusive);
  wk()->addOutput(hist_yj_myy_4060_inclusive);

  wk()->addOutput(hist_yy_myy_myy_purityweight_inclusive);
  wk()->addOutput(hist_jj_myy_myy_purityweight_inclusive);
  wk()->addOutput(hist_yj_myy_myy_purityweight_inclusive);
  wk()->addOutput(hist_jy_myy_myy_purityweight_inclusive);

  wk()->addOutput(hist_yy_myy_010_myy_purityweight_inclusive);
  wk()->addOutput(hist_jj_myy_010_myy_purityweight_inclusive);
  wk()->addOutput(hist_yj_myy_010_myy_purityweight_inclusive);
  wk()->addOutput(hist_jy_myy_010_myy_purityweight_inclusive);

  wk()->addOutput(hist_yy_myy_1020_myy_purityweight_inclusive);
  wk()->addOutput(hist_jj_myy_1020_myy_purityweight_inclusive);
  wk()->addOutput(hist_jy_myy_1020_myy_purityweight_inclusive);
  wk()->addOutput(hist_yj_myy_1020_myy_purityweight_inclusive);

  wk()->addOutput(hist_yy_myy_2030_myy_purityweight_inclusive);
  wk()->addOutput(hist_jj_myy_2030_myy_purityweight_inclusive);
  wk()->addOutput(hist_jy_myy_2030_myy_purityweight_inclusive);
  wk()->addOutput(hist_yj_myy_2030_myy_purityweight_inclusive);

  wk()->addOutput(hist_yy_myy_3040_myy_purityweight_inclusive);
  wk()->addOutput(hist_jj_myy_3040_myy_purityweight_inclusive);
  wk()->addOutput(hist_jy_myy_3040_myy_purityweight_inclusive);
  wk()->addOutput(hist_yj_myy_3040_myy_purityweight_inclusive);

  wk()->addOutput(hist_yy_myy_4060_myy_purityweight_inclusive);
  wk()->addOutput(hist_jj_myy_4060_myy_purityweight_inclusive);
  wk()->addOutput(hist_jy_myy_4060_myy_purityweight_inclusive);
  wk()->addOutput(hist_yj_myy_4060_myy_purityweight_inclusive);

  wk()->addOutput(hist_j130_pt_central);
  wk()->addOutput(hist_j130_eta_central);

  wk()->addOutput(hist_myy_010_central);
  wk()->addOutput(hist_myy_1020_central);
  wk()->addOutput(hist_myy_2030_central);
  wk()->addOutput(hist_myy_3040_central);
  wk()->addOutput(hist_myy_4060_central);

  wk()->addOutput(hist_j130_pt_010_central);
  wk()->addOutput(hist_j130_pt_1020_central);
  wk()->addOutput(hist_j130_pt_2030_central);
  wk()->addOutput(hist_j130_pt_3040_central);
  wk()->addOutput(hist_j130_pt_4060_central);
  
  wk()->addOutput(hist_yy_myy_myy_purityweight_central);
  wk()->addOutput(hist_jj_myy_myy_purityweight_central);
  wk()->addOutput(hist_jy_myy_myy_purityweight_central);
  wk()->addOutput(hist_yj_myy_myy_purityweight_central);

  wk()->addOutput(hist_yy_myy_central);
  wk()->addOutput(hist_jj_myy_central);
  wk()->addOutput(hist_jy_myy_central);
  wk()->addOutput(hist_yj_myy_central);

  wk()->addOutput(hist_yy_pflowj1_pt_010_central);
  wk()->addOutput(hist_jj_pflowj1_pt_010_central);
  wk()->addOutput(hist_yj_pflowj1_pt_010_central);
  wk()->addOutput(hist_jy_pflowj1_pt_010_central);

  wk()->addOutput(hist_yy_pflowj1_pt_1020_central);
  wk()->addOutput(hist_jj_pflowj1_pt_1020_central);
  wk()->addOutput(hist_yj_pflowj1_pt_1020_central);
  wk()->addOutput(hist_jy_pflowj1_pt_1020_central);

  wk()->addOutput(hist_yy_pflowj1_pt_2030_central);
  wk()->addOutput(hist_jj_pflowj1_pt_2030_central);
  wk()->addOutput(hist_yj_pflowj1_pt_2030_central);
  wk()->addOutput(hist_jy_pflowj1_pt_2030_central);

  wk()->addOutput(hist_yy_pflowj1_pt_3040_central);
  wk()->addOutput(hist_jj_pflowj1_pt_3040_central);
  wk()->addOutput(hist_yj_pflowj1_pt_3040_central);
  wk()->addOutput(hist_jy_pflowj1_pt_3040_central);

  wk()->addOutput(hist_yy_pflowj1_pt_4060_central);
  wk()->addOutput(hist_jj_pflowj1_pt_4060_central);
  wk()->addOutput(hist_yj_pflowj1_pt_4060_central);
  wk()->addOutput(hist_jy_pflowj1_pt_4060_central);

  wk()->addOutput(hist_jj_pflowj1_pt_010_ptj1_purityweight_central);
  wk()->addOutput(hist_yj_pflowj1_pt_010_ptj1_purityweight_central);
  wk()->addOutput(hist_jy_pflowj1_pt_010_ptj1_purityweight_central);

  wk()->addOutput(hist_jj_pflowj1_pt_1020_ptj1_purityweight_central);
  wk()->addOutput(hist_yj_pflowj1_pt_1020_ptj1_purityweight_central);
  wk()->addOutput(hist_jy_pflowj1_pt_1020_ptj1_purityweight_central);

  wk()->addOutput(hist_jj_pflowj1_pt_2030_ptj1_purityweight_central);
  wk()->addOutput(hist_yj_pflowj1_pt_2030_ptj1_purityweight_central);
  wk()->addOutput(hist_jy_pflowj1_pt_2030_ptj1_purityweight_central);

  wk()->addOutput(hist_jj_pflowj1_pt_3040_ptj1_purityweight_central);
  wk()->addOutput(hist_yj_pflowj1_pt_3040_ptj1_purityweight_central);
  wk()->addOutput(hist_jy_pflowj1_pt_3040_ptj1_purityweight_central);

  wk()->addOutput(hist_jj_pflowj1_pt_4060_ptj1_purityweight_central);
  wk()->addOutput(hist_yj_pflowj1_pt_4060_ptj1_purityweight_central);
  wk()->addOutput(hist_jy_pflowj1_pt_4060_ptj1_purityweight_central);

  wk()->addOutput(hist_yy_myy_010_central);
  wk()->addOutput(hist_jj_myy_010_central);
  wk()->addOutput(hist_yj_myy_010_central);
  wk()->addOutput(hist_jy_myy_010_central);

  wk()->addOutput(hist_yy_myy_1020_central);
  wk()->addOutput(hist_jj_myy_1020_central);
  wk()->addOutput(hist_yj_myy_1020_central);
  wk()->addOutput(hist_jy_myy_1020_central);

  wk()->addOutput(hist_yy_myy_2030_central);
  wk()->addOutput(hist_jj_myy_2030_central);
  wk()->addOutput(hist_yj_myy_2030_central);
  wk()->addOutput(hist_jy_myy_2030_central);

  wk()->addOutput(hist_yy_myy_3040_central);
  wk()->addOutput(hist_jj_myy_3040_central);
  wk()->addOutput(hist_yj_myy_3040_central);
  wk()->addOutput(hist_jy_myy_3040_central);

  wk()->addOutput(hist_yy_myy_4060_central);
  wk()->addOutput(hist_jj_myy_4060_central);
  wk()->addOutput(hist_yj_myy_4060_central);
  wk()->addOutput(hist_jy_myy_4060_central);

  wk()->addOutput(hist_jj_myy_010_myy_purityweight_central);
  wk()->addOutput(hist_yj_myy_010_myy_purityweight_central);
  wk()->addOutput(hist_jy_myy_010_myy_purityweight_central);

  wk()->addOutput(hist_jj_myy_1020_myy_purityweight_central);
  wk()->addOutput(hist_yj_myy_1020_myy_purityweight_central);
  wk()->addOutput(hist_jy_myy_1020_myy_purityweight_central);

  wk()->addOutput(hist_jj_myy_2030_myy_purityweight_central);
  wk()->addOutput(hist_yj_myy_2030_myy_purityweight_central);
  wk()->addOutput(hist_jy_myy_2030_myy_purityweight_central);

  wk()->addOutput(hist_jj_myy_3040_myy_purityweight_central);
  wk()->addOutput(hist_yj_myy_3040_myy_purityweight_central);
  wk()->addOutput(hist_jy_myy_3040_myy_purityweight_central);

  wk()->addOutput(hist_jj_myy_4060_myy_purityweight_central);
  wk()->addOutput(hist_yj_myy_4060_myy_purityweight_central);
  wk()->addOutput(hist_jy_myy_4060_myy_purityweight_central);

  wk()->addOutput(hist_mc_pt_ptj1_purityweight);
  wk()->addOutput(hist_mc_myy_myy_purityweight);
  wk()->addOutput(hist_mc_mu_mu_purityweight);
  wk()->addOutput(hist_mc_myy_myy_purityweight_inclusive);

  wk()->addOutput(hist_mc_myy_010_myy_purityweight);
  wk()->addOutput(hist_mc_myy_1020_myy_purityweight);
  wk()->addOutput(hist_mc_myy_2030_myy_purityweight);
  wk()->addOutput(hist_mc_myy_3040_myy_purityweight);
  wk()->addOutput(hist_mc_myy_4060_myy_purityweight);

  wk()->addOutput(hist_mc_pt_010_ptj1_purityweight);
  wk()->addOutput(hist_mc_pt_1020_ptj1_purityweight);
  wk()->addOutput(hist_mc_pt_2030_ptj1_purityweight);
  wk()->addOutput(hist_mc_pt_3040_ptj1_purityweight);
  wk()->addOutput(hist_mc_pt_4060_ptj1_purityweight);


  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamPhotonAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  std::cout << "IS mc16a?: " << isMCa << std::endl;
  std::cout << "IS mc16d?: " << isMCd << std::endl;
  std::cout << "IS mc16e?: " << isMCe << std::endl;
  std::cout << "IS mc16de?: " << isMCde << std::endl;
  std::cout << "IS data?: " << isData << std::endl;
  if (isMCa == true){
    cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_100_160_noDalitz_weighted");
    // cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_160_250_noDalitz_weighted");
    // cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa2_myy_90_175_noDalitz_weighted");
    sum_weights = ((cutflow->GetBinContent(1) / cutflow->GetBinContent(2)) * cutflow->GetBinContent(3));
    // sum_weights = 104724945.164;
  }
  if (isMCd == true){
    std::cout << "mc16d file" << std::endl;
    cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_100_160_noDalitz_weighted");
    // cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_160_250_noDalitz_weighted");
    // cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa2_myy_90_175_noDalitz_weighted");
    sum_weights = ((cutflow->GetBinContent(1) / cutflow->GetBinContent(2)) * cutflow->GetBinContent(3));
    // sum_weights = 131279689.835;
  }
  if (isMCe == true){
    std::cout << "mc16e file" << std::endl;
    cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_100_160_noDalitz_weighted");
    // cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_160_250_noDalitz_weighted");
    // cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa2_myy_90_175_noDalitz_weighted");
    sum_weights = ((cutflow->GetBinContent(1) / cutflow->GetBinContent(2)) * cutflow->GetBinContent(3));
    // sum_weights = 35667314.9538;
  }
  if (isMCde == true){
    std::cout << "mc16d+mc16e file" << std::endl;
    cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_100_160_noDalitz_weighted");
    // cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa_2DP20_myy_160_250_noDalitz_weighted");
    // cutflow = (TH1F*)wk()->inputFile()->Get("CutFlow_Sherpa2_myy_90_175_noDalitz_weighted");
    sum_weights = ((cutflow->GetBinContent(1) / cutflow->GetBinContent(2)) * cutflow->GetBinContent(3));
  }


  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamPhotonAnalysis :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamPhotonAnalysis :: initialize ()
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
  // as a check, let's see the number of events in our xAOD
  Warning("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamPhotonAnalysis :: execute ()
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

  // if( (m_eventCounter % 10000) ==0 ){Info("execute()", "Event number = %i", m_eventCounter );}
  // Info("execute()", "Event number = %i", m_eventCounter );

  m_eventCounter++;


  // if (m_eventCounter < 500){


  // initialize variable
  ResetVariables();

  m_eventInfoCont =0;

  EL_RETURN_CHECK("execute()",event->retrieve( m_eventInfoCont, "EventInfo"));
  
  const xAOD::EventInfo *HGamEventInfo = NULL;
  if (! event->retrieve(HGamEventInfo, "HGamEventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::PhotonContainer* HgamPhotons = 0;
  if (! event->retrieve(HgamPhotons, "HGamPhotons").isSuccess()) {
    Error("execute()", "Failed to retrieve HgamPhotons. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::JetContainer* pflowjets = NULL;
  if (!event->retrieve(pflowjets, "HGamAntiKt4EMPFlowJets").isSuccess()) {
    Error("execute()", "Failed to retrieve pflowjets. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  isPassedTriggerMatch = HGamEventInfo->auxdata<char>("isPassedTriggerMatch");
  isPassedRelPtCuts = HGamEventInfo->auxdata<char>("isPassedRelPtCuts");
  isPassedMassCut = HGamEventInfo->auxdata<char>("isPassedMassCut");
  isPassedPreselection = HGamEventInfo->auxdata<char>("isPassedPreselection");
  HGam_isPassed = HGamEventInfo->auxdata<char>("isPassed");

  m_yy = HGamEventInfo->auxdata<float>("m_yy")*0.001;
  m_mu = static_cast<int>(m_eventInfoCont->actualInteractionsPerCrossing());


  if (isMCa == true){
    lumi_mc16 = 36205.26;//36215.0;
    eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
              * HGamEventInfo->auxdataConst<float>("weight") 
              * lumi_mc16)
              / sum_weights);
  }
  if (isMCd == true){
    lumi_mc16 = 44307.4; 
    eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
              * HGamEventInfo->auxdataConst<float>("weight") 
              * lumi_mc16)
              / sum_weights);
  }
  if (isMCe == true){
    lumi_mc16 = 58450.1;
    eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
              * HGamEventInfo->auxdataConst<float>("weight") 
              * lumi_mc16)
              / sum_weights);
  }

  if (isMCde == true){
    lumi_mc16 = 44307.4 + 58450.1; 
    eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
              * HGamEventInfo->auxdataConst<float>("weight") 
              * lumi_mc16)
              / sum_weights);
  }

  if (isData == true){eventweight = 1;}


  // from https://gitlab.cern.ch/atlas-hgam-sw/HGamBackgroundStudies/blob/master/Root/DiPhotonBkg2x2DSB.cxx#L746
  const unsigned int PhotonLoosePrime5 = egammaPID::PhotonLoose |
    0x1 << egammaPID::ClusterStripsEratio_Photon | // not the normal "Eratio" (this is f1 = E(layer1)/E(total), needed to have a meaningful measurement of the shower shape in the strips
     0x1 << egammaPID::ClusterStripsDeltaEmax2_Photon | // never failed in isEMTight anymore, but added since it's included in tight |
    0x1 << egammaPID::ClusterStripsDEmaxs1_Photon; // Eratio

  const unsigned int PhotonLoosePrime4 = PhotonLoosePrime5;

  const unsigned int PhotonLoosePrime3 = PhotonLoosePrime4 | 
    0x1 << egammaPID::ClusterStripsWtot_Photon;
  
  // const unsigned int PhotonLoosePrime2 = PhotonLoosePrime3 | // also require "DeltaE" ("w3" and "Fside" are only remaining requirements for tight)
  //   0x1 << egammaPID::ClusterStripsDeltaE_Photon;

passed = false;
leading_photon = 0;
// std::cout << "Pass TriggerMatch?: " << isPassedTriggerMatch << "   Pass RelPtCuts?: " << isPassedRelPtCuts << "   Pass MassCut?: " << isPassedMassCut << "   Pass Preselection?: " << isPassedPreselection << std::endl;
if (isPassedTriggerMatch && isPassedRelPtCuts && isPassedMassCut && isPassedPreselection){
  if (pflowjets->size() > 0){
  auto jet = (*pflowjets)[0];
    if (jet->pt() * 0.001 > 30){
    passed = true;
      for (auto photon: *HgamPhotons){
        if (leading_photon == 0){
          leading_photon = 1;
          // This is the leading photon
          // std::cout << "Leading photon pt: " << photon->auxdataConst<float>("pt") << std::endl;
          gam1_isEMTight = photon->auxdataConst<unsigned int>("isEMTight");
          y1_tight = photon->auxdataConst<char>("isTight");
          // std::cout << "Tight1?: "<< photon->auxdataConst<unsigned int>("isEMTight") << std::endl;

          loose1 = !(gam1_isEMTight & PhotonLoosePrime3); //if(!loose1) continue;

          // std::cout << "loose1 " << loose1 << std::endl;
          // std::cout << "y1_tight: " << y1_tight << "    PhotonLoosePrime3: " << PhotonLoosePrime3 << "    loose1: " << loose1<< std::endl;
          tmp_y1_m = photon->auxdataConst<float>("m");
          tmp_y1_phi = photon->auxdataConst<float>("phi");
          tmp_y1_eta = photon->auxdataConst<float>("eta");
          tmp_y1_pt = photon->auxdataConst<float>("pt");

          y1_IsIso_def =  (photon->auxdataConst<float>("topoetcone20") < photon->auxdataConst<float>("pt")*0.065 &&
              photon->auxdataConst<float>("ptcone20") < photon->auxdataConst<float>("pt")*0.05 )?1:0;
          y1_IsIso = photon->auxdataConst<char>("isIsoFixedCutLoose");
          if (y1_IsIso != y1_IsIso_def){std::cout << "y1 isolation change" << std::endl;}

        }
        else if (leading_photon == 1){
          leading_photon = 2;
          // This is the subleading photon
          // std::cout << "Subleading photon pt: " << photon->auxdataConst<float>("pt") << std::endl;
          gam2_isEMTight = photon->auxdataConst<unsigned int>("isEMTight");
          y2_tight = photon->auxdataConst<char>("isTight");
          // std::cout << "Tight2?: "<< photon->auxdataConst<char>("isTight") << std::endl;

          loose2 = !(gam2_isEMTight & PhotonLoosePrime3); //if(!loose1) continue;
          tmp_y2_m = photon->auxdataConst<float>("m");
          tmp_y2_phi = photon->auxdataConst<float>("phi");
          tmp_y2_eta = photon->auxdataConst<float>("eta");
          tmp_y2_pt = photon->auxdataConst<float>("pt");

          y2_IsIso_def =  (photon->auxdataConst<float>("topoetcone20")<photon->auxdataConst<float>("pt")*0.065 &&
              photon->auxdataConst<float>("ptcone20")<photon->auxdataConst<float>("pt")*0.05 )?1:0; 
          y2_IsIso = photon->auxdataConst<char>("isIsoFixedCutLoose");
          if (y2_IsIso != y2_IsIso_def){std::cout << "y2 isolation change" << std::endl;}
        }
      } // end of jet pt requirement
    } //end of 1 jet requirement
  } // end of photon loop
} // end of passed requirements

if (tmp_y2_pt > tmp_y1_pt){std::cout << "subleading biggger" << std::endl;}

  npflow30jetsperevent  = 0;
  npflow50jetsperevent  = 0;

  npflow30jetsperevent_fJVT  = 0;
  npflow50jetsperevent_fJVT  = 0;


  leadingpflow30jetpt = 0;
  leadingpflow50jetpt = 0;

  leadingpflow30jetpt_fJVT = 0;
  leadingpflow50jetpt_fJVT = 0;

if (HGam_isPassed){

  hist_myy_inclusive->Fill(m_yy, eventweight);
  if (m_mu < 10){hist_myy_010_inclusive->Fill(m_yy, eventweight);}
  else if (m_mu < 20){hist_myy_1020_inclusive->Fill(m_yy, eventweight);}
  else if (m_mu < 30){hist_myy_2030_inclusive->Fill(m_yy, eventweight);}
  else if (m_mu < 40){hist_myy_3040_inclusive->Fill(m_yy, eventweight);}
  else if (m_mu < 60){hist_myy_4060_inclusive->Fill(m_yy, eventweight);}

  int N_points_mc_myy = gr_m_yy_gg_purity_TotErr->GetN();
  for(int i=0; i < N_points_mc_myy; i++){
    gr_m_yy_gg_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_yy);
    myy_purity_weight = eventweight * (myy_purity_value_yy);//myy_purity_value_yy); //lydia test
    if ((m_yy > myy_value - gr_m_yy_gg_purity_TotErr->GetErrorX(i)) && (m_yy < myy_value + gr_m_yy_gg_purity_TotErr->GetErrorX(i))){
      hist_mc_myy_myy_purityweight_inclusive->Fill(m_yy, myy_purity_weight);
    } // end of myy bin check    
  } // end of loop over each myy bin

}
if (pflowjets->size() > 0){
auto jet = (*pflowjets)[0];
  if (jet->pt() * 0.001 > 30){
  // 
  //  Begin loop over particle flow jets comparing leading jet pt thresholds
  //
    if (HGam_isPassed){
      // std::cout << "is data?" << isData << " and m_yy = " << m_yy << std::endl;
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
              leadingpflow30jetm_fJVT  = (jet->m() * 0.001);
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
              leadingpflow50jetm_fJVT  = (jet->m() * 0.001);
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
              leadingpflow30jetm  = (jet->m() * 0.001);
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
              leadingpflow50jetm  = (jet->m() * 0.001);
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
        else {
          pflow_fjvt_fail_eta = (jet->eta());
          // std::cerr<<"did not pass fjvt"<<std::endl;
        }
        
      hist_pass_fJVT->Fill(pflow_fjvt_pass_eta, eventweight);
      hist_fail_fJVT->Fill(pflow_fjvt_fail_eta, eventweight);

      } //end of jet loop
    } //end of HGam passed 




  if (passed){
    if (y1_IsIso && y2_IsIso){
      y1TLVec.SetPtEtaPhiM(tmp_y1_pt, tmp_y1_eta, tmp_y1_phi, tmp_y1_m);
      y2TLVec.SetPtEtaPhiM(tmp_y2_pt, tmp_y2_eta, tmp_y2_phi, tmp_y2_m);
      yyTLVec = y1TLVec + y2TLVec;

      if (y1_tight && y2_tight){// && y1_IsIso && y2_IsIso){ 
        // std::cout << "yy" << std::endl;
        hist_yy_pflowj1_pt->Fill(jet->pt() * 0.001); 
        hgam_yy_pflowj1_pt = jet->pt() * 0.001;
        hist_yy_pflowj1_eta->Fill(jet->eta());
        hgam_yy_pflowj1_eta = jet->eta();

        hist_yy_y1_eta->Fill(tmp_y1_eta);
        hist_yy_y1_pt->Fill(tmp_y1_pt * 0.001);
        hist_yy_y2_eta->Fill(tmp_y2_eta);
        hist_yy_y2_pt->Fill(tmp_y2_pt * 0.001);
        hgam_yy_y1_eta = tmp_y1_eta;
        hgam_yy_y2_eta = tmp_y2_eta;
        hgam_yy_y1_pt = tmp_y1_pt * 0.001;
        hgam_yy_y2_pt = tmp_y2_pt * 0.001;

        hist_yy_myy->Fill(yyTLVec.M() * 0.001);

        hist_yy_mu->Fill(m_mu);

        hgam_yy_m = yyTLVec.M() * 0.001;
        hgam_yy_pt = yyTLVec.Pt() * 0.001;
        hgam_yy_eta = yyTLVec.Eta();
        hist_yy_m->Fill(yyTLVec.M() * 0.001);
        hist_yy_pt->Fill(yyTLVec.Pt() * 0.001);
        hist_yy_eta->Fill(yyTLVec.Eta());              
        if (m_mu < 10){hist_yy_pflowj1_pt_010->Fill((jet->pt() * 0.001));hist_yy_myy_010->Fill((yyTLVec.M() * 0.001));}
        else if (m_mu < 20){hist_yy_pflowj1_pt_1020->Fill((jet->pt() * 0.001));hist_yy_myy_1020->Fill((yyTLVec.M() * 0.001));}
        else if (m_mu < 30){hist_yy_pflowj1_pt_2030->Fill((jet->pt() * 0.001));hist_yy_myy_2030->Fill((yyTLVec.M() * 0.001));}
        else if (m_mu < 40){hist_yy_pflowj1_pt_3040->Fill((jet->pt() * 0.001));hist_yy_myy_3040->Fill((yyTLVec.M() * 0.001));}
        else if (m_mu < 60){hist_yy_pflowj1_pt_4060->Fill((jet->pt() * 0.001));hist_yy_myy_4060->Fill((yyTLVec.M() * 0.001));}
        if (abs(jet->eta()) < 2.5){
          hist_yy_myy_central->Fill(yyTLVec.M() * 0.001);
          if (m_mu < 10){hist_yy_pflowj1_pt_010_central->Fill((jet->pt() * 0.001));hist_yy_myy_010_central->Fill((yyTLVec.M() * 0.001));}
          else if (m_mu < 20){hist_yy_pflowj1_pt_1020_central->Fill((jet->pt() * 0.001));hist_yy_myy_1020_central->Fill((yyTLVec.M() * 0.001));}
          else if (m_mu < 30){hist_yy_pflowj1_pt_2030_central->Fill((jet->pt() * 0.001));hist_yy_myy_2030_central->Fill((yyTLVec.M() * 0.001));}
          else if (m_mu < 40){hist_yy_pflowj1_pt_3040_central->Fill((jet->pt() * 0.001));hist_yy_myy_3040_central->Fill((yyTLVec.M() * 0.001));}
          else if (m_mu < 60){hist_yy_pflowj1_pt_4060_central->Fill((jet->pt() * 0.001));hist_yy_myy_4060_central->Fill((yyTLVec.M() * 0.001));}

        }
      }// end of yy

      else if (!y1_tight && !y2_tight && loose1 && loose2){
        // std::cout << "jj" << std::endl;
        hist_jj_j1_pt->Fill(tmp_y1_pt * 0.001);
        hist_jj_j2_pt->Fill(tmp_y2_pt * 0.001);
        hist_jj_j1_eta->Fill(tmp_y1_eta);
        hist_jj_j2_eta->Fill(tmp_y2_eta);

        hist_jj_myy->Fill(yyTLVec.M() * 0.001);
        hist_jj_mu->Fill(m_mu);

        hgam_jj_j1_pt = tmp_y1_pt * 0.001;
        hgam_jj_j2_pt = tmp_y2_pt * 0.001;
        hgam_jj_j1_eta = tmp_y1_eta;
        hgam_jj_j2_eta = tmp_y2_eta;
        hist_jj_pflowj1_pt->Fill(jet->pt() * 0.001); 
        hgam_jj_pflowj1_pt = jet->pt() * 0.001;
        hist_jj_pflowj1_eta->Fill(jet->eta());
        hgam_jj_pflowj1_eta = jet->eta();
        if (m_mu < 10){hist_jj_pflowj1_pt_010->Fill(jet->pt() * 0.001);hist_jj_myy_010->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 20){hist_jj_pflowj1_pt_1020->Fill(jet->pt() * 0.001);hist_jj_myy_1020->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 30){hist_jj_pflowj1_pt_2030->Fill(jet->pt() * 0.001);hist_jj_myy_2030->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 40){hist_jj_pflowj1_pt_3040->Fill(jet->pt() * 0.001);hist_jj_myy_3040->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 60){hist_jj_pflowj1_pt_4060->Fill(jet->pt() * 0.001);hist_jj_myy_4060->Fill(yyTLVec.M() * 0.001);}
        if (abs(jet->eta()) < 2.5){
          hist_jj_myy_central->Fill(yyTLVec.M() * 0.001);
          if (m_mu < 10){hist_jj_pflowj1_pt_010_central->Fill(jet->pt() * 0.001);hist_jj_myy_010_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 20){hist_jj_pflowj1_pt_1020_central->Fill(jet->pt() * 0.001);hist_jj_myy_1020_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 30){hist_jj_pflowj1_pt_2030_central->Fill(jet->pt() * 0.001);hist_jj_myy_2030_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 40){hist_jj_pflowj1_pt_3040_central->Fill(jet->pt() * 0.001);hist_jj_myy_3040_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 60){hist_jj_pflowj1_pt_4060_central->Fill(jet->pt() * 0.001);hist_jj_myy_4060_central->Fill(yyTLVec.M() * 0.001);}
        }
      }// end of jj

      else if (y1_tight && !y2_tight && loose2) {// && y1_IsIso) {
        // std::cout << "yj" << std::endl;
        hist_yj_y_pt->Fill(tmp_y1_pt * 0.001);
        hist_yj_j_pt->Fill(tmp_y2_pt * 0.001);
        hist_yj_y_eta->Fill(tmp_y1_eta);
        hist_yj_j_eta->Fill(tmp_y2_eta);

        hgam_yj_y_pt = tmp_y1_pt * 0.001;
        hgam_yj_j_pt = tmp_y2_pt * 0.001;
        hgam_yj_y_eta = tmp_y1_eta;
        hgam_yj_j_eta = tmp_y2_eta;   

        hist_yj_myy->Fill(yyTLVec.M() * 0.001);

        hist_yj_mu->Fill(m_mu);
        // hgam_yy_pt = yyTLVec.Pt() * 0.001;
        // hgam_yy_eta = yyTLVec.Eta();

        hist_yj_pflowj1_pt->Fill(jet->pt() * 0.001); 
        hgam_yj_pflowj1_pt = jet->pt() * 0.001;
        hist_yj_pflowj1_eta->Fill(jet->eta());
        hgam_yj_pflowj1_eta = jet->eta();

        if (m_mu < 10){hist_yj_pflowj1_pt_010->Fill(jet->pt() * 0.001);hist_yj_myy_010->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 20){hist_yj_pflowj1_pt_1020->Fill(jet->pt() * 0.001);hist_yj_myy_1020->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 30){hist_yj_pflowj1_pt_2030->Fill(jet->pt() * 0.001);hist_yj_myy_2030->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 40){hist_yj_pflowj1_pt_3040->Fill(jet->pt() * 0.001);hist_yj_myy_3040->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 60){hist_yj_pflowj1_pt_4060->Fill(jet->pt() * 0.001);hist_yj_myy_4060->Fill(yyTLVec.M() * 0.001);}
        if (abs(jet->eta()) < 2.5){
          hist_yj_myy_central->Fill(yyTLVec.M() * 0.001);
          if (m_mu < 10){hist_yj_pflowj1_pt_010_central->Fill(jet->pt() * 0.001);hist_yj_myy_010_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 20){hist_yj_pflowj1_pt_1020_central->Fill(jet->pt() * 0.001);hist_yj_myy_1020_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 30){hist_yj_pflowj1_pt_2030_central->Fill(jet->pt() * 0.001);hist_yj_myy_2030_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 40){hist_yj_pflowj1_pt_3040_central->Fill(jet->pt() * 0.001);hist_yj_myy_3040_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 60){hist_yj_pflowj1_pt_4060_central->Fill(jet->pt() * 0.001);hist_yj_myy_4060_central->Fill(yyTLVec.M() * 0.001);}
        }
     }//end of yj

      else if (!y1_tight && y2_tight && loose1){// && y2_IsIso){
        // std::cout << "jy" << std::endl;
        hist_jy_j_pt->Fill(tmp_y1_pt * 0.001);
        hist_jy_y_pt->Fill(tmp_y2_pt * 0.001);
        hist_jy_j_eta->Fill(tmp_y1_eta);
        hist_jy_y_eta->Fill(tmp_y2_eta);

        hgam_jy_j_pt = tmp_y1_pt * 0.001;
        hgam_jy_y_pt = tmp_y2_pt * 0.001;
        hgam_jy_j_eta = tmp_y1_eta;
        hgam_jy_y_eta = tmp_y2_eta;      

        hist_jy_myy->Fill(yyTLVec.M() * 0.001);

        hist_jy_mu->Fill(m_mu);

        hist_jy_pflowj1_pt->Fill(jet->pt() * 0.001); 
        hgam_jy_pflowj1_pt = jet->pt() * 0.001;
        hist_jy_pflowj1_eta->Fill(jet->eta());
        hgam_jy_pflowj1_eta = jet->eta();
        if (m_mu < 10){hist_jy_pflowj1_pt_010->Fill(jet->pt() * 0.001);hist_jy_myy_010->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 20){hist_jy_pflowj1_pt_1020->Fill(jet->pt() * 0.001);hist_jy_myy_1020->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 30){hist_jy_pflowj1_pt_2030->Fill(jet->pt() * 0.001);hist_jy_myy_2030->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 40){hist_jy_pflowj1_pt_3040->Fill(jet->pt() * 0.001);hist_jy_myy_3040->Fill(yyTLVec.M() * 0.001);}
        else if (m_mu < 60){hist_jy_pflowj1_pt_4060->Fill(jet->pt() * 0.001);hist_jy_myy_4060->Fill(yyTLVec.M() * 0.001);}
        if (abs(jet->eta()) < 2.5){
          hist_jy_myy_central->Fill(yyTLVec.M() * 0.001);
          if (m_mu < 10){hist_jy_pflowj1_pt_010_central->Fill(jet->pt() * 0.001);hist_jy_myy_010_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 20){hist_jy_pflowj1_pt_1020_central->Fill(jet->pt() * 0.001);hist_jy_myy_1020_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 30){hist_jy_pflowj1_pt_2030_central->Fill(jet->pt() * 0.001);hist_jy_myy_2030_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 40){hist_jy_pflowj1_pt_3040_central->Fill(jet->pt() * 0.001);hist_jy_myy_3040_central->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 60){hist_jy_pflowj1_pt_4060_central->Fill(jet->pt() * 0.001);hist_jy_myy_4060_central->Fill(yyTLVec.M() * 0.001);}
        }
      }//end of jy

      if (y1_tight && y2_tight){// && y1_IsIso && y2_IsIso){ 
        // std::cout << "yy" << std::endl;
        int N_points_ptj1 = gr_pT_j1_30_gg_purity_TotErr->GetN();
        for(int i=0; i < N_points_ptj1; i++){
          gr_pT_j1_30_gg_purity_TotErr->GetPoint(i, pt_value, ptj1_purity_value_yy);
          // std::cout <<  pt_value - gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i)  << " - " << pt_value + gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i) << std::endl;
          ptj1_purity_weight = eventweight * ptj1_purity_value_yy; // = 1; lydia test
          if ((jet->pt() * 0.001 > pt_value - gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i)) && (jet->pt() * 0.001 < pt_value + gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i))){
            // std::cout << jet->pt() * 0.001  <<"  in bin " <<  pt_value  << "  with purity weight:  " << ptj1_purity_weight << std::endl;
            hist_yy_pflowj1_pt_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight); 
            hist_yy_pflowj1_eta_purityweight->Fill(jet->eta(), ptj1_purity_weight);

            if (m_mu < 10){hist_yy_pflowj1_pt_010_ptj1_purityweight->Fill((jet->pt() * 0.001), ptj1_purity_weight);}
            else if (m_mu < 20){hist_yy_pflowj1_pt_1020_ptj1_purityweight->Fill((jet->pt() * 0.001), ptj1_purity_weight);}
            else if (m_mu < 30){hist_yy_pflowj1_pt_2030_ptj1_purityweight->Fill((jet->pt() * 0.001), ptj1_purity_weight);}
            else if (m_mu < 40){hist_yy_pflowj1_pt_3040_ptj1_purityweight->Fill((jet->pt() * 0.001), ptj1_purity_weight);}
            else if (m_mu < 60){hist_yy_pflowj1_pt_4060_ptj1_purityweight->Fill((jet->pt() * 0.001), ptj1_purity_weight);}
          } // end of pt bin check    
        } // end of loop over each ptj1 bin

        int N_points_etaj1 = gr_eta_j1_30_gg_purity_TotErr->GetN();
        for(int i=0; i < N_points_etaj1; i++){
          gr_eta_j1_30_gg_purity_TotErr->GetPoint(i, eta_value, etaj1_purity_value_yy);
          // std::cout <<  eta_value - gr_eta_j1_30_gg_purity_TotErr->GetErrorX(i)  << " - " << eta_value + gr_eta_j1_30_gg_purity_TotErr->GetErrorX(i) << std::endl;
          etaj1_purity_weight = eventweight * etaj1_purity_value_yy; // = 1; lydia test
          if ((jet->eta() > eta_value - gr_eta_j1_30_gg_purity_TotErr->GetErrorX(i)) && (jet->eta() < eta_value + gr_eta_j1_30_gg_purity_TotErr->GetErrorX(i))){
            // std::cout << jet->eta()  <<"  in bin " <<  eta_value  << "  with purity weight:  " << etaj1_purity_weight << std::endl;
            hist_yy_pflowj1_pt_ptj1_purityweight->Fill(jet->eta(), etaj1_purity_weight); 
            // hgam_yy_pflowj1_pt = jet->eta();
            hist_yy_pflowj1_eta_purityweight->Fill(jet->eta(), etaj1_purity_weight);
          } // end of eta bin check    
        } // end of loop over each etaj1 bin

        int N_points_myy = gr_m_yy_gg_purity_TotErr->GetN();
        for(int i=0; i < N_points_myy; i++){
          gr_m_yy_gg_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_yy);
          // std::cout <<  myy_value - gr_m_yy_gg_purity_TotErr->GetErrorX(i)  << " - " << myy_value + gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i) << std::endl;
          myy_purity_weight = eventweight * myy_purity_value_yy; // = 1; lydia test
          if ((yyTLVec.M() * 0.001 > myy_value - gr_m_yy_gg_purity_TotErr->GetErrorX(i)) && (yyTLVec.M() * 0.001 < myy_value + gr_m_yy_gg_purity_TotErr->GetErrorX(i))){
            // std::cout << yyTLVec.M() * 0.001  <<"  in bin " <<  myy_value  << "  with purity weight:  " << myy_purity_weight << std::endl;
            hist_yy_myy_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight); 

            if (m_mu < 10){hist_yy_myy_010_myy_purityweight->Fill((yyTLVec.M() * 0.001), myy_purity_weight);}
            else if (m_mu < 20){hist_yy_myy_1020_myy_purityweight->Fill((yyTLVec.M() * 0.001), myy_purity_weight);}
            else if (m_mu < 30){hist_yy_myy_2030_myy_purityweight->Fill((yyTLVec.M() * 0.001), myy_purity_weight);}
            else if (m_mu < 40){hist_yy_myy_3040_myy_purityweight->Fill((yyTLVec.M() * 0.001), myy_purity_weight);}
            else if (m_mu < 60){hist_yy_myy_4060_myy_purityweight->Fill((yyTLVec.M() * 0.001), myy_purity_weight);}
          } // end of myy bin check    
        } // end of loop over each myy bin
        int N_points_mu = gr_mu_gg_purity_TotErr->GetN();
        for(int i=0; i < N_points_mu; i++){
          gr_mu_gg_purity_TotErr->GetPoint(i, mu_value, mu_purity_value_yy);
          // std::cout <<  mu_value - gr_mu_gg_purity_TotErr->GetErrorX(i)  << " - " << mu_value + gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i) << std::endl;
          myy_purity_weight = eventweight * mu_purity_value_yy; // = 1; lydia test
          if ((m_mu > mu_value - gr_mu_gg_purity_TotErr->GetErrorX(i)) && (m_mu < mu_value + gr_mu_gg_purity_TotErr->GetErrorX(i))){
            // std::cout << yyTLVec.M() * 0.001  <<"  in bin " <<  mu_value  << "  with purity weight:  " << myy_purity_weight << std::endl;             
            hist_yy_mu_mu_purityweight->Fill((m_mu), mu_purity_weight);
          } // end of mu bin check    
        } // end of loop over each mu bin
      }// end of yy

      else if (!y1_tight && !y2_tight && loose1 && loose2){
        y1TLVec.SetPtEtaPhiM(tmp_y1_pt, tmp_y1_eta, tmp_y1_phi, tmp_y1_m);
        y2TLVec.SetPtEtaPhiM(tmp_y2_pt, tmp_y2_eta, tmp_y2_phi, tmp_y2_m);
        yyTLVec = y1TLVec + y2TLVec;      // std::cout << "jj" << std::endl;
        int N_points_ptj1 = gr_pT_j1_30_jj_purity_TotErr->GetN();
        for(int i=0; i < N_points_ptj1; i++){
          gr_pT_j1_30_jj_purity_TotErr->GetPoint(i, pt_value, ptj1_purity_value_jj);
          ptj1_purity_value_yy = gr_pT_j1_30_gg_purity_TotErr->GetY()[i];
          // std::cout <<  pt_value - gr_pT_j1_30_jj_purity_TotErr->GetErrorX(i)  << " - " << pt_value + gr_pT_j1_30_jj_purity_TotErr->GetErrorX(i) << std::endl;
          ptj1_purity_weight = eventweight * (ptj1_purity_value_jj / ptj1_purity_value_yy); // lydia test
          if ((jet->pt() * 0.001 > pt_value - gr_pT_j1_30_jj_purity_TotErr->GetErrorX(i)) && (jet->pt() * 0.001 < pt_value + gr_pT_j1_30_jj_purity_TotErr->GetErrorX(i))){

            hist_jj_pflowj1_pt_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight); 
            // hgam_jj_pflowj1_pt = jet->pt() * 0.001;
            hist_jj_pflowj1_eta_purityweight->Fill(jet->eta(), ptj1_purity_weight);
            // hgam_jj_pflowj1_eta = jet->eta();
            if (m_mu < 10){hist_jj_pflowj1_pt_010_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 20){hist_jj_pflowj1_pt_1020_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 30){hist_jj_pflowj1_pt_2030_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 40){hist_jj_pflowj1_pt_3040_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 60){hist_jj_pflowj1_pt_4060_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            if (abs(jet->eta()) < 2.5){
              if (m_mu < 10){hist_jj_pflowj1_pt_010_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
              else if (m_mu < 20){hist_jj_pflowj1_pt_1020_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
              else if (m_mu < 30){hist_jj_pflowj1_pt_2030_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
              else if (m_mu < 40){hist_jj_pflowj1_pt_3040_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
              else if (m_mu < 60){hist_jj_pflowj1_pt_4060_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            }
          } // end of pt bin check    
        } // end of loop over each ptj1 bin

        int N_points_etaj1 = gr_eta_j1_30_jj_purity_TotErr->GetN();
        for(int i=0; i < N_points_etaj1; i++){
          gr_eta_j1_30_jj_purity_TotErr->GetPoint(i, eta_value, etaj1_purity_value_jj);
          etaj1_purity_value_yy = gr_eta_j1_30_gg_purity_TotErr->GetY()[i];
          etaj1_purity_weight = eventweight * (etaj1_purity_value_jj/etaj1_purity_value_yy); // = 1; lydia test
          if ((jet->eta() > eta_value - gr_eta_j1_30_jj_purity_TotErr->GetErrorX(i)) && (jet->eta() < eta_value + gr_eta_j1_30_jj_purity_TotErr->GetErrorX(i))){
            hist_jj_pflowj1_pt_ptj1_purityweight->Fill(jet->eta(), etaj1_purity_weight); 
            hist_jj_pflowj1_eta_purityweight->Fill(jet->eta(), etaj1_purity_weight);
          } // end of eta bin check    
        } // end of loop over each etaj1 bin

        int N_points_myy = gr_m_yy_jj_purity_TotErr->GetN();
        for(int i=0; i < N_points_myy; i++){
          gr_m_yy_jj_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_jj);
          myy_purity_value_yy = gr_m_yy_gg_purity_TotErr->GetY()[i];
          // std::cout <<  myy_value - gr_m_yy_jj_purity_TotErr->GetErrorX(i)  << " - " << myy_value + gr_m_yy_jj_purity_TotErr->GetErrorX(i) << std::endl;
          myy_purity_weight = eventweight * (myy_purity_value_jj/myy_purity_value_yy); //lydia test
          if ((yyTLVec.M() * 0.001 > myy_value - gr_m_yy_jj_purity_TotErr->GetErrorX(i)) && (yyTLVec.M() * 0.001 < myy_value + gr_m_yy_jj_purity_TotErr->GetErrorX(i))){

            hist_jj_myy_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);

            if (m_mu < 10){hist_jj_myy_010_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 20){hist_jj_myy_1020_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 30){hist_jj_myy_2030_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 40){hist_jj_myy_3040_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 60){hist_jj_myy_4060_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            if (abs(jet->eta()) < 2.5){
              hist_jj_myy_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);
              if (m_mu < 10){hist_jj_myy_010_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 20){hist_jj_myy_1020_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 30){hist_jj_myy_2030_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 40){hist_jj_myy_3040_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 60){hist_jj_myy_4060_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            }
          } // end of myy bin check    
        } // end of loop over each myy bin
        int N_points_mu = gr_mu_jj_purity_TotErr->GetN();
        for(int i=0; i < N_points_mu; i++){
          gr_mu_jj_purity_TotErr->GetPoint(i, mu_value, mu_purity_value_jj);
          mu_purity_value_yy = gr_mu_gg_purity_TotErr->GetY()[i];
          // std::cout <<  mu_value - gr_mu_jj_purity_TotErr->GetErrorX(i)  << " - " << mu_value + gr_mu_jj_purity_TotErr->GetErrorX(i) << std::endl;
          mu_purity_weight = eventweight * (mu_purity_value_jj/mu_purity_value_yy); //lydia test
          if ((m_mu > mu_value - gr_mu_jj_purity_TotErr->GetErrorX(i)) && (m_mu < mu_value + gr_mu_jj_purity_TotErr->GetErrorX(i))){
            hist_jj_mu_mu_purityweight->Fill(m_mu, mu_purity_weight);
          } // end of mu bin check    
        } // end of loop over each mu bin
      }// end of jj

      else if (y1_tight && !y2_tight && loose2){// && y1_IsIso) {
        y1TLVec.SetPtEtaPhiM(tmp_y1_pt, tmp_y1_eta, tmp_y1_phi, tmp_y1_m);
        y2TLVec.SetPtEtaPhiM(tmp_y2_pt, tmp_y2_eta, tmp_y2_phi, tmp_y2_m);
        yyTLVec = y1TLVec + y2TLVec;    

        // std::cout << "yj" << std::endl;
        int N_points_ptj1 = gr_pT_j1_30_gjjg_purity_TotErr->GetN();
        for(int i=0; i < N_points_ptj1; i++){
          gr_pT_j1_30_gjjg_purity_TotErr->GetPoint(i, pt_value, ptj1_purity_value_yj);
          ptj1_purity_value_yy = gr_pT_j1_30_gg_purity_TotErr->GetY()[i];
          // std::cout <<  pt_value - gr_pT_j1_30_gjjg_purity_TotErr->GetErrorX(i)  << " - " << pt_value + gr_pT_j1_30_gjjg_purity_TotErr->GetErrorX(i) << std::endl;
          ptj1_purity_weight = eventweight * (ptj1_purity_value_yj/ptj1_purity_value_yy); //lydia test 
          if ((jet->pt() * 0.001 > pt_value - gr_pT_j1_30_gjjg_purity_TotErr->GetErrorX(i)) && (jet->pt() * 0.001 < pt_value + gr_pT_j1_30_gjjg_purity_TotErr->GetErrorX(i))){

            hist_yj_pflowj1_pt_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight); 
            hist_yj_pflowj1_eta_purityweight->Fill(jet->eta(), ptj1_purity_weight);

            if (m_mu < 10){hist_yj_pflowj1_pt_010_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 20){hist_yj_pflowj1_pt_1020_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 30){hist_yj_pflowj1_pt_2030_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 40){hist_yj_pflowj1_pt_3040_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 60){hist_yj_pflowj1_pt_4060_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            if (abs(jet->eta()) < 2.5){
            if (m_mu < 10){hist_yj_pflowj1_pt_010_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 20){hist_yj_pflowj1_pt_1020_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 30){hist_yj_pflowj1_pt_2030_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 40){hist_yj_pflowj1_pt_3040_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 60){hist_yj_pflowj1_pt_4060_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
   
            }
          } // end of pt bin check    
        } // end of loop over each ptj1 bin

        int N_points_etaj1 = gr_eta_j1_30_gjjg_purity_TotErr->GetN();
        for(int i=0; i < N_points_etaj1; i++){
          gr_eta_j1_30_gjjg_purity_TotErr->GetPoint(i, eta_value, etaj1_purity_value_yj);
          etaj1_purity_value_yy = gr_eta_j1_30_gg_purity_TotErr->GetY()[i];
          etaj1_purity_weight = eventweight * (etaj1_purity_value_yj/etaj1_purity_value_yy); // = 1; lydia test
          if ((jet->eta() > eta_value - gr_eta_j1_30_gjjg_purity_TotErr->GetErrorX(i)) && (jet->eta() < eta_value + gr_eta_j1_30_gjjg_purity_TotErr->GetErrorX(i))){
            hist_yj_pflowj1_pt_ptj1_purityweight->Fill(jet->eta(), etaj1_purity_weight); 
            hist_yj_pflowj1_eta_purityweight->Fill(jet->eta(), etaj1_purity_weight);
          } // end of eta bin check    
        } // end of loop over each etaj1 bin


        int N_points_myy = gr_m_yy_gjjg_purity_TotErr->GetN();
        for(int i=0; i < N_points_myy; i++){
          gr_m_yy_gjjg_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_yj);
          myy_purity_value_yy = gr_m_yy_gg_purity_TotErr->GetY()[i];
          // std::cout <<  myy_value - gr_m_yy_gjjg_purity_TotErr->GetErrorX(i)  << " - " << myy_value + gr_m_yy_gjjg_purity_TotErr->GetErrorX(i) << std::endl;
          myy_purity_weight = eventweight * (myy_purity_value_yj/myy_purity_value_yy); //lydia test
          if ((yyTLVec.M() * 0.001 > myy_value - gr_m_yy_gjjg_purity_TotErr->GetErrorX(i)) && (yyTLVec.M() * 0.001 < myy_value + gr_m_yy_gjjg_purity_TotErr->GetErrorX(i))){
            hist_yj_myy_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);  

            if (m_mu < 10){hist_yj_myy_010_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 20){hist_yj_myy_1020_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 30){hist_yj_myy_2030_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 40){hist_yj_myy_3040_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 60){hist_yj_myy_4060_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            if (abs(jet->eta()) < 2.5){ 
              hist_yj_myy_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);  
              if (m_mu < 10){hist_yj_myy_010_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 20){hist_yj_myy_1020_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 30){hist_yj_myy_2030_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 40){hist_yj_myy_3040_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 60){hist_yj_myy_4060_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            }
          } // end of myy bin check    
        } // end of loop over each myy bin
        int N_points_mu = gr_mu_gjjg_purity_TotErr->GetN();
        for(int i=0; i < N_points_mu; i++){
          gr_mu_gjjg_purity_TotErr->GetPoint(i, mu_value, mu_purity_value_yj);
          mu_purity_value_yy = gr_mu_gg_purity_TotErr->GetY()[i];
          // std::cout <<  mu_value - gr_mu_gjjg_purity_TotErr->GetErrorX(i)  << " - " << mu_value + gr_mu_gjjg_purity_TotErr->GetErrorX(i) << std::endl;
          mu_purity_weight = eventweight * (mu_purity_value_yj / mu_purity_value_yy); //lydia test 
          if ((m_mu > mu_value - gr_mu_gjjg_purity_TotErr->GetErrorX(i)) && (m_mu < mu_value + gr_mu_gjjg_purity_TotErr->GetErrorX(i))){
            hist_yj_mu_mu_purityweight->Fill(m_mu, mu_purity_weight);  
          } // end of mu bin check    
        } // end of loop over each mu bin
      }//end of yj

      else if (!y1_tight && y2_tight && loose1){// && y2_IsIso){
        y1TLVec.SetPtEtaPhiM(tmp_y1_pt, tmp_y1_eta, tmp_y1_phi, tmp_y1_m);
        y2TLVec.SetPtEtaPhiM(tmp_y2_pt, tmp_y2_eta, tmp_y2_phi, tmp_y2_m);
        yyTLVec = y1TLVec + y2TLVec;
        // std::cout << "jy" << std::endl;
        int N_points_ptj1 = gr_pT_j1_30_gjjg_purity_TotErr->GetN();
        for(int i=0; i < N_points_ptj1; i++){
          gr_pT_j1_30_gjjg_purity_TotErr->GetPoint(i, pt_value, ptj1_purity_value_yj);
          ptj1_purity_value_yy = gr_pT_j1_30_gg_purity_TotErr->GetY()[i];
          // std::cout <<  pt_value - gr_pT_j1_30_gjjg_purity_TotErr->GetErrorX(i)  << " - " << pt_value + gr_pT_j1_30_gjjg_purity_TotErr->GetErrorX(i) << std::endl;
          ptj1_purity_weight = eventweight * (ptj1_purity_value_yj/ptj1_purity_value_yy);//lydia test
          if ((jet->pt() * 0.001 > pt_value - gr_pT_j1_30_gjjg_purity_TotErr->GetErrorX(i)) && (jet->pt() * 0.001 < pt_value + gr_pT_j1_30_gjjg_purity_TotErr->GetErrorX(i))){

            hist_jy_pflowj1_pt_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight); 
            hist_jy_pflowj1_eta_purityweight->Fill(jet->eta(), ptj1_purity_weight);

            if (m_mu < 10){hist_jy_pflowj1_pt_010_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 20){hist_jy_pflowj1_pt_1020_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 30){hist_jy_pflowj1_pt_2030_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 40){hist_jy_pflowj1_pt_3040_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            else if (m_mu < 60){hist_jy_pflowj1_pt_4060_ptj1_purityweight->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            if (abs(jet->eta()) < 2.5){
              if (m_mu < 10){hist_jy_pflowj1_pt_010_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
              else if (m_mu < 20){hist_jy_pflowj1_pt_1020_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
              else if (m_mu < 30){hist_jy_pflowj1_pt_2030_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
              else if (m_mu < 40){hist_jy_pflowj1_pt_3040_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
              else if (m_mu < 60){hist_jy_pflowj1_pt_4060_ptj1_purityweight_central->Fill(jet->pt() * 0.001, ptj1_purity_weight);}
            }
          } // end of pt bin check    
        } // end of loop over each ptj1 bin

        int N_points_etaj1 = gr_eta_j1_30_gjjg_purity_TotErr->GetN();
        for(int i=0; i < N_points_etaj1; i++){
          gr_eta_j1_30_gjjg_purity_TotErr->GetPoint(i, eta_value, etaj1_purity_value_jy);
          etaj1_purity_value_yy = gr_eta_j1_30_gg_purity_TotErr->GetY()[i];
          etaj1_purity_weight = eventweight * (etaj1_purity_value_jy/etaj1_purity_value_yy); // = 1; lydia test
          if ((jet->eta() > eta_value - gr_eta_j1_30_gjjg_purity_TotErr->GetErrorX(i)) && (jet->eta() < eta_value + gr_eta_j1_30_gjjg_purity_TotErr->GetErrorX(i))){
            hist_jy_pflowj1_pt_ptj1_purityweight->Fill(jet->eta(), etaj1_purity_weight); 
            hist_jy_pflowj1_eta_purityweight->Fill(jet->eta(), etaj1_purity_weight);
          } // end of eta bin check    
        } // end of loop over each etaj1 bin

        int N_points_myy = gr_m_yy_gjjg_purity_TotErr->GetN();
        for(int i=0; i < N_points_myy; i++){
          gr_m_yy_gjjg_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_yj);
          myy_purity_value_yy = gr_m_yy_gg_purity_TotErr->GetY()[i];
          // std::cout <<  myy_value - gr_m_yy_gjjg_purity_TotErr->GetErrorX(i)  << " - " << myy_value + gr_m_yy_gjjg_purity_TotErr->GetErrorX(i) << std::endl;
          myy_purity_weight = eventweight * (myy_purity_value_yj/myy_purity_value_yy); //lydia test
          if ((yyTLVec.M() * 0.001 > myy_value - gr_m_yy_gjjg_purity_TotErr->GetErrorX(i)) && (yyTLVec.M() * 0.001 < myy_value + gr_m_yy_gjjg_purity_TotErr->GetErrorX(i))){
            hist_jy_myy_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);

            if (m_mu < 10){hist_jy_myy_010_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 20){hist_jy_myy_1020_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 30){hist_jy_myy_2030_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 40){hist_jy_myy_3040_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            else if (m_mu < 60){hist_jy_myy_4060_myy_purityweight->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            if (abs(jet->eta()) < 2.5){
              hist_jy_myy_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);
              if (m_mu < 10){hist_jy_myy_010_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 20){hist_jy_myy_1020_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 30){hist_jy_myy_2030_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 40){hist_jy_myy_3040_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
              else if (m_mu < 60){hist_jy_myy_4060_myy_purityweight_central->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
            }
          } // end of myy bin check    
        } // end of loop over each myy bin
        int N_points_mu = gr_mu_gjjg_purity_TotErr->GetN();
        for(int i=0; i < N_points_mu; i++){
          gr_mu_gjjg_purity_TotErr->GetPoint(i, mu_value, mu_purity_value_yj);
          mu_purity_value_yy = gr_mu_gg_purity_TotErr->GetY()[i];
          // std::cout <<  mu_value - gr_mu_gjjg_purity_TotErr->GetErrorX(i)  << " - " << mu_value + gr_mu_gjjg_purity_TotErr->GetErrorX(i) << std::endl;
          mu_purity_weight = eventweight * (mu_purity_value_yj/mu_purity_value_yy); //lydia test
          if ((m_mu > mu_value - gr_mu_gjjg_purity_TotErr->GetErrorX(i)) && (m_mu < mu_value + gr_mu_gjjg_purity_TotErr->GetErrorX(i))){
            hist_jy_mu_mu_purityweight->Fill(m_mu, mu_purity_weight);
          } // end of mu bin check    
        } // end of loop over each mu bin
      }//end of jy
    }// end of isolation requirement
  }// end of passed flagg


  if (npflow30jetsperevent > 0){
      // 
      //  npflowjetsperevent > 0 to make sure we have one jet
      //  shouldn't matter if >1, leading values stay the same
      //
    // if (( leadingpflow30jetpt > 120 ) && ( leadingpflow30jetpt < 130 )) {}
    // else{
    // std::cout << "leadingpflow30jetpt in other loop: " << leadingpflow30jetpt << std::endl;

    if (abs(leadingpflow30jeteta) < 2.5){
      hist_j130_pt_central->Fill(leadingpflow30jetpt);
      hist_j130_eta_central->Fill(leadingpflow30jeteta);
          if (m_mu < 10){hist_myy_010_central->Fill(m_yy, eventweight);hist_j130_pt_010_central->Fill(leadingpflow30jetpt, eventweight);}
          else if (m_mu < 20){hist_myy_1020_central->Fill(m_yy, eventweight);hist_j130_pt_1020_central->Fill(leadingpflow30jetpt, eventweight);}
          else if (m_mu < 30){hist_myy_2030_central->Fill(m_yy, eventweight);hist_j130_pt_2030_central->Fill(leadingpflow30jetpt, eventweight);}
          else if (m_mu < 40){hist_myy_3040_central->Fill(m_yy, eventweight);hist_j130_pt_3040_central->Fill(leadingpflow30jetpt, eventweight);}
          else if (m_mu < 60){hist_myy_4060_central->Fill(m_yy, eventweight);hist_j130_pt_4060_central->Fill(leadingpflow30jetpt, eventweight);}

    }
        hist_j130_pt->Fill(leadingpflow30jetpt);
        hist_j130_eta->Fill(leadingpflow30jeteta);

        int N_points_mc_mu = gr_mu_gg_purity_TotErr->GetN();
        for(int i=0; i < N_points_mc_mu; i++){
          gr_mu_gg_purity_TotErr->GetPoint(i, mu_value, mu_purity_value_mc);
          // std::cout <<  mu_value - gr_mu_gg_purity_TotErr->GetErrorX(i)  << " - " << mu_value + gr_mu_gg_purity_TotErr->GetErrorX(i) << std::endl;
          mu_purity_weight_mc = eventweight * (mu_purity_value_mc);//mu_purity_value_mc); //lydia test
          if ((m_mu > mu_value - gr_mu_gg_purity_TotErr->GetErrorX(i)) && (m_mu < mu_value + gr_mu_gg_purity_TotErr->GetErrorX(i))){
            hist_mc_mu_mu_purityweight->Fill(m_mu, mu_purity_weight_mc);

          } // end of mu bin check    
        } // end of loop over each mu bin
        int N_points_mc_myy = gr_m_yy_gg_purity_TotErr->GetN();
        for(int i=0; i < N_points_mc_myy; i++){
          gr_m_yy_gg_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_mc);
          // std::cout <<  myy_value - gr_m_yy_gg_purity_TotErr->GetErrorX(i)  << " - " << myy_value + gr_m_yy_gg_purity_TotErr->GetErrorX(i) << std::endl;
          myy_purity_weight_mc = eventweight * (myy_purity_value_mc);//myy_purity_value_mc); //lydia test
          if ((m_yy > myy_value - gr_m_yy_gg_purity_TotErr->GetErrorX(i)) && (m_yy < myy_value + gr_m_yy_gg_purity_TotErr->GetErrorX(i))){
            
            hist_mc_myy_myy_purityweight->Fill(m_yy, myy_purity_weight_mc);
            if (m_mu < 10){hist_mc_myy_010_myy_purityweight->Fill(m_yy, myy_purity_weight_mc);}
            else if (m_mu < 20){hist_mc_myy_1020_myy_purityweight->Fill(m_yy, myy_purity_weight_mc);}
            else if (m_mu < 30){hist_mc_myy_2030_myy_purityweight->Fill(m_yy, myy_purity_weight_mc);}
            else if (m_mu < 40){hist_mc_myy_3040_myy_purityweight->Fill(m_yy, myy_purity_weight_mc);}
            else if (m_mu < 60){hist_mc_myy_4060_myy_purityweight->Fill(m_yy, myy_purity_weight_mc);}

          } // end of myy bin check    
        } // end of loop over each myy bin
        int N_points_mc_ptj1 = gr_pT_j1_30_gg_purity_TotErr->GetN();
        for(int i=0; i < N_points_mc_ptj1; i++){
          gr_pT_j1_30_gg_purity_TotErr->GetPoint(i, pt_value, ptj1_purity_value_mc);
          // std::cout <<  pt_value - gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i)  << " - " << pt_value + gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i) << std::endl;
          ptj1_purity_weight_mc = eventweight * (ptj1_purity_value_mc);//myy_purity_value_yy); //lydia test
          if ((leadingpflow30jetpt > pt_value - gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i)) && (leadingpflow30jetpt < pt_value + gr_pT_j1_30_gg_purity_TotErr->GetErrorX(i))){
            
            hist_mc_pt_ptj1_purityweight->Fill(leadingpflow30jetpt, ptj1_purity_weight_mc);
            if (m_mu < 10){hist_mc_pt_010_ptj1_purityweight->Fill(leadingpflow30jetpt, ptj1_purity_weight_mc);}
            else if (m_mu < 20){hist_mc_pt_1020_ptj1_purityweight->Fill(leadingpflow30jetpt, ptj1_purity_weight_mc);}
            else if (m_mu < 30){hist_mc_pt_2030_ptj1_purityweight->Fill(leadingpflow30jetpt, ptj1_purity_weight_mc);}
            else if (m_mu < 40){hist_mc_pt_3040_ptj1_purityweight->Fill(leadingpflow30jetpt, ptj1_purity_weight_mc);}
            else if (m_mu < 60){hist_mc_pt_4060_ptj1_purityweight->Fill(leadingpflow30jetpt, ptj1_purity_weight_mc);}


          } // end of pt bin check    
        } //end of loop over each pt bin

        if (m_mu < 15){
          pflow_j130_pt_15 = (leadingpflow30jetpt);
          hist_j130_pt_015->Fill(leadingpflow30jetpt, eventweight);
          myy_15 = m_yy;
          hist_myy_015->Fill(m_yy, eventweight);
          // pflow_j130_pt_15_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j130_y_15 = (leadingpflow30jety);
          hist_j130_y_015->Fill(leadingpflow30jety, eventweight);
          
          // pflow_j130_y_15_nofJVT = (leadingpflowjety_nofJVT);
        }
        else if (m_mu < 25){
          pflow_j130_pt_1525 = (leadingpflow30jetpt);
          hist_j130_pt_1525->Fill(leadingpflow30jetpt, eventweight);
          myy_1525 = m_yy;
          hist_myy_1525->Fill(m_yy, eventweight);
          // pflow_j130_pt_1525_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j130_y_1525 = (leadingpflow30jety);
          hist_j130_y_1525->Fill(leadingpflow30jety, eventweight);
        }
        else if (m_mu < 35){
          pflow_j130_pt_2535 = (leadingpflow30jetpt);
          hist_j130_pt_2535->Fill(leadingpflow30jetpt, eventweight);
          myy_2535 = m_yy;
          hist_myy_2535->Fill(m_yy, eventweight);
          // pflow_j130_pt_2535_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j130_y_2535 = (leadingpflow30jety);
          hist_j130_y_2535->Fill(leadingpflow30jety, eventweight);
        }
        else if (m_mu < 50){
          pflow_j130_pt_3550 = (leadingpflow30jetpt);
          hist_j130_pt_3550->Fill(leadingpflow30jetpt, eventweight);
          myy_3550 = m_yy;
          hist_myy_3550->Fill(m_yy, eventweight);
          // pflow_j130_pt_3550_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j130_y_3550 = (leadingpflow30jety);
          hist_j130_y_3550->Fill(leadingpflow30jety, eventweight);
        }
        else if (m_mu > 50){
          pflow_j130_pt_50 = (leadingpflow30jetpt);
          hist_j130_pt_50->Fill(leadingpflow30jetpt, eventweight);
          myy_50 = m_yy;
          hist_myy_50->Fill(m_yy, eventweight);
          // pflow_j130_pt_50_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j130_y_50 = (leadingpflow30jety);
          hist_j130_y_50->Fill(leadingpflow30jety, eventweight);
        }

    hist_mu->Fill(m_mu, eventweight);
    if (m_mu < 10){myy_10 = m_yy; hist_myy_010->Fill(m_yy, eventweight);hist_j130_pt_010->Fill(leadingpflow30jetpt, eventweight);pflow_j130_pt_10 = leadingpflow30jetpt;}
    else if (m_mu < 20){myy_1020 = m_yy; hist_myy_1020->Fill(m_yy, eventweight);hist_j130_pt_1020->Fill(leadingpflow30jetpt, eventweight);pflow_j130_pt_1020 = leadingpflow30jetpt;}
    else if (m_mu < 30){myy_2030 = m_yy; hist_myy_2030->Fill(m_yy, eventweight);hist_j130_pt_2030->Fill(leadingpflow30jetpt, eventweight);pflow_j130_pt_2030 = leadingpflow30jetpt;}
    else if (m_mu < 40){myy_3040 = m_yy; hist_myy_3040->Fill(m_yy, eventweight);hist_j130_pt_3040->Fill(leadingpflow30jetpt, eventweight);pflow_j130_pt_3040 = leadingpflow30jetpt;}
    else if (m_mu < 60){myy_4060 = m_yy; hist_myy_4060->Fill(m_yy, eventweight);hist_j130_pt_4060->Fill(leadingpflow30jetpt, eventweight);pflow_j130_pt_4060 = leadingpflow30jetpt;}
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
        }
        else if (m_mu < 25){
          pflow_j150_pt_1525 = (leadingpflow50jetpt);
          hist_j150_pt_1525->Fill(leadingpflow50jetpt, eventweight);
          // pflow_j150_pt_1525_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j150_y_1525 = (leadingpflow50jety);
          hist_j150_y_1525->Fill(leadingpflow50jety, eventweight);
          // pflow_j150_y_1525_nofJVT = (leadingpflowjety_nofJVT);
        }
        else if (m_mu < 35){
          pflow_j150_pt_2535 = (leadingpflow50jetpt);
          hist_j150_pt_2535->Fill(leadingpflow50jetpt, eventweight);
          // pflow_j150_pt_2535_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j150_y_2535 = (leadingpflow50jety);
          hist_j150_y_2535->Fill(leadingpflow50jety, eventweight);
          // pflow_j150_y_2535_nofJVT = (leadingpflowjety_nofJVT);
        }
        else if (m_mu < 50){
          pflow_j150_pt_3550 = (leadingpflow50jetpt);
          hist_j150_pt_3550->Fill(leadingpflow50jetpt, eventweight);
          // pflow_j150_pt_3550_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j150_y_3550 = (leadingpflow50jety);
          hist_j150_y_3550->Fill(leadingpflow50jety, eventweight);
          // pflow_j150_y_3550_nofJVT = (leadingpflowjety_nofJVT);
        }
        else if (m_mu > 50){
          pflow_j150_pt_50 = (leadingpflow50jetpt);
          hist_j150_pt_50->Fill(leadingpflow50jetpt, eventweight);
          // pflow_j150_pt_50_nofJVT = (leadingpflowjetpt_nofJVT);
          pflow_j150_y_50 = (leadingpflow50jety);
          hist_j150_y_50->Fill(leadingpflow50jety, eventweight);
          // pflow_j150_y_50_nofJVT = (leadingpflowjety_nofJVT);
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
      }
      else if (m_mu < 25){
        pflow_j130_pt_1525_fJVT = (leadingpflow30jetpt_fJVT);
        hist_j130_pt_1525_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
        // pflow_j130_pt_1525_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_1525_fJVT = (leadingpflow30jety_fJVT);
        hist_j130_y_1525_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
        // pflow_j130_y_1525_nofJVT = (leadingpflowjety_nofJVT);
      }
      else if (m_mu < 35){
        pflow_j130_pt_2535_fJVT = (leadingpflow30jetpt_fJVT);
        hist_j130_pt_2535_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
        // pflow_j130_pt_2535_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_2535_fJVT = (leadingpflow30jety_fJVT);
        hist_j130_y_2535_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
        // pflow_j130_y_2535_nofJVT = (leadingpflowjety_nofJVT);
      }
      else if (m_mu < 50){
        pflow_j130_pt_3550_fJVT = (leadingpflow30jetpt_fJVT);
        hist_j130_pt_3550_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
        // pflow_j130_pt_3550_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_3550_fJVT = (leadingpflow30jety_fJVT);
        hist_j130_y_3550_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
        // pflow_j130_y_3550_nofJVT = (leadingpflowjety_nofJVT);
      }
      else if (m_mu > 50){
        pflow_j130_pt_50_fJVT = (leadingpflow30jetpt_fJVT);
        hist_j130_pt_50_fJVT->Fill(leadingpflow30jetpt_fJVT, eventweight);
        // pflow_j130_pt_50_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j130_y_50_fJVT = (leadingpflow30jety_fJVT);
        hist_j130_y_50_fJVT->Fill(leadingpflow30jety_fJVT, eventweight);
        // pflow_j130_y_50_nofJVT = (leadingpflowjety_nofJVT);
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
      }
      else if (m_mu < 25){
        pflow_j150_pt_1525_fJVT = (leadingpflow50jetpt_fJVT);
        hist_j150_pt_1525_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
        // pflow_j150_pt_1525_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_1525_fJVT = (leadingpflow50jety_fJVT);
        hist_j150_y_1525_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
        // pflow_j150_y_1525_nofJVT = (leadingpflowjety_nofJVT);
      }
      else if (m_mu < 35){
        pflow_j150_pt_2535_fJVT = (leadingpflow50jetpt_fJVT);
        hist_j150_pt_2535_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
        // pflow_j150_pt_2535_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_2535_fJVT = (leadingpflow50jety_fJVT);
        hist_j150_y_2535_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
        // pflow_j150_y_2535_nofJVT = (leadingpflowjety_nofJVT);
      }
      else if (m_mu < 50){
        pflow_j150_pt_3550_fJVT = (leadingpflow50jetpt_fJVT);
        hist_j150_pt_3550_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
        // pflow_j150_pt_3550_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_3550_fJVT = (leadingpflow50jety_fJVT);
        hist_j150_y_3550_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
      }
      else if (m_mu > 50){
        pflow_j150_pt_50_fJVT = (leadingpflow50jetpt_fJVT);
        hist_j150_pt_50_fJVT->Fill(leadingpflow50jetpt_fJVT, eventweight);
        // pflow_j150_pt_50_nofJVT = (leadingpflowjetpt_nofJVT);
        pflow_j150_y_50_fJVT = (leadingpflow50jety_fJVT);
        hist_j150_y_50_fJVT->Fill(leadingpflow50jety_fJVT, eventweight);
        // pflow_j150_y_50_nofJVT = (leadingpflowjety_nofJVT);
      }
    // }
    }
  }
} // end of jet requirement



if (passed){ //no jet requirement
  if (y1_IsIso && y2_IsIso){
    y1TLVec.SetPtEtaPhiM(tmp_y1_pt, tmp_y1_eta, tmp_y1_phi, tmp_y1_m);
    y2TLVec.SetPtEtaPhiM(tmp_y2_pt, tmp_y2_eta, tmp_y2_phi, tmp_y2_m);
    yyTLVec = y1TLVec + y2TLVec;
    if (y1_tight && y2_tight){ 
            hist_yy_myy_inclusive->Fill(yyTLVec.M() * 0.001);
            if (m_mu < 10){hist_yy_myy_010_inclusive->Fill((yyTLVec.M() * 0.001));}
            else if (m_mu < 20){hist_yy_myy_1020_inclusive->Fill((yyTLVec.M() * 0.001));}
            else if (m_mu < 30){hist_yy_myy_2030_inclusive->Fill((yyTLVec.M() * 0.001));}
            else if (m_mu < 40){hist_yy_myy_3040_inclusive->Fill((yyTLVec.M() * 0.001));}
            else if (m_mu < 60){hist_yy_myy_4060_inclusive->Fill((yyTLVec.M() * 0.001));}
    }// end of yy
    else if (!y1_tight && !y2_tight && loose1 && loose2){
          hist_jj_myy_inclusive->Fill(yyTLVec.M() * 0.001);
          if (m_mu < 10){hist_jj_myy_010_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 20){hist_jj_myy_1020_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 30){hist_jj_myy_2030_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 40){hist_jj_myy_3040_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 60){hist_jj_myy_4060_inclusive->Fill(yyTLVec.M() * 0.001);}
  }// end of jj
    else if (y1_tight && !y2_tight && loose2) {
          hist_yj_myy_inclusive->Fill(yyTLVec.M() * 0.001);
          if (m_mu < 10){hist_yj_myy_010_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 20){hist_yj_myy_1020_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 30){hist_yj_myy_2030_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 40){hist_yj_myy_3040_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 60){hist_yj_myy_4060_inclusive->Fill(yyTLVec.M() * 0.001);}
  }//end of yj
    else if (!y1_tight && y2_tight && loose1){
          hist_jy_myy_inclusive->Fill(yyTLVec.M() * 0.001);
          if (m_mu < 10){hist_jy_myy_010_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 20){hist_jy_myy_1020_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 30){hist_jy_myy_2030_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 40){hist_jy_myy_3040_inclusive->Fill(yyTLVec.M() * 0.001);}
          else if (m_mu < 60){hist_jy_myy_4060_inclusive->Fill(yyTLVec.M() * 0.001);}
  }//end of jy

    if (y1_tight && y2_tight){ 
      int N_points_myy = gr_m_yy_gg_purity_TotErr->GetN();
      for(int i=0; i < N_points_myy; i++){
        gr_m_yy_gg_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_yy);
        myy_purity_value_yy = gr_m_yy_gg_purity_TotErr->GetY()[i];
        // std::cout <<  myy_value - gr_m_yy_gg_purity_TotErr->GetErrorX(i)  << " - " << myy_value + gr_m_yy_gg_purity_TotErr->GetErrorX(i) << std::endl;
        myy_purity_weight = eventweight * (myy_purity_value_yy); // /myy_purity_value_yy); //lydia test
        if ((yyTLVec.M() * 0.001 > myy_value - gr_m_yy_gg_purity_TotErr->GetErrorX(i)) && (yyTLVec.M() * 0.001 < myy_value + gr_m_yy_gg_purity_TotErr->GetErrorX(i))){
          hist_yy_myy_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);
          if (m_mu < 10){hist_yy_myy_010_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 20){hist_yy_myy_1020_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 30){hist_yy_myy_2030_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 40){hist_yy_myy_3040_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 60){hist_yy_myy_4060_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
        } // end of pt bin check    
      } // end of loop over each myy bin
    }// end of yy
    else if (!y1_tight && !y2_tight && loose1 && loose2){
      int N_points_myy = gr_m_yy_jj_purity_TotErr->GetN();
      for(int i=0; i < N_points_myy; i++){
        gr_m_yy_jj_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_jj);
        myy_purity_value_yy = gr_m_yy_gg_purity_TotErr->GetY()[i];
        // std::cout <<  myy_value - gr_m_yy_jj_purity_TotErr->GetErrorX(i)  << " - " << myy_value + gr_m_yy_jj_purity_TotErr->GetErrorX(i) << std::endl;
        myy_purity_weight = eventweight * (myy_purity_value_jj /myy_purity_value_yy); //lydia test
        if ((yyTLVec.M() * 0.001 > myy_value - gr_m_yy_jj_purity_TotErr->GetErrorX(i)) && (yyTLVec.M() * 0.001 < myy_value + gr_m_yy_jj_purity_TotErr->GetErrorX(i))){
          hist_jj_myy_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);
          if (m_mu < 10){hist_jj_myy_010_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 20){hist_jj_myy_1020_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 30){hist_jj_myy_2030_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 40){hist_jj_myy_3040_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 60){hist_jj_myy_4060_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
      } // end of pt bin check    
    } // end of loop over each myy bin
  }// end of jj

    else if (y1_tight && !y2_tight && loose2) {
      int N_points_myy = gr_m_yy_gjjg_purity_TotErr->GetN();
      for(int i=0; i < N_points_myy; i++){
        gr_m_yy_gjjg_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_yj);
        myy_purity_value_yy = gr_m_yy_gg_purity_TotErr->GetY()[i];
        // std::cout <<  myy_value - gr_m_yy_gjjg_purity_TotErr->GetErrorX(i)  << " - " << myy_value + gr_m_yy_gjjg_purity_TotErr->GetErrorX(i) << std::endl;
        myy_purity_weight = eventweight * (myy_purity_value_yj/myy_purity_value_yy); //lydia test
        if ((yyTLVec.M() * 0.001 > myy_value - gr_m_yy_gjjg_purity_TotErr->GetErrorX(i)) && (yyTLVec.M() * 0.001 < myy_value + gr_m_yy_gjjg_purity_TotErr->GetErrorX(i))){
          hist_yj_myy_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);  
          if (m_mu < 10){hist_yj_myy_010_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 20){hist_yj_myy_1020_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 30){hist_yj_myy_2030_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 40){hist_yj_myy_3040_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 60){hist_yj_myy_4060_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
        } // end of pt bin check    
    } // end of loop over each myy bin
  }//end of yj

    else if (!y1_tight && y2_tight && loose1){
      int N_points_myy = gr_m_yy_gjjg_purity_TotErr->GetN();
      for(int i=0; i < N_points_myy; i++){
        gr_m_yy_gjjg_purity_TotErr->GetPoint(i, myy_value, myy_purity_value_yj);
        myy_purity_value_yy = gr_m_yy_gg_purity_TotErr->GetY()[i];
        myy_purity_weight = eventweight * (myy_purity_value_yj/myy_purity_value_yy); //lydia test
        if ((yyTLVec.M() * 0.001 > myy_value - gr_m_yy_gjjg_purity_TotErr->GetErrorX(i)) && (yyTLVec.M() * 0.001 < myy_value + gr_m_yy_gjjg_purity_TotErr->GetErrorX(i))){
          hist_jy_myy_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);
          if (m_mu < 10){hist_jy_myy_010_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 20){hist_jy_myy_1020_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 30){hist_jy_myy_2030_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 40){hist_jy_myy_3040_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
          else if (m_mu < 60){hist_jy_myy_4060_myy_purityweight_inclusive->Fill(yyTLVec.M() * 0.001, myy_purity_weight);}
        } // end of pt bin check    
      } // end of loop over each myy bin
    }//end of jy
  }// end of isolation requirement
}// end of passed flagg
tree->Fill();

  return EL::StatusCode::SUCCESS;

}



EL::StatusCode HGamPhotonAnalysis :: postExecute ()
{

  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamPhotonAnalysis :: finalize ()
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


void HGamPhotonAnalysis::ResetVariables()
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

  pflow_j130_pt_15 = 0;
  pflow_j130_pt_1525 = 0;
  pflow_j130_pt_2535 = 0;
  pflow_j130_pt_3550 = 0;
  pflow_j130_pt_50 = 0;

  pflow_j130_pt_10 = 0;
  pflow_j130_pt_1020 = 0;
  pflow_j130_pt_2030 = 0;
  pflow_j130_pt_3040 = 0;
  pflow_j130_pt_4060 = 0;

  myy_10 = 0;
  myy_1020 = 0;
  myy_2030 = 0;
  myy_3040 = 0;
  myy_4060 = 0;

  myy_15 = 0;
  myy_1525 = 0;
  myy_2535 = 0;
  myy_3550 = 0;
  myy_50 = 0;

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

  hgam_yy_pflowj1_pt = -999.9;
  hgam_jj_pflowj1_pt = -999.9;
  hgam_yj_pflowj1_pt = -999.9;
  hgam_jy_pflowj1_pt = -999.9;
    
  hgam_yy_pflowj1_eta = -999.9;
  hgam_jj_pflowj1_eta = -999.9;
  hgam_yj_pflowj1_eta = -999.9;
  hgam_jy_pflowj1_eta = -999.9;

  hgam_yy_y1_eta = -999.9;
  hgam_yy_y1_pt = -999.9;
  hgam_yy_y2_eta = -999.9;
  hgam_yy_y2_pt = -999.9;
  hgam_yy_pt = -999.9;
  hgam_yy_eta = -999.9;
  hgam_yy_m = -999.9;

  hgam_jj_j1_pt = -999.9;
  hgam_jj_j1_eta = -999.9;
  hgam_jj_j2_pt = -999.9;
  hgam_jj_j2_eta = -999.9;

  hgam_yj_j_pt = -999.9;
  hgam_yj_y_pt = -999.9;
  hgam_yj_j_eta = -999.9;
  hgam_yj_y_eta = -999.9;

  hgam_jj_j1_pt = -999.9;
  hgam_jj_j2_pt = -999.9;
  hgam_jj_j1_eta = -999.9;
  hgam_jj_j2_eta = -999.9;
    
  tmp_y1_m = 0.;
  tmp_y1_phi = -999.9;
  tmp_y1_eta = -999.9;
  tmp_y1_pt = -999.9;

  tmp_y2_m = 0.;
  tmp_y2_phi = -999.9;
  tmp_y2_eta = -999.9;
  tmp_y2_pt = -999.9;

}


EL::StatusCode HGamPhotonAnalysis :: histFinalize ()
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





