///////////////////////////////////////////
// Tool based on https://gitlab.cern.ch/atlas/athena/tree/21.2/PhysicsAnalysis/AnalysisCommon/PMGOverlapRemovalTools/GammaORTools
// Documentation: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/VGammaORTool
// Modified to fit into HGamCore analysis framework 
// Outputs boolean if event falls into defined overlap region
// All info decorated to MxAODs
// @author: brianna.dwyer@cern.ch
///////////////////////////////////////////

// STL include(s):
#include <algorithm>

// EDM include(s):
#include "AsgTools/MsgStream.h"
#include "AsgTools/MsgStreamMacros.h"
#include "AsgTools/AsgTool.h"
#include "AsgTools/AnaToolHandle.h"

// Local include(s):
#include "HGamAnalysisFramework/EventHandler.h"
#include "HGamAnalysisFramework/GammaORTool.h"
#include "HGamAnalysisFramework/JetHandler.h"
#include "HGamAnalysisFramework/ElectronHandler.h"
#include "HGamAnalysisFramework/MuonHandler.h"
#include "HGamAnalysisFramework/TruthHandler.h"
#include "MCTruthClassifier/MCTruthClassifier.h"

typedef std::pair<MCTruthPartClassifier::ParticleType, MCTruthPartClassifier::ParticleOrigin>ClassifierResult;

namespace HG {
  // _______________________________________________________________________________________
  GammaORTool::GammaORTool(const char *name, HG::EventHandler *eventHandler, HG::TruthHandler *truthHandler)
    : asg::AsgMessaging(name)
    , m_eventHandler(eventHandler)
    , m_truthHandler(truthHandler)
    , m_truthClassifier(new MCTruthClassifier("MCTruthClassifier"))
    , m_max_barcode(1e5)
    , m_n_leptons(-2)
    , m_lepton_pdgIds({11, -11, 13, -13, 15, -15})
    , m_lepton_veto_origins({3, 5, 6, 7, 8, 9, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42})
    , m_preferred_lepton_origins({1, 2, 4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21})
    , m_veto_photon_origins({9, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 42})
    , m_photon_pT_cuts(25e3)
    , m_n_photons(1)
    , m_dR_lepton_photon_cut(0.2)
    , m_dR_lepton_photon_cuts({0.0, 0.05, 0.075, 0.1, 0.125, 0.15, 0.2})
    , m_min_considered_photon_pT(3e3)
  {}

  // _______________________________________________________________________________________
  GammaORTool::~GammaORTool()
  {
  }

  // _______________________________________________________________________________________
  HG::EventHandler *GammaORTool::eventHandler()
  {
    return m_eventHandler;
  }

  // _______________________________________________________________________________________
  HG::TruthHandler *GammaORTool::truthHandler()
  {
    return m_truthHandler;
  }

  // _______________________________________________________________________________________
  EL::StatusCode GammaORTool::initialize(Config &config)
  {

    return EL::StatusCode::SUCCESS;
  }


bool GammaORTool::isFromTau(const xAOD::TruthParticle& lepton, int nRecursions) const{
  // avoid being stuck in some weird particle family tree
  if(nRecursions>20){
    return false;
  }
  for(uint i=0; i<lepton.nParents(); i++){
    const xAOD::TruthParticle* parent=lepton.parent(i);
    if(abs(parent->pdgId())==15){
      return true;
    }
    if(parent->pdgId()==lepton.pdgId()){
      return isFromTau(lepton, nRecursions+1);
    }
  }  
  return false;

}

  // _______________________________________________________________________________________
  void GammaORTool::saveGammaORInfo(const xAOD::PhotonContainer &photons,
                              const xAOD::JetContainer   &jets,
                              xAOD::JetContainer   &jetsJVT,
                              const xAOD::MissingETContainer &met,
                              xAOD::MuonContainer &muons,
                              xAOD::ElectronContainer &electrons)
  {
    // --------
    // Maps containing all event info to decorate to MxAOD
    // Floats for all decimal values
    // Chars for all bools
    // Ints for all counters (Category and multiplicities)
    std::map<TString, float> eventInfoFloats;
    std::map<TString, int>   eventInfoInts;


    // Perform selection
    // Save all the eventInfoMaps to the eventHandler()
    // Should always be called last, once all of these have been filled
    saveMapsToEventInfo(eventInfoFloats, eventInfoInts);
  }


