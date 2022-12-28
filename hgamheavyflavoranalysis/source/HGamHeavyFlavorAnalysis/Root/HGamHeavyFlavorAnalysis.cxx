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

  my_cutflow_hist_unweighted = new TH1F("my_cutflow_hist_unweighted", "my_cutflow_hist_unweighted",6,0,6);
  my_cutflow_hist_unweighted->GetXaxis()->SetBinLabel(1, "NEvents");
  my_cutflow_hist_unweighted->GetXaxis()->SetBinLabel(2, "isPassed");
  my_cutflow_hist_unweighted->GetXaxis()->SetBinLabel(3, "2 photons");
  my_cutflow_hist_unweighted->GetXaxis()->SetBinLabel(4, "electron veto");
  my_cutflow_hist_unweighted->GetXaxis()->SetBinLabel(5, "muon veto");
  my_cutflow_hist_unweighted->GetXaxis()->SetBinLabel(6, "central jets");

  my_cutflow_hist = new TH1F("my_cutflow_hist", "my_cutflow_hist",6,0,6);
  my_cutflow_hist->GetXaxis()->SetBinLabel(1, "NEvents");
  my_cutflow_hist->GetXaxis()->SetBinLabel(2, "isPassed");
  my_cutflow_hist->GetXaxis()->SetBinLabel(3, "2 photons");
  my_cutflow_hist->GetXaxis()->SetBinLabel(4, "electron veto");
  my_cutflow_hist->GetXaxis()->SetBinLabel(5, "muon veto");
  my_cutflow_hist->GetXaxis()->SetBinLabel(6, "central jets");

  hist_LeadDL1Jet_btagbin = new TH1F("hist_LeadDL1Jet_btagbin", "hist_LeadDL1Jet_btagbin;;Events", 5, 0, 5);
  hist_LeadDL1Jet_truthlabel = new TH1F("hist_LeadDL1Jet_truthlabel", "hist_LeadDL1Jet_truthlabel;;Events", 37, 0, 37);
  hist_btagbin_truthjet = new TH2F("hist_btagbin_truthjet", "hist_btagbin_truthjet;B-Tag Category;Jet Truth Label", 3, 0, 3, 3, 0, 3);
  hist_btagbin_truthevent = new TH2F("hist_btagbin_truthevent", "hist_btagbin_truthevent;B-Tag Category;Event Truth Label", 3, 0, 3, 3, 0, 3);

  hist_btagbin_truthjet->GetXaxis()->SetBinLabel(1, "untagged");
  hist_btagbin_truthjet->GetXaxis()->SetBinLabel(2, "77 WP");
  hist_btagbin_truthjet->GetXaxis()->SetBinLabel(3, "70/60 WP");

  hist_btagbin_truthjet->GetYaxis()->SetBinLabel(1, "non-H.F.");
  hist_btagbin_truthjet->GetYaxis()->SetBinLabel(2, "c");
  hist_btagbin_truthjet->GetYaxis()->SetBinLabel(3, "b");

  hist_btagbin_truthevent->GetXaxis()->SetBinLabel(1, "untagged");
  hist_btagbin_truthevent->GetXaxis()->SetBinLabel(2, "77 WP");
  hist_btagbin_truthevent->GetXaxis()->SetBinLabel(3, "70/60 WP");

  hist_btagbin_truthevent->GetYaxis()->SetBinLabel(1, "non-H.F.");
  hist_btagbin_truthevent->GetYaxis()->SetBinLabel(2, "c");
  hist_btagbin_truthevent->GetYaxis()->SetBinLabel(3, "b");

  hist_nbjets = new TH2F("hist_nbjets", "hist_nbjets;Reco N_{b-jets};Truth N_{b-jets}", 3, 0, 3, 3, 0, 3);

  hist_HFTool_btagbin_truthjet = new TH2F("hist_HFTool_btagbin_truthjet", "hist_HFTool_btagbin_truthjet;B-Tag Category;Jet Truth Label", 3, 0, 3, 3, 0, 3);
  hist_HFTool_btagbin_truthevent = new TH2F("hist_HFTool_btagbin_truthevent", "hist_HFTool_btagbin_truthevent;B-Tag Category;Event Truth Label", 3, 0, 3, 3, 0, 3);

  hist_HFTool_btagbin_truthjet->GetXaxis()->SetBinLabel(1, "untagged");
  hist_HFTool_btagbin_truthjet->GetXaxis()->SetBinLabel(2, "77 WP");
  hist_HFTool_btagbin_truthjet->GetXaxis()->SetBinLabel(3, "70/60 WP");

  hist_HFTool_btagbin_truthjet->GetYaxis()->SetBinLabel(1, "non-H.F.");
  hist_HFTool_btagbin_truthjet->GetYaxis()->SetBinLabel(2, "c");
  hist_HFTool_btagbin_truthjet->GetYaxis()->SetBinLabel(3, "b");

  hist_HFTool_btagbin_truthevent->GetXaxis()->SetBinLabel(1, "untagged");
  hist_HFTool_btagbin_truthevent->GetXaxis()->SetBinLabel(2, "77 WP");
  hist_HFTool_btagbin_truthevent->GetXaxis()->SetBinLabel(3, "70/60 WP");

  hist_HFTool_btagbin_truthevent->GetYaxis()->SetBinLabel(1, "non-H.F.");
  hist_HFTool_btagbin_truthevent->GetYaxis()->SetBinLabel(2, "c");
  hist_HFTool_btagbin_truthevent->GetYaxis()->SetBinLabel(3, "b");


  hist_truth_cutflow = new TH1I("hist_truth_cutflow", "hist_truth_cutflow", 6, 0, 6);
  hist_reco_cutflow = new TH1I("hist_reco_cutflow", "hist_reco_cutflow", 6, 0, 6);

  hist_mismatch_b_cutflow = new TH1I("hist_mismatch_b_cutflow", "hist_mismatch_b_cutflow", 6, 0, 6);
  hist_mismatch_c_cutflow = new TH1I("hist_mismatch_c_cutflow", "hist_mismatch_c_cutflow", 6, 0, 6);

  hist_truth_cutflow->GetXaxis()->SetBinLabel(1, "photons");
  hist_truth_cutflow->GetXaxis()->SetBinLabel(2, "lepveto");
  hist_truth_cutflow->GetXaxis()->SetBinLabel(3, "cenjet_min");
  hist_truth_cutflow->GetXaxis()->SetBinLabel(4, "cenjet_max");
  hist_truth_cutflow->GetXaxis()->SetBinLabel(5, "btag");
  hist_truth_cutflow->GetXaxis()->SetBinLabel(6, "pass");

  hist_reco_cutflow->GetXaxis()->SetBinLabel(1, "photons");
  hist_reco_cutflow->GetXaxis()->SetBinLabel(2, "lepveto");
  hist_reco_cutflow->GetXaxis()->SetBinLabel(3, "cenjet_min");
  hist_reco_cutflow->GetXaxis()->SetBinLabel(4, "cenjet_max");
  hist_reco_cutflow->GetXaxis()->SetBinLabel(5, "btag");
  hist_reco_cutflow->GetXaxis()->SetBinLabel(6, "pass");

  hist_mismatch_c_cutflow->GetXaxis()->SetBinLabel(1, "photons");
  hist_mismatch_c_cutflow->GetXaxis()->SetBinLabel(2, "lepveto");
  hist_mismatch_c_cutflow->GetXaxis()->SetBinLabel(3, "cenjet_min");
  hist_mismatch_c_cutflow->GetXaxis()->SetBinLabel(4, "cenjet_max");
  hist_mismatch_c_cutflow->GetXaxis()->SetBinLabel(5, "btag");
  hist_mismatch_c_cutflow->GetXaxis()->SetBinLabel(6, "pass");

  hist_mismatch_b_cutflow->GetXaxis()->SetBinLabel(1, "photons");
  hist_mismatch_b_cutflow->GetXaxis()->SetBinLabel(2, "lepveto");
  hist_mismatch_b_cutflow->GetXaxis()->SetBinLabel(3, "cenjet_min");
  hist_mismatch_b_cutflow->GetXaxis()->SetBinLabel(4, "cenjet_max");
  hist_mismatch_b_cutflow->GetXaxis()->SetBinLabel(5, "btag");
  hist_mismatch_b_cutflow->GetXaxis()->SetBinLabel(6, "pass");

  // hist_LeadDL1Jet_truthlabel->GetXaxis()->SetBinLabel(0, "None");
  // hist_LeadDL1Jet_truthlabel->GetXaxis()->SetBinLabel(1, "b");
  // hist_LeadDL1Jet_truthlabel->GetXaxis()->SetBinLabel(2, "c");
  // hist_LeadDL1Jet_truthlabel->GetXaxis()->SetBinLabel(3, "l");

  // hist_j130_pt_015 = new TH1F("hist_j130_pt_015", "hist_j130_pt_015;p_{T};Events", ptbins, ptmin, ptmax);

  // hist_mu = TH1F("hist_mu", "hist_mu;#mu;Events;", 6, 0, 60);
  
  tree->Branch("isPassed" , &isPassed);
  tree->Branch("y1_pt" , &y1_pt);
  tree->Branch("y2_pt" , &y2_pt);
  tree->Branch("y1_eta" , &y1_eta);
  tree->Branch("y2_eta" , &y2_eta);
  tree->Branch("y1_phi" , &y1_phi);
  tree->Branch("y2_phi" , &y2_phi);
  tree->Branch("PythiaHerwigMatch" , &PythiaHerwigMatch);


  tree->Branch("weight_crossSectionBRfilterEff", &weight_crossSectionBRfilterEff); 
  tree->Branch("weight_HGamEventInfoWeight",     &weight_HGamEventInfoWeight); 
  tree->Branch("weight_weightJvt",               &weight_weightJvt); 
  tree->Branch("weight_lumi",                    &weight_lumi); 
  tree->Branch("weight_sumweights",              &weight_sumweights); 
  tree->Branch("weight_totalweight",             &weight_totalweight); 


  tree->Branch("btagbin_LeadDL1Jet",     &btagbin_LeadDL1Jet);
  tree->Branch("truthlabel_LeadDL1Jet",  &truthlabel_LeadDL1Jet);
  tree->Branch("event_weight",           &event_weight);
  tree->Branch("btag_weight",            &btag_weight);

  tree->Branch("Njets_central",  &Njets_central);
  tree->Branch("m_yy",  &m_yy);


  tree->Branch("n_btag_0",  &n_btag_0);
  tree->Branch("n_btag_1",  &n_btag_1);
  tree->Branch("n_btag_2",  &n_btag_2);
  tree->Branch("n_btag_3",  &n_btag_3);
  tree->Branch("n_btag_4",  &n_btag_4);
  tree->Branch("n_btag_none",  &n_btag_none);

  tree->Branch("n_truthjet_b",  &n_truthjet_b);
  tree->Branch("n_truthjet_c",  &n_truthjet_c);
  tree->Branch("n_truthjet_l",  &n_truthjet_l);
  tree->Branch("n_truthjet_none",  &n_truthjet_none);

  tree->Branch("ncdisagree", &ncdisagree);
  tree->Branch("nbdisagree", &nbdisagree);

  wk()->addOutput(tree);
  
  wk()->addOutput(hist_LeadDL1Jet_btagbin);
  wk()->addOutput(hist_LeadDL1Jet_truthlabel);
  wk()->addOutput(hist_btagbin_truthjet);
  wk()->addOutput(hist_btagbin_truthevent);
  wk()->addOutput(hist_HFTool_btagbin_truthjet);
  wk()->addOutput(hist_HFTool_btagbin_truthevent);

  wk()->addOutput(hist_reco_cutflow);
  wk()->addOutput(hist_truth_cutflow);
  wk()->addOutput(hist_mismatch_b_cutflow);
  wk()->addOutput(hist_mismatch_c_cutflow);
  wk()->addOutput(my_cutflow_hist);
  wk()->addOutput(my_cutflow_hist_unweighted);
  wk()->addOutput(hist_nbjets);


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
      if (histname.EndsWith("noDalitz_weighted")){
        std::cout << "Weighted cutflow name:  " << histname << std::endl;
        cutflow_hist = (TH1F*)key->ReadObj();
      }
      if (histname.EndsWith("noDalitz")){
        cutflow_hist_unweighted = (TH1F*)key->ReadObj();
      }
      TTree *tree = (TTree*)key->ReadObj();
      TString treename(h->GetName());
    }

    TString hname(cutflow_hist->GetName());
    
    if (hname.Contains("PowhegPy8_NNLOPS_ggH125") && isMCe == true){sum_weights=342535142.0;}
    else if (hname.Contains("Sherpa2_diphoton_myy_90_175") && isMCa == true){sum_weights=13657083.25;}
    else if (hname.Contains("Sherpa2_diphoton_myy_90_175") && isMCd == true){sum_weights=17291509.8594;}
    else if (hname.Contains("Sherpa2_diphoton_myy_90_175") && isMCe == true){sum_weights=22950038.3203;}
    
    else if (hname.Contains("PowhegPy8_ttH125_fixweight") && isMCa == true){sum_weights=962732.367188;}
    else if (hname.Contains("PowhegPy8_ttH125_fixweight") && isMCd == true){sum_weights=1202285.45703;}
    else if (hname.Contains("PowhegPy8_ttH125_fixweight") && isMCe == true){sum_weights=1589029.06836;}

    else if (hname.Contains("PowhegH713_NNLOPS_ggH125") && isMCa == true){sum_weights=219597662.5;}
    else if (hname.Contains("PowhegH713_NNLOPS_ggH125") && isMCd == true){sum_weights=219847218.0;}
    else if (hname.Contains("PowhegH713_NNLOPS_ggH125") && isMCe == true){sum_weights=363888645.75;}

    else {sum_weights = ((cutflow_hist->GetBinContent(1) / cutflow_hist->GetBinContent(2)) * cutflow_hist->GetBinContent(3));}
  }

  std::cout << "Sum_weights = " << sum_weights << std::endl;

  std::cout << "*************** Checking for CutFlow_noDalitz ***************" << std::endl;
  std::cout << "          NDAOD: " << cutflow_hist_unweighted->GetBinContent(2) << std::endl;
  std::cout << "  No duplicates: " << cutflow_hist_unweighted->GetBinContent(4) << std::endl;
  std::cout << "   Pass trigger: " << cutflow_hist_unweighted->GetBinContent(6) << std::endl;
  std::cout << "         Had PV: " << cutflow_hist_unweighted->GetBinContent(8) << std::endl;
  std::cout << "2 loose photons: " << cutflow_hist_unweighted->GetBinContent(9) << std::endl;
  std::cout << "  e-y ambiguity: " << cutflow_hist_unweighted->GetBinContent(10) << std::endl;
  std::cout << "  Trigger match: " << cutflow_hist_unweighted->GetBinContent(11) << std::endl;
  std::cout <<        "tight ID: " << cutflow_hist_unweighted->GetBinContent(12) << std::endl;
  std::cout << "      isolation: " << cutflow_hist_unweighted->GetBinContent(13) << std::endl;
  std::cout << "    rel pt cuts: " << cutflow_hist_unweighted->GetBinContent(14) << std::endl;
  std::cout << "    myy 105-160: " << cutflow_hist_unweighted->GetBinContent(15) << std::endl;

  std::cout << "*************** Checking for CutFlow_noDalitz_weighted ***************" << std::endl;
  std::cout << "          NDAOD: " << cutflow_hist->GetBinContent(2) << std::endl;
  std::cout << "  No duplicates: " << cutflow_hist->GetBinContent(4) << std::endl;
  std::cout << "   Pass trigger: " << cutflow_hist->GetBinContent(6) << std::endl;
  std::cout << "         Had PV: " << cutflow_hist->GetBinContent(8) << std::endl;
  std::cout << "2 loose photons: " << cutflow_hist->GetBinContent(9) << std::endl;
  std::cout << "  e-y ambiguity: " << cutflow_hist->GetBinContent(10) << std::endl;
  std::cout << "  Trigger match: " << cutflow_hist->GetBinContent(11) << std::endl;
  std::cout <<        "tight ID: " << cutflow_hist->GetBinContent(12) << std::endl;
  std::cout << "      isolation: " << cutflow_hist->GetBinContent(13) << std::endl;
  std::cout << "    rel pt cuts: " << cutflow_hist->GetBinContent(14) << std::endl;
  std::cout << "    myy 105-160: " << cutflow_hist->GetBinContent(15) << std::endl;

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

  // std::cout << "BLS New Event" << std::endl;

  xAOD::TEvent* event = wk()->xaodEvent();
  m_eventCounter++;
  ResetVariables();
  my_cutflow_hist_unweighted->Fill(0);

  m_eventInfoCont =0;
  EL_RETURN_CHECK("execute()",event->retrieve( m_eventInfoCont, "EventInfo"));
  
  const xAOD::EventInfo *HGamEventInfo = NULL;
  if (! event->retrieve(HGamEventInfo, "HGamEventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamEventInfo. Exiting.");
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

  const xAOD::JetContainer *hgamJets = NULL;
  if (! event->retrieve(hgamJets, "HGamAntiKt4PFlowCustomVtxHggJets").isSuccess()) {
      Error("execute()", "Failed to retrieve hgamJets. Exiting.");
      return EL::StatusCode::FAILURE;
    }

  // const xAOD::JetContainer *pflowjets = NULL;
  // if (! event->retrieve(pflowjets, "HGamAntiKt4EMPFlowJets").isSuccess()) {
  //   Error("execute()", "Failed to retrieve pflowjets. Exiting.");
  //   return EL::StatusCode::FAILURE;
  // }

  const xAOD::EventInfo *HGamTruthEventInfo = NULL;
  if (! event->retrieve(HGamTruthEventInfo, "HGamTruthEventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamTruthEventInfo. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::TruthParticleContainer *HGamTruthMuons = NULL;
  if (! event->retrieve(HGamTruthMuons, "HGamTruthMuons").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamTruthMuons. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::TruthParticleContainer *HGamTruthElectrons = NULL;
  if (! event->retrieve(HGamTruthElectrons, "HGamTruthElectrons").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamTruthElectrons. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::TruthParticleContainer *HGamTruthPhotons = NULL;
  if (! event->retrieve(HGamTruthPhotons, "HGamTruthPhotons").isSuccess()) {
    Error("execute()", "Failed to retrieve HGamTruthPhotons. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::JetContainer *TruthJets = NULL;
  if (! event->retrieve(TruthJets, "HGamAntiKt4TruthWZJets").isSuccess()) {
    Error("execute()", "Failed to retrieve TruthJets. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  if (isMCa == true){lumi_mc16 = 36205.26;}
  if (isMCd == true){lumi_mc16 = 44307.4;}
  if (isMCe == true){lumi_mc16 = 58450.1;}
  if (isMCde == true){lumi_mc16 = 44307.4 + 58450.1;}

  btag_eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
          * HGamEventInfo->auxdataConst<float>("weight") 
          * HGamEventInfo->auxdataConst<float>("weightCatXS_nbjet")
          * lumi_mc16)
          / sum_weights);

  eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
          * HGamEventInfo->auxdataConst<float>("weight") 
          * HGamEventInfo->auxdataConst<float>("weightJvt")
          * lumi_mc16)
          / sum_weights);
  if (isData == true){eventweight = 1;}
  
  my_cutflow_hist->Fill(0., eventweight);

  hist_reco_cutflow->Fill(HGamEventInfo->auxdataConst<int>("HiggsHF_cutFlow"));
  hist_truth_cutflow->Fill(HGamTruthEventInfo->auxdataConst<int>("HiggsHF_cutFlow"));

  isPassed = HGamEventInfo->auxdataConst<char>("isPassed");
// eventweight = 1;
  if (isPassed && HGamTruthPhotons->size() > 0){
  my_cutflow_hist->Fill(1., eventweight);
  my_cutflow_hist_unweighted->Fill(1);

  bool pass_nphotons;
  bool pass_nelectrons;
  bool pass_nmuons;

  bool pass_truth_photons;
  bool pass_truth_electrons;
  bool pass_truth_muons;

  // Save b-tagging weights for leading & subleading DL1 jet
  double LeadDL1Weight = -999;
  double SubleadDL1Weight = -999;

  // Save b-tagging bin for leading & subleading DL1 jet
  int LeadDL1Jet_btagbin = -999;
  //int SubleadDL1Jet_btagbin = -999;

  // Save truth label of leading & subleading DL1 jet
  int LeadDL1Jet_truthlabel = -999;
  //int SubleadDL1Jet_truthlabel = -999;

  // Store weight for continuous b-tagging
  double weight_b_tagging = 1.0;

  weight_crossSectionBRfilterEff = HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff");
  weight_HGamEventInfoWeight = HGamEventInfo->auxdataConst<float>("weight");
  weight_weightJvt = HGamEventInfo->auxdataConst<float>("weightJvt");
  weight_lumi = lumi_mc16;
  weight_sumweights = sum_weights;
  weight_totalweight = eventweight;

  // Save four-vectors of leading & subleading DL1 jet and save TLorentzVectors of all central jets
  TLorentzVector LeadDL1Jet;
  LeadDL1Jet.SetPtEtaPhiM(0, 0, 0, 0);
  TLorentzVector SubleadDL1Jet;
  SubleadDL1Jet.SetPtEtaPhiM(0, 0, 0, 0);
  std::vector<TLorentzVector> central_jets;

  if (HGamPhotons->size() >= 2){pass_nphotons = true;my_cutflow_hist_unweighted->Fill(2);my_cutflow_hist->Fill(2., eventweight);}
  // else {}

  auto leading_photon = (*HGamTruthPhotons)[0];
  auto subleading_photon = (*HGamTruthPhotons)[1];

  y1_pt = leading_photon->pt();
  // y2_pt = subleading_photon->pt();

  y1_eta = leading_photon->eta();
  // y2_eta = subleading_photon->eta();

  y1_phi = leading_photon->phi();
  // y2_phi = subleading_photon->phi();
  PythiaHerwigMatch = -99;

  if (abs(y1_pt - (56407.312)) < 50){
    if (abs(y1_eta - (-0.016767)) < 0.1){
      if (abs(y1_phi - (0.3903292)) < 0.1){
        PythiaHerwigMatch = 200;
      }
    }
  }//ggH pythia event 200
  
  if (abs(y1_pt - (99881.734)) < 50){
    if (abs(y1_eta - (-0.587987)) < 0.1){
      if (abs(y1_phi - (-1.972285)) < 0.1){
        PythiaHerwigMatch = 801;
      }
    }
  }//ggH pythia event 801

  if (abs(y1_pt - (66694.351)) < 50){
    if (abs(y1_eta - (0.2711741)) < 0.1){
      if (abs(y1_phi - (2.1674904)) < 0.1){
        PythiaHerwigMatch = 1200;
      }
    }
  }//ggH pythia event 1200

  // TLorentzVector LV_leading = leading_photon->p4();
  // TLorentzVector LV_subleading = subleading_photon->p4();
  // std::cout << "BLS TEST LV_leading is " << std::endl;
  // LV_leading.Print();

  // std::cout << "BLS leading photon pt: " << leading_photon.Pt() << " eta: " << leading_photon.Eta() << " phi: " << leading_photon.Phi() << std::endl;

  // std::cout << "BLS TEST LV_leading is " << LV_leading.Print() << std::endl;
  // std::cout << "BLS TEST LV_subleading is " << LV_subleading.Print() << std::endl;


  if (HGamElectrons->size() == 0){pass_nelectrons = true;}
  else{
    for (auto electron : *HGamElectrons){
      if(electron->pt() * 0.001 > 10){pass_nelectrons = false;}
    }
  }
  if (pass_nelectrons){my_cutflow_hist_unweighted->Fill(3);my_cutflow_hist->Fill(3., eventweight);}

  if (HGamMuons->size() == 0 ){pass_nmuons = true;}
  else{
    for (auto muon : *HGamMuons){
      if(muon->pt() * 0.001 > 10){pass_nmuons = false;}
    }
  }
  if (pass_nmuons && pass_nelectrons){my_cutflow_hist_unweighted->Fill(4);my_cutflow_hist->Fill(4., eventweight);}

  if (HGamTruthEventInfo->auxdataConst<char>("isFiducial")){pass_truth_photons = true;}
  else{pass_truth_photons = false;}

  if (HGamTruthElectrons->size() == 0){pass_truth_electrons = true;}
  else{
    for (auto electron : *HGamTruthElectrons){
      if(electron->pt() * 0.001 > 10){pass_truth_electrons = false;}
    }
  }

  if (HGamTruthMuons->size() == 0 ){pass_truth_muons = true;}
  else{
    for (auto muon : *HGamTruthMuons){
      if(muon->pt() * 0.001 > 10){pass_truth_muons = false;}
    }
  }


  bool higgs_range=false;
  m_yy = HGamEventInfo->auxdata<float>("m_yy")*0.001;
  // hist_myy->Fill(m_yy);
  if (m_yy < 129 && m_yy > 121){
    // std::cout << "m_yy is " << m_yy << std::endl;
    higgs_range=true;
    }

// std::cout << "begin event" << std::endl;
  int Njet_truth_central = 0;
  for (auto jet : *TruthJets) {
    if (fabs(jet->eta()) > 2.5  || jet->pt() * 0.001 < 30){continue;}
    // std::cout << "BLS Truth Jet pt: " << jet->pt()*0.001 << " eta: " << jet->eta() << " truthlabelid: " <<  jet->auxdata<int>("HadronConeExclTruthLabelID") << std::endl;

    ++Njet_truth_central;

    if (jet->auxdata<int>("HadronConeExclTruthLabelID") == 5) {
      ++n_bjets;
      // std::cout << "truth b jet info:  pt: " << jet->pt()*0.001 << " eta: " << jet->eta() << " phi: " << jet->phi() << std::endl;
    }
    else if (jet->auxdata<int>("HadronConeExclTruthLabelID") == 4) {
      ++n_cjets;
      // std::cout << "truth c jet info:  pt: " << jet->pt()*0.001 << " eta: " << jet->eta() << " phi: " << jet->phi() << std::endl;
    }
  }

  // std::cout << "Njet_central " << Njet_truth_central << std::endl;

  float HiggsHF_leadBtagjet_pt = HGamEventInfo->auxdataConst<float>("HiggsHF_leadBtagjet_pt");


if (pass_truth_photons){
  int catXS_nbjet = HGamEventInfo->auxdataConst<char>("catXS_nbjet");
  int truth_catXS_nbjet = HGamTruthEventInfo->auxdataConst<char>("catXS_nbjet");
  int N_j_central30 = HGamTruthEventInfo->auxdataConst<int>("N_j_central30");
  int modified_catXS_nbjet;
  int modified_truth_catXS_nbjet;
  if (catXS_nbjet == 0){modified_catXS_nbjet = 0;}
  if (catXS_nbjet == 1){modified_catXS_nbjet = 1;}
  if (catXS_nbjet == 2){modified_catXS_nbjet = 2;}
  if (catXS_nbjet == 3){modified_catXS_nbjet = 2;}

  if (truth_catXS_nbjet == 0){modified_truth_catXS_nbjet = 0;}
  if (truth_catXS_nbjet == 1){modified_truth_catXS_nbjet = 1;}
  if (truth_catXS_nbjet == 2){modified_truth_catXS_nbjet = 2;}
  if (truth_catXS_nbjet == 3){modified_truth_catXS_nbjet = 2;}

  // if (N_j_central30 > 0 && N_j_central30 < 4){// bls remove cenjetmax cuts
    hist_nbjets->Fill(modified_catXS_nbjet, modified_truth_catXS_nbjet, btag_eventweight);
  // }
}


  bool pass_truth_centralmax;
  if (Njet_truth_central > 0 && Njet_truth_central < 4){pass_truth_centralmax = true;}
  else {pass_truth_centralmax = false;}

  if (!pass_truth_muons || !pass_truth_photons || !pass_truth_electrons){n_bjets = 0; n_cjets=0;}// bls remove cenjetmax cuts
  // if (!pass_truth_centralmax || !pass_truth_muons || !pass_truth_photons || !pass_truth_electrons){n_bjets = 0; n_cjets=0;}// bls remove cenjetmax cuts

  // float 
// if (higgs_range){
  if (pass_nphotons && pass_nelectrons && pass_nmuons){

    int Njet_central = 0;
    for (auto jet : *hgamJets) {
      if (fabs(jet->eta()) > 2.5  || jet->pt() * 0.001 < 30){continue;}
      // if (jet->pt() * 0.001 == HiggsHF_leadBtagjet_pt){std::cout << "found jet with matching pt" << std::endl;}
      ispassed = true;
      Njet_central++;
      TLorentzVector jet_tmp = jet->p4();
      central_jets.push_back(jet_tmp);


      double DL1_disc = jet->auxdata<int>("DL1r_bin");
      int truthLabel = jet->auxdata<int>("HadronConeExclTruthLabelID");
      // int truthLabel = jet->auxdata<int>("PartonTruthLabelID");
      int btagbin = -999;

      // if (jet->auxdata<char>("DL1r_FixedCutBEff_85")) { ntag85_25++; }

      if (jet->auxdata<char>("DL1r_FixedCutBEff_60")) { btagbin = 4; }
      else if (jet->auxdata<char>("DL1r_FixedCutBEff_70")) { btagbin = 3; }
      else if (jet->auxdata<char>("DL1r_FixedCutBEff_77")) { btagbin = 2; }
      else if (jet->auxdata<char>("DL1r_FixedCutBEff_85")) { btagbin = 1; }
      else { btagbin = 0; }

      // weight_b_tagging *= jet->auxdata<float>("SF_DL1r_Continuous");
      weight_b_tagging *= jet->auxdata<float>("SF_DL1r_FixedCutBEff_85");

      if (DL1_disc > LeadDL1Weight) {
        if (Njet_central > 1) {
          SubleadDL1Jet = LeadDL1Jet;
          SubleadDL1Weight = LeadDL1Weight;
        }
        LeadDL1Weight = DL1_disc;
        LeadDL1Jet_truthlabel = truthLabel;
        LeadDL1Jet_btagbin = btagbin;
        LeadDL1Jet.SetPtEtaPhiM(jet->pt(), jet->eta(), jet->phi(), jet->m());
      }
      else if ((DL1_disc > SubleadDL1Weight) && (Njet_central > 1)) {
        SubleadDL1Jet.SetPtEtaPhiM(jet->pt(), jet->eta(), jet->phi(), jet->m());
        SubleadDL1Weight = DL1_disc;
      }
    }//end of jet loop
    pass_centralmax = true;// bls remove cenjetmax cuts
    // if (Njet_central > 0 && Njet_central < 4) {pass_centralmax = true;}// bls remove cenjetmax cuts
    } // end of y, e, u check
// }  //end of higgs range
  
  if (pass_centralmax){
    my_cutflow_hist_unweighted->Fill(5);
    my_cutflow_hist->Fill(5., eventweight);
    btag_weight = weight_b_tagging;
    eventweight *= weight_b_tagging;
    hist_LeadDL1Jet_btagbin->Fill(LeadDL1Jet_btagbin, eventweight);
    hist_LeadDL1Jet_truthlabel->Fill(LeadDL1Jet_truthlabel, eventweight);
    // if (LeadDL1Jet_truthlabel > 37){std::cout<< "unexpected partice of type: " << LeadDL1Jet_truthlabel << std::endl;}

    btagbin_LeadDL1Jet = LeadDL1Jet_btagbin;
    truthlabel_LeadDL1Jet = LeadDL1Jet_truthlabel;
    // event_weight = eventweight;

    int modified_truth_label;
    int modified_b_cat;

    int HFTool_modified_truth_label;
    int HFTool_modified_b_cat;

    int HFTool_LeadDL1Jet_truthlabel = HGamEventInfo->auxdataConst<int>("HiggsHF_truth_label_LeadBtagJet");
    int HFTool_LeadDL1Jet_btagbin = HGamEventInfo->auxdataConst<int>("HiggsHF_leadBtagJet_btagbin");


    if (LeadDL1Jet_truthlabel == 5){modified_truth_label = 2;n_truthjet_b = 1;}
    else if (LeadDL1Jet_truthlabel == 4){modified_truth_label = 1;n_truthjet_c = 1;}
    else if (LeadDL1Jet_truthlabel == -999){modified_truth_label = -999;n_truthjet_none = 1;}
    // else if (LeadDL1Jet_truthlabel == 0){modified_truth_label = 3;}
    else {modified_truth_label = 0;n_truthjet_l = 1;}

    if (HFTool_LeadDL1Jet_truthlabel == 5){HFTool_modified_truth_label = 2;}
    else if (HFTool_LeadDL1Jet_truthlabel == 4){HFTool_modified_truth_label = 1;}
    else if (HFTool_LeadDL1Jet_truthlabel == -999){HFTool_modified_truth_label = -999;}
    // else if (LeadDL1Jet_truthlabel == 0){modified_truth_label = 3;}
    else {HFTool_modified_truth_label = 0;}


    if (LeadDL1Jet_btagbin == 0){modified_b_cat = 0;n_btag_0 = 1;}
    else if (LeadDL1Jet_btagbin == 1){modified_b_cat = 1;n_btag_1 = 1;}
    else if (LeadDL1Jet_btagbin == 2){modified_b_cat = 1; n_btag_2 = 1;}
    else if (LeadDL1Jet_btagbin == 3){modified_b_cat = 2;n_btag_3 = 1;}
    else if (LeadDL1Jet_btagbin == 4){modified_b_cat = 2;n_btag_4 = 1;}
    else if (LeadDL1Jet_btagbin == -999){modified_b_cat=-999;n_btag_none = 1;}

    if (HFTool_LeadDL1Jet_btagbin == 0){HFTool_modified_b_cat = 0;}
    else if (HFTool_LeadDL1Jet_btagbin == 1){HFTool_modified_b_cat = 1;}
    else if (HFTool_LeadDL1Jet_btagbin == 2){HFTool_modified_b_cat = 1; }
    else if (HFTool_LeadDL1Jet_btagbin == 3){HFTool_modified_b_cat = 2;}
    else if (HFTool_LeadDL1Jet_btagbin == 4){HFTool_modified_b_cat = 2;}
    else if (HFTool_LeadDL1Jet_btagbin == -999){HFTool_modified_b_cat=-999;}


    n_HFcjets = HGamTruthEventInfo->auxdataConst<int>("HiggsHF_N_cjets");
    n_HFbjets = HGamTruthEventInfo->auxdataConst<int>("HiggsHF_N_bjets");

    int truth_event_label = -999;
    int HFTool_truth_event_label = -999;

    // if (ispassed){
      if (n_bjets > 0){truth_event_label = 2; n_truthevent_b = 1;}
      else if (n_cjets > 0){truth_event_label = 1; n_truthevent_c = 1;}
      else {truth_event_label = 0; n_truthevent_none = 1;}


      if (n_HFbjets > 0){HFTool_truth_event_label = 2;}
      else if (n_HFcjets > 0){HFTool_truth_event_label = 1;}
      else {HFTool_truth_event_label = 0;}

    // }
    
    // if (HFTool_LeadDL1Jet_btagbin != LeadDL1Jet_btagbin){
    //   std::cout << " --------------- mismatch! ---------------" << std::endl; 
    //   std::cout << "HFTool_LeadDL1Jet_btagbin: " << HFTool_LeadDL1Jet_btagbin << "  LeadDL1Jet_btagbin: " << LeadDL1Jet_btagbin << std::endl; 
    //   std::cout << "HiggsHF_leadBtagjet_pt: " << HiggsHF_leadBtagjet_pt << " LeadDL1Jet.Pt(): " << LeadDL1Jet.Pt() * 0.001 << std::endl;
    // }

    if (n_HFbjets == 0 && n_bjets != 0){nbdisagree= 1; 
      hist_mismatch_b_cutflow->Fill(HGamTruthEventInfo->auxdataConst<int>("HiggsHF_cutFlow"));
    }
    if (n_HFcjets == 0 && n_cjets != 0){ncdisagree= 1; 
      hist_mismatch_c_cutflow->Fill(HGamTruthEventInfo->auxdataConst<int>("HiggsHF_cutFlow"));
    }

    hist_btagbin_truthjet->Fill(modified_b_cat, modified_truth_label, eventweight);
    hist_btagbin_truthevent->Fill(modified_b_cat, truth_event_label, eventweight);

    hist_HFTool_btagbin_truthjet->Fill(HFTool_modified_b_cat, HFTool_modified_truth_label, eventweight);
    hist_HFTool_btagbin_truthevent->Fill(HFTool_modified_b_cat, HFTool_truth_event_label, eventweight);

    // if (HFTool_modified_b_cat != modified_b_cat){
    //   std::cout << " --------------- mismatch! ---------------" << std::endl; 
    //   std::cout << "HFTool_modified_b_cat: " << HFTool_modified_b_cat << "  modified_b_cat: " << modified_b_cat << std::endl; 
    //   // std::cout << "HiggsHF_leadBtagjet_pt: " << HiggsHF_leadBtagjet_pt << " LeadDL1Jet.Pt(): " << LeadDL1Jet.Pt() * 0.001 << std::endl;
    // }

    // if (HFTool_modified_truth_label != modified_truth_label){
    //   std::cout << " --------------- mismatch! ---------------" << std::endl; 
    //   std::cout << "HFTool_modified_truth_label: " << HFTool_modified_truth_label << "  modified_truth_label: " << modified_truth_label << std::endl; 
    //   // std::cout << "HiggsHF_leadBtagjet_pt: " << HiggsHF_leadBtagjet_pt << " LeadDL1Jet.Pt(): " << LeadDL1Jet.Pt() * 0.001 << std::endl;
    // }

    // if (HFTool_truth_event_label != truth_event_label){
    //   std::cout << " --------------- mismatch! ---------------" << std::endl; 
    //   std::cout << "HFTool_truth_event_label: " << HFTool_truth_event_label << "  truth_event_label: " << truth_event_label << std::endl; 
    //   std::cout << "HiggsHF_N_bjets: " << n_HFbjets << " n_bjets: " << n_bjets << std::endl;
    //   std::cout << "HiggsHF_N_cjets: " << n_HFcjets << " n_cjets: " << n_cjets << std::endl;
    // }

  }
// } //end of higgs_range

  // std::cout << truth_event_label << std::endl;
// std::cout << "end event" << std::endl;

  tree->Fill();
  }// end of isPassed
  // else{my_cutflow_hist_unweighted->Fill(1);}

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
n_truthjet_b = 0;
n_truthjet_c = 0;
n_truthjet_none = 0;
n_truthjet_l = 0;

n_truthevent_b = 0;
n_truthevent_c = 0;
n_truthevent_none = 0;
n_truthevent_l = 0;

pass_centralmax = false;
n_bjets = 0;
n_cjets = 0;
n_HFbjets = 0;
n_HFcjets = 0;
nbdisagree = 0;
ncdisagree = 0;

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
  return EL::StatusCode::SUCCESS;
}






