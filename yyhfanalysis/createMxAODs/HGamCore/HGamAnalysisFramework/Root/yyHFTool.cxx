///////////////////////////////////////////
// yy+HF Tool
// Perform preselection and calculate variables
// All info decorated to MxAODs
// @author: jahred.adelman@cern.ch
///////////////////////////////////////////

// STL include(s):
#include <algorithm>

// EDM include(s):
#include "AsgTools/MsgStream.h"
#include "AsgTools/MsgStreamMacros.h"

// Local include(s):
#include "HGamAnalysisFramework/EventHandler.h"
#include "HGamAnalysisFramework/yyHFTool.h"
#include "HGamAnalysisFramework/JetHandler.h"
#include "HGamAnalysisFramework/ElectronHandler.h"
#include "HGamAnalysisFramework/MuonHandler.h"
#include "HGamAnalysisFramework/TruthHandler.h"


namespace HG {
  // _______________________________________________________________________________________
  yyHFTool::yyHFTool(const char *name, HG::EventHandler *eventHandler, HG::TruthHandler *truthHandler)
    : asg::AsgMessaging(name)
    , m_eventHandler(eventHandler)
    , m_truthHandler(truthHandler)
    , m_minMuonPT(10)
    , m_minElectronPT(10)
    , m_centraljet_eta_max(2.5)
    , m_truthjet_rapidity_max(2.5)
    , m_centraljet_pt_min(25)
  {}

  // _______________________________________________________________________________________
  yyHFTool::~yyHFTool()
  {
  }

  // _______________________________________________________________________________________
  HG::EventHandler *yyHFTool::eventHandler()
  {
    return m_eventHandler;
  }

  // _______________________________________________________________________________________
  HG::TruthHandler *yyHFTool::truthHandler()
  {
    return m_truthHandler;
  }

  // _______________________________________________________________________________________
  EL::StatusCode yyHFTool::initialize(Config &config)
  {
    // Set default cut values etc here...
    // Almost all of these are set hard-coded because this will be used by the nominal MxAOD production

    m_minMuonPT = config.getNum("yyHFTool.MinMuonPt", 10.0); //! minimum muon pt (in GeV) for lepton veto
    ATH_MSG_INFO("MinMuonPt.................................. " << m_minMuonPT);

    m_minElectronPT = config.getNum("yyHFTool.MinElectronPt", 10.0); //! minimum electron pt (in GeV) for lepton veto
    ATH_MSG_INFO("MinElectronPt.............................. " << m_minElectronPT);

    m_centraljet_eta_max = config.getNum("yyHFTool.MaxCentralJetEta", 2.5); //! Max central jet abs eta
    ATH_MSG_INFO("MaxCentralJetEta........................... " << m_centraljet_eta_max);

    m_centraljet_pt_min = config.getNum("yyHFTool.MinCentralJetPt", 25); //! Min central jet abs pt
    ATH_MSG_INFO("MinCentralJetPt........................... " << m_centraljet_pt_min);

    return EL::StatusCode::SUCCESS;
  }


  // _______________________________________________________________________________________
  void yyHFTool::saveyyHFInfo(const xAOD::PhotonContainer &photons,
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
    performSelection(photons, jets, jetsJVT, met, muons, electrons,
                     eventInfoFloats, eventInfoInts);


    // Save all the eventInfoMaps to the eventHandler()
    // Should always be called last, once all of these have been filled
    saveMapsToEventInfo(eventInfoFloats, eventInfoInts);
  }


  // _______________________________________________________________________________________
  void yyHFTool::saveyyHFTruthInfo(const xAOD::TruthParticleContainer &photons,
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
    performTruthSelection(photons, jets, bjets, cjets, met, muons, electrons, trutheventInfoInts, trutheventInfoFloats);

    // Save all the eventInfoMaps to the eventHandler()
    // Should always be called last, once all of these have been filled
    saveMapsToTruthEventInfo(trutheventInfoFloats, trutheventInfoInts);
  }

