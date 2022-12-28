#include <AsgTools/MessageCheck.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <FTKxAODAnalysis/FTKxAODAnalysis.h>
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/Message.h"
#include <typeinfo>


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
ClassImp(FTKxAODAnalysis)

const xAOD::TruthParticle* get_truth(const xAOD::TrackParticle *track)
{
  typedef ElementLink< xAOD::TruthParticleContainer > Link_t;
  static const char* NAME = "truthParticleLink";
  if( ! track->isAvailable< Link_t >( NAME ) ) {
    return NULL;
  }
  const Link_t& link = track->auxdata< Link_t >( NAME );
  if( ! link.isValid() ) {
    return NULL;
  }
  return *link;
}

std::pair<const xAOD::TrackParticle*, int> best_match(const xAOD::TruthParticle* truth, const xAOD::TrackParticleContainer* tracks)
{
  // std::cerr << "BRI best_match TEST 1" << std::endl;

  // Find track that best matches a truth particle
  // Return the best matching track (if any) and index of this track in the
  // container
  int itrack = -1, best_itrack = -1;
  float best_truth_prob = 0., truth_prob;
  const xAOD::TrackParticle* best_track = NULL;
  const xAOD::TruthParticle* matched_truth;
  for (const auto track : *tracks) {
    ++itrack;
    matched_truth = get_truth(track);
    if (!matched_truth or matched_truth->barcode() != truth->barcode()) {
      continue;
    }
    truth_prob = track->auxdata<float>("truthMatchProbability");
    if (truth_prob > best_truth_prob) {
      best_truth_prob = truth_prob;
      best_track = track;
      best_itrack = itrack;
    }
       // std::cerr << "best match: " << best_itrack << std::endl;
  }
  return std::pair<const xAOD::TrackParticle*, int>(best_track, best_itrack);
}


bool FTKxAODAnalysis::isAcceptedTruth(const xAOD::TruthParticle* tp)
{
  // Check to see if it's a stable particle
  if (tp->status() != 1)
    return false;
  // Clearly for tracking we don't care about Neutrals
  if (tp->isNeutral())
    return false;
  // Barcode of zero indicates there was no truth particle found for this track
  // if (tp->barcode() == 0 or tp->barcode() >= 200e3)
  if (tp->barcode() >= 200e3)
    return false;
  // Check the particle is within acceptance)
  // if (tp->pt() < 1000 || fabs(tp->eta()) > 2.4)
  if (tp->pt() < 1000 || fabs(tp->eta()) > 2.5)//tomoya
    return false;
  // Make sure particle decays before the last pixel layer
  if (!tp->hasProdVtx() or tp->prodVtx()->perp() > 110)
    return false;
  // muon (tomoya)
  // if (fabs(tp->pdgId()) != 13)
  //   return false;
  return true;
}

// tomoya check track quality
bool FTKxAODAnalysis::isAcceptedReco(const xAOD::TrackParticle* recp)
{
  // Recommendation from TrackingCP group for Moriond 2016.
  // Check the track leaves enough hits inside ID.

  // standard track selection
  // pt cut
  if (recp->pt() / 1000. < 1)
    return false;
  // Eta cut
  if (fabs(recp->eta()) > 2.5)
    return false;
  // Number of Si Hits
  if (recp->auxdata<unsigned char>("numberOfPixelHits") + recp->auxdata<unsigned char>("numberOfPixelDeadSensors") + recp->auxdata<unsigned char>("numberOfSCTHits") + recp->auxdata<unsigned char>("numberOfSCTDeadSensors") < 7)
    return false;
  // Maximum of Shared module
  if (recp->auxdata<unsigned char>("numberOfPixelSharedHits") + recp->auxdata<unsigned char>("numberOfSCTSharedHits") / 2 > 1)
    return false;
  // Number of Si Holes
  if (recp->auxdata<unsigned char>("numberOfPixelHoles") + recp->auxdata<unsigned char>("numberOfSCTHoles") > 2)
    return false;
  // Maximum of Pixel Holes
  if (recp->auxdata<unsigned char>("numberOfPixelHoles") > 1)
    return false;
// Slice A:
  if (isData == true){
    if (recp->eta() > 0.1)
      return false;
    if (recp->eta() < -1.6)
      return false;
    if (recp->phi() < 1.5)
      return false;
    if (recp->phi() > 2.1)
      return false;
  }

  // // Slice 2:
  // if (isData == true){
  //   if (recp->eta() > 1.6)
  //     return false;
  //   if (recp->eta() < -0.1)
  //     return false;
  //   if (recp->phi() < 2.9)
  //     return false;
  //   if (recp->phi() > 2.3)
  //     return false;
  // }

  return true;
}

// tomoya check track quality
bool FTKxAODAnalysis::isAcceptedReco_FTKTDR(const xAOD::TrackParticle* recp)
{
  // Recommendation used for FTKTDR study.
  // Check the track leaves enough hits inside ID.

  // standard track selection
  // pt cut
  if (recp->pt() / 1000. < 1)
    return false;
  // Eta cut
  if (fabs(recp->eta()) > 2.5)
    return false;
  // Number of Si Hits
  if (recp->auxdata<unsigned char>("numberOfPixelHits") + recp->auxdata<unsigned char>("numberOfPixelDeadSensors") + recp->auxdata<unsigned char>("numberOfSCTHits") + recp->auxdata<unsigned char>("numberOfSCTDeadSensors") < 9)
    return false;
  // Maximum of Shared module
  // if (recp->auxdata<unsigned char>("numberOfPixelSharedHits") + recp->auxdata<unsigned char>("numberOfSCTSharedHits") / 2 > 1)
  //   return false;
  // Number of Si Holes
  // if (recp->auxdata<unsigned char>("numberOfPixelHoles") + recp->auxdata<unsigned char>("numberOfSCTHoles") > 2)
  //   return false;
  // Maximum of Pixel Holes
  if (recp->auxdata<unsigned char>("numberOfPixelHoles") > 0)
    return false;

  return true;
}

// tomoya check track quality
bool FTKxAODAnalysis::isAcceptedReco_muon(const xAOD::TrackParticle* recp)
{
  // Recommendation for muon tracks from TrackingCP group for Moriond 2016.
  // Check the track leaves enough hits inside ID.

  // Muon tracks
  // Pixel Hits
  if (recp->auxdata<unsigned char>("numberOfPixelHits") < 1)
    return false;
  // SCT Hits
  if (recp->auxdata<unsigned char>("numberOfSCTHits") < 5)
    return false;
  // Number of Si Holes
  if (recp->auxdata<unsigned char>("numberOfPixelHoles") + recp->auxdata<unsigned char>("numberOfSCTHoles") > 2)
    return false;
  // TRT Hits
  if (0.1 <= fabs(recp->eta()) && fabs(recp->eta()) <= 1.9){
    if (recp->auxdata<unsigned char>("numberOfTRTHits") + recp->auxdata<unsigned char>("numberOfTRTOutliers") <= 5)
      return false;
    if (recp->auxdata<unsigned char>("numberOfTRTOutliers") >= 0.9 * (recp->auxdata<unsigned char>("numberOfTRTHits") + recp->auxdata<unsigned char>("numberOfTRTOutliers")) )
      return false;
  }

  // standard track selection
  // pt cut
  if (recp->pt() / 1000. < 1)
    return false;
  // Eta cut
  if (fabs(recp->eta()) > 2.5)
    return false;

  return true;
}

// tomoya check track quality
bool FTKxAODAnalysis::isAcceptedFTKfiducial(const xAOD::TrackParticle* recp)
{
  // Check the track is inside FTK fiducial
  // ************************************************   Checking with no ftk cuts ************************************************
  // if (isData == false){
  // d0 cut
  if (fabs(recp->auxdata<float>("d0")) > 2)
    return false;
  // z0 cut
  if (fabs(recp->auxdata<float>("z0")) > 110)
    return false;
  // }

  return true;
}


FTKxAODAnalysis :: FTKxAODAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().

  // deltaRval = 0.01;
  dx = -0.5;

  dy = -0.5;

  // std::cerr << "BRI TEST deltaRval is equal to " << deltaRval << std::endl;
  // std::cerr << "BRI TEST dRval is equal to " << dRval << std::endl;

}



EL::StatusCode FTKxAODAnalysis :: setupJob (EL::Job& job)
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