  // _______________________________________________________________________________________
  void GammaORTool::saveGammaORTruthInfo(const xAOD::TruthParticleContainer &photons,
                                   const xAOD::JetContainer   &jets,
                                   const xAOD::JetContainer   &bjets,
                                   const xAOD::JetContainer   &cjets,
                                   const xAOD::MissingETContainer &met,
                                   xAOD::TruthParticleContainer &muons,
                                   xAOD::TruthParticleContainer &electrons)
  {
    // --------
    // Maps containing all event info to decorate to MxAOD
    // Floats for all decimal values
    // Chars for all bools
    // Ints for all counters (Category and multiplicities)
    std::map<TString, float> trutheventInfoFloats;
    std::map<TString, int>   trutheventInfoInts;

    // Perform truth selection
    performVGammaOverlapSelection(trutheventInfoInts, trutheventInfoFloats);


    // Save all the eventInfoMaps to the eventHandler()
    // Should always be called last, once all of these have been filled
    saveMapsToTruthEventInfo(trutheventInfoFloats, trutheventInfoInts);
  }


  void GammaORTool::performVGammaOverlapSelection(std::map<TString, int> &eventInfoInts, std::map<TString, float> &eventInfoFloats)
  {
    const xAOD::TruthParticleContainer *truthParticles = m_truthHandler->getTruthParticles();

    std::vector<TLorentzVector> photon_p4s;
    std::vector<int> photon_origins;
    for (const auto& p : *truthParticles) {
      // ATH_MSG_INFO("truth partciles loop");
      // consider only final state photons, not from geant, above a lower pt cut
      if (p->status() != 1 || p->barcode() > m_max_barcode || p->pdgId() != 22 || p->pt() < m_min_considered_photon_pT) {continue;}
      // ATH_MSG_INFO("p->status() " << p->status());
      // ATH_MSG_INFO("p->barcode()" << p->barcode() << " < m_max_barcode " << m_max_barcode);

      // determine photon origin
      static SG::AuxElement::ConstAccessor<ElementLink<xAOD::IParticleContainer> > link("originalObjectLink");
      ClassifierResult res = m_truthClassifier->particleTruthClassifier(p);
      // ATH_MSG_INFO("Photon origin: " << res.second);
      photon_origins.push_back(res.second);
      photon_p4s.push_back(p->p4());
    }

    // if (photon_p4s.size() != photon_origins.size()) {
    //     ATH_MSG_ERROR(BOOST_CURRENT_FUNCTION << ": size of photon candidates (" << photon_p4s.size() << ") different from number of photon origins (" << photon_origins.size() <<").");
    // }

    std::vector<TLorentzVector> photon_candidates;
    for (uint i = 0; i < photon_p4s.size(); i++) {
      TLorentzVector p4 = photon_p4s[i];
      int p_origin = photon_origins[i];
      bool vetoed = std::find(m_veto_photon_origins.begin(), m_veto_photon_origins.end(), p_origin) != m_veto_photon_origins.end();
      if (!vetoed) {
        photon_candidates.push_back(p4);
        // ATH_MSG_INFO("accepted photon candidate with origin " << p_origin);
      }
    }


    //next electrons/muons
    std::vector<const xAOD::TruthParticle*> elmu_candidates;
    for (const auto& l : *truthParticles) {
      // ignore all particles with geant barcodes
      if (l->barcode() > m_max_barcode) {continue;}
      // ignore all particles with the wrong pdgid
      if (std::find(m_lepton_pdgIds.begin(), m_lepton_pdgIds.end(), l->pdgId()) == m_lepton_pdgIds.end()) {continue;}
      if (l->status() == 1 && !isFromTau(*l)) {
        // ATH_MSG_INFO("found elmu_candidates");
        elmu_candidates.push_back(l);
      }
    }
    sort(elmu_candidates.begin(), elmu_candidates.end(),[](const xAOD::TruthParticle*& p1, const xAOD::TruthParticle*& p2) {return p1->pt() > p2->pt();});

    //next taus
    std::vector<const xAOD::TruthParticle*> tau_candidates;
    for (const auto& t : *truthParticles) {
      // ignore all particles with geant barcodes
      if (t->barcode() > m_max_barcode) {continue;}
      // ignore all particles with the wrong pdgid
      if (std::find(m_lepton_pdgIds.begin(), m_lepton_pdgIds.end(), t->pdgId()) == m_lepton_pdgIds.end()) {continue;}
      if (std::abs(t->pdgId()) == 15) {
        bool childIsTau = false;
        bool hasChildren = false;
        // make sure tau has no tau children, i.e. is tau before decay
        for (uint i = 0; i < t->nChildren(); i++) {
          if (t->child(i) == nullptr) continue;
          if (t->child(i)->barcode() == t->barcode()) continue;
          hasChildren = true;
          if (t->child(i)->pdgId() == t->pdgId()) {
            childIsTau = true;
            break;
          }
        }
        if (hasChildren && !childIsTau) {
          tau_candidates.push_back(t);
          // ATH_MSG_INFO("found tau candidates");
        }
      }
    }
    sort(tau_candidates.begin(), tau_candidates.end(),[](const xAOD::TruthParticle*& p1, const xAOD::TruthParticle*& p2) {return p1->pt() > p2->pt();});

    // put taus before other leptons in a vector
    std::vector<const xAOD::TruthParticle*> initial_lepton_candidates(tau_candidates);
    initial_lepton_candidates.insert(initial_lepton_candidates.end(), elmu_candidates.begin(), elmu_candidates.end());

    std::vector<TLorentzVector> lepton_p4s;
    std::vector<int> lepton_origins;

    for (const auto& l : initial_lepton_candidates) {
      static SG::AuxElement::ConstAccessor<ElementLink<xAOD::IParticleContainer> > link("originalObjectLink");
      ClassifierResult res_lepton = m_truthClassifier->particleTruthClassifier(l);
      // // auto res = const_cast<asg::AnaToolHandle<MCTruthClassifier>*>(&m_truthClassifier)->get()->particleTruthClassifier(l);
      lepton_origins.push_back(res_lepton.second);
      lepton_p4s.push_back(l->p4());
    }

    if (lepton_p4s.size() != lepton_origins.size()) {
      ATH_MSG_ERROR(BOOST_CURRENT_FUNCTION << ": size of lepton candidates (" << lepton_p4s.size() << ") different from number of lepton origins (" << lepton_origins.size() <<").");
    }

    std::vector<TLorentzVector> lepton_candidates;
    std::vector<TLorentzVector> lepton_candidates_not_vetoed;

    for (uint i = 0; i < lepton_p4s.size(); i++) {
      const TLorentzVector p4 = lepton_p4s[i];
      const int p_origin = lepton_origins[i];
      const bool use = std::find(m_preferred_lepton_origins.begin(), m_preferred_lepton_origins.end(), p_origin) != m_preferred_lepton_origins.end();
      if (use) {
        lepton_candidates.push_back(p4);
        // ATH_MSG_INFO("accepted lepton with preferred origin " << p_origin);
        if (m_n_leptons>=0 && int(lepton_candidates.size()) >= m_n_leptons) {
          // as soon as enough leptons are found, return them
          // this is why the order of lepton candidates matters
          // if this tool identifies the leptons, taus will be before mu/el and otherwise leptons are ordered by pT
          // in most cases the origin should unambiguosly identify the lepton anyway
          break;
        }
      } else {
        bool vetoed = std::find(m_lepton_veto_origins.begin(), m_lepton_veto_origins.end(), p_origin) != m_lepton_veto_origins.end();
        if (!vetoed) {
          lepton_candidates_not_vetoed.push_back(p4);
          // ATH_MSG_INFO("accepted lepton with origin " << p_origin);
        }
      }
    }

    for (const auto& l : lepton_candidates_not_vetoed) {
      lepton_candidates.push_back(l);
      if (m_n_leptons>=0 && int(lepton_candidates.size()) >= m_n_leptons) {
        break;
      }
    }
    
    // std::vector<float> drCuts = std::vector<float>(1, m_dR_lepton_photon_cut);


    std::map<float, std::vector<float> > photon_pt_map;

    for (const auto& drCut : m_dR_lepton_photon_cuts) {
      // ATH_MSG_INFO("drCut: " << drCut);
      photon_pt_map[drCut] = std::vector<float>();
      for (const auto& photon : photon_candidates) {
        bool tooCloseToLepton = false;
        for (uint i_lep = 0; i_lep < lepton_candidates.size() && (m_n_leptons<0 || int(i_lep) < m_n_leptons); i_lep++) {
          const float dr = photon.DeltaR(lepton_candidates[i_lep]);
          // ATH_MSG_INFO("DR(l,y)  = " << dr);
          if (dr < drCut) {
            tooCloseToLepton = true;
            break;
          }
        }
        if (!tooCloseToLepton) {
          photon_pt_map[drCut].push_back(photon.Pt());
          // ATH_MSG_INFO("accepted photon, check pt: " << photon.Pt());
        }
      }
      // photon pts are sorted and returned
      sort(photon_pt_map[drCut].begin(), photon_pt_map[drCut].end(), std::greater<float>());
    }

    std::vector<float> photon_pts = photon_pt_map[m_dR_lepton_photon_cut];


    // ATH_MSG_INFO("m_photon_pT_cuts.size(): " << m_photon_pT_cuts.size());
    // ATH_MSG_INFO("photon_pts.size(): " << photon_pts.size());


    // ATH_MSG_INFO("m_photon_pT_cuts: " << m_photon_pT_cuts);

    bool inOverlapBool = true;
    // if(m_photon_pT_cuts.size()==0){
    //   ATH_MSG_ERROR("photon_pT_cuts needs to be a non-empty list, when inOverlap is called, set as property or in constructor.");
    //   inOverlapBool = false;
    // }
    if(int(photon_pts.size()) < m_n_photons){
      ATH_MSG_INFO("too few photons");
      inOverlapBool = false;
    }
    else{
      for(uint i=0; i < m_n_photons;i++){
        if(photon_pts[i] < m_photon_pT_cuts){
          ATH_MSG_INFO("Photon PT too low at " << photon_pts[i] * 0.001 << "  so inOverlapBool = false");
          inOverlapBool = false;
        }
        else{
          ATH_MSG_INFO("Photon PT okay at " << photon_pts[i] * 0.001 << "  so inOverlapBool = true");
        }
      } 
    }

    
    ATH_MSG_INFO("final inOverlapBool: " << inOverlapBool);

    eventInfoInts["GammaOR_inOverlap"] = inOverlapBool;
  }


  // _______________________________________________________________________________________
  // Save event info from maps to eventInfo
  void GammaORTool::saveMapsToEventInfo(std::map<TString, float> &eventInfoFloats, std::map<TString, int> &eventInfoInts)
  {
    // Floats
    for (auto element : eventInfoFloats) {
      eventHandler()->storeVar<float>(element.first.Data(), element.second);
    }

    // Ints
    for (auto element : eventInfoInts) {
      eventHandler()->storeVar<int>(element.first.Data(), element.second);
    }
  }

  // _______________________________________________________________________________________
  // Save event info from maps to eventInfo
  void GammaORTool::saveMapsToTruthEventInfo(std::map<TString, float> &eventInfoFloats, std::map<TString, int> &eventInfoInts)
  {
    // Floats
    for (auto element : eventInfoFloats) {
      eventHandler()->storeTruthVar<float>(element.first.Data(), element.second);
    }

    // Ints
    for (auto element : eventInfoInts) {
      eventHandler()->storeTruthVar<int>(element.first.Data(), element.second);
    }
  }
}
