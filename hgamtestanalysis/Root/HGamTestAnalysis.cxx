#include <AsgTools/MessageCheck.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <HGamTestAnalysis/HGamTestAnalysis.h>
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
ClassImp(HGamTestAnalysis)


HGamTestAnalysis :: HGamTestAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().


}



EL::StatusCode HGamTestAnalysis :: setupJob (EL::Job& job)
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



EL::StatusCode HGamTestAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // myclass = new TH1F(...);
  tree = new TTree("hgamvariables", "tree with hgam variables per event");

  // hist_LeadMV2Jet_btagbin = new TH1F("hist_LeadMV2Jet_btagbin", "hist_LeadMV2Jet_btagbin;;Events", 5, 0, 5);
  
  // tree->Branch("btagbin_LeadMV2Jet",     &btagbin_LeadMV2Jet);

  wk()->addOutput(tree);
  
  // wk()->addOutput(hist_LeadMV2Jet_btagbin);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamTestAnalysis :: fileExecute ()
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



EL::StatusCode HGamTestAnalysis :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamTestAnalysis :: initialize ()
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



EL::StatusCode HGamTestAnalysis :: execute ()
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

  const xAOD::JetContainer *pflowjets = NULL;
  if (! event->retrieve(pflowjets, "HGamAntiKt4EMPFlowJets").isSuccess()) {
    Error("execute()", "Failed to retrieve pflowjets. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  const xAOD::JetContainer *topojets = NULL;
  if (! event->retrieve(topojets, "HGamAntiKt4EMTopoJets").isSuccess()) {
    Error("execute()", "Failed to retrieve topojets. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  if (isMCa == true){lumi_mc16 = 36205.26;}
  if (isMCd == true){lumi_mc16 = 44307.4;}
  if (isMCe == true){lumi_mc16 = 58450.1;}
  if (isMCde == true){lumi_mc16 = 44307.4 + 58450.1;}
  
  eventweight = ((HGamEventInfo->auxdataConst<float>("crossSectionBRfilterEff") 
          * HGamEventInfo->auxdataConst<float>("weight") 
          * HGamEventInfo->auxdataConst<float>("weightJvt")
          * lumi_mc16)
          / sum_weights);

  if (isData == true){eventweight = 1;}
  // std::cout << "Event weight = " << eventweight << std::endl;

  // passed = HGamEventInfo->auxdata<char>("isPassed");
  // m_yy = HGamEventInfo->auxdata<float>("m_yy")*0.001;

  // m_mu   = static_cast<int>(m_eventInfoCont->actualInteractionsPerCrossing());

  // n_events = 1;
  // std::cout<<"Number of photons" << HGamPhotons->size() << std::endl;
  // std::cout<<"Number of electrons" << HGamElectrons->size() << std::endl;
  // std::cout<<"Number of muons" << HGamMuons->size() << std::endl;


  for (auto jet : *topojets) {
  }
  
  tree->Fill();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamTestAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HGamTestAnalysis :: finalize ()
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


void HGamTestAnalysis::ResetVariables()
{

}

EL::StatusCode HGamTestAnalysis :: histFinalize ()
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