EL::StatusCode FTKxAODAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.



  tree = new TTree("tracks", "tree with track variables per event");

  tree->Branch("event_number", &m_eventNumber, "event_number/I");
  tree->Branch("run_number",   &m_runNumber,   "run_number/I");
  tree->Branch("mu",   &m_mu,   "mu/I");
  tree->Branch("lumiblock",   &m_lb,   "lumiblock/I");

  tree->Branch("truth_track_n",      &truth_track_n,      "truth_track_n/I");

  tree->Branch("reco_accepted_track_n",        &reco_accepted_track_n,        "reco_accepted_track_n/I");
  tree->Branch("reco_inclusive_track_n",       &reco_inclusive_track_n,       "reco_inclusive_track_n/I");
  tree->Branch("ftk_accepted_track_n",         &ftk_accepted_track_n,         "ftk_accepted_track_n/I");
  tree->Branch("ftk_inclusive_track_n",        &ftk_inclusive_track_n,        "ftk_inclusive_track_n/I");
  tree->Branch("ftk_refit_accepted_track_n",   &ftk_refit_accepted_track_n,   "ftk_refit_accepted_track_n/I");
  tree->Branch("ftk_refit_inclusive_track_n",  &ftk_refit_inclusive_track_n,  "ftk_refit_inclusive_track_n/I");

  tree->Branch("reco_ftkMatch_track_n",         &reco_ftkMatch_track_n,         "reco_ftkMatch_track_n/I");
  tree->Branch("reco_ftkrefitMatch_track_n",    &reco_ftkrefitMatch_track_n,    "reco_ftkrefitMatch_track_n/I");
  tree->Branch("truth_recoMatch_track_n",       &truth_recoMatch_track_n,       "truth_recoMatch_track_n/I");
  tree->Branch("truth_ftkMatch_track_n",        &truth_ftkMatch_track_n,        "truth_ftkMatch_track_n/I");
  tree->Branch("truth_ftkrefitMatch_track_n",   &truth_ftkrefitMatch_track_n,   "truth_ftkrefitMatch_track_n/I");


  tree->Branch("truth_track_reco_match_prob",      &truth_track_reco_match_prob);
  tree->Branch("truth_track_ftk_match_prob",       &truth_track_ftk_match_prob);
  tree->Branch("truth_track_ftk_refit_match_prob", &truth_track_ftk_refit_match_prob);
  tree->Branch("truth_track_reco_match",           &truth_track_reco_match);
  tree->Branch("truth_track_ftk_match",            &truth_track_ftk_match);
  tree->Branch("truth_track_ftk_refit_match",      &truth_track_ftk_refit_match);


  tree->Branch("truth_track_pt",           &truth_track_pt);
  tree->Branch("truth_track_eta",          &truth_track_eta);
  tree->Branch("truth_track_phi",          &truth_track_phi);
  tree->Branch("truth_track_m",            &truth_track_m);
  tree->Branch("truth_track_theta",        &truth_track_theta);
  tree->Branch("truth_track_d0",           &truth_track_d0);
  tree->Branch("truth_track_z0",           &truth_track_z0);
  tree->Branch("truth_track_qop",          &truth_track_qop);
  tree->Branch("truth_track_charge",       &truth_track_charge);
  tree->Branch("truth_track_chi2ndof",     &truth_track_chi2ndof);
  tree->Branch("truth_track_pdgid",        &truth_track_pdgid);
  tree->Branch("truth_track_parent_pdgid", &truth_track_parent_pdgid);
  tree->Branch("truth_track_status",       &truth_track_status);
  tree->Branch("truth_track_barcode",      &truth_track_barcode);
  tree->Branch("truth_accepted",           &truth_accepted);

  // tree->Branch("muonRoI_eta",         &muonRoI_eta);
  // tree->Branch("muonRoI_phi",         &muonRoI_phi);
  // tree->Branch("muonRoI_roiWord",     &muonRoI_roiWord);
  // tree->Branch("muonRoI_thrValue",    &muonRoI_thrValue);
  tree->Branch("reco_accepted",                     &reco_accepted);
  tree->Branch("reco_accepted_FTKTDR",              &reco_accepted_FTKTDR);
  tree->Branch("reco_muon_accepted",                &reco_muon_accepted);
  tree->Branch("reco_ftk_fiducial",                 &reco_ftk_fiducial);

  tree->Branch("reco_inclusive_track_pt",           &reco_inclusive_track_pt);
  tree->Branch("reco_inclusive_track_eta",          &reco_inclusive_track_eta);
  tree->Branch("reco_inclusive_track_phi",          &reco_inclusive_track_phi);
  tree->Branch("reco_inclusive_track_m",            &reco_inclusive_track_m);
  tree->Branch("reco_inclusive_track_theta",        &reco_inclusive_track_theta);
  tree->Branch("reco_inclusive_track_d0",           &reco_inclusive_track_d0);
  tree->Branch("reco_inclusive_track_z0",           &reco_inclusive_track_z0);
  tree->Branch("reco_inclusive_track_qop",          &reco_inclusive_track_qop);
  tree->Branch("reco_inclusive_track_charge",       &reco_inclusive_track_charge);
  tree->Branch("reco_inclusive_track_chi2",         &reco_inclusive_track_chi2);
  tree->Branch("reco_inclusive_track_chi2ndof",     &reco_inclusive_track_chi2ndof);
  tree->Branch("reco_inclusive_track_hitPattern",   &reco_inclusive_track_hitPattern);

  tree->Branch("reco_accepted_track_pt",           &reco_accepted_track_pt);
  tree->Branch("reco_accepted_track_eta",          &reco_accepted_track_eta);
  tree->Branch("reco_accepted_track_eta_barrel",          &reco_accepted_track_eta_barrel);
  tree->Branch("reco_accepted_track_eta_endcap",          &reco_accepted_track_eta_endcap);
  tree->Branch("reco_accepted_track_phi",          &reco_accepted_track_phi);
  tree->Branch("reco_accepted_track_m",            &reco_accepted_track_m);
  tree->Branch("reco_accepted_track_theta",        &reco_accepted_track_theta);
  tree->Branch("reco_accepted_track_d0",           &reco_accepted_track_d0);
  tree->Branch("reco_accepted_track_z0",           &reco_accepted_track_z0);
  tree->Branch("reco_accepted_track_qop",          &reco_accepted_track_qop);
  tree->Branch("reco_accepted_track_charge",       &reco_accepted_track_charge);
  tree->Branch("reco_accepted_track_chi2",         &reco_accepted_track_chi2);
  tree->Branch("reco_accepted_track_chi2ndof",     &reco_accepted_track_chi2ndof);
  tree->Branch("reco_accepted_track_hitPattern",   &reco_accepted_track_hitPattern);

  tree->Branch("ftk_accepted",                    &ftk_accepted);
  tree->Branch("ftk_inclusive_track_pt",          &ftk_inclusive_track_pt);
  tree->Branch("ftk_inclusive_track_eta",         &ftk_inclusive_track_eta);
  tree->Branch("ftk_inclusive_track_phi",         &ftk_inclusive_track_phi);
  tree->Branch("ftk_inclusive_track_m",           &ftk_inclusive_track_m);
  tree->Branch("ftk_inclusive_track_theta",       &ftk_inclusive_track_theta);
  tree->Branch("ftk_inclusive_track_d0",          &ftk_inclusive_track_d0);
  tree->Branch("ftk_inclusive_track_corrected_d0",&ftk_inclusive_track_corrected_d0);
  tree->Branch("ftk_inclusive_track_z0",          &ftk_inclusive_track_z0);
  tree->Branch("ftk_inclusive_track_qop",         &ftk_inclusive_track_qop);
  tree->Branch("ftk_inclusive_track_charge",      &ftk_inclusive_track_charge);
  tree->Branch("ftk_inclusive_track_chi2ndof",    &ftk_inclusive_track_chi2ndof);
  tree->Branch("ftk_inclusive_track_chi2",        &ftk_inclusive_track_chi2);
  tree->Branch("ftk_inclusive_track_hitPattern",  &ftk_inclusive_track_hitPattern);
  // tree->Branch("ftk_inclusive_reco_match",     &ftk_inclusive_reco_match);

  tree->Branch("ftk_accepted_track_pt",          &ftk_accepted_track_pt);
  tree->Branch("ftk_accepted_track_eta",         &ftk_accepted_track_eta);
  tree->Branch("ftk_accepted_track_eta_barrel",         &ftk_accepted_track_eta_barrel);
  tree->Branch("ftk_accepted_track_eta_endcap",         &ftk_accepted_track_eta_endcap);
  tree->Branch("ftk_accepted_track_phi",         &ftk_accepted_track_phi);
  tree->Branch("ftk_accepted_track_m",           &ftk_accepted_track_m);
  tree->Branch("ftk_accepted_track_theta",       &ftk_accepted_track_theta);
  tree->Branch("ftk_accepted_track_d0",          &ftk_accepted_track_d0);
  tree->Branch("ftk_accepted_track_corrected_d0",&ftk_accepted_track_corrected_d0);
  tree->Branch("ftk_accepted_track_z0",          &ftk_accepted_track_z0);
  tree->Branch("ftk_accepted_track_qop",         &ftk_accepted_track_qop);
  tree->Branch("ftk_accepted_track_charge",      &ftk_accepted_track_charge);
  tree->Branch("ftk_accepted_track_chi2ndof",    &ftk_accepted_track_chi2ndof);
  tree->Branch("ftk_accepted_track_chi2",        &ftk_accepted_track_chi2);
  tree->Branch("ftk_accepted_track_hitPattern",  &ftk_accepted_track_hitPattern);

  tree->Branch("ftk_refit_accepted",                      &ftk_refit_accepted);
  tree->Branch("ftk_refit_inclusive_track_pt",           &ftk_refit_inclusive_track_pt);
  tree->Branch("ftk_refit_inclusive_track_eta",          &ftk_refit_inclusive_track_eta);
  tree->Branch("ftk_refit_inclusive_track_phi",          &ftk_refit_inclusive_track_phi);
  tree->Branch("ftk_refit_inclusive_track_m",            &ftk_refit_inclusive_track_m);
  tree->Branch("ftk_refit_inclusive_track_theta",        &ftk_refit_inclusive_track_theta);
  tree->Branch("ftk_refit_inclusive_track_d0",           &ftk_refit_inclusive_track_d0);
  tree->Branch("ftk_refit_inclusive_track_z0",           &ftk_refit_inclusive_track_z0);
  tree->Branch("ftk_refit_inclusive_track_qop",          &ftk_refit_inclusive_track_qop);
  tree->Branch("ftk_refit_inclusive_track_charge",       &ftk_refit_inclusive_track_charge);
  tree->Branch("ftk_refit_inclusive_track_chi2",         &ftk_refit_inclusive_track_chi2);
  tree->Branch("ftk_refit_inclusive_track_chi2ndof",     &ftk_refit_inclusive_track_chi2ndof);
  tree->Branch("ftk_refit_inclusive_track_hitPattern",   &ftk_refit_inclusive_track_hitPattern);

  tree->Branch("ftk_refit_accepted_track_pt",           &ftk_refit_accepted_track_pt);
  tree->Branch("ftk_refit_accepted_track_eta",          &ftk_refit_accepted_track_eta);
  tree->Branch("ftk_refit_accepted_track_eta_barrel",          &ftk_refit_accepted_track_eta_barrel);
  tree->Branch("ftk_refit_accepted_track_eta_endcap",          &ftk_refit_accepted_track_eta_endcap);
  tree->Branch("ftk_refit_accepted_track_phi",          &ftk_refit_accepted_track_phi);
  tree->Branch("ftk_refit_accepted_track_m",            &ftk_refit_accepted_track_m);
  tree->Branch("ftk_refit_accepted_track_theta",        &ftk_refit_accepted_track_theta);
  tree->Branch("ftk_refit_accepted_track_d0",           &ftk_refit_accepted_track_d0);
  tree->Branch("ftk_refit_accepted_track_z0",           &ftk_refit_accepted_track_z0);
  tree->Branch("ftk_refit_accepted_track_qop",          &ftk_refit_accepted_track_qop);
  tree->Branch("ftk_refit_accepted_track_charge",       &ftk_refit_accepted_track_charge);
  tree->Branch("ftk_refit_accepted_track_chi2",         &ftk_refit_accepted_track_chi2);
  tree->Branch("ftk_refit_accepted_track_chi2ndof",     &ftk_refit_accepted_track_chi2ndof);
  tree->Branch("ftk_refit_accepted_track_hitPattern",   &ftk_refit_accepted_track_hitPattern);


  tree->Branch("ftk_reco_deltaR",         &ftk_reco_deltaR);
  tree->Branch("truth_reco_deltaR",       &truth_reco_deltaR);
  tree->Branch("ftk_truth_deltaR",        &ftk_truth_deltaR);
  tree->Branch("ftk_refit_truth_deltaR",  &ftk_refit_truth_deltaR);
  tree->Branch("ftk_refit_reco_deltaR",   &ftk_refit_reco_deltaR);


  tree->Branch("ftk_reco_pt_bias",         &ftk_reco_pt_bias);
  tree->Branch("truth_reco_pt_bias",       &truth_reco_pt_bias);
  tree->Branch("ftk_truth_pt_bias",        &ftk_truth_pt_bias);
  tree->Branch("ftk_refit_truth_pt_bias",  &ftk_refit_truth_pt_bias);
  tree->Branch("ftk_refit_reco_pt_bias",   &ftk_refit_reco_pt_bias);

  tree->Branch("ftk_refit_reco_eta_bias",    &ftk_refit_reco_eta_bias);
  tree->Branch("ftk_reco_eta_bias",          &ftk_reco_eta_bias);
  tree->Branch("ftk_refit_truth_eta_bias",   &ftk_refit_truth_eta_bias);
  tree->Branch("ftk_truth_eta_bias",         &ftk_truth_eta_bias);
  tree->Branch("truth_reco_eta_bias",        &truth_reco_eta_bias);

  tree->Branch("ftk_refit_reco_phi_bias",   &ftk_refit_reco_phi_bias);
  tree->Branch("ftk_reco_phi_bias",         &ftk_reco_phi_bias);
  tree->Branch("truth_reco_phi_bias",       &truth_reco_phi_bias);
  tree->Branch("ftk_truth_phi_bias",        &ftk_truth_phi_bias);
  tree->Branch("ftk_refit_truth_phi_bias",  &ftk_refit_truth_phi_bias);

  tree->Branch("ftk_refit_reco_d0_bias",   &ftk_refit_reco_d0_bias);
  tree->Branch("ftk_reco_d0_bias",         &ftk_reco_d0_bias);
  tree->Branch("ftk_reco_corrected_d0_bias",         &ftk_reco_corrected_d0_bias);
  tree->Branch("ftk_refit_truth_d0_bias",  &ftk_refit_truth_d0_bias);
  tree->Branch("ftk_truth_d0_bias",        &ftk_truth_d0_bias);
  tree->Branch("ftk_truth_corrected_d0_bias",        &ftk_truth_corrected_d0_bias);
  tree->Branch("truth_reco_d0_bias",       &truth_reco_d0_bias);


  tree->Branch("truth_recoMatch_track_eta",      &truth_recoMatch_track_eta);
  tree->Branch("truth_recoMatch_track_phi",      &truth_recoMatch_track_phi);
  tree->Branch("reco_truthMatch_track_eta",      &reco_truthMatch_track_eta);
  tree->Branch("reco_truthMatch_track_phi",      &reco_truthMatch_track_phi);
  tree->Branch("truth_recoMatch_track_pt",       &truth_recoMatch_track_pt);
  tree->Branch("reco_truthMatch_track_pt",       &reco_truthMatch_track_pt);
  tree->Branch("truth_recoMatch_track_d0",       &truth_recoMatch_track_d0);
  tree->Branch("truth_recoMatch_track_z0",       &truth_recoMatch_track_z0);

  tree->Branch("ftk_truthMatch_track_eta",       &ftk_truthMatch_track_eta);
  tree->Branch("ftk_truthMatch_track_phi",       &ftk_truthMatch_track_phi);
  tree->Branch("truth_ftkMatch_track_eta",       &truth_ftkMatch_track_eta);
  tree->Branch("truth_ftkMatch_track_phi",       &truth_ftkMatch_track_phi);
  tree->Branch("ftk_truthMatch_track_pt",        &ftk_truthMatch_track_pt);
  tree->Branch("truth_ftkMatch_track_pt",        &truth_ftkMatch_track_pt);
  tree->Branch("truth_ftkMatch_track_d0",        &truth_ftkMatch_track_d0);
  // tree->Branch("truth_ftkMatch_track_corrected_d0",        &truth_ftkMatch_track_corrected_d0);
  tree->Branch("truth_ftkMatch_track_z0",        &truth_ftkMatch_track_z0);

  tree->Branch("ftk_recoMatch_track_eta",      &ftk_recoMatch_track_eta);
  tree->Branch("ftk_recoMatch_track_phi",      &ftk_recoMatch_track_phi);
  tree->Branch("reco_ftkMatch_track_eta",      &reco_ftkMatch_track_eta);
  tree->Branch("reco_ftkMatch_track_phi",      &reco_ftkMatch_track_phi);
  tree->Branch("reco_ftkMatch_track_d0",       &reco_ftkMatch_track_d0);
  // tree->Branch("reco_ftkMatch_track_corrected_d0",       &reco_ftkMatch_track_corrected_d0);
  tree->Branch("reco_ftkMatch_track_z0",       &reco_ftkMatch_track_z0);
  tree->Branch("ftk_recoMatch_track_pt",       &ftk_recoMatch_track_pt);
  tree->Branch("reco_ftkMatch_track_pt",       &reco_ftkMatch_track_pt);

  tree->Branch("ftk_refit_truthMatch_track_eta",     &ftk_refit_truthMatch_track_eta);
  tree->Branch("ftk_refit_truthMatch_track_phi",     &ftk_refit_truthMatch_track_phi);
  tree->Branch("truth_ftkrefitMatch_track_eta",      &truth_ftkrefitMatch_track_eta);
  tree->Branch("truth_ftkrefitMatch_track_phi",      &truth_ftkrefitMatch_track_phi);
  tree->Branch("ftk_refit_truthMatch_track_pt",      &ftk_refit_truthMatch_track_pt);
  tree->Branch("truth_ftkrefitMatch_track_pt",       &truth_ftkrefitMatch_track_pt);
  tree->Branch("truth_ftkrefitMatch_track_d0",       &truth_ftkrefitMatch_track_d0);
  tree->Branch("truth_ftkrefitMatch_track_z0",       &truth_ftkrefitMatch_track_z0);

  tree->Branch("ftk_refit_recoMatch_track_eta",     &ftk_refit_recoMatch_track_eta);
  tree->Branch("ftk_refit_recoMatch_track_phi",     &ftk_refit_recoMatch_track_phi);
  tree->Branch("reco_ftkrefitMatch_track_eta",      &reco_ftkrefitMatch_track_eta);
  tree->Branch("reco_ftkrefitMatch_track_phi",      &reco_ftkrefitMatch_track_phi);
  tree->Branch("ftk_refit_recoMatch_track_pt",      &ftk_refit_recoMatch_track_pt);
  tree->Branch("reco_ftkrefitMatch_track_pt",       &reco_ftkrefitMatch_track_pt);
  tree->Branch("reco_ftkrefitMatch_track_d0",       &reco_ftkrefitMatch_track_d0);
  tree->Branch("reco_ftkrefitMatch_track_z0",       &reco_ftkrefitMatch_track_z0);


  wk()->addOutput(tree);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKxAODAnalysis :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKxAODAnalysis :: initialize ()
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
  GeV = 0.001;

  ntracks_before_selection = 0;
  ntracks_after_selection = 0;

  // if (isData == false){std::cerr << "BRI TEST Simulation" << std::endl;}
  // if (isData == true){std::cerr << "BRI TEST Data" << std::endl;}
  // // else {std::cerr << isData << std::endl;}

  // as a check, let's see the number of events in our xAOD
  Warning("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKxAODAnalysis :: execute ()
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

  if( (m_eventCounter % 100) ==0 ) Info("execute()", "Event number = %i", m_eventCounter );
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
  
  // truth info, comment if processing data
  
  const xAOD::TruthParticleContainer* truthParticles = NULL;
  if (isData == false){
    if (!event->retrieve(truthParticles, "TruthParticles").isSuccess()) {
      Error("execute()", "Failed to retrieve TruthParticles. Exiting.");
      return EL::StatusCode::FAILURE;
    }
  }

  // const xAOD::JetAuxContainer* jets = NULL;
  //   if (!event->retrieve(jets, "Jets").isSuccess()) {
  //     Error("execute()", "Failed to retrieve Jets. Exiting.");
  //     return EL::StatusCode::FAILURE;
  //   }
  // truth info, comment if processing data end

  // L1 muon objects
  // const xAOD::MuonRoIContainer* muonRoI = NULL;
  // if (!event->retrieve(muonRoI, "LVL1MuonRoIs").isSuccess()) {
  //   Error("execute()", "Failed to retrieve LVL1MuonRoIs. Exiting.");
  //   return EL::StatusCode::FAILURE;
  // }

  // offline tracks
  const xAOD::TrackParticleContainer* recoTracks = NULL;
  if (!event->retrieve(recoTracks, "InDetTrackParticles").isSuccess()) {
    Error("execute()", "Failed to retrieve InDetTrackParticles. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  // offline tracks
  //const xAOD::JetContainer* jets = NULL;
  //if (!event->retrieve(jets, "AntiKt4EMTopoJets").isSuccess()) {
    //Error("execute()", "Failed to retrieve jets. Exiting.");
    //return EL::StatusCode::FAILURE;
  //}


// ************************************************************ RECO_BLS_TEST************************************************************
  const xAOD::TrackParticleContainer* ftkTracks = NULL;
  
  if (isData == false){
    if (!event->retrieve(ftkTracks, "Converted_FTKTrackParticleContainer").isSuccess()) {
      Error("execute()", "Failed to retrieve FTK_TrackParticleContainer. Exiting.");
      return EL::StatusCode::FAILURE;
    }
  }

  if (isData == true){
    if (!event->retrieve(ftkTracks, "FTK_TrackParticleContainer").isSuccess()) {
      Error("execute()", "Failed to retrieve FTK_TrackParticleContainer. Exiting.");
      return EL::StatusCode::FAILURE;
    }
  }
    // std::cerr << ftf << std::endl;
  // if (isAOD == (false)){
  // if (!event->retrieve(ftkTracks, "Converted_FTK_TrackParticles").isSuccess()) {
  //  Error("execute()", "Failed to retrieve Converted_FTK_TrackParticles. Exiting.");
  //  return EL::StatusCode::FAILURE;
  // }}

  const xAOD::TrackParticleContainer* ftkRefitTracks = NULL;
  // for AOD
  if (isData == false){
    if (!event->retrieve(ftkRefitTracks, "Converted_FTKTrackParticleContainerRefit").isSuccess()) {
      Error("execute()", "Failed to retrieve FTK_TrackParticleContainerRefit. Exiting.");
      return EL::StatusCode::FAILURE;
    }
  }

  if (isData == true){
    if (!event->retrieve(ftkRefitTracks, "FTK_TrackParticleContainerRefit").isSuccess()) {
      Error("execute()", "Failed to retrieve FTK_TrackParticleContainerRefit. Exiting.");
      return EL::StatusCode::FAILURE;
    }
  }
  // if (isAOD == (false)){
  // if (!event->retrieve(ftkRefitTracks, "Converted_FTK_RefitTrackParticles").isSuccess()) {
  //  Error("execute()", "Failed to retrieve Converted_FTK_RefitTrackParticles. Exiting.");
  //    return EL::StatusCode::FAILURE;
  //  }}
// ************************************************************ RECO_BLS_TEST************************************************************


  m_eventNumber = static_cast<int>(m_eventInfoCont->eventNumber());
  m_runNumber   = static_cast<int>(m_eventInfoCont->runNumber());
  m_mu   = static_cast<int>(m_eventInfoCont->actualInteractionsPerCrossing());
  m_lb = static_cast<int>(m_eventInfoCont->lumiBlock());

  m_isMC = m_eventInfoCont->eventType( xAOD::EventInfo::IS_SIMULATION );

  // tomoya add

  int itruth = -1;
  int ireco_accepted = -1;
  int ireco_inclusive = -1;
  //  int imuRoI = -1;
  int iftk_accepted = -1;
  int iftk_inclusive = -1;

  int iftk_refit_accepted = -1;
  int iftk_refit_inclusive = -1;

  int truth_recoMatch_n = 0;
  int truth_ftkMatch_n = 0;
  int truth_ftkrefitMatch_n = 0;


// for (auto jet: *jets){

  
// }
// truth particle loop
if (isData == false){
  for (auto truthPart: *truthParticles) {

    if (isAcceptedTruth(truthPart)){
      // truth_accepted.push_back(1);
    }else{
      // truth_accepted.push_back(0);
      continue;
    }

    ++itruth;

    truth_track_pt.push_back(truthPart->pt() / 1000.);
    truth_track_eta.push_back(truthPart->eta());
    truth_track_phi.push_back(truthPart->phi());
    // truth_track_phi.push_back(truthPart->auxdata<float>("phi"));


    // only DAOD??
    // if (isAOD == false){
    truth_track_theta.push_back(truthPart->auxdata<float>("theta"));
    truth_track_d0.push_back(truthPart->auxdata<float>("d0"));
    truth_track_z0.push_back(truthPart->auxdata<float>("z0"));
    truth_track_z0st.push_back(truthPart->auxdata<float>("z0st"));
    truth_track_qop.push_back(truthPart->auxdata<float>("qOverP"));
    // }


    truth_track_m.push_back(truthPart->m() / 1000.);
    truth_track_charge.push_back(truthPart->charge());
    truth_track_pdgid.push_back(truthPart->pdgId());
    truth_track_status.push_back(truthPart->status());
    truth_track_barcode.push_back(truthPart->barcode());

    const xAOD::TruthParticle * parentPart = truthPart->parent(0);
    truth_track_parent_pdgid.push_back(parentPart->pdgId());

    // if (truthPart->hasProdVtx())
    //   truth_track_prod_perp.push_back(truthPart->prodVtx()->perp());
    // else
    //   truth_track_prod_perp.push_back(1e7);

    // Find best offline track match
    auto match = best_match(truthPart, recoTracks);
    if (match.first != NULL) {
      ++ truth_recoMatch_n;
      truth_track_reco_match_prob.push_back(match.first->auxdata<float>("truthMatchProbability"));

      Float_t truth_reco_deta = match.first->eta() - truthPart->eta();
      Float_t truth_reco_dphi = match.first->phi() - truthPart->phi();
      if(abs(truth_reco_dphi) > TMath::Pi()) truth_reco_dphi = 2 * TMath::Pi() - abs(truth_reco_dphi);

      Float_t tmp_truth_reco_temp_dR = (sqrt(pow(truth_reco_dphi, 2) + pow(truth_reco_deta, 2)));

      Float_t tmp_truth_reco_pt_bias = (match.first->pt()/ 1000. - truthPart->pt()/ 1000.);
      Float_t tmp_truth_reco_eta_bias = (match.first->eta() - truthPart->eta());
      Float_t tmp_truth_reco_phi_bias = (match.first->phi() - truthPart->phi());
      Float_t tmp_truth_reco_d0_bias = (match.first->auxdata<float>("d0") - truthPart->auxdata<float>("d0"));

      Float_t tmp_reco_truthMatch_track_eta = match.first->eta();
      Float_t tmp_reco_truthMatch_track_phi = match.first->phi();
      Float_t tmp_truth_recoMatch_track_phi = truthPart->phi();
      Float_t tmp_truth_recoMatch_track_eta = truthPart->eta();

      Float_t tmp_reco_truthMatch_track_pt = match.first->pt()/ 1000.;
      Float_t tmp_truth_recoMatch_track_pt = truthPart->pt()/ 1000.;

      Float_t tmp_truth_recoMatch_track_d0 = truthPart->auxdata<float>("d0");
      Float_t tmp_truth_recoMatch_track_z0 = truthPart->auxdata<float>("z0");

      truth_reco_deltaR.push_back(tmp_truth_reco_temp_dR);
      reco_truthMatch_track_eta.push_back(tmp_reco_truthMatch_track_eta);
      reco_truthMatch_track_phi.push_back(tmp_reco_truthMatch_track_phi);
      truth_recoMatch_track_eta.push_back(tmp_truth_recoMatch_track_eta);
      truth_recoMatch_track_phi.push_back(tmp_truth_recoMatch_track_phi);
      reco_truthMatch_track_pt.push_back(tmp_reco_truthMatch_track_pt);
      truth_recoMatch_track_pt.push_back(tmp_truth_recoMatch_track_pt);
      truth_recoMatch_track_z0.push_back(tmp_truth_recoMatch_track_z0); 
      truth_recoMatch_track_d0.push_back(tmp_truth_recoMatch_track_d0);

      truth_reco_pt_bias.push_back(tmp_truth_reco_pt_bias);
      truth_reco_eta_bias.push_back(tmp_truth_reco_eta_bias);
      truth_reco_phi_bias.push_back(tmp_truth_reco_phi_bias);
      truth_reco_d0_bias.push_back(tmp_truth_reco_d0_bias);
    } else {
      truth_track_reco_match_prob.push_back(0.);
    }
    truth_track_reco_match.push_back(match.second);


    // Find best FTK track match

// ************************************************************ RECO_BLS_TEST************************************************************

    match = best_match(truthPart, ftkTracks);
    // std::cerr << "BRI TEST 2" << std::endl;
    if (match.first != NULL) {
      ++ truth_ftkMatch_n;
      truth_track_ftk_match_prob.push_back(match.first->auxdata<float>("truthMatchProbability"));
      Float_t ftk_truth_deta = match.first->eta() - truthPart->eta();
      Float_t ftk_truth_dphi = match.first->phi() - truthPart->phi();
      if(abs(ftk_truth_dphi) > TMath::Pi()) ftk_truth_dphi = 2 * TMath::Pi() - abs(ftk_truth_dphi);


      Float_t tmp_ftk_truth_pt_bias = (match.first->pt()/ 1000. - truthPart->pt()/ 1000.);
      Float_t tmp_ftk_truth_eta_bias = (match.first->eta() - truthPart->eta());
      Float_t tmp_ftk_truth_phi_bias = (match.first->phi() - truthPart->phi());
      Float_t tmp_ftk_truth_corrected_d0_bias = (match.first->auxdata<float>("d0")-dx*TMath::Sin(match.first->phi())+dy*TMath::Cos(match.first->phi()) - truthPart->auxdata<float>("d0"));
      Float_t tmp_ftk_truth_d0_bias = (match.first->auxdata<float>("d0") - truthPart->auxdata<float>("d0"));

      Float_t ftk_truth_dR = (sqrt(pow(ftk_truth_dphi, 2) + pow(ftk_truth_deta, 2)));

      Float_t tmp_ftk_truthMatch_track_eta = match.first->eta();
      Float_t tmp_ftk_truthMatch_track_phi = match.first->phi();
      Float_t tmp_truth_ftkMatch_track_eta = truthPart->eta();
      Float_t tmp_truth_ftkMatch_track_phi = truthPart->phi();
      Float_t tmp_ftk_truthMatch_track_pt = match.first->pt()/ 1000.;
      Float_t tmp_truth_ftkMatch_track_pt = truthPart->pt()/ 1000.;

      Float_t tmp_truth_ftkMatch_track_d0 = truthPart->auxdata<float>("d0");
      Float_t tmp_truth_ftkMatch_track_z0 = truthPart->auxdata<float>("z0");

      ftk_truth_deltaR.push_back(ftk_truth_dR);
      truth_ftkMatch_track_eta.push_back(tmp_truth_ftkMatch_track_eta);
      truth_ftkMatch_track_phi.push_back(tmp_truth_ftkMatch_track_phi);
      ftk_truthMatch_track_eta.push_back(tmp_ftk_truthMatch_track_eta);
      ftk_truthMatch_track_phi.push_back(tmp_ftk_truthMatch_track_phi);
      truth_ftkMatch_track_pt.push_back(tmp_truth_ftkMatch_track_pt);
      ftk_truthMatch_track_pt.push_back(tmp_ftk_truthMatch_track_pt);

      truth_ftkMatch_track_d0.push_back(tmp_truth_ftkMatch_track_d0);
      truth_ftkMatch_track_z0.push_back(tmp_truth_ftkMatch_track_z0);

      ftk_truth_pt_bias.push_back(tmp_ftk_truth_pt_bias);
      ftk_truth_eta_bias.push_back(tmp_ftk_truth_eta_bias);
      ftk_truth_phi_bias.push_back(tmp_ftk_truth_phi_bias);
      ftk_truth_d0_bias.push_back(tmp_ftk_truth_d0_bias);
      ftk_truth_corrected_d0_bias.push_back(tmp_ftk_truth_corrected_d0_bias);


    } else {
      truth_track_ftk_match_prob.push_back(0.);
    }
    truth_track_ftk_match.push_back(match.second);

    // Find best FTK refit track match
    match = best_match(truthPart, ftkRefitTracks);
    // std::cerr << "BRI best_match TEST 4" << std::endl;
    // std::cerr << "BRI TEST 3" << std::endl;
    if (match.first != NULL) {
      ++ truth_ftkrefitMatch_n;

      truth_track_ftk_refit_match_prob.push_back(match.first->auxdata<float>("truthMatchProbability"));

      Float_t ftk_refit_truth_deta = match.first->eta() - truthPart->eta();
      Float_t ftk_refit_truth_dphi = match.first->phi() - truthPart->phi();
      if(abs(ftk_refit_truth_dphi) > TMath::Pi()) ftk_refit_truth_dphi = 2 * TMath::Pi() - abs(ftk_refit_truth_dphi);


      Float_t tmp_ftk_refit_truth_pt_bias = (match.first->pt()/ 1000. - truthPart->pt()/ 1000.);
      Float_t tmp_ftk_refit_truth_eta_bias = (match.first->eta() - truthPart->eta());
      Float_t tmp_ftk_refit_truth_phi_bias = (match.first->phi() - truthPart->phi());
      Float_t tmp_ftk_refit_truth_d0_bias = (match.first->auxdata<float>("d0") - truthPart->auxdata<float>("d0"));

      Float_t ftk_refit_truth_dR = (sqrt(pow(ftk_refit_truth_dphi, 2) + pow(ftk_refit_truth_deta, 2)));

      Float_t tmp_ftk_refit_truthMatch_track_eta = match.first->eta();
      Float_t tmp_ftk_refit_truthMatch_track_phi = match.first->phi();
      Float_t tmp_truth_ftkrefitMatch_track_eta = truthPart->eta();
      Float_t tmp_truth_ftkrefitMatch_track_phi = truthPart->phi();
      Float_t tmp_ftk_refit_truthMatch_track_pt = match.first->pt()/ 1000.;
      Float_t tmp_truth_ftkrefitMatch_track_pt = truthPart->pt()/ 1000.;

      Float_t tmp_truth_ftkrefitMatch_track_d0 = truthPart->auxdata<float>("d0");
      Float_t tmp_truth_ftkrefitMatch_track_z0 = truthPart->auxdata<float>("z0");

      ftk_refit_truth_deltaR.push_back(ftk_refit_truth_dR);
      truth_ftkrefitMatch_track_eta.push_back(tmp_truth_ftkrefitMatch_track_eta);
      truth_ftkrefitMatch_track_phi.push_back(tmp_truth_ftkrefitMatch_track_phi);
      ftk_refit_truthMatch_track_eta.push_back(tmp_ftk_refit_truthMatch_track_eta);
      ftk_refit_truthMatch_track_phi.push_back(tmp_ftk_refit_truthMatch_track_phi);
      truth_ftkrefitMatch_track_pt.push_back(tmp_truth_ftkrefitMatch_track_pt);
      ftk_refit_truthMatch_track_pt.push_back(tmp_ftk_refit_truthMatch_track_pt);

      truth_ftkrefitMatch_track_d0.push_back(tmp_truth_ftkrefitMatch_track_d0);
      truth_ftkrefitMatch_track_z0.push_back(tmp_truth_ftkrefitMatch_track_z0);

      ftk_refit_truth_pt_bias.push_back(tmp_ftk_refit_truth_pt_bias);
      ftk_refit_truth_eta_bias.push_back(tmp_ftk_refit_truth_eta_bias);
      ftk_refit_truth_phi_bias.push_back(tmp_ftk_refit_truth_phi_bias);
      ftk_refit_truth_d0_bias.push_back(tmp_ftk_refit_truth_d0_bias);

    } else {
      truth_track_ftk_refit_match_prob.push_back(0.);
    }
    truth_track_ftk_refit_match.push_back(match.second);
// ************************************************************ RECO_BLS_TEST************************************************************

  
}
  truth_track_n = itruth + 1;
  truth_recoMatch_track_n = truth_recoMatch_n;
  truth_ftkMatch_track_n = truth_ftkMatch_n;
  truth_ftkrefitMatch_track_n = truth_ftkrefitMatch_n;

}

  //  L1 muon loops
  // imuRoI = -1;
  // for (auto muRoI : *muonRoI) {

  //   imuRoI++;

  //   muonRoI_eta.push_back(muRoI->eta());
  //   muonRoI_phi.push_back(muRoI->phi());
  //   muonRoI_roiWord.push_back(muRoI->roiWord());
  //   muonRoI_thrValue.push_back(muRoI->thrValue());

  // }

// std::cerr << "BRI TEST 4" << std::endl;
  // reco track loops
  float chi2, ndof;
  // int nPix, nSCT;
  ireco_accepted = -1;
  ireco_inclusive = -1;

  int reco_ftkMatch = 0;
  int reco_ftkrefitMatch = 0;

  for (auto recotrack : *recoTracks) {
    // std::cerr << "RECO TRACKS FOUND BLS" << std::endl;
    Int_t ftk_dR_flag = 0;
    Int_t ftk_refit_dR_flag = 0;


    if (isAcceptedReco(recotrack)){
      reco_accepted.push_back(1);
    }else{
      reco_accepted.push_back(0);
      // continue;
    }

    if (isAcceptedReco_muon(recotrack)){
      reco_muon_accepted.push_back(1);
    }else{
      reco_muon_accepted.push_back(0);
      // continue;
    }

    if (isAcceptedReco_FTKTDR(recotrack)){
      reco_accepted_FTKTDR.push_back(1);
    }else{
      reco_accepted_FTKTDR.push_back(0);
      // continue;
    }

    if (isAcceptedFTKfiducial(recotrack)){
      reco_ftk_fiducial.push_back(1);
    }else{
      reco_ftk_fiducial.push_back(0);
      // continue;
    }

    ++ireco_inclusive;
    Float_t tmp_ftk_refit_reco_pt_bias;
    Float_t tmp_ftk_refit_reco_eta_bias;
    Float_t tmp_ftk_refit_reco_phi_bias;
    Float_t tmp_ftk_refit_reco_d0_bias;
    Float_t ftk_refit_reco_dR = dRval;
    Float_t tmp_ftk_refit_recoMatch_track_eta;
    Float_t tmp_ftk_refit_recoMatch_track_phi;
    Float_t tmp_reco_ftkrefitMatch_track_eta;
    Float_t tmp_reco_ftkrefitMatch_track_phi;
    Float_t tmp_ftk_refit_recoMatch_track_pt;
    Float_t tmp_reco_ftkrefitMatch_track_pt;
    Float_t tmp_reco_ftkrefitMatch_track_d0;
    Float_t tmp_reco_ftkrefitMatch_track_z0;
    Float_t tmp_ftk_reco_pt_bias;
    Float_t tmp_ftk_reco_eta_bias;
    Float_t tmp_ftk_reco_phi_bias;
    Float_t tmp_ftk_reco_d0_bias;
    Float_t tmp_ftk_reco_corrected_d0_bias;
    Float_t ftk_reco_dR = dRval;
    Float_t tmp_ftk_recoMatch_track_eta;
    Float_t tmp_ftk_recoMatch_track_phi;
    Float_t tmp_reco_ftkMatch_track_eta;
    Float_t tmp_reco_ftkMatch_track_phi;
    Float_t tmp_ftk_recoMatch_track_pt;
    Float_t tmp_reco_ftkMatch_track_pt;
    
    Float_t tmp_reco_ftkMatch_track_d0;
    // Float_t tmp_reco_ftkMatch_track_corrected_d0;
    Float_t tmp_reco_ftkMatch_track_z0;

    Float_t tmp_ftk_recoMatch_track_d0;
    Float_t tmp_ftk_recoMatch_track_corrected_d0;
    Float_t tmp_ftk_recoMatch_track_z0;

    chi2 = recotrack->auxdata<float>("chiSquared");
    ndof = recotrack->auxdata<float>("numberDoF");

    reco_inclusive_track_hitPattern.push_back(recotrack->auxdata<unsigned int>("hitPattern"));
    reco_inclusive_track_pt.push_back(recotrack->pt()/ 1000.);
    reco_inclusive_track_eta.push_back(recotrack->eta());
    reco_inclusive_track_phi.push_back(recotrack->phi());
    reco_inclusive_track_m.push_back(recotrack->m() / 1000.);
    reco_inclusive_track_theta.push_back(recotrack->theta());
    reco_inclusive_track_d0.push_back(recotrack->auxdata<float>("d0"));
    reco_inclusive_track_z0.push_back(recotrack->auxdata<float>("z0"));
    reco_inclusive_track_qop.push_back(recotrack->qOverP());
    reco_inclusive_track_chi2.push_back(chi2);
    reco_inclusive_track_chi2ndof.push_back(chi2 / ndof);
    reco_inclusive_track_charge.push_back(recotrack->charge());

    
    if (isAcceptedReco(recotrack)){
      if (isAcceptedReco_FTKTDR(recotrack)){
        ++ireco_accepted;

        chi2 = recotrack->auxdata<float>("chiSquared");
        ndof = recotrack->auxdata<float>("numberDoF");

        reco_accepted_track_hitPattern.push_back(recotrack->auxdata<unsigned int>("hitPattern"));
        reco_accepted_track_pt.push_back(recotrack->pt()/ 1000.);
        reco_accepted_track_eta.push_back(recotrack->eta());
        if (abs(recotrack->eta()) >= 1.5){reco_accepted_track_eta_endcap.push_back(recotrack->eta());}
        if (abs(recotrack->eta()) <= 1){reco_accepted_track_eta_barrel.push_back(recotrack->eta());}
        reco_accepted_track_phi.push_back(recotrack->phi());
        reco_accepted_track_m.push_back(recotrack->m() / 1000.);
        reco_accepted_track_theta.push_back(recotrack->theta());
        reco_accepted_track_d0.push_back(recotrack->auxdata<float>("d0"));
        reco_accepted_track_z0.push_back(recotrack->auxdata<float>("z0"));
        reco_accepted_track_qop.push_back(recotrack->qOverP());
        reco_accepted_track_chi2.push_back(chi2);
        reco_accepted_track_chi2ndof.push_back(chi2 / ndof);
        reco_accepted_track_charge.push_back(recotrack->charge());

// ************************************************************ RECO_BLS_TEST************************************************************

        for (auto track : *ftkTracks) {
          // std::cerr << "FTK Track Found" << std::endl;

          if (isAcceptedFTKfiducial(track)){
            // std::cerr << "FTK Track Found" << std::endl;
            Float_t ftk_reco_deta = 0;
            Float_t ftk_reco_dphi = 0;
            Float_t ftk_reco_temp_dR = 100;

            ftk_reco_deta = recotrack->eta() - track->eta();
            ftk_reco_dphi = recotrack->phi() - track->phi();
            if(abs(ftk_reco_dphi) > TMath::Pi()) ftk_reco_dphi = 2 * TMath::Pi() - abs(ftk_reco_dphi);

            ftk_reco_temp_dR = (sqrt(pow((ftk_reco_deta), 2) + pow(ftk_reco_dphi, 2)));
            if (ftk_reco_temp_dR < ftk_reco_dR){
              ftk_reco_dR = ftk_reco_temp_dR;
              tmp_ftk_recoMatch_track_eta = track->eta();
              tmp_ftk_recoMatch_track_phi = track->phi();
              tmp_reco_ftkMatch_track_eta = recotrack->eta();
              tmp_reco_ftkMatch_track_phi = recotrack->phi();
              tmp_ftk_recoMatch_track_pt = track->pt()/ 1000.;
              tmp_reco_ftkMatch_track_pt = recotrack->pt()/ 1000.;
              tmp_reco_ftkMatch_track_d0 = recotrack->auxdata<float>("d0");

              // d0 = track.getD0()-dx*sin( track.getPhi())+dy*cos( track.getPhi());
              // tmp_reco_ftkMatch_track_corrected_d0 = recotrack->auxdata<float>("d0");
              tmp_reco_ftkMatch_track_z0 = recotrack->auxdata<float>("z0");

              tmp_ftk_recoMatch_track_d0 = (track->auxdata<float>("d0"));
              tmp_ftk_recoMatch_track_corrected_d0 = (track->auxdata<float>("d0"))-dx*TMath::Sin(track->phi())+dy*TMath::Cos(track->phi());
              tmp_ftk_recoMatch_track_z0 = track->auxdata<float>("z0");

              // tmp_reco_pt = recotrack->pt();
              // tmp_ftk_pt = track->pt();
              tmp_ftk_reco_pt_bias = (track->pt()/ 1000. - recotrack->pt()/ 1000.);
              tmp_ftk_reco_eta_bias = (track->eta() - recotrack->eta());
              tmp_ftk_reco_phi_bias = (track->phi() - recotrack->phi());
              tmp_ftk_reco_d0_bias = track->auxdata<float>("d0") - recotrack->auxdata<float>("d0");
              tmp_ftk_reco_corrected_d0_bias = (((track->auxdata<float>("d0"))-dx*TMath::Sin(track->phi())+dy*TMath::Cos(track->phi())) - recotrack->auxdata<float>("d0"));
              ftk_dR_flag = 1;
            }
          }
        }

        for (auto refittrack : *ftkRefitTracks) {
          
          if (isAcceptedFTKfiducial(refittrack)){

            Float_t ftk_refit_reco_deta = 0;
            Float_t ftk_refit_reco_dphi = 0;
            Float_t ftk_refit_reco_temp_dR = 100;

            ftk_refit_reco_deta = recotrack->eta() - refittrack->eta();
            ftk_refit_reco_dphi = recotrack->phi() - refittrack->phi();
          
            if(abs(ftk_refit_reco_dphi) > TMath::Pi()) ftk_refit_reco_dphi = 2 * TMath::Pi() - abs(ftk_refit_reco_dphi);

            ftk_refit_reco_temp_dR = (sqrt(pow((ftk_refit_reco_deta), 2) + pow(ftk_refit_reco_dphi, 2)));
            
            if (ftk_refit_reco_temp_dR < ftk_refit_reco_dR){
              ftk_refit_reco_dR = ftk_refit_reco_temp_dR;
              tmp_ftk_refit_recoMatch_track_eta = refittrack->eta();
              tmp_ftk_refit_recoMatch_track_phi = refittrack->phi();
              tmp_reco_ftkrefitMatch_track_eta = recotrack->eta();
              tmp_reco_ftkrefitMatch_track_phi = recotrack->phi();
              tmp_reco_ftkrefitMatch_track_d0 = recotrack->auxdata<float>("d0");
              tmp_reco_ftkrefitMatch_track_z0 = recotrack->auxdata<float>("z0");

              tmp_ftk_refit_recoMatch_track_pt = refittrack->pt()/ 1000.;
              tmp_reco_ftkrefitMatch_track_pt = recotrack->pt()/ 1000.;
              // tmp_reco_pt = recotrack->pt();
              // tmp_ftk_pt = track->pt();
              tmp_ftk_refit_reco_pt_bias = (refittrack->pt()/ 1000. - recotrack->pt()/ 1000.);
              tmp_ftk_refit_reco_eta_bias = (refittrack->eta() - recotrack->eta());
              tmp_ftk_refit_reco_phi_bias = (refittrack->phi() - recotrack->phi());
              tmp_ftk_refit_reco_d0_bias = (refittrack->auxdata<float>("d0") - recotrack->auxdata<float>("d0"));
              ftk_refit_dR_flag = 1;
            }
          }
        }
// ************************************************************ RECO_BLS_TEST************************************************************

      }
    }
// ************************************************************ RECO_BLS_TEST************************************************************
    if (ftk_refit_dR_flag == 1){
    ++ reco_ftkrefitMatch;

    ftk_refit_reco_deltaR.push_back(ftk_refit_reco_dR);
    ftk_refit_recoMatch_track_eta.push_back(tmp_ftk_refit_recoMatch_track_eta);
    ftk_refit_recoMatch_track_phi.push_back(tmp_ftk_refit_recoMatch_track_phi);
    reco_ftkrefitMatch_track_eta.push_back(tmp_reco_ftkrefitMatch_track_eta);
    reco_ftkrefitMatch_track_phi.push_back(tmp_reco_ftkrefitMatch_track_phi);
    reco_ftkrefitMatch_track_d0.push_back(tmp_reco_ftkrefitMatch_track_d0);
    reco_ftkrefitMatch_track_z0.push_back(tmp_reco_ftkrefitMatch_track_z0);

    ftk_refit_recoMatch_track_pt.push_back(tmp_ftk_refit_recoMatch_track_pt);
    reco_ftkrefitMatch_track_pt.push_back(tmp_reco_ftkrefitMatch_track_pt);

    ftk_refit_reco_pt_bias.push_back(tmp_ftk_refit_reco_pt_bias);
    ftk_refit_reco_eta_bias.push_back(tmp_ftk_refit_reco_eta_bias);
    ftk_refit_reco_phi_bias.push_back(tmp_ftk_refit_reco_phi_bias);
    ftk_refit_reco_d0_bias.push_back(tmp_ftk_refit_reco_d0_bias);
    }

    if (ftk_dR_flag == 1){
      ++ reco_ftkMatch;
   
      ftk_reco_deltaR.push_back(ftk_reco_dR);
      ftk_recoMatch_track_eta.push_back(tmp_ftk_recoMatch_track_eta);
      ftk_recoMatch_track_phi.push_back(tmp_ftk_recoMatch_track_phi);
      reco_ftkMatch_track_eta.push_back(tmp_reco_ftkMatch_track_eta);
      reco_ftkMatch_track_phi.push_back(tmp_reco_ftkMatch_track_phi);
      reco_ftkMatch_track_d0.push_back(tmp_reco_ftkMatch_track_d0);
      // reco_ftkMatch_track_corrected_d0.push_back(tmp_reco_ftkMatch_track_corrected_d0);
      reco_ftkMatch_track_z0.push_back(tmp_reco_ftkMatch_track_z0);

      ftk_recoMatch_track_pt.push_back(tmp_ftk_recoMatch_track_pt);
      reco_ftkMatch_track_pt.push_back(tmp_reco_ftkMatch_track_pt);

      ftk_reco_pt_bias.push_back(tmp_ftk_reco_pt_bias);
      ftk_reco_eta_bias.push_back(tmp_ftk_reco_eta_bias);
      ftk_reco_phi_bias.push_back(tmp_ftk_reco_phi_bias);
      ftk_reco_d0_bias.push_back(tmp_ftk_reco_d0_bias);
      ftk_reco_corrected_d0_bias.push_back(tmp_ftk_reco_corrected_d0_bias);

      // std::cerr << "FTK-Reco matched track in event  " << m_eventNumber << std::endl;
      // std::cerr << "FTK pt: " << tmp_ftk_recoMatch_track_pt  << "  FTK eta: " << tmp_ftk_recoMatch_track_eta  << "  FTK phi: " << tmp_ftk_recoMatch_track_phi  << "  FTK d0: " << tmp_ftk_recoMatch_track_d0  << "  FTK z0: " << tmp_ftk_recoMatch_track_z0 << std::endl;
      // std::cerr << "Reco pt: " << tmp_reco_ftkMatch_track_pt  << "  Reco eta: " << tmp_reco_ftkMatch_track_eta  << "  Reco phi: " << tmp_reco_ftkMatch_track_phi  << "  Reco d0: " << tmp_reco_ftkMatch_track_d0  << "  Reco z0: " << tmp_reco_ftkMatch_track_z0 << std::endl;
      // std::cerr << "" << std::endl;

    }
// ************************************************************ RECO_BLS_TEST************************************************************

} // reco track loop
  reco_inclusive_track_n = ireco_inclusive + 1;
  reco_accepted_track_n = ireco_accepted + 1;

    
  // ftk track loops
  iftk_accepted = -1;
  iftk_inclusive = -1;
  // Float_t tmp_ftk_reco_pt_bias = -999;
  // std::cerr << "BRI TEST 5" << std::endl;

// ************************************************************ RECO_BLS_TEST************************************************************

 for (auto track : *ftkTracks){
  // std::cerr << "Found ftk track" << std::endl;
    // int counter = 0;
  if (isAcceptedReco(track)){
        ftk_accepted.push_back(1);
    }else{
      ftk_accepted.push_back(0);
      // continue;
    }
    if (isAcceptedFTKfiducial(track)){
      // ++ counter;
      ++iftk_accepted;
      chi2 = track->auxdata<float>("chiSquared");
      ndof = track->auxdata<float>("numberDoF");

      ftk_accepted_track_hitPattern.push_back(track->hitPattern());
      ftk_accepted_track_pt.push_back(track->pt() / 1000.);
      ftk_accepted_track_eta.push_back(track->eta());

      if (abs(track->eta()) >= 1.5){ftk_accepted_track_eta_endcap.push_back(track->eta());}
      if (abs(track->eta()) <= 1){ftk_accepted_track_eta_barrel.push_back(track->eta());}

      ftk_accepted_track_phi.push_back(track->phi());
      ftk_accepted_track_m.push_back(track->m() / 1000.);
      ftk_accepted_track_theta.push_back(track->theta());
      ftk_accepted_track_d0.push_back(track->auxdata<float>("d0"));
      ftk_accepted_track_corrected_d0.push_back((track->auxdata<float>("d0"))-dx*TMath::Sin(track->phi())+dy*TMath::Cos(track->phi()));
      ftk_accepted_track_z0.push_back(track->auxdata<float>("z0"));
      ftk_accepted_track_qop.push_back(track->qOverP());
      if (chi2 > 100000){ftk_inclusive_track_chi2.push_back(-999);}
      else{ftk_inclusive_track_chi2.push_back(track->auxdata<float>("chiSquared"));}
      if (chi2 > 100000){ftk_accepted_track_chi2.push_back(-999);
        ftk_accepted_track_chi2ndof.push_back(-999);}
      else{ftk_accepted_track_chi2.push_back(track->auxdata<float>("chiSquared"));
        ftk_accepted_track_chi2ndof.push_back(chi2 / ndof);}
      ftk_accepted_track_charge.push_back(track->charge());

      // std::cerr << "Accepted FTK Tracks Found in event " << m_eventNumber << std::endl;
      // std::cerr << "pt: " << (track->pt() / 1000.)  << "  eta: " << (track->eta())  << "  phi: " << (track->phi())  << "  d0: " << track->auxdata<float>("d0")  << "  z0: " << track->auxdata<float>("z0") << std::endl;
      // std::cerr << "" << std::endl;
    }
    ++iftk_inclusive;
    chi2 = track->auxdata<float>("chiSquared");
    ndof = track->auxdata<float>("numberDoF");

    ftk_inclusive_track_hitPattern.push_back(track->hitPattern());
    ftk_inclusive_track_pt.push_back(track->pt() / 1000.);
    ftk_inclusive_track_eta.push_back(track->eta());
    ftk_inclusive_track_phi.push_back(track->phi());
    ftk_inclusive_track_m.push_back(track->m() / 1000.);
    ftk_inclusive_track_theta.push_back(track->theta());
    ftk_inclusive_track_d0.push_back(track->auxdata<float>("d0"));
    ftk_inclusive_track_corrected_d0.push_back((track->auxdata<float>("d0"))-dx*TMath::Sin(track->phi())+dy*TMath::Cos(track->phi()));
    ftk_inclusive_track_z0.push_back(track->auxdata<float>("z0"));
    ftk_inclusive_track_qop.push_back(track->qOverP());

    if (chi2 > 100000){ftk_inclusive_track_chi2.push_back(-999);
      ftk_inclusive_track_chi2ndof.push_back(-999);}
    else{ftk_inclusive_track_chi2.push_back(track->auxdata<float>("chiSquared"));
      ftk_inclusive_track_chi2ndof.push_back(chi2 / ndof);}
    ftk_inclusive_track_charge.push_back(track->charge());
    // std::cerr << track->auxdata<float>("chiSquared") << std::endl;


     // if (isData == true){
     //  std::cerr << "FTK Track Found in event " << m_eventNumber << std::endl;
     //  std::cerr << "pt: " << (track->pt() / 1000.)  << "  eta: " << (track->eta())  << "  phi: " << (track->phi())  << "  d0: " << track->auxdata<float>("d0")  << "  z0: " << track->auxdata<float>("z0") << "  Chi2: " << chi2 << std::endl;
     //  std::cerr << "" << std::endl;

     //  // std::cerr << chi2 << std::endl;
     //  // // if (chi2 == "inf"){std::cerr << "string" << std::endl;}
     //  // if (chi2 > 100000){std::cerr << "inf" << std::endl;}


     // }
} // ftk track loop
// ************************************************************ RECO_BLS_TEST************************************************************

// ************************************************************ RECO_BLS_TEST************************************************************

  ftk_accepted_track_n = iftk_accepted + 1;
  ftk_inclusive_track_n = iftk_inclusive + 1;
  // if (isData == true){
  // if ((m_lb !=136)||(m_lb !=300)||(m_lb !=301)||(m_lb !=278)||(m_lb !=249)||(m_lb !=137)||(m_lb !=199)||(m_lb !=200)||(m_lb !=201)||(m_lb !=202)||(m_lb !=478)){
  // if ((m_lb !=719)){
  //     reco_accepted_track_n = 0;
  //     reco_inclusive_track_n = 0;  
  //     reco_accepted_track_pt.clear();
  //     reco_accepted_track_eta.clear();
  //     reco_accepted_track_phi.clear();
  //     reco_accepted_track_m.clear();
  //     reco_accepted_track_theta.clear();
  //     reco_accepted_track_d0.clear();
  //     reco_accepted_track_z0.clear();
  //     reco_accepted_track_qop.clear();
  //     reco_accepted_track_charge.clear();
  //     reco_accepted_track_chi2.clear();
  //     reco_accepted_track_chi2ndof.clear();
  //     reco_accepted_track_hitPattern.clear();

  //     reco_inclusive_track_pt.clear();
  //     reco_inclusive_track_eta.clear();
  //     reco_inclusive_track_phi.clear();
  //     reco_inclusive_track_m.clear();
  //     reco_inclusive_track_theta.clear();
  //     reco_inclusive_track_d0.clear();
  //     reco_inclusive_track_z0.clear();
  //     reco_inclusive_track_qop.clear();
  //     reco_inclusive_track_charge.clear();
  //     reco_inclusive_track_chi2.clear();
  //     reco_inclusive_track_chi2ndof.clear();
  //     reco_inclusive_track_hitPattern.clear();
  //   }
    // if (ftk_inclusive_track_n > 1){std::cerr << m_lb << std::endl;}
  // }
  // ftk refit track loops
  iftk_refit_inclusive = -1;
  iftk_refit_accepted = -1;
  

    // Float_t tmp_reco_pt = -999;
    // Float_t tmp_ftk_pt = 999;

    
      // if (tmp_ftk_refit_reco_pt_bias != (-999-999)){tmp_ftk_refit_reco_pt_bias = (tmp_ftk_pt - tmp_reco_pt);}
    
     
    for (auto track : *ftkRefitTracks) {

    if (isAcceptedReco(track)){
      ftk_refit_accepted.push_back(1);
    }
    else{
      ftk_refit_accepted.push_back(0);
      // continue;
    }
    if(isAcceptedFTKfiducial(track)){
      ++iftk_refit_accepted;

      chi2 = track->auxdata<float>("chiSquared");
      ndof = track->auxdata<float>("numberDoF");

      ftk_refit_accepted_track_hitPattern.push_back(track->hitPattern());
      // std::cerr << "hit pattern for refit:  " << track->hitPattern() << std::endl;
      ftk_refit_accepted_track_pt.push_back(track->pt() / 1000.);
      ftk_refit_accepted_track_eta.push_back(track->eta());
      
      if (abs(track->eta()) >= 1.5){ftk_refit_accepted_track_eta_endcap.push_back(track->eta());}
      if (abs(track->eta()) <= 1){ftk_refit_accepted_track_eta_barrel.push_back(track->eta());}


      ftk_refit_accepted_track_phi.push_back(track->phi());
      ftk_refit_accepted_track_m.push_back(track->m() / 1000.);
      ftk_refit_accepted_track_theta.push_back(track->theta());
      ftk_refit_accepted_track_d0.push_back(track->auxdata<float>("d0"));
      ftk_refit_accepted_track_z0.push_back(track->auxdata<float>("z0"));
      ftk_refit_accepted_track_qop.push_back(track->qOverP());
      ftk_refit_accepted_track_chi2.push_back(chi2);
      ftk_refit_accepted_track_chi2ndof.push_back(chi2 / ndof);
      ftk_refit_accepted_track_charge.push_back(track->charge());
    }
    ++iftk_refit_inclusive;
    chi2 = track->auxdata<float>("chiSquared");
    ndof = track->auxdata<float>("numberDoF");

    ftk_refit_inclusive_track_hitPattern.push_back(track->hitPattern());

    

    ftk_refit_inclusive_track_pt.push_back(track->pt() / 1000.);
    ftk_refit_inclusive_track_eta.push_back(track->eta());
    ftk_refit_inclusive_track_phi.push_back(track->phi());
    ftk_refit_inclusive_track_m.push_back(track->m() / 1000.);
    ftk_refit_inclusive_track_theta.push_back(track->theta());
    ftk_refit_inclusive_track_d0.push_back(track->auxdata<float>("d0"));
    ftk_refit_inclusive_track_z0.push_back(track->auxdata<float>("z0"));
    ftk_refit_inclusive_track_qop.push_back(track->qOverP());
    ftk_refit_inclusive_track_chi2.push_back(chi2);
    ftk_refit_inclusive_track_chi2ndof.push_back(chi2 / ndof);
    ftk_refit_inclusive_track_charge.push_back(track->charge());
    // if (isData == true){
    //   std::cerr << "FTK Refit Track Found in event " << m_eventNumber << std::endl;
    //   std::cerr << "pt: " << (track->pt() / 1000.)  << "  eta: " << (track->eta())  << "  phi: " << (track->phi())  << "  d0: " << track->auxdata<float>("d0")  << "  z0: " << track->auxdata<float>("z0") << "  Chi2: " << chi2 << std::endl;
    //   std::cerr << "" << std::endl;}
    
  } // refit ftk track loop
  ftk_refit_accepted_track_n = iftk_refit_accepted + 1;
  ftk_refit_inclusive_track_n = iftk_refit_inclusive + 1;
  reco_ftkMatch_track_n = reco_ftkMatch;
  reco_ftkrefitMatch_track_n = reco_ftkrefitMatch;
  // std::cout<<"BLS 1 finished execute"<<std::endl;
// ************************************************************ RECO_BLS_TEST************************************************************


// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************

// Float_t ftk_ftkR_deltaR = dRval;
// if (isData == true){
//  for (auto track : *ftkTracks){
//   Int_t ftk_ftkR_dR_Flag = 0;
//   for (auto refittrack : *ftkRefitTracks){
//     Float_t ftk_ftkR_deta;
//     Float_t ftk_ftkR_dphi;
//     Float_t ftk_ftkR_temp_dR = 100;
//     ftk_ftkR_deta = (track->eta() - refittrack->eta());
//     ftk_ftkR_dphi = (track->phi() - refittrack->phi());
//     if(abs(ftk_ftkR_dphi) > TMath::Pi()) ftk_ftkR_dphi = 2 * TMath::Pi() - abs(ftk_ftkR_dphi);
//     ftk_ftkR_temp_dR = (sqrt(pow((ftk_ftkR_deta), 2) + pow(ftk_ftkR_dphi, 2)));
//     if (ftk_ftkR_temp_dR > ftk_ftkR_deltaR){
//       ftk_ftkR_deltaR = ftk_ftkR_temp_dR;
//       ftk_ftkR_dR_Flag = 1;
//     }

//   }
//  }
//    if (ftk_ftkR_dR_Flag == 1){
//     ftk_ftkrefit_deltaR.push_back(ftk_ftkR_deltaR);
//   }
// }

// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************



  tree->Fill();
  return EL::StatusCode::SUCCESS;
// };
}



EL::StatusCode FTKxAODAnalysis :: postExecute ()
{
  // std::cout<<"BLS 2 finished postExecute"<<std::endl;

  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKxAODAnalysis :: finalize ()
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


void FTKxAODAnalysis::ResetVariables()
{

  truth_track_pt.clear();
  truth_track_eta.clear();
  truth_track_phi.clear();
  truth_track_m.clear();
  truth_track_theta.clear();
  truth_track_d0.clear();
  truth_track_z0.clear();
  truth_track_z0st.clear();
  truth_track_qop.clear();
  truth_track_charge.clear();
  truth_track_pdgid.clear();
  truth_track_parent_pdgid.clear();
  truth_track_status.clear();
  truth_track_barcode.clear();
  truth_track_prod_perp.clear();
  truth_track_reco_match_prob.clear();
  truth_track_ftk_match_prob.clear();
  truth_track_ftk_refit_match_prob.clear();
  truth_track_reco_match.clear();
  truth_track_ftk_match.clear();
  truth_track_ftk_refit_match.clear();
  truth_track_ftk_match.clear();
  truth_track_ftk_refit_match.clear();
  truth_accepted.clear();

  // muonRoI_eta.clear();
  // muonRoI_phi.clear();
  // muonRoI_roiWord.clear();
  // muonRoI_thrValue.clear();

  reco_accepted_track_pt.clear();
  reco_accepted_track_eta.clear();
  reco_accepted_track_phi.clear();
  reco_accepted_track_m.clear();
  reco_accepted_track_theta.clear();
  reco_accepted_track_d0.clear();
  reco_accepted_track_z0.clear();
  reco_accepted_track_qop.clear();
  reco_accepted_track_charge.clear();
  reco_accepted_track_chi2.clear();
  reco_accepted_track_chi2ndof.clear();
  reco_accepted_track_hitPattern.clear();

  reco_inclusive_track_pt.clear();
  reco_inclusive_track_eta.clear();
  reco_inclusive_track_phi.clear();
  reco_inclusive_track_m.clear();
  reco_inclusive_track_theta.clear();
  reco_inclusive_track_d0.clear();
  reco_inclusive_track_z0.clear();
  reco_inclusive_track_qop.clear();
  reco_inclusive_track_charge.clear();
  reco_inclusive_track_chi2.clear();
  reco_inclusive_track_chi2ndof.clear();
  reco_inclusive_track_hitPattern.clear();

  reco_accepted.clear();
  reco_accepted_FTKTDR.clear();
  reco_muon_accepted.clear();
  reco_ftk_fiducial.clear();

  ftk_accepted_track_pt.clear();
  ftk_accepted_track_eta.clear();
  ftk_accepted_track_phi.clear();
  ftk_accepted_track_m.clear();
  ftk_accepted_track_theta.clear();
  ftk_accepted_track_d0.clear();
  ftk_accepted_track_corrected_d0.clear();
  ftk_accepted_track_z0.clear();
  ftk_accepted_track_qop.clear();
  ftk_accepted_track_charge.clear();
  ftk_accepted_track_chi2ndof.clear();
  ftk_accepted_track_chi2.clear();
  ftk_accepted_track_hitPattern.clear();

  ftk_inclusive_track_pt.clear();
  ftk_inclusive_track_eta.clear();
  ftk_inclusive_track_phi.clear();
  ftk_inclusive_track_m.clear();
  ftk_inclusive_track_theta.clear();
  ftk_inclusive_track_d0.clear();
  ftk_inclusive_track_corrected_d0.clear();
  ftk_inclusive_track_z0.clear();
  ftk_inclusive_track_qop.clear();
  ftk_inclusive_track_charge.clear();
  ftk_inclusive_track_chi2ndof.clear();
  ftk_inclusive_track_chi2.clear();
  ftk_inclusive_track_hitPattern.clear();

  ftk_refit_accepted_track_pt.clear();
  ftk_refit_accepted_track_eta.clear();
  ftk_refit_accepted_track_phi.clear();
  ftk_refit_accepted_track_m.clear();
  ftk_refit_accepted_track_theta.clear();
  ftk_refit_accepted_track_d0.clear();
  ftk_refit_accepted_track_z0.clear();
  ftk_refit_accepted_track_qop.clear();
  ftk_refit_accepted_track_charge.clear();
  ftk_refit_accepted_track_chi2ndof.clear();
  ftk_refit_accepted_track_chi2.clear();
  ftk_refit_accepted_track_hitPattern.clear();

  ftk_refit_inclusive_track_pt.clear();
  ftk_refit_inclusive_track_eta.clear();
  ftk_refit_inclusive_track_phi.clear();
  ftk_refit_inclusive_track_m.clear();
  ftk_refit_inclusive_track_theta.clear();
  ftk_refit_inclusive_track_d0.clear();
  ftk_refit_inclusive_track_z0.clear();
  ftk_refit_inclusive_track_qop.clear();
  ftk_refit_inclusive_track_charge.clear();
  ftk_refit_inclusive_track_chi2ndof.clear();
  ftk_refit_inclusive_track_chi2.clear();
  ftk_refit_inclusive_track_hitPattern.clear();


  ftk_reco_deltaR.clear();
  truth_reco_deltaR.clear();
  ftk_truth_deltaR.clear();
  ftk_refit_truth_deltaR.clear();
  ftk_refit_reco_deltaR.clear();
  ftk_refit_reco_deltaR.clear();

  ftk_reco_pt_bias.clear();
  ftk_refit_reco_pt_bias.clear();
  truth_reco_pt_bias.clear();
  ftk_truth_pt_bias.clear();
  ftk_refit_truth_pt_bias.clear();

  ftk_refit_reco_phi_bias.clear();
  ftk_reco_phi_bias.clear();
  ftk_refit_truth_phi_bias.clear();
  ftk_truth_phi_bias.clear();
  truth_reco_phi_bias.clear();

  ftk_refit_reco_eta_bias.clear();
  ftk_reco_eta_bias.clear();
  ftk_refit_truth_eta_bias.clear();
  ftk_truth_eta_bias.clear();
  truth_reco_eta_bias.clear();

  ftk_refit_reco_d0_bias.clear();
  ftk_reco_d0_bias.clear();
  ftk_reco_corrected_d0_bias.clear();
  ftk_refit_truth_d0_bias.clear();
  ftk_truth_d0_bias.clear();
  ftk_truth_corrected_d0_bias.clear();
  truth_reco_d0_bias.clear();

  ftk_refit_recoMatch_track_eta.clear();
  ftk_refit_recoMatch_track_phi.clear();
  reco_ftkrefitMatch_track_eta.clear();
  reco_ftkrefitMatch_track_phi.clear();
  ftk_refit_recoMatch_track_pt.clear();
  reco_ftkrefitMatch_track_pt.clear();
  reco_ftkrefitMatch_track_d0.clear();
  reco_ftkrefitMatch_track_z0.clear();

  ftk_recoMatch_track_eta.clear();
  ftk_recoMatch_track_phi.clear();
  reco_ftkMatch_track_eta.clear();
  reco_ftkMatch_track_phi.clear();
  ftk_recoMatch_track_pt.clear();
  reco_ftkMatch_track_pt.clear();
  reco_ftkMatch_track_d0.clear();
  // reco_ftkMatch_track_corrected_d0.clear();
  reco_ftkMatch_track_z0.clear();

  ftk_refit_truthMatch_track_eta.clear();
  ftk_refit_truthMatch_track_phi.clear();
  truth_ftkrefitMatch_track_eta.clear();
  truth_ftkrefitMatch_track_phi.clear();
  ftk_refit_truthMatch_track_pt.clear();
  truth_ftkrefitMatch_track_pt.clear();
  truth_ftkrefitMatch_track_d0.clear();
  truth_ftkrefitMatch_track_z0.clear();

  ftk_truthMatch_track_eta.clear();
  ftk_truthMatch_track_phi.clear();
  truth_ftkMatch_track_eta.clear();
  truth_ftkMatch_track_phi.clear();
  ftk_truthMatch_track_pt.clear();
  truth_ftkMatch_track_pt.clear();
  truth_ftkMatch_track_d0.clear();
  // truth_ftkMatch_track_corrected_d0.clear();
  truth_ftkMatch_track_z0.clear();

  truth_recoMatch_track_eta.clear();
  truth_recoMatch_track_phi.clear();
  reco_truthMatch_track_eta.clear();
  reco_truthMatch_track_phi.clear();
  truth_recoMatch_track_pt.clear();
  reco_truthMatch_track_pt.clear();
  truth_recoMatch_track_d0.clear();
  truth_recoMatch_track_z0.clear();

  ftk_accepted.clear();
  ftk_refit_accepted.clear();


}

EL::StatusCode FTKxAODAnalysis :: histFinalize ()
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


Float_t FTKxAODAnalysis::calc_delta_R(Float_t eta1, Float_t eta2, Float_t phi1, Float_t phi2){

  Float_t deta = 0;
  Float_t dphi = 0;
  Float_t dR = 0;
  
  deta = eta1 - eta2;
  dphi = phi1 - phi2;
  if(abs(dphi) > TMath::Pi()) dphi = 2 * TMath::Pi() - abs(dphi);

  dR = sqrt(pow(deta, 2) + pow(dphi, 2));
  return dR;

}