  // _______________________________________________________________________________________
  // Function which performs full HiggsHF truth selection and saves info to info maps (nominal by default)
  void yyHFTool::performTruthSelection(const xAOD::TruthParticleContainer &photons,
                                       const xAOD::JetContainer   &jets,
                                       const xAOD::JetContainer   &bjets,
                                       const xAOD::JetContainer   &cjets,
                                       const xAOD::MissingETContainer &met,
                                       xAOD::TruthParticleContainer &muons,
                                       xAOD::TruthParticleContainer &electrons,
                                       std::map<TString, int> &eventInfoInts, std::map<TString, float> &eventInfoFloats)
  {

    // First apply photon selection
    //if (photons.size() < 2) {
    if (!truthHandler()->passFiducial(&photons)) {
      eventInfoInts["yyHF_cutFlow"] = PHOTONS;
      return;
    }

    TLorentzVector yy_true = photons[0]->p4() + photons[1]->p4();

    if (yy_true.M() < 105 * HG::GeV) {
      eventInfoInts["yyHF_cutFlow"] = MYY;
      return;
    }

    // if (yy_true.M() > 120 * HG::GeV && yy_true.M() < 130 * HG::GeV) {
    //   eventInfoInts["yyHF_cutFlow"] = MYY;
    //   return;
    // }

    // Next apply lepton selection, but not veto
    xAOD::TruthParticleContainer muonsPassing(SG::VIEW_ELEMENTS);

    // Apply muon requirements
    std::copy_if(muons.begin(), muons.end(), std::back_inserter(muonsPassing), [this](const xAOD::TruthParticle * muon) {
      return (muon->pt() >= m_minMuonPT * HG::GeV);
    });


    xAOD::TruthParticleContainer electronsPassing(SG::VIEW_ELEMENTS);

    // Apply electron requirements
    std::copy_if(electrons.begin(), electrons.end(), std::back_inserter(electronsPassing), [this](const xAOD::TruthParticle * electron) {
      return (electron->pt() >= m_minElectronPT * HG::GeV);
    });

    // Number of central jets
    int Njet_central = 0;
    int Njet_b = 0;
    int Njet_c = 0;

    //Save TLorentzVectors
    std::vector<TLorentzVector> central_jets;
    std::vector<TLorentzVector> sel_bjets;
    std::vector<TLorentzVector> sel_cjets;

    //Loop over jets
    for (auto jet : jets) {
      if (fabs(jet->eta()) > m_truthjet_rapidity_max || jet->pt() < m_centraljet_pt_min * HG::GeV) { continue; }

      Njet_central++;
      TLorentzVector jet_tmp = jet->p4();
      central_jets.push_back(jet_tmp);
    }

    //Loop over bjets
    for (auto bjet : bjets) {
      if (fabs(bjet->eta()) > m_truthjet_rapidity_max || bjet->pt() < m_centraljet_pt_min * HG::GeV) { continue; }

      Njet_b++;
      TLorentzVector bjet_tmp = bjet->p4();
      sel_bjets.push_back(bjet_tmp);
    }

    //Loop over cjets, reject jets that are already matched to a b-jet
    for (auto cjet : cjets) {
      if (fabs(cjet->eta()) > m_truthjet_rapidity_max || cjet->pt() < m_centraljet_pt_min * HG::GeV) { continue; }

      TLorentzVector cjet_tmp = cjet->p4();

      for (unsigned int i_jet = 0; i_jet < sel_bjets.size(); i_jet++) {
        if (cjet_tmp == sel_bjets[i_jet]) { continue; }
      }

      sel_cjets.push_back(cjet_tmp);
      Njet_c++;
    }

    // Minimum requirement on the number of truth jets
    if (Njet_central == 0) { eventInfoInts["yyHF_cutFlow"] = CENJET_MIN; return;}

    // Save events that pass all requirements
    eventInfoInts["yyHF_cutFlow"] = PASS;
    eventInfoInts["yyHF_N_bjets"] = Njet_b;
    eventInfoInts["yyHF_N_cjets"] = Njet_c;

    if (Njet_b >= 2) { eventInfoInts["yyHF_jjcat"] = BB; }
    else if (Njet_b == 1 && Njet_c >= 1) { eventInfoInts["yyHF_jjcat"] = BC; }
    else if (Njet_b == 1 && Njet_central >= 2) { eventInfoInts["yyHF_jjcat"] = BL; }
    else if (Njet_c >= 2) { eventInfoInts["yyHF_jjcat"] = CC; }
    else if (Njet_c == 1 && Njet_central >= 2) { eventInfoInts["yyHF_jjcat"] = CL; }
    else if (Njet_central >= 2) { eventInfoInts["yyHF_jjcat"] = LL; }
    else { eventInfoInts["yyHF_jjcat"] = NOTTWOJETS; }

    if (Njet_b >= 1) { eventInfoInts["yyHF_jcat"] = B; }
    else if (Njet_c >= 1) { eventInfoInts["yyHF_jcat"] = C; }
    else { eventInfoInts["yyHF_jcat"] = L; }

    // MET and lepton cuts are not made but are saved here instead
    eventInfoInts["yyHF_nelectron"] = electronsPassing.size();
    eventInfoInts["yyHF_nmuon"] = muonsPassing.size();

    //    xAOD::MissingET *metFinalInt = *(met.find("Int"));
    xAOD::MissingET *metFinalNonInt = *(met.find("NonInt"));
    //    double metx = metFinalInt->mpx() + metFinalNonInt->mpx();
    //    double mety = metFinalInt->mpy() + metFinalNonInt->mpy();
    //    std::cerr << "JAAA mpx int = " << metFinalInt->mpx() << " and nonint = " << metFinalNonInt->mpx() << std::endl;
    //    eventInfoFloats["yyHF_met"] = sqrt(metx*metx + mety*mety);
    eventInfoFloats["yyHF_met"] = metFinalNonInt->met();
    eventInfoInts["yyHF_Njet_central"] = Njet_central;
  }

  // _______________________________________________________________________________________
  // Function which performs full yyHF selection and saves info to info maps (nominal by default)
  void yyHFTool::performSelection(const xAOD::PhotonContainer &photons,
                                  const xAOD::JetContainer &jets,
                                  xAOD::JetContainer &jets_noJVT,
                                  const xAOD::MissingETContainer &met,
                                  xAOD::MuonContainer &muons,
                                  xAOD::ElectronContainer &electrons,
                                  std::map<TString, float> &eventInfoFloats,
                                  std::map<TString, int> &eventInfoInts)
  {

    // First apply photon selection
    if (photons.size() < 2) {
      eventInfoInts["yyHF_cutFlow"] = PHOTONS;
      return;
    }

    TLorentzVector yy = photons[0]->p4() + photons[1]->p4();

    if (yy.M() < 105 * HG::GeV) {
      eventInfoInts["yyHF_cutFlow"] = MYY;
      return;
    }

    // if (yy.M() > 120 * HG::GeV && yy.M() < 130 * HG::GeV) {
    //   eventInfoInts["yyHF_cutFlow"] = MYY;
    //   return;
    // }


    // Next apply lepton selection, but don't veto
    xAOD::MuonContainer muonsPassing(SG::VIEW_ELEMENTS);

    // Apply muon requirements
    std::copy_if(muons.begin(), muons.end(), std::back_inserter(muonsPassing), [this](const xAOD::Muon * muon) {
      return (muon->pt() >= m_minMuonPT * HG::GeV);
    });


    xAOD::ElectronContainer electronsPassing(SG::VIEW_ELEMENTS);

    // Apply electron requirements
    std::copy_if(electrons.begin(), electrons.end(), std::back_inserter(electronsPassing), [this](const xAOD::Electron * electron) {
      return (electron->pt() >= m_minElectronPT * HG::GeV);
    });


    // Number of central jets
    int Njet_central = 0;

    // Save four-vectors of leading & subleading (pt) jet
    TLorentzVector LeadJet;
    LeadJet.SetPtEtaPhiM(0, 0, 0, 0);
    TLorentzVector SubleadJet;
    SubleadJet.SetPtEtaPhiM(0, 0, 0, 0);

    // Save b-tagging weights for leading & subleading jet
    double LeadJetWeight = -999;
    double SubleadJetWeight = -999;

    // Save b-tagging bin for leading & subleading jet
    int LeadJet_btagbin = -999;
    int SubleadJet_btagbin = -999;

    // Save truth label of leading & subleading jet
    int LeadJet_truthlabel = -999;
    int SubleadJet_truthlabel = -999;


    //Loop over jets
    for (auto jet : jets) {
      if (fabs(jet->eta()) > m_centraljet_eta_max || jet->pt() < m_centraljet_pt_min * HG::GeV) { continue; }

      Njet_central++;

      TLorentzVector jet_tmp = jet->p4();

      if (jet_tmp.Pt() > LeadJet.Pt()) {
        SubleadJet = LeadJet;
        LeadJet = jet_tmp;

        SubleadJet_truthlabel = LeadJet_truthlabel;
        LeadJet_truthlabel = HG::isMC() ? jet->auxdata<int>("HadronConeExclTruthLabelID") : -99;

        SubleadJetWeight = LeadJetWeight;
        LeadJetWeight = jet->auxdata<float>("SF_DL1r_Continuous");

        SubleadJet_btagbin = LeadJet_btagbin;

        if (jet->auxdata<char>("DL1r_FixedCutBEff_60")) { LeadJet_btagbin = 4; }
        else if (jet->auxdata<char>("DL1r_FixedCutBEff_70")) { LeadJet_btagbin = 3; }
        else if (jet->auxdata<char>("DL1r_FixedCutBEff_77")) { LeadJet_btagbin = 2; }
        else if (jet->auxdata<char>("DL1r_FixedCutBEff_85")) { LeadJet_btagbin = 1; }
        else { LeadJet_btagbin = 0; }
      } else if (jet_tmp.Pt() > SubleadJet.Pt()) {
        SubleadJet = jet_tmp;
        SubleadJet_truthlabel = HG::isMC() ? jet->auxdata<int>("HadronConeExclTruthLabelID") : -99;
        SubleadJetWeight = jet->auxdata<float>("SF_DL1r_Continuous");

        if (jet->auxdata<char>("DL1r_FixedCutBEff_60")) { SubleadJet_btagbin = 4; }
        else if (jet->auxdata<char>("DL1r_FixedCutBEff_70")) { SubleadJet_btagbin = 3; }
        else if (jet->auxdata<char>("DL1r_FixedCutBEff_77")) { SubleadJet_btagbin = 2; }
        else if (jet->auxdata<char>("DL1r_FixedCutBEff_85")) { SubleadJet_btagbin = 1; }
        else { SubleadJet_btagbin = 0; }
      }
    }

    // Minimum requirement on the number of central jets
    if (Njet_central == 0) { eventInfoInts["yyHF_cutFlow"] = CENJET_MIN; return;}

    // Save events that pass all requirements
    eventInfoInts["yyHF_cutFlow"] = PASS;

    // Calculate the JVT scale-factor from uncorrected, no-JVT jets
    double weight_JVT = weightJVT(jets_noJVT);

    // Get yyHF weight from JVT and b-tagging
    eventInfoFloats["yyHFjj_weight"] = weight_JVT * SubleadJetWeight * LeadJetWeight;
    eventInfoFloats["yyHFj_weight"] = weight_JVT * LeadJetWeight;

    // MET and lepton cuts are not made but are saved here instead
    eventInfoInts["yyHF_nelectron"] = electronsPassing.size();
    eventInfoInts["yyHF_nmuon"] = muonsPassing.size();
    xAOD::MissingET *metFinal = *(met.find("TST"));
    eventInfoFloats["yyHF_met"] = metFinal->met();

    eventInfoInts["yyHF_leadjet_btagbin"] = LeadJet_btagbin;
    eventInfoInts["yyHF_subleadjet_btagbin"] = SubleadJet_btagbin;

    eventInfoFloats["yyHF_leadjet_pt"] = LeadJet.Pt();
    eventInfoFloats["yyHF_subleadjet_pt"] = SubleadJet.Pt();
    eventInfoFloats["yyHF_leadjet_eta"] = LeadJet.Eta();
    eventInfoFloats["yyHF_subleadjet_eta"] = SubleadJet.Eta();
    eventInfoFloats["yyHF_leadjet_phi"] = LeadJet.Phi();
    eventInfoFloats["yyHF_subleadjet_phi"] = SubleadJet.Phi();
    eventInfoFloats["yyHF_leadjet_m"] = LeadJet.M();
    eventInfoFloats["yyHF_subleadjet_m"] = SubleadJet.M();

    eventInfoInts["yyHF_leadjet_truthlabel"] = LeadJet_truthlabel;
    eventInfoInts["yyHF_subleadjet_truthlabel"] = SubleadJet_truthlabel;
    eventInfoInts["yyHF_Njet_central"] = Njet_central;


  }

  // ___________________________________________________________________________________________
  // Multiply all the JVT (in)efficiencies for all jets passing the selection before the JVT cut
  double yyHFTool::weightJVT(xAOD::JetContainer &jets_noJVT)
  {

    // Construct output jet container
    xAOD::JetContainer jets_noJVT_passing_cuts(SG::VIEW_ELEMENTS);

    // Apply central jet requirement (for b-tagging reasons) and appropriate pT cuts
    for (auto jet : jets_noJVT) {
      if (fabs(jet->eta()) > m_centraljet_eta_max) { continue; }

      if (jet->pt() < m_centraljet_pt_min * HG::GeV) { continue; }

      jets_noJVT_passing_cuts.push_back(jet);
    }

    // Return multiplicative combination of JVT efficiencies
    if (jets_noJVT_passing_cuts.size() > 0) {
      return HG::JetHandler::multiplyJvtWeights(&jets_noJVT_passing_cuts);
    }

    return 1.0;
  }


  // _______________________________________________________________________________________
  // Save event info from maps to eventInfo
  void yyHFTool::saveMapsToEventInfo(std::map<TString, float> &eventInfoFloats, std::map<TString, int> &eventInfoInts)
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
  void yyHFTool::saveMapsToTruthEventInfo(std::map<TString, float> &eventInfoFloats, std::map<TString, int> &eventInfoInts)
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
