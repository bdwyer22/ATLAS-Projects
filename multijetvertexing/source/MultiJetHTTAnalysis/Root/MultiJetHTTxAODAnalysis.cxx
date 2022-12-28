#include <AsgTools/MessageCheck.h>
#include <MultiJetHTTAnalysis/MultiJetHTTxAODAnalysis.h>

#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>
#include <xAODCore/ShallowCopy.h>

#include "src/d0Fitparam_MoU2in.C"
#include "src/z0Fitparam_MoU2in.C"
#include "src/d0Fitparam_N.C"
#include "src/z0Fitparam_N.C"
#include "src/z0Fitparam_L0_L1_InIn.C"
#include "src/d0Fitparam_L0_L1_InIn.C"
#include "src/z0Fitparam_NoPix.C"
#include "src/d0Fitparam_NoPix.C"
#include "src/z0Fitparam_TDR2in.C"
#include "src/d0Fitparam_TDR2in.C"

MultiJetHTTxAODAnalysis :: MultiJetHTTxAODAnalysis (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm (name, pSvcLocator)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  This is also where you
  // declare all properties for your algorithm.  Note that things like
  // resetting statistics variables or booking histograms should
  // rather go into the initialize() function.

  declareProperty( "FlatTrackInefficiency", m_flatTrackInefficiency = 1.0,
                   "Default flat track inefficiency" );

  declareProperty( "SmearFactor", m_smearFactor = 1.0,
                   "Default smear factor" );

  declareProperty( "TrackPtCut", m_trackptcut = 4.0,
                   "Minimum track pT (in GeV) " );

  declareProperty( "isSignal", m_issignal = false,
                   "Boolean for signal vs. background " );

  declareProperty( "isfixedwindow", m_isfixedwindow = false,
                   "Boolean for fixed vs. variable window " );

  declareProperty( "isHTTtracks", m_isHTTtracks = false,
                   "Boolean for htt vs. nominal tracks " );

  declareProperty( "isleadingtracks", m_isleadingtracks = false,
                   "Boolean for leading vs. all tracks " );

  declareProperty( "geometry", m_geometry = "Nominal",
                   "Default geometry for track smearing " );
  
  declareProperty( "OutputTrackContainerName", m_outputTrackContainerName,
                   "Name of track container name for smeared/fake tracks " );

  declareProperty( "SetRandomSeed", m_randomSeed,
                   "Name of track container name for smeared/fake tracks " );

  declareProperty( "EnableFakeKiller", m_fakeKiller,
                   "Name of track container name for smeared/fake tracks " );
}


bool myComparePt(const xAOD::Jet *a, const xAOD::Jet *b) { return a->pt() > b->pt(); }


StatusCode MultiJetHTTxAODAnalysis :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  // ANA_MSG_INFO ("in initialize");

  // From https://gitlab.cern.ch/atlas/athena/blob/master/Tracking/TrkEvent/TrkEventPrimitives/TrkEventPrimitives/ParamDefs.h#L69
  m_d0sigma_idx = 0;
  m_z0sigma_idx = 2;


  ANA_MSG_INFO( "FlatTrackInefficiency = " << m_flatTrackInefficiency );
  ANA_MSG_INFO( "TrackPtCut = " <<  m_trackptcut);
  ANA_MSG_INFO( "SmearFactor = " << m_smearFactor );
  ANA_MSG_INFO( "Signal = " << m_issignal );
  ANA_MSG_INFO( "Using geometry = " << m_geometry );

  if (m_isfixedwindow){ANA_MSG_INFO("Using Fixed Window");}
  else{ANA_MSG_INFO("Using Variable Window");}
  
  if (m_isHTTtracks){ANA_MSG_INFO("Using HTT Tracks");}
  else{ANA_MSG_INFO("Using Nominal Tracks");}

  if (m_isleadingtracks){ANA_MSG_INFO("Using Leading Tracks");}
  else{ANA_MSG_INFO("Using All Tracks");}

  m_CalibPath = "JES_HLLHC_mu200_r9589_Aug2017.config";

ANA_CHECK ( book ( new TH1F("multijet_cutflow", "Multi-jet Cutflow", 14, 0, 14 )));
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(5, "4+ Truth Jets");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(1, "J1 p_{t} > 95");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(2, "J2 p_{t} > 60");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(3, "J3 p_{t} > 30");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(4, "J4 p_{t} > 30");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(6, "J1 found trk");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(7, "J2 found trk");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(8, "J3 found trk");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(9, "J4 found trk");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(10, "Pass PVwindow double 0.1 mm");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(11, "Pass PVwindow double 0.5 mm");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(12, "Pass PVwindow double 1 mm");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(13, "Pass PVwindow double 2.5 mm");
  hist("multijet_cutflow")->GetXaxis()->SetBinLabel(14, "Pass PVwindow double 5 mm");

ANA_CHECK ( book ( new TH1F("multijet_cutflow_Nominal", "Multi-jet Cutflow", 14, 0, 14 )));
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(5, "4+ Truth Jets");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(1, "J1 p_{t} > 95");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(2, "J2 p_{t} > 60");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(3, "J3 p_{t} > 30");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(4, "J4 p_{t} > 30");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(6, "J1 found trk");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(7, "J2 found trk");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(8, "J3 found trk");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(9, "J4 found trk");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(10, "Pass PVwindow double 0.1 mm");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(11, "Pass PVwindow double 0.5 mm");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(12, "Pass PVwindow double 1 mm");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(13, "Pass PVwindow double 2.5 mm");
  hist("multijet_cutflow_Nominal")->GetXaxis()->SetBinLabel(14, "Pass PVwindow double 5 mm");

ANA_CHECK ( book ( new TH1F("multijet_cutflow_jetvec", "Multi-jet Cutflow", 14, 0, 14 )));
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(5, "4+ Truth Jets");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(1, "J1 p_{t} > 95");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(2, "J2 p_{t} > 60");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(3, "J3 p_{t} > 30");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(4, "J4 p_{t} > 30");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(6, "J1 found trk");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(7, "J2 found trk");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(8, "J3 found trk");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(9, "J4 found trk");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(10, "Pass PVwindow double 0.1 mm");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(11, "Pass PVwindow double 0.5 mm");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(12, "Pass PVwindow double 1 mm");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(13, "Pass PVwindow double 2.5 mm");
  hist("multijet_cutflow_jetvec")->GetXaxis()->SetBinLabel(14, "Pass PVwindow double 5 mm");

ANA_CHECK ( book ( new TH1F("multijet_cutflow_Nominal_jetvec", "Multi-jet Cutflow", 14, 0, 14 )));
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(5, "4+ Truth Jets");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(1, "J1 p_{t} > 95");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(2, "J2 p_{t} > 60");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(3, "J3 p_{t} > 30");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(4, "J4 p_{t} > 30");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(6, "J1 found trk");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(7, "J2 found trk");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(8, "J3 found trk");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(9, "J4 found trk");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(10, "Pass PVwindow double 0.1 mm");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(11, "Pass PVwindow double 0.5 mm");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(12, "Pass PVwindow double 1 mm");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(13, "Pass PVwindow double 2.5 mm");
  hist("multijet_cutflow_Nominal_jetvec")->GetXaxis()->SetBinLabel(14, "Pass PVwindow double 5 mm");


ANA_CHECK ( book ( new TH1F("hist_missingtrack", "Missing track", 4, 0, 4 )));
  hist("hist_missingtrack")->GetXaxis()->SetBinLabel(1, "J1 missing trk");
  hist("hist_missingtrack")->GetXaxis()->SetBinLabel(2, "J2 missing trk");
  hist("hist_missingtrack")->GetXaxis()->SetBinLabel(3, "J3 missing trk");
  hist("hist_missingtrack")->GetXaxis()->SetBinLabel(4, "J4 missing trk");

ANA_CHECK ( book ( new TH1F("hist_missingtrack_Nominal", "Missing track", 4, 0, 4 )));
  hist("hist_missingtrack_Nominal")->GetXaxis()->SetBinLabel(1, "J1 missing trk");
  hist("hist_missingtrack_Nominal")->GetXaxis()->SetBinLabel(2, "J2 missing trk");
  hist("hist_missingtrack_Nominal")->GetXaxis()->SetBinLabel(3, "J3 missing trk");
  hist("hist_missingtrack_Nominal")->GetXaxis()->SetBinLabel(4, "J4 missing trk");

ANA_CHECK (book (TTree ("CollectionTree", "My analysis ntuple")));
  TTree* mytree = tree ("CollectionTree");
  mytree->Branch ("RunNumber", &m_runNumber);
  mytree->Branch ("EventNumber", &m_eventNumber);

  mytree->Branch ("j1pt", &j1pt);
  mytree->Branch ("j2pt", &j2pt);
  mytree->Branch ("j3pt", &j3pt);
  mytree->Branch ("j4pt", &j4pt);

  mytree->Branch ("j1trackz0", &j1trackz0);
  mytree->Branch ("j2trackz0", &j2trackz0);
  mytree->Branch ("j3trackz0", &j3trackz0);
  mytree->Branch ("j4trackz0", &j4trackz0);

  mytree->Branch ("j1trackavgz0", &j1trackavgz0);
  mytree->Branch ("j2trackavgz0", &j2trackavgz0);
  mytree->Branch ("j3trackavgz0", &j3trackavgz0);
  mytree->Branch ("j4trackavgz0", &j4trackavgz0);

  mytree->Branch ("trk_z0Res", &trk_z0Res);
  mytree->Branch ("trk_z0", &trk_z0);
  mytree->Branch ("trk_parentID", &trk_parentID);
  mytree->Branch ("trk_type", &trk_type);
  mytree->Branch ("trk_jetmatch", &trk_jetmatch);

  mytree->Branch ("nEventPassJetReq", &nEventPassJetReq);
  mytree->Branch ("nTruthEvents_3HS", &nTruthEvents_3HS);
  mytree->Branch ("nTruthEvents_3HS4trk", &nTruthEvents_3HS4trk);



  mytree->Branch ("j1trackz0_Nominal", &j1trackz0_Nominal);
  mytree->Branch ("j2trackz0_Nominal", &j2trackz0_Nominal);
  mytree->Branch ("j3trackz0_Nominal", &j3trackz0_Nominal);
  mytree->Branch ("j4trackz0_Nominal", &j4trackz0_Nominal);

  mytree->Branch ("j1trackavgz0_Nominal", &j1trackavgz0_Nominal);
  mytree->Branch ("j2trackavgz0_Nominal", &j2trackavgz0_Nominal);
  mytree->Branch ("j3trackavgz0_Nominal", &j3trackavgz0_Nominal);
  mytree->Branch ("j4trackavgz0_Nominal", &j4trackavgz0_Nominal);

  mytree->Branch ("trk_z0Res_Nominal", &trk_z0Res_Nominal);
  mytree->Branch ("trk_z0_Nominal", &trk_z0_Nominal);
  mytree->Branch ("trk_jetmatch_Nominal", &trk_jetmatch_Nominal);

  mytree->Branch ("nEventPassJetReq_Nominal", &nEventPassJetReq_Nominal);
  mytree->Branch ("nTruthEvents_3HS_Nominal", &nTruthEvents_3HS_Nominal);
  mytree->Branch ("nTruthEvents_3HS4trk_Nominal", &nTruthEvents_3HS4trk_Nominal);



  mytree->Branch ("trk_z0Res_mean_1xRes", &trk_z0Res_mean_1xRes);
  mytree->Branch ("trk_z0Res_mean_01xRes", &trk_z0Res_mean_01xRes);
  mytree->Branch ("trk_z0Res_mean_05xRes", &trk_z0Res_mean_05xRes);
  mytree->Branch ("trk_z0Res_mean_005xRes", &trk_z0Res_mean_005xRes);
  mytree->Branch ("trk_z0Res_mean_0005xRes", &trk_z0Res_mean_0005xRes);
  mytree->Branch ("trk_z0Res_mean_25xRes", &trk_z0Res_mean_25xRes);
  mytree->Branch ("trk_z0Res_mean_2xRes", &trk_z0Res_mean_2xRes);
  mytree->Branch ("trk_z0Res_mean_3xRes", &trk_z0Res_mean_3xRes);
  mytree->Branch ("trk_z0Res_mean_5xRes", &trk_z0Res_mean_5xRes);
  mytree->Branch ("trk_z0Res_mean_10xRes", &trk_z0Res_mean_10xRes);
  mytree->Branch ("trk_z0Res_mean_12xRes", &trk_z0Res_mean_12xRes);
  mytree->Branch ("trk_z0Res_mean_15xRes", &trk_z0Res_mean_15xRes);
  mytree->Branch ("trk_z0Res_mean_20xRes", &trk_z0Res_mean_20xRes);
  mytree->Branch ("trk_z0Res_mean_4xRes", &trk_z0Res_mean_4xRes);
  mytree->Branch ("trk_z0Res_mean_50xRes", &trk_z0Res_mean_50xRes);
  mytree->Branch ("trk_z0Res_mean_150xRes", &trk_z0Res_mean_150xRes);
  mytree->Branch ("trk_z0Res_mean_075xRes", &trk_z0Res_mean_075xRes);
  mytree->Branch ("trk_z0Res_mean_025xRes", &trk_z0Res_mean_025xRes);
  mytree->Branch ("trk_z0Res_mean_0075xRes", &trk_z0Res_mean_0075xRes);
  mytree->Branch ("trk_z0Res_mean_00075xRes", &trk_z0Res_mean_00075xRes);

  mytree->Branch ("foundPVwindow_1xRes", &foundPVwindow_1xRes);
  mytree->Branch ("foundPVwindow_01xRes", &foundPVwindow_01xRes);
  mytree->Branch ("foundPVwindow_05xRes", &foundPVwindow_05xRes);
  mytree->Branch ("foundPVwindow_005xRes", &foundPVwindow_005xRes);
  mytree->Branch ("foundPVwindow_0005xRes", &foundPVwindow_0005xRes);
  mytree->Branch ("foundPVwindow_25xRes", &foundPVwindow_25xRes);
  mytree->Branch ("foundPVwindow_2xRes", &foundPVwindow_2xRes);
  mytree->Branch ("foundPVwindow_3xRes", &foundPVwindow_3xRes);
  mytree->Branch ("foundPVwindow_5xRes", &foundPVwindow_5xRes);
  mytree->Branch ("foundPVwindow_10xRes", &foundPVwindow_10xRes);
  mytree->Branch ("foundPVwindow_12xRes", &foundPVwindow_12xRes);
  mytree->Branch ("foundPVwindow_15xRes", &foundPVwindow_15xRes);
  mytree->Branch ("foundPVwindow_20xRes", &foundPVwindow_20xRes);
  mytree->Branch ("foundPVwindow_4xRes", &foundPVwindow_4xRes);
  mytree->Branch ("foundPVwindow_50xRes", &foundPVwindow_50xRes);
  mytree->Branch ("foundPVwindow_150xRes", &foundPVwindow_150xRes);
  mytree->Branch ("foundPVwindow_075xRes", &foundPVwindow_075xRes);
  mytree->Branch ("foundPVwindow_025xRes", &foundPVwindow_025xRes);
  mytree->Branch ("foundPVwindow_0075xRes", &foundPVwindow_0075xRes);
  mytree->Branch ("foundPVwindow_00075xRes", &foundPVwindow_00075xRes);

  mytree->Branch ("foundPVwindow_double_1xRes", &foundPVwindow_double_1xRes);
  mytree->Branch ("foundPVwindow_double_01xRes", &foundPVwindow_double_01xRes);
  mytree->Branch ("foundPVwindow_double_05xRes", &foundPVwindow_double_05xRes);
  mytree->Branch ("foundPVwindow_double_005xRes", &foundPVwindow_double_005xRes);
  mytree->Branch ("foundPVwindow_double_0005xRes", &foundPVwindow_double_0005xRes);
  mytree->Branch ("foundPVwindow_double_25xRes", &foundPVwindow_double_25xRes);
  mytree->Branch ("foundPVwindow_double_2xRes", &foundPVwindow_double_2xRes);
  mytree->Branch ("foundPVwindow_double_3xRes", &foundPVwindow_double_3xRes);
  mytree->Branch ("foundPVwindow_double_5xRes", &foundPVwindow_double_5xRes);
  mytree->Branch ("foundPVwindow_double_10xRes", &foundPVwindow_double_10xRes);
  mytree->Branch ("foundPVwindow_double_12xRes", &foundPVwindow_double_12xRes);
  mytree->Branch ("foundPVwindow_double_15xRes", &foundPVwindow_double_15xRes);
  mytree->Branch ("foundPVwindow_double_20xRes", &foundPVwindow_double_20xRes);
  mytree->Branch ("foundPVwindow_double_4xRes", &foundPVwindow_double_4xRes);
  mytree->Branch ("foundPVwindow_double_50xRes", &foundPVwindow_double_50xRes);
  mytree->Branch ("foundPVwindow_double_150xRes", &foundPVwindow_double_150xRes);
  mytree->Branch ("foundPVwindow_double_075xRes", &foundPVwindow_double_075xRes);
  mytree->Branch ("foundPVwindow_double_025xRes", &foundPVwindow_double_025xRes);
  mytree->Branch ("foundPVwindow_double_0075xRes", &foundPVwindow_double_0075xRes);
  mytree->Branch ("foundPVwindow_double_00075xRes", &foundPVwindow_double_00075xRes);

  mytree->Branch ("foundPVwindow_JetVecs_1xRes", &foundPVwindow_JetVecs_1xRes);
  mytree->Branch ("foundPVwindow_JetVecs_01xRes", &foundPVwindow_JetVecs_01xRes);
  mytree->Branch ("foundPVwindow_JetVecs_05xRes", &foundPVwindow_JetVecs_05xRes);
  mytree->Branch ("foundPVwindow_JetVecs_005xRes", &foundPVwindow_JetVecs_005xRes);
  mytree->Branch ("foundPVwindow_JetVecs_0005xRes", &foundPVwindow_JetVecs_0005xRes);
  mytree->Branch ("foundPVwindow_JetVecs_25xRes", &foundPVwindow_JetVecs_25xRes);
  mytree->Branch ("foundPVwindow_JetVecs_2xRes", &foundPVwindow_JetVecs_2xRes);
  mytree->Branch ("foundPVwindow_JetVecs_3xRes", &foundPVwindow_JetVecs_3xRes);
  mytree->Branch ("foundPVwindow_JetVecs_5xRes", &foundPVwindow_JetVecs_5xRes);
  mytree->Branch ("foundPVwindow_JetVecs_10xRes", &foundPVwindow_JetVecs_10xRes);
  mytree->Branch ("foundPVwindow_JetVecs_12xRes", &foundPVwindow_JetVecs_12xRes);
  mytree->Branch ("foundPVwindow_JetVecs_15xRes", &foundPVwindow_JetVecs_15xRes);
  mytree->Branch ("foundPVwindow_JetVecs_20xRes", &foundPVwindow_JetVecs_20xRes);
  mytree->Branch ("foundPVwindow_JetVecs_4xRes", &foundPVwindow_JetVecs_4xRes);
  mytree->Branch ("foundPVwindow_JetVecs_50xRes", &foundPVwindow_JetVecs_50xRes);
  mytree->Branch ("foundPVwindow_JetVecs_150xRes", &foundPVwindow_JetVecs_150xRes);
  mytree->Branch ("foundPVwindow_JetVecs_075xRes", &foundPVwindow_JetVecs_075xRes);
  mytree->Branch ("foundPVwindow_JetVecs_025xRes", &foundPVwindow_JetVecs_025xRes);
  mytree->Branch ("foundPVwindow_JetVecs_0075xRes", &foundPVwindow_JetVecs_0075xRes);
  mytree->Branch ("foundPVwindow_JetVecs_00075xRes", &foundPVwindow_JetVecs_00075xRes);

  mytree->Branch ("z0Segment_1xRes", &z0Segment_1xRes);
  mytree->Branch ("z0Segment_01xRes", &z0Segment_01xRes);
  mytree->Branch ("z0Segment_05xRes", &z0Segment_005xRes);
  mytree->Branch ("z0Segment_005xRes", &z0Segment_0005xRes);
  mytree->Branch ("z0Segment_0005xRes", &z0Segment_05xRes);
  mytree->Branch ("z0Segment_25xRes", &z0Segment_25xRes);
  mytree->Branch ("z0Segment_2xRes", &z0Segment_2xRes);
  mytree->Branch ("z0Segment_3xRes", &z0Segment_3xRes);
  mytree->Branch ("z0Segment_5xRes", &z0Segment_5xRes);
  mytree->Branch ("z0Segment_10xRes", &z0Segment_10xRes);
  mytree->Branch ("z0Segment_12xRes", &z0Segment_12xRes);
  mytree->Branch ("z0Segment_15xRes", &z0Segment_15xRes);
  mytree->Branch ("z0Segment_20xRes", &z0Segment_20xRes);
  mytree->Branch ("z0Segment_4xRes", &z0Segment_4xRes);
  mytree->Branch ("z0Segment_50xRes", &z0Segment_50xRes);
  mytree->Branch ("z0Segment_150xRes", &z0Segment_150xRes);
  mytree->Branch ("z0Segment_075xRes", &z0Segment_075xRes);
  mytree->Branch ("z0Segment_025xRes", &z0Segment_025xRes);
  mytree->Branch ("z0Segment_0075xRes", &z0Segment_0075xRes);
  mytree->Branch ("z0Segment_00075xRes", &z0Segment_00075xRes);

  mytree->Branch ("foundPVwindow_1xRes_Nominal", &foundPVwindow_1xRes_Nominal);
  mytree->Branch ("foundPVwindow_01xRes_Nominal", &foundPVwindow_01xRes_Nominal);
  mytree->Branch ("foundPVwindow_05xRes_Nominal", &foundPVwindow_05xRes_Nominal);
  mytree->Branch ("foundPVwindow_005xRes_Nominal", &foundPVwindow_005xRes_Nominal);
  mytree->Branch ("foundPVwindow_0005xRes_Nominal", &foundPVwindow_0005xRes_Nominal);
  mytree->Branch ("foundPVwindow_25xRes_Nominal", &foundPVwindow_25xRes_Nominal);
  mytree->Branch ("foundPVwindow_2xRes_Nominal", &foundPVwindow_2xRes_Nominal);
  mytree->Branch ("foundPVwindow_3xRes_Nominal", &foundPVwindow_3xRes_Nominal);
  mytree->Branch ("foundPVwindow_5xRes_Nominal", &foundPVwindow_5xRes_Nominal);
  mytree->Branch ("foundPVwindow_10xRes_Nominal", &foundPVwindow_10xRes_Nominal);
  mytree->Branch ("foundPVwindow_12xRes_Nominal", &foundPVwindow_12xRes_Nominal);
  mytree->Branch ("foundPVwindow_15xRes_Nominal", &foundPVwindow_15xRes_Nominal);
  mytree->Branch ("foundPVwindow_20xRes_Nominal", &foundPVwindow_20xRes_Nominal);
  mytree->Branch ("foundPVwindow_4xRes_Nominal", &foundPVwindow_4xRes_Nominal);
  mytree->Branch ("foundPVwindow_50xRes_Nominal", &foundPVwindow_50xRes_Nominal);
  mytree->Branch ("foundPVwindow_150xRes_Nominal", &foundPVwindow_150xRes_Nominal);
  mytree->Branch ("foundPVwindow_075xRes_Nominal", &foundPVwindow_075xRes_Nominal);
  mytree->Branch ("foundPVwindow_025xRes_Nominal", &foundPVwindow_025xRes_Nominal);
  mytree->Branch ("foundPVwindow_0075xRes_Nominal", &foundPVwindow_0075xRes_Nominal);
  mytree->Branch ("foundPVwindow_00075xRes_Nominal", &foundPVwindow_00075xRes_Nominal);

  mytree->Branch ("foundPVwindow_double_1xRes_Nominal", &foundPVwindow_double_1xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_01xRes_Nominal", &foundPVwindow_double_01xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_05xRes_Nominal", &foundPVwindow_double_05xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_005xRes_Nominal", &foundPVwindow_double_005xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_0005xRes_Nominal", &foundPVwindow_double_0005xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_25xRes_Nominal", &foundPVwindow_double_25xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_2xRes_Nominal", &foundPVwindow_double_2xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_3xRes_Nominal", &foundPVwindow_double_3xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_5xRes_Nominal", &foundPVwindow_double_5xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_10xRes_Nominal", &foundPVwindow_double_10xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_12xRes_Nominal", &foundPVwindow_double_12xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_15xRes_Nominal", &foundPVwindow_double_15xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_20xRes_Nominal", &foundPVwindow_double_20xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_4xRes_Nominal", &foundPVwindow_double_4xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_50xRes_Nominal", &foundPVwindow_double_50xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_150xRes_Nominal", &foundPVwindow_double_150xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_075xRes_Nominal", &foundPVwindow_double_075xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_025xRes_Nominal", &foundPVwindow_double_025xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_0075xRes_Nominal", &foundPVwindow_double_0075xRes_Nominal);
  mytree->Branch ("foundPVwindow_double_00075xRes_Nominal", &foundPVwindow_double_00075xRes_Nominal);

  mytree->Branch ("foundPVwindow_JetVecs_1xRes_Nominal", &foundPVwindow_JetVecs_1xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_01xRes_Nominal", &foundPVwindow_JetVecs_01xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_05xRes_Nominal", &foundPVwindow_JetVecs_05xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_005xRes_Nominal", &foundPVwindow_JetVecs_005xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_0005xRes_Nominal", &foundPVwindow_JetVecs_0005xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_25xRes_Nominal", &foundPVwindow_JetVecs_25xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_2xRes_Nominal", &foundPVwindow_JetVecs_2xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_3xRes_Nominal", &foundPVwindow_JetVecs_3xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_5xRes_Nominal", &foundPVwindow_JetVecs_5xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_10xRes_Nominal", &foundPVwindow_JetVecs_10xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_12xRes_Nominal", &foundPVwindow_JetVecs_12xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_15xRes_Nominal", &foundPVwindow_JetVecs_15xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_20xRes_Nominal", &foundPVwindow_JetVecs_20xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_4xRes_Nominal", &foundPVwindow_JetVecs_4xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_50xRes_Nominal", &foundPVwindow_JetVecs_50xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_150xRes_Nominal", &foundPVwindow_JetVecs_150xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_075xRes_Nominal", &foundPVwindow_JetVecs_075xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_025xRes_Nominal", &foundPVwindow_JetVecs_025xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_0075xRes_Nominal", &foundPVwindow_JetVecs_0075xRes_Nominal);
  mytree->Branch ("foundPVwindow_JetVecs_00075xRes_Nominal", &foundPVwindow_JetVecs_00075xRes_Nominal);

  mytree->Branch ("z0Segment_1xRes_Nominal", &z0Segment_1xRes_Nominal);
  mytree->Branch ("z0Segment_01xRes_Nominal", &z0Segment_01xRes_Nominal);
  mytree->Branch ("z0Segment_05xRes_Nominal", &z0Segment_005xRes_Nominal);
  mytree->Branch ("z0Segment_005xRes_Nominal", &z0Segment_0005xRes_Nominal);
  mytree->Branch ("z0Segment_0005xRes_Nominal", &z0Segment_05xRes_Nominal);
  mytree->Branch ("z0Segment_25xRes_Nominal", &z0Segment_25xRes_Nominal);
  mytree->Branch ("z0Segment_2xRes_Nominal", &z0Segment_2xRes_Nominal);
  mytree->Branch ("z0Segment_3xRes_Nominal", &z0Segment_3xRes_Nominal);
  mytree->Branch ("z0Segment_5xRes_Nominal", &z0Segment_5xRes_Nominal);
  mytree->Branch ("z0Segment_10xRes_Nominal", &z0Segment_10xRes_Nominal);
  mytree->Branch ("z0Segment_12xRes_Nominal", &z0Segment_12xRes_Nominal);
  mytree->Branch ("z0Segment_15xRes_Nominal", &z0Segment_15xRes_Nominal);
  mytree->Branch ("z0Segment_20xRes_Nominal", &z0Segment_20xRes_Nominal);
  mytree->Branch ("z0Segment_4xRes_Nominal", &z0Segment_4xRes_Nominal);
  mytree->Branch ("z0Segment_50xRes_Nominal", &z0Segment_50xRes_Nominal);
  mytree->Branch ("z0Segment_150xRes_Nominal", &z0Segment_150xRes_Nominal);
  mytree->Branch ("z0Segment_075xRes_Nominal", &z0Segment_075xRes_Nominal);
  mytree->Branch ("z0Segment_025xRes_Nominal", &z0Segment_025xRes_Nominal);
  mytree->Branch ("z0Segment_0075xRes_Nominal", &z0Segment_0075xRes_Nominal);
  mytree->Branch ("z0Segment_00075xRes_Nominal", &z0Segment_00075xRes_Nominal);

  mytree->Branch ("ntracksj1", &ntracksj1);
  mytree->Branch ("ntracksj2", &ntracksj2);
  mytree->Branch ("ntracksj3", &ntracksj3);
  mytree->Branch ("ntracksj4", &ntracksj4);

  mytree->Branch ("j1dr", &j1dr);
  mytree->Branch ("j2dr", &j2dr);
  mytree->Branch ("j3dr", &j3dr);
  mytree->Branch ("j4dr", &j4dr);

  mytree->Branch ("ntracks_tot", &ntracks_tot);
  
  mytree->Branch ("recotruthmatch", &recotruthmatch);


  mytree->Branch ("ntracksj1_Nominal", &ntracksj1_Nominal);
  mytree->Branch ("ntracksj2_Nominal", &ntracksj2_Nominal);
  mytree->Branch ("ntracksj3_Nominal", &ntracksj3_Nominal);
  mytree->Branch ("ntracksj4_Nominal", &ntracksj4_Nominal);

  mytree->Branch ("j1dr_Nominal", &j1dr_Nominal);
  mytree->Branch ("j2dr_Nominal", &j2dr_Nominal);
  mytree->Branch ("j3dr_Nominal", &j3dr_Nominal);
  mytree->Branch ("j4dr_Nominal", &j4dr_Nominal);

  mytree->Branch ("ntracks_tot_Nominal", &ntracks_tot_Nominal);
  
  mytree->Branch ("recotruthmatch_Nominal", &recotruthmatch_Nominal);



  const std::uniform_real_distribution<float>::param_type range{0,1.0};
  m_flat.param( range );

  // const std::string name_JetCalibTools = "MultiJetHTTxAODAnalysis";
  TString jetAlgo = "AntiKt4EMTopo";  // This is for EM scale
  TString config = m_CalibPath;
  TString calibSeq ="JetArea_Residual_Origin_EtaJES";

  bool isData = false;

  m_JetCalibrationTool = new JetCalibrationTool("MultiJetHTTxAODAnalysis");

  
  ANA_CHECK(m_JetCalibrationTool->setProperty("JetCollection",jetAlgo.Data()) );
  ANA_CHECK(m_JetCalibrationTool->setProperty("ConfigFile",config.Data()) );
  ANA_CHECK(m_JetCalibrationTool->setProperty("CalibSequence",calibSeq.Data()) );
  ANA_CHECK(m_JetCalibrationTool->setProperty("IsData",isData) );
  //ANA_CHECK(m_JetCalibrationTool->initialize() );
  ANA_CHECK(m_JetCalibrationTool->initializeTool("MultiJetHTTxAODAnalysis") );


  return StatusCode::SUCCESS;
}



StatusCode MultiJetHTTxAODAnalysis :: execute ()

{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  // ANA_MSG_INFO ("in execute");
  // retrieve the eventInfo object from the event store
  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK (evtStore()->retrieve (eventInfo, "EventInfo"));

const xAOD::TrackParticleContainer* smearedFakeTracks = nullptr;

if (m_isHTTtracks){
  if (evtStore()->retrieve( smearedFakeTracks, m_outputTrackContainerName ).isFailure() )
    {ATH_MSG_ERROR(m_outputTrackContainerName<<" could not be retrieved."); return StatusCode::FAILURE;}
  // else ATH_MSG_INFO(m_outputTrackContainerName<<" container successfully retrieved.");
 }



  ResetVariables();

  // print out run and event number from retrieved object
  // ATH_MSG_INFO("BLSTEST in execute, runNumber = " << eventInfo->runNumber() << ", eventNumber = " << eventInfo->eventNumber());


  TLorentzVector firstjet;   firstjet.SetPtEtaPhiM(0, 0, 0, 0);
  TLorentzVector secondjet;  secondjet.SetPtEtaPhiM(0, 0, 0, 0);
  TLorentzVector thirdjet;   thirdjet.SetPtEtaPhiM(0, 0, 0, 0);
  TLorentzVector fourthjet;  fourthjet.SetPtEtaPhiM(0, 0, 0, 0);

  const xAOD::JetContainer* jets = nullptr;
  ANA_CHECK (evtStore()->retrieve (jets, "AntiKt4EMTopoJets"));

  const xAOD::JetContainer* truthjets = nullptr;
  ANA_CHECK (evtStore()->retrieve (truthjets, "AntiKt4TruthJets"));

  auto shallowCopy = xAOD::shallowCopyContainer( *jets );

std::unique_ptr<xAOD::JetContainer> shallowJets (shallowCopy.first);
std::unique_ptr<xAOD::ShallowAuxContainer> shallowAux (shallowCopy.second);
for (auto jetSC : *shallowJets) {ANA_CHECK(m_JetCalibrationTool->applyCorrection(*jetSC));}
std::sort(shallowCopy.first->begin(), shallowCopy.first->end(), myComparePt);

const xAOD::JetContainer* calibJets = shallowCopy.first;

  for (const xAOD::Jet* jet : *calibJets) {
    if (fabs(jet->eta()) > 3.0) {continue;}
      if (jet->pt() > firstjet.Pt() && jet->pt() * 0.001 > 95){firstjet.SetPtEtaPhiM(jet->pt(), jet->eta(), jet->phi(), jet->m());}
      else if (jet->pt() > secondjet.Pt() && jet->pt() * 0.001 > 60){secondjet.SetPtEtaPhiM(jet->pt(), jet->eta(), jet->phi(), jet->m());}
      else if (jet->pt() > thirdjet.Pt()  && jet->pt() * 0.001 > 30){thirdjet.SetPtEtaPhiM(jet->pt(), jet->eta(), jet->phi(), jet->m());}
      else if (jet->pt() > fourthjet.Pt() && jet->pt() * 0.001 > 30){fourthjet.SetPtEtaPhiM(jet->pt(), jet->eta(), jet->phi(), jet->m());}
  } // end for loop over jets

    if (firstjet.Pt() > 0){hist("multijet_cutflow")->Fill(0);;hist("multijet_cutflow_Nominal")->Fill(0);hist("multijet_cutflow_jetvec")->Fill(0);;hist("multijet_cutflow_Nominal_jetvec")->Fill(0);}
    if (firstjet.Pt() > 0 && secondjet.Pt() > 0){hist("multijet_cutflow")->Fill(1);;hist("multijet_cutflow_Nominal")->Fill(1);hist("multijet_cutflow_jetvec")->Fill(1);;hist("multijet_cutflow_Nominal_jetvec")->Fill(1);}
    if (firstjet.Pt() > 0 && secondjet.Pt() > 0 && thirdjet.Pt() > 0){hist("multijet_cutflow")->Fill(2);;hist("multijet_cutflow_Nominal")->Fill(2);hist("multijet_cutflow_jetvec")->Fill(2);;hist("multijet_cutflow_Nominal_jetvec")->Fill(2);}
    if (firstjet.Pt() > 0 && secondjet.Pt() > 0 && thirdjet.Pt() > 0 && fourthjet.Pt() > 0){hist("multijet_cutflow")->Fill(3);hist("multijet_cutflow_Nominal")->Fill(3);hist("multijet_cutflow_jetvec")->Fill(3);hist("multijet_cutflow_Nominal_jetvec")->Fill(3);
    j1pt = firstjet.Pt() * 0.001;
    j2pt = secondjet.Pt() * 0.001;
    j3pt = thirdjet.Pt() * 0.001;
    j4pt = fourthjet.Pt() * 0.001;}


  float pv_z(0.);
  const xAOD::VertexContainer* vertices = nullptr;
  ANA_CHECK (evtStore()->retrieve (vertices, "PrimaryVertices")); 
  for ( const auto * vtx: *vertices ) {
  if ( vtx->vertexType() == xAOD::VxType::PriVtx ) {
    pv_z = vtx->z();
    break;
  }
  }

  const xAOD::TrackParticleContainer* NominalTracks = nullptr;
  ANA_CHECK (evtStore()->retrieve (NominalTracks, "InDetTrackParticles"));

  xAOD::TrackParticleContainer* myTracks = new xAOD::TrackParticleContainer;

  // ATH_MSG_INFO("ntracks_tot starting " << ntracks_tot);
  // if (m_isHTTtracks){ *myTracks = *smearedFakeTracks; //ATH_MSG_INFO("Using HTT tracks");
  // }
  // else if (!m_isHTTtracks){ *myTracks = *NominalTracks; //ATH_MSG_INFO("BLS Using Nominal tracks");
  // }
  // else{ATH_MSG_INFO("ERROR: Not sure which tracks to use");}

  bool truthmatched = false;
  bool matched1 = false;
  bool matched2 = false;
  bool matched3 = false;
  bool matched4 = false;
  for (const xAOD::Jet* truthjet : *truthjets) {
      float tmp_deta1 = firstjet.Eta()  - truthjet->eta();
      float tmp_dphi1 = firstjet.Phi()  - truthjet->phi();
      float tmp_deta2 = secondjet.Eta() - truthjet->eta();
      float tmp_dphi2 = secondjet.Phi() - truthjet->phi();
      float tmp_deta3 = thirdjet.Eta()  - truthjet->eta();
      float tmp_dphi3 = thirdjet.Phi()  - truthjet->phi();
      float tmp_deta4 = fourthjet.Eta() - truthjet->eta();
      float tmp_dphi4 = fourthjet.Phi() - truthjet->phi();
      if(abs(tmp_dphi1) > TMath::Pi()) tmp_dphi1 = 2 * TMath::Pi() - abs(tmp_dphi1);
      if(abs(tmp_dphi2) > TMath::Pi()) tmp_dphi2 = 2 * TMath::Pi() - abs(tmp_dphi2);
      if(abs(tmp_dphi3) > TMath::Pi()) tmp_dphi3 = 2 * TMath::Pi() - abs(tmp_dphi3);
      if(abs(tmp_dphi4) > TMath::Pi()) tmp_dphi4 = 2 * TMath::Pi() - abs(tmp_dphi4);
      float tmp_dR1 = (sqrt(pow(tmp_dphi1, 2) + pow(tmp_deta1, 2)));
      float tmp_dR2 = (sqrt(pow(tmp_dphi2, 2) + pow(tmp_deta2, 2)));
      float tmp_dR3 = (sqrt(pow(tmp_dphi3, 2) + pow(tmp_deta3, 2)));
      float tmp_dR4 = (sqrt(pow(tmp_dphi4, 2) + pow(tmp_deta4, 2)));
      // ATH_MSG_INFO("tmp_dR1: " << tmp_dR1 << "  tmp_dR2: " << tmp_dR2 << "  tmp_dR3: " << tmp_dR3 << "  tmp_dR4: " << tmp_dR4);
      // ATH_MSG_INFO("truth pt: " << truthjet->pt() * 0.001);
      if (tmp_dR1 < 0.4 && truthjet->pt() * 0.001 > 60){
        matched1 = true;//first jet is matched
      }
      else if (tmp_dR2 < 0.4 && truthjet->pt() * 0.001 > 40){
        matched2 = true;//second jet is matched
      }
      else if (tmp_dR3 < 0.4 && truthjet->pt() * 0.001 > 30){
        matched3 = true;//third jet is matched
      }
      else if (tmp_dR4 < 0.4 && truthjet->pt() * 0.001 > 30){
        matched4 = true;//fourth jet is matched
      }
      // ATH_MSG_INFO("matched to " << matched1<<matched2<< matched3<< matched4);
  }
  if (matched1 && matched2 && matched3 && matched4){recotruthmatch = 1; truthmatched = true;}
  else{recotruthmatch = -999;}


  bool event_pass = false;
  int n_HSjets = 0;
  if (m_issignal && firstjet.Pt() > 0 && secondjet.Pt() > 0 && thirdjet.Pt() > 0 && fourthjet.Pt() > 0){
    float ptj160 = 0;
    float ptj240 = 0;
    float ptj330 = 0;
    float ptj430 = 0;
    for (const xAOD::Jet* truthjet : *truthjets) {
      if (fabs(truthjet->eta()) > 3.0) {continue;}
      if (truthjet->pt() > ptj160 && truthjet->pt() * 0.001 > 60){ptj160 = truthjet->pt();}
      else if (truthjet->pt() > ptj240 && truthjet->pt() * 0.001 > 40){ptj240 = truthjet->pt();}
      else if (truthjet->pt() > ptj330 && truthjet->pt() * 0.001 > 30){ptj330 = truthjet->pt();}
      else if (truthjet->pt() > ptj430 && truthjet->pt() * 0.001 > 30){ptj430 = truthjet->pt();}

      ++n_HSjets;
    }
    // ATH_MSG_INFO("n_HSjets: " << n_HSjets);
    if (ptj160 > 0 && ptj240 > 0 && ptj330 > 0 && ptj430 > 0){event_pass = true;hist("multijet_cutflow")->Fill(4);hist("multijet_cutflow_Nominal")->Fill(4);hist("multijet_cutflow_jetvec")->Fill(4);hist("multijet_cutflow_Nominal_jetvec")->Fill(4);}
    // if (n_HSjets > 3){event_pass = true;}
  }//end of signal-only checks
  else if (firstjet.Pt() > 0 && secondjet.Pt() > 0 && thirdjet.Pt() > 0 && fourthjet.Pt() > 0 && !m_issignal){
    event_pass = true;
  }
  // ATH_MSG_INFO("event_pass " << event_pass);
  if (event_pass){

    // ATH_MSG_INFO("start of event");
    nTruthEvents_3HS = 1;
    nTruthEvents_3HS_Nominal = 1;
    // ATH_MSG_INFO("starting multipliers loop");
    std::vector<std::string> multipliers;

    // if (m_isfixedwindow) {multipliers = {10.};} // fixed window sizes
    if (m_isfixedwindow) {multipliers = {"0.005", "0.0075", "0.075", "0.05", "0.1", "0.25", "0.5", "0.75", "1", "1.5", "2", "2.5", "3", "4", "5", "10", "12", "15", "20", "50"};} // fixed window sizes
    // if (m_isfixedwindow) {multipliers = {0.005, 0.05};} // fixed window sizes
    else {ATH_MSG_INFO("error with window sizes");}
    // if (m_isfixedwindow) {multipliers = {50};} // BLSTEST fixed window sizes
    // if (m_isfixedwindow) {multipliers = {1.};} // fixed window sizes

    bool j1trkfound = false;
    bool j2trkfound = false; 
    bool j3trkfound = false;
    bool j4trkfound = false;

    int count_ntracks = 0;


    bool j1trkfound_Nominal = false;
    bool j2trkfound_Nominal = false; 
    bool j3trkfound_Nominal = false;
    bool j4trkfound_Nominal = false;

    int count_ntracks_Nominal = 0;

    for(std::string multiplier : multipliers){
      // ATH_MSG_INFO("multiplier: " << multiplier);
      double average_dZResTrks = 0;
      // int ntracks = 0;
      float deltaR = 0.4;
      // float deltaR1 = 0.4;
      // float deltaR2 = 0.4;
      // float deltaR3 = 0.4;
      // float deltaR4 = 0.4;
      // double j1trkz0 = -999;
      // double j2trkz0 = -999;
      // double j3trkz0 = -999;
      // double j4trkz0 = -999;
      // double j1trkz0res = -999; 
      // double j2trkz0res = -999; 
      // double j3trkz0res = -999;
      // double j4trkz0res = -999;
      // double j1trkpt = 0;
      // double j2trkpt = 0;
      // double j3trkpt = 0;
      // double j4trkpt = 0;

      // if (m_isfixedwindow){average_dZResTrks = multiplier;}
      // else {ATH_MSG_INFO("ERROR: Not sure how to calculate window");}

      // ATH_MSG_INFO("average_dZResTrks " << average_dZResTrks);
          if (multiplier == "0.1"){average_dZResTrks = 0.1;trk_z0Res_mean_01xRes = average_dZResTrks;}
          else if (multiplier == "0.005"){average_dZResTrks = 0.005;trk_z0Res_mean_0005xRes = average_dZResTrks;}
          else if (multiplier == "0.05"){average_dZResTrks = 0.05;trk_z0Res_mean_005xRes = average_dZResTrks;}
          else if (multiplier == "0.5"){average_dZResTrks = 0.5;trk_z0Res_mean_05xRes = average_dZResTrks;}
      else if (multiplier == "1"){average_dZResTrks = 1.0;trk_z0Res_mean_1xRes = average_dZResTrks;}
      else if (multiplier == "2"){average_dZResTrks = 2.0;trk_z0Res_mean_2xRes = average_dZResTrks;}
      else if (multiplier == "2.5"){average_dZResTrks = 2.5;trk_z0Res_mean_25xRes = average_dZResTrks;}
      else if (multiplier == "3"){average_dZResTrks = 3.0;trk_z0Res_mean_3xRes = average_dZResTrks;}
      else if (multiplier == "5"){average_dZResTrks = 5.0;trk_z0Res_mean_5xRes = average_dZResTrks;}
      else if (multiplier == "10"){average_dZResTrks = 10.0;trk_z0Res_mean_10xRes = average_dZResTrks;}
      else if (multiplier == "12"){average_dZResTrks = 12.0;trk_z0Res_mean_12xRes = average_dZResTrks;}
      else if (multiplier == "15"){average_dZResTrks = 15.0;trk_z0Res_mean_15xRes = average_dZResTrks;}
      else if (multiplier == "20"){average_dZResTrks = 20.0;trk_z0Res_mean_20xRes = average_dZResTrks;}
      else if (multiplier == "4"){average_dZResTrks = 4.0;trk_z0Res_mean_4xRes = average_dZResTrks;}
      else if (multiplier == "50"){average_dZResTrks = 50.0;trk_z0Res_mean_50xRes = average_dZResTrks;}
          else if (multiplier == "1.5"){average_dZResTrks = 1.5;trk_z0Res_mean_150xRes = average_dZResTrks;}
      else if (multiplier == "0.75"){average_dZResTrks = 0.75;trk_z0Res_mean_075xRes = average_dZResTrks;}
      else if (multiplier == "0.25"){average_dZResTrks = 0.25;trk_z0Res_mean_025xRes = average_dZResTrks;}
      else if (multiplier == "0.075"){average_dZResTrks = 0.075;trk_z0Res_mean_0075xRes = average_dZResTrks;}
      else if (multiplier == "0.0075"){average_dZResTrks = 0.0075;trk_z0Res_mean_00075xRes = average_dZResTrks;}
      else{ATH_MSG_INFO("Error in res window loop, unknown multiplier is " << multiplier);}

      // ATH_MSG_INFO("averz0 res is " << average_dZResTrks);
      std::vector<int> event_SegmentN;
      std::vector<int> event_SegmentN_doublebins;

      std::vector<int> jet1_SegmentN;
      std::vector<int> jet2_SegmentN;
      std::vector<int> jet3_SegmentN;
      std::vector<int> jet4_SegmentN;

      std::vector<int> jet1_SegmentN_doublebins;
      std::vector<int> jet2_SegmentN_doublebins;
      std::vector<int> jet3_SegmentN_doublebins;
      std::vector<int> jet4_SegmentN_doublebins;

      double j1tracksumz0 = 0;
      double j2tracksumz0 = 0;
      double j3tracksumz0 = 0;
      double j4tracksumz0 = 0;

      double totalsumz0 = -999;

      std::vector<int> event_SegmentN_Nominal;
      std::vector<int> event_SegmentN_doublebins_Nominal;

      std::vector<int> jet1_SegmentN_Nominal;
      std::vector<int> jet2_SegmentN_Nominal;
      std::vector<int> jet3_SegmentN_Nominal;
      std::vector<int> jet4_SegmentN_Nominal;

      std::vector<int> jet1_SegmentN_doublebins_Nominal;
      std::vector<int> jet2_SegmentN_doublebins_Nominal;
      std::vector<int> jet3_SegmentN_doublebins_Nominal;
      std::vector<int> jet4_SegmentN_doublebins_Nominal;

      double j1tracksumz0_Nominal = 0;
      double j2tracksumz0_Nominal = 0;
      double j3tracksumz0_Nominal = 0;
      double j4tracksumz0_Nominal = 0;

      double totalsumz0_Nominal = -999;
      ntracksj1 = 0;
      ntracksj2 = 0;
      ntracksj3 = 0;
      ntracksj4 = 0;

      ntracksj1_Nominal = 0;
      ntracksj2_Nominal = 0;
      ntracksj3_Nominal = 0;
      ntracksj4_Nominal = 0;

      if (!m_isleadingtracks){// using all track in jet cone
        for (auto trk : *smearedFakeTracks ) {
          if (fabs(trk->eta()) > 3.0 || trk->pt() * 0.001 < 4) {continue;}
          count_ntracks++;
          int matchedto = 0;
          double dZRes = average_dZResTrks * getZ0ResParam_N(fabs(trk->eta()), trk->pt()*0.001) * 0.001;
          trk_z0Res.push_back(dZRes);trk_z0.push_back(trk->z0());
          // if (multiplier == "20"){ATH_MSG_INFO("BLSTEST output track dump -- pt: " << trk->pt()*0.001 << "  eta: " << trk->eta() << "  phi: " << trk->phi() << "  z0: " << trk->z0());}
          float tmp_deta1 = firstjet.Eta() - trk->eta();
          float tmp_dphi1 = firstjet.Phi() - trk->phi();
          if(abs(tmp_dphi1) > TMath::Pi()) tmp_dphi1 = 2 * TMath::Pi() - abs(tmp_dphi1);
          float tmp_dR1 = (sqrt(pow(tmp_dphi1, 2) + pow(tmp_deta1, 2)));
          if (tmp_dR1 < deltaR){
            j1trkfound = true;matchedto = 1;
            j1trackz0.push_back(trk->z0());
            j1tracksumz0 += trk->z0();
            ntracksj1++;
            j1dr = tmp_dR1;
            // std::cout << "BLS TEST smear dr is: " << tmp_dR1 << std::endl;
            // std::cout << "BLS TEST smear eta is: " << trk->eta() << std::endl;
            // std::cout << "BLS TEST smear phi is: " << trk->phi() << std::endl;
            // double z0_max = average_dZResTrks;
            // double z0_min = 0;
            int SegmentN = trk->z0()/average_dZResTrks;
            int SegmentN_doublebins = trk->z0()/(average_dZResTrks/2);
            if (multiplier == "1"){z0Segment_1xRes.push_back(SegmentN);}
            else if (multiplier == "0.1"){z0Segment_01xRes.push_back(SegmentN);}
            else if (multiplier == "0.5"){z0Segment_05xRes.push_back(SegmentN);}
            else if (multiplier == "0.05"){z0Segment_005xRes.push_back(SegmentN);}
            else if (multiplier == "0.005"){z0Segment_0005xRes.push_back(SegmentN);}
            else if (multiplier == "2.5"){z0Segment_25xRes.push_back(SegmentN);}
            else if (multiplier == "2"){z0Segment_2xRes.push_back(SegmentN);}
            else if (multiplier == "3"){z0Segment_3xRes.push_back(SegmentN);}
            else if (multiplier == "5"){z0Segment_5xRes.push_back(SegmentN);}
            else if (multiplier == "10"){z0Segment_10xRes.push_back(SegmentN);}
            else if (multiplier == "12"){z0Segment_12xRes.push_back(SegmentN);}
            else if (multiplier == "15"){z0Segment_15xRes.push_back(SegmentN);}
            else if (multiplier == "20"){z0Segment_20xRes.push_back(SegmentN);}
            else if (multiplier == "4"){z0Segment_4xRes.push_back(SegmentN);}
            else if (multiplier == "50"){z0Segment_50xRes.push_back(SegmentN);}
            else if (multiplier == "1.5"){z0Segment_150xRes.push_back(SegmentN);}
            else if (multiplier == "0.75"){z0Segment_075xRes.push_back(SegmentN);}
            else if (multiplier == "0.25"){z0Segment_025xRes.push_back(SegmentN);}
            else if (multiplier == "0.075"){z0Segment_0075xRes.push_back(SegmentN);}
            else if (multiplier == "0.0075"){z0Segment_00075xRes.push_back(SegmentN);}
            if(std::find(jet1_SegmentN.begin(), jet1_SegmentN.end(), SegmentN) != jet1_SegmentN.end()){continue;}
            else {jet1_SegmentN.push_back(SegmentN);}
            if(std::find(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), SegmentN_doublebins) != jet1_SegmentN_doublebins.end()){continue;}
            else {jet1_SegmentN_doublebins.push_back(SegmentN_doublebins);}
          }//end deltaR check
          float tmp_deta2 = secondjet.Eta() - trk->eta();
          float tmp_dphi2 = secondjet.Phi() - trk->phi();
          if(abs(tmp_dphi2) > TMath::Pi()) tmp_dphi2 = 2 * TMath::Pi() - abs(tmp_dphi2);
          float tmp_dR2 = (sqrt(pow(tmp_dphi2, 2) + pow(tmp_deta2, 2)));
          if (tmp_dR2 < deltaR){
            j2trkfound = true;matchedto = 2;
            j2trackz0.push_back(trk->z0());
            j2tracksumz0 += trk->z0();
            ntracksj2++;
            j2dr = tmp_dR2;
            // std::cout << "j2trkfound" << std::endl;
            // if (firstpass == 1) {count_ntracksj2++;}
            // double z0_max = average_dZResTrks;
            // double z0_min = 0;
            int SegmentN = trk->z0()/average_dZResTrks;
            int SegmentN_doublebins = trk->z0()/(average_dZResTrks/2);
            if (multiplier == "1"){z0Segment_1xRes.push_back(SegmentN);}
            else if (multiplier == "0.1"){z0Segment_01xRes.push_back(SegmentN);}
            else if (multiplier == "0.5"){z0Segment_05xRes.push_back(SegmentN);}
            else if (multiplier == "0.05"){z0Segment_005xRes.push_back(SegmentN);}
            else if (multiplier == "0.005"){z0Segment_0005xRes.push_back(SegmentN);}
            else if (multiplier == "2.5"){z0Segment_25xRes.push_back(SegmentN);}
            else if (multiplier == "2"){z0Segment_2xRes.push_back(SegmentN);}
            else if (multiplier == "3"){z0Segment_3xRes.push_back(SegmentN);}
            else if (multiplier == "5"){z0Segment_5xRes.push_back(SegmentN);}
            else if (multiplier == "10"){z0Segment_10xRes.push_back(SegmentN);}
            else if (multiplier == "12"){z0Segment_12xRes.push_back(SegmentN);}
            else if (multiplier == "15"){z0Segment_15xRes.push_back(SegmentN);}
            else if (multiplier == "20"){z0Segment_20xRes.push_back(SegmentN);}
            else if (multiplier == "4"){z0Segment_4xRes.push_back(SegmentN);}
            else if (multiplier == "50"){z0Segment_50xRes.push_back(SegmentN);}
            else if (multiplier == "1.5"){z0Segment_150xRes.push_back(SegmentN);}
            else if (multiplier == "0.75"){z0Segment_075xRes.push_back(SegmentN);}
            else if (multiplier == "0.25"){z0Segment_025xRes.push_back(SegmentN);}
            else if (multiplier == "0.075"){z0Segment_0075xRes.push_back(SegmentN);}
            else if (multiplier == "0.0075"){z0Segment_00075xRes.push_back(SegmentN);}
            if(std::find(jet2_SegmentN.begin(), jet2_SegmentN.end(), SegmentN) != jet2_SegmentN.end()){continue;}
            else {jet2_SegmentN.push_back(SegmentN);}
            if(std::find(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), SegmentN_doublebins) != jet2_SegmentN_doublebins.end()){continue;}
            else {jet2_SegmentN_doublebins.push_back(SegmentN_doublebins);}
          }//end deltaR check
          float tmp_deta3 = thirdjet.Eta() - trk->eta();
          float tmp_dphi3 = thirdjet.Phi() - trk->phi();
          if(abs(tmp_dphi3) > TMath::Pi()) tmp_dphi3 = 2 * TMath::Pi() - abs(tmp_dphi3);
          float tmp_dR3 = (sqrt(pow(tmp_dphi3, 2) + pow(tmp_deta3, 2)));
          if (tmp_dR3 < deltaR){
            j3trkfound = true;matchedto = 3;
            j3trackz0.push_back(trk->z0());
            j3tracksumz0 += trk->z0();
            ntracksj3++;
            j3dr = tmp_dR3;
            // std::cout << "j3trkfound" << std::endl;
            // if (firstpass == 1) {count_ntracksj3++;}
            // double z0_max = average_dZResTrks;
            // double z0_min = 0;
            int SegmentN = trk->z0()/average_dZResTrks;
            int SegmentN_doublebins = trk->z0()/(average_dZResTrks/2);
            if (multiplier == "1"){z0Segment_1xRes.push_back(SegmentN);}
            else if (multiplier == "0.1"){z0Segment_01xRes.push_back(SegmentN);}
            else if (multiplier == "0.5"){z0Segment_05xRes.push_back(SegmentN);}
            else if (multiplier == "0.05"){z0Segment_005xRes.push_back(SegmentN);}
            else if (multiplier == "0.005"){z0Segment_0005xRes.push_back(SegmentN);}
            else if (multiplier == "2.5"){z0Segment_25xRes.push_back(SegmentN);}
            else if (multiplier == "2"){z0Segment_2xRes.push_back(SegmentN);}
            else if (multiplier == "3"){z0Segment_3xRes.push_back(SegmentN);}
            else if (multiplier == "5"){z0Segment_5xRes.push_back(SegmentN);}
            else if (multiplier == "10"){z0Segment_10xRes.push_back(SegmentN);}
            else if (multiplier == "12"){z0Segment_12xRes.push_back(SegmentN);}
            else if (multiplier == "15"){z0Segment_15xRes.push_back(SegmentN);}
            else if (multiplier == "20"){z0Segment_20xRes.push_back(SegmentN);}
            else if (multiplier == "4"){z0Segment_4xRes.push_back(SegmentN);}
            else if (multiplier == "50"){z0Segment_50xRes.push_back(SegmentN);}
            else if (multiplier == "1.5"){z0Segment_150xRes.push_back(SegmentN);}
            else if (multiplier == "0.75"){z0Segment_075xRes.push_back(SegmentN);}
            else if (multiplier == "0.25"){z0Segment_025xRes.push_back(SegmentN);}
            else if (multiplier == "0.075"){z0Segment_0075xRes.push_back(SegmentN);}
            else if (multiplier == "0.0075"){z0Segment_00075xRes.push_back(SegmentN);}
            if(std::find(jet3_SegmentN.begin(), jet3_SegmentN.end(), SegmentN) != jet3_SegmentN.end()){continue;}
            else {jet3_SegmentN.push_back(SegmentN);}
            if(std::find(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), SegmentN_doublebins) != jet3_SegmentN_doublebins.end()){continue;}
            else {jet3_SegmentN_doublebins.push_back(SegmentN_doublebins);}
          }//end deltaR check
          float tmp_deta4 = fourthjet.Eta() - trk->eta();
          float tmp_dphi4 = fourthjet.Phi() - trk->phi();
          if(abs(tmp_dphi4) > TMath::Pi()) tmp_dphi4 = 2 * TMath::Pi() - abs(tmp_dphi4);
          float tmp_dR4 = (sqrt(pow(tmp_dphi4, 2) + pow(tmp_deta4, 2)));
          if (tmp_dR4 < deltaR){
            j4trkfound = true;matchedto = 4;
            j4trackz0.push_back(trk->z0());
            j4tracksumz0 += trk->z0();
            ntracksj4++;
            j4dr = tmp_dR4;
            // std::cout << "j4trkfound" << std::endl;
            // ATH_MSG_INFO("has track");
            // if (firstpass == 1) {count_ntracksj4++;}
            // double z0_max = average_dZResTrks;
            // double z0_min = 0;
            int SegmentN = trk->z0()/average_dZResTrks;
            int SegmentN_doublebins = trk->z0()/(average_dZResTrks/2);
            if (multiplier == "1"){z0Segment_1xRes.push_back(SegmentN);}
            else if (multiplier == "0.1"){z0Segment_01xRes.push_back(SegmentN);}
            else if (multiplier == "0.5"){z0Segment_05xRes.push_back(SegmentN);}
            else if (multiplier == "0.05"){z0Segment_005xRes.push_back(SegmentN);}
            else if (multiplier == "0.005"){z0Segment_0005xRes.push_back(SegmentN);}
            else if (multiplier == "2.5"){z0Segment_25xRes.push_back(SegmentN);}
            else if (multiplier == "2"){z0Segment_2xRes.push_back(SegmentN);}
            else if (multiplier == "3"){z0Segment_3xRes.push_back(SegmentN);}
            else if (multiplier == "5"){z0Segment_5xRes.push_back(SegmentN);}
            else if (multiplier == "10"){z0Segment_10xRes.push_back(SegmentN);}
            else if (multiplier == "12"){z0Segment_12xRes.push_back(SegmentN);}
            else if (multiplier == "15"){z0Segment_15xRes.push_back(SegmentN);}
            else if (multiplier == "20"){z0Segment_20xRes.push_back(SegmentN);}
            else if (multiplier == "4"){z0Segment_4xRes.push_back(SegmentN);}
            else if (multiplier == "50"){z0Segment_50xRes.push_back(SegmentN);}
            else if (multiplier == "1.5"){z0Segment_150xRes.push_back(SegmentN);}
            else if (multiplier == "0.75"){z0Segment_075xRes.push_back(SegmentN);}
            else if (multiplier == "0.25"){z0Segment_025xRes.push_back(SegmentN);}
            else if (multiplier == "0.075"){z0Segment_0075xRes.push_back(SegmentN);}
            else if (multiplier == "0.0075"){z0Segment_00075xRes.push_back(SegmentN);}
            if(std::find(jet4_SegmentN.begin(), jet4_SegmentN.end(), SegmentN) != jet4_SegmentN.end()){continue;}
            else {jet4_SegmentN.push_back(SegmentN);}
            if(std::find(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), SegmentN_doublebins) != jet4_SegmentN_doublebins.end()){continue;}
            else {jet4_SegmentN_doublebins.push_back(SegmentN_doublebins);}
          }//end deltaR check
          trk_parentID.push_back(trk->numberDoF());
          trk_jetmatch.push_back(matchedto);
          trk_type.push_back(trk->chiSquared());
          // if (multiplier == "20"){ATH_MSG_INFO("BLSTEST output track dump --  intial track: " << trk->numberDoF() << " jet association: " << matchedto << " COREvsTAIL: " << trk->chiSquared() << " FakeKillerEnabled?: "<< m_fakeKiller << " RandomSeed = " << m_randomSeed << " pt: " << trk->pt()*0.001 << "  eta: " << trk->eta() << "  phi: " << trk->phi() << "  z0: " << trk->z0());}
        }//end loop over input tracks
        // ATH_MSG_INFO("count_ntracks post track loop " << count_ntracks);

        for (auto trk : *NominalTracks ) {
          if (fabs(trk->eta()) > 3.0 || trk->pt() * 0.001 < 4) {continue;}
          count_ntracks_Nominal++;
          int matchedto = 0;
          double dZRes = average_dZResTrks * getZ0ResParam_N(fabs(trk->eta()), trk->pt()*0.001) * 0.001;
          trk_z0Res_Nominal.push_back(dZRes);trk_z0.push_back(trk->z0());
          // if (multiplier == "20"){ATH_MSG_INFO("BLSTEST output track dump -- pt: " << trk->pt()*0.001 << "  eta: " << trk->eta() << "  phi: " << trk->phi() << "  z0: " << trk->z0());}
          float tmp_deta1 = firstjet.Eta() - trk->eta();
          float tmp_dphi1 = firstjet.Phi() - trk->phi();
          if(abs(tmp_dphi1) > TMath::Pi()) tmp_dphi1 = 2 * TMath::Pi() - abs(tmp_dphi1);
          float tmp_dR1 = (sqrt(pow(tmp_dphi1, 2) + pow(tmp_deta1, 2)));
          if (tmp_dR1 < deltaR){
            j1trkfound_Nominal = true;matchedto = 1;
            j1trackz0_Nominal.push_back(trk->z0());
            j1tracksumz0_Nominal += trk->z0();
            ntracksj1_Nominal++;
            j1dr_Nominal = tmp_dR1;
            // std::cout << "BLS TEST nominal dr is: " << tmp_dR1 << std::endl;
            // std::cout << "BLS TEST nominal eta is: " << trk->eta() << std::endl;
            // std::cout << "BLS TEST nominal phi is: " << trk->phi() << std::endl;
            // double z0_max = average_dZResTrks;
            // double z0_min = 0;
            int SegmentN = trk->z0()/average_dZResTrks;
            int SegmentN_doublebins = trk->z0()/(average_dZResTrks/2);
            if (multiplier == "1"){z0Segment_1xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.1"){z0Segment_01xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.5"){z0Segment_05xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.05"){z0Segment_005xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.005"){z0Segment_0005xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "2.5"){z0Segment_25xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "2"){z0Segment_2xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "3"){z0Segment_3xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "5"){z0Segment_5xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "10"){z0Segment_10xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "12"){z0Segment_12xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "15"){z0Segment_15xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "20"){z0Segment_20xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "4"){z0Segment_4xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "50"){z0Segment_50xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "1.5"){z0Segment_150xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.75"){z0Segment_075xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.25"){z0Segment_025xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.075"){z0Segment_0075xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.0075"){z0Segment_00075xRes_Nominal.push_back(SegmentN);}
            if(std::find(jet1_SegmentN_Nominal.begin(), jet1_SegmentN_Nominal.end(), SegmentN) != jet1_SegmentN_Nominal.end()){continue;}
            else {jet1_SegmentN_Nominal.push_back(SegmentN);}
            if(std::find(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), SegmentN_doublebins) != jet1_SegmentN_doublebins_Nominal.end()){continue;}
            else {jet1_SegmentN_doublebins_Nominal.push_back(SegmentN_doublebins);}
          }//end deltaR check
          float tmp_deta2 = secondjet.Eta() - trk->eta();
          float tmp_dphi2 = secondjet.Phi() - trk->phi();
          if(abs(tmp_dphi2) > TMath::Pi()) tmp_dphi2 = 2 * TMath::Pi() - abs(tmp_dphi2);
          float tmp_dR2 = (sqrt(pow(tmp_dphi2, 2) + pow(tmp_deta2, 2)));
          if (tmp_dR2 < deltaR){
            j2trkfound_Nominal = true;matchedto = 2;
            j2trackz0_Nominal.push_back(trk->z0());
            j2tracksumz0_Nominal += trk->z0();
            ntracksj2_Nominal++;
            j2dr_Nominal = tmp_dR2;
            // std::cout << "j2trkfound" << std::endl;
            // if (firstpass == 1) {count_ntracksj2++;}
            // double z0_max = average_dZResTrks;
            // double z0_min = 0;
            int SegmentN = trk->z0()/average_dZResTrks;
            int SegmentN_doublebins = trk->z0()/(average_dZResTrks/2);
            if (multiplier == "1"){z0Segment_1xRes.push_back(SegmentN);}
            else if (multiplier == "0.1"){z0Segment_01xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.5"){z0Segment_05xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.05"){z0Segment_005xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.005"){z0Segment_0005xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "2.5"){z0Segment_25xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "2"){z0Segment_2xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "3"){z0Segment_3xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "5"){z0Segment_5xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "10"){z0Segment_10xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "12"){z0Segment_12xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "15"){z0Segment_15xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "20"){z0Segment_20xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "4"){z0Segment_4xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "50"){z0Segment_50xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "1.5"){z0Segment_150xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.75"){z0Segment_075xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.25"){z0Segment_025xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.075"){z0Segment_0075xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.0075"){z0Segment_00075xRes_Nominal.push_back(SegmentN);}
            if(std::find(jet2_SegmentN_Nominal.begin(), jet2_SegmentN_Nominal.end(), SegmentN) != jet2_SegmentN_Nominal.end()){continue;}
            else {jet2_SegmentN_Nominal.push_back(SegmentN);}
            if(std::find(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), SegmentN_doublebins) != jet2_SegmentN_doublebins_Nominal.end()){continue;}
            else {jet2_SegmentN_doublebins_Nominal.push_back(SegmentN_doublebins);}
          }//end deltaR check
          float tmp_deta3 = thirdjet.Eta() - trk->eta();
          float tmp_dphi3 = thirdjet.Phi() - trk->phi();
          if(abs(tmp_dphi3) > TMath::Pi()) tmp_dphi3 = 2 * TMath::Pi() - abs(tmp_dphi3);
          float tmp_dR3 = (sqrt(pow(tmp_dphi3, 2) + pow(tmp_deta3, 2)));
          if (tmp_dR3 < deltaR){
            j3trkfound_Nominal = true;matchedto = 3;
            j3trackz0_Nominal.push_back(trk->z0());
            j3tracksumz0_Nominal += trk->z0();
            ntracksj3_Nominal++;
            j3dr_Nominal = tmp_dR3;
            // std::cout << "j3trkfound" << std::endl;
            // if (firstpass == 1) {count_ntracksj3++;}
            // double z0_max = average_dZResTrks;
            // double z0_min = 0;
            int SegmentN = trk->z0()/average_dZResTrks;
            int SegmentN_doublebins = trk->z0()/(average_dZResTrks/2);
            if (multiplier == "1"){z0Segment_1xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.1"){z0Segment_01xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.5"){z0Segment_05xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.05"){z0Segment_005xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.005"){z0Segment_0005xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "2.5"){z0Segment_25xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "2"){z0Segment_2xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "3"){z0Segment_3xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "5"){z0Segment_5xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "10"){z0Segment_10xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "12"){z0Segment_12xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "15"){z0Segment_15xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "20"){z0Segment_20xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "4"){z0Segment_4xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "50"){z0Segment_50xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "1.5"){z0Segment_150xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.75"){z0Segment_075xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.25"){z0Segment_025xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.075"){z0Segment_0075xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.0075"){z0Segment_00075xRes_Nominal.push_back(SegmentN);}
            if(std::find(jet3_SegmentN_Nominal.begin(), jet3_SegmentN_Nominal.end(), SegmentN) != jet3_SegmentN_Nominal.end()){continue;}
            else {jet3_SegmentN_Nominal.push_back(SegmentN);}
            if(std::find(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), SegmentN_doublebins) != jet3_SegmentN_doublebins_Nominal.end()){continue;}
            else {jet3_SegmentN_doublebins_Nominal.push_back(SegmentN_doublebins);}
          }//end deltaR check
          float tmp_deta4 = fourthjet.Eta() - trk->eta();
          float tmp_dphi4 = fourthjet.Phi() - trk->phi();
          if(abs(tmp_dphi4) > TMath::Pi()) tmp_dphi4 = 2 * TMath::Pi() - abs(tmp_dphi4);
          float tmp_dR4 = (sqrt(pow(tmp_dphi4, 2) + pow(tmp_deta4, 2)));
          if (tmp_dR4 < deltaR){
            j4trkfound_Nominal = true;matchedto = 4;
            j4trackz0_Nominal.push_back(trk->z0());
            j4tracksumz0_Nominal += trk->z0();
            ntracksj4_Nominal++;
            j4dr_Nominal = tmp_dR4;
            // std::cout << "j4trkfound" << std::endl;
            // ATH_MSG_INFO("has track");
            // if (firstpass == 1) {count_ntracksj4++;}
            // double z0_max = average_dZResTrks;
            // double z0_min = 0;
            int SegmentN = trk->z0()/average_dZResTrks;
            int SegmentN_doublebins = trk->z0()/(average_dZResTrks/2);
            if (multiplier == "1"){z0Segment_1xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.1"){z0Segment_01xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.5"){z0Segment_05xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.05"){z0Segment_005xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.005"){z0Segment_0005xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "2.5"){z0Segment_25xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "2"){z0Segment_2xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "3"){z0Segment_3xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "5"){z0Segment_5xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "10"){z0Segment_10xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "12"){z0Segment_12xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "15"){z0Segment_15xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "20"){z0Segment_20xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "4"){z0Segment_4xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "50"){z0Segment_50xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "1.5"){z0Segment_150xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.75"){z0Segment_075xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.25"){z0Segment_025xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.075"){z0Segment_0075xRes_Nominal.push_back(SegmentN);}
            else if (multiplier == "0.0075"){z0Segment_00075xRes_Nominal.push_back(SegmentN);}
            if(std::find(jet4_SegmentN_Nominal.begin(), jet4_SegmentN_Nominal.end(), SegmentN) != jet4_SegmentN_Nominal.end()){continue;}
            else {jet4_SegmentN_Nominal.push_back(SegmentN);}
            if(std::find(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), SegmentN_doublebins) != jet4_SegmentN_doublebins_Nominal.end()){continue;}
            else {jet4_SegmentN_doublebins_Nominal.push_back(SegmentN_doublebins);}
          }//end deltaR check
          // trk_parentID.push_back(trk->numberDoF());
          trk_jetmatch_Nominal.push_back(matchedto);
          // trk_type.push_back(trk->chiSquared());
          // if (multiplier == "20"){ATH_MSG_INFO("BLSTEST output track dump --  intial track: " << trk->numberDoF() << " jet association: " << matchedto << " COREvsTAIL: " << trk->chiSquared() << " FakeKillerEnabled?: "<< m_fakeKiller << " RandomSeed = " << m_randomSeed << " pt: " << trk->pt()*0.001 << "  eta: " << trk->eta() << "  phi: " << trk->phi() << "  z0: " << trk->z0());}
        }//end loop over input tracks

      }//END OF using all track in jet cone
      else {ATH_MSG_INFO("Error in finding tracks in jets");}
      j1trackavgz0 = j1tracksumz0 / ntracksj1;
      j2trackavgz0 = j2tracksumz0 / ntracksj2;
      j3trackavgz0 = j3tracksumz0 / ntracksj3;
      j4trackavgz0 = j4tracksumz0 / ntracksj4;

      j1trackavgz0_Nominal = j1tracksumz0_Nominal / ntracksj1_Nominal;
      j2trackavgz0_Nominal = j2tracksumz0_Nominal / ntracksj2_Nominal;
      j3trackavgz0_Nominal = j3tracksumz0_Nominal / ntracksj3_Nominal;
      j4trackavgz0_Nominal = j4tracksumz0_Nominal / ntracksj4_Nominal;
      //

      for (int i = 0; i < jet1_SegmentN.size(); i++) {event_SegmentN.push_back(jet1_SegmentN[i]);}//ATH_MSG_INFO("BLS jet1_SegmentN: " << jet1_SegmentN[i]);}
      for (int i = 0; i < jet2_SegmentN.size(); i++) {event_SegmentN.push_back(jet2_SegmentN[i]);}//ATH_MSG_INFO("BLS jet2_SegmentN: " << jet2_SegmentN[i]);}
      for (int i = 0; i < jet3_SegmentN.size(); i++) {event_SegmentN.push_back(jet3_SegmentN[i]);}//ATH_MSG_INFO("BLS jet3_SegmentN: " << jet3_SegmentN[i]);}
      for (int i = 0; i < jet4_SegmentN.size(); i++) {event_SegmentN.push_back(jet4_SegmentN[i]);}//ATH_MSG_INFO("BLS jet4_SegmentN: " << jet4_SegmentN[i]);}
      for (int i = 0; i < jet1_SegmentN_doublebins.size(); i++) {event_SegmentN_doublebins.push_back(jet1_SegmentN_doublebins[i]);}//ATH_MSG_INFO("BLS jet1_SegmentN_doublebins: " << jet1_SegmentN_doublebins[i]);}
      for (int i = 0; i < jet2_SegmentN_doublebins.size(); i++) {event_SegmentN_doublebins.push_back(jet2_SegmentN_doublebins[i]);}//ATH_MSG_INFO("BLS jet2_SegmentN_doublebins: " << jet2_SegmentN_doublebins[i]);}
      for (int i = 0; i < jet3_SegmentN_doublebins.size(); i++) {event_SegmentN_doublebins.push_back(jet3_SegmentN_doublebins[i]);}//ATH_MSG_INFO("BLS jet3_SegmentN_doublebins: " << jet3_SegmentN_doublebins[i]);}
      for (int i = 0; i < jet4_SegmentN_doublebins.size(); i++) {event_SegmentN_doublebins.push_back(jet4_SegmentN_doublebins[i]);}//ATH_MSG_INFO("BLS jet4_SegmentN_doublebins: " << jet4_SegmentN_doublebins[i]);}


      for (int i = 0; i < jet1_SegmentN_Nominal.size(); i++) {event_SegmentN_Nominal.push_back(jet1_SegmentN_Nominal[i]);}//ATH_MSG_INFO("BLS jet1_SegmentN_Nominal: " << jet1_SegmentN_Nominal[i]);}
      for (int i = 0; i < jet2_SegmentN_Nominal.size(); i++) {event_SegmentN_Nominal.push_back(jet2_SegmentN_Nominal[i]);}//ATH_MSG_INFO("BLS jet2_SegmentN_Nominal: " << jet2_SegmentN_Nominal[i]);}
      for (int i = 0; i < jet3_SegmentN_Nominal.size(); i++) {event_SegmentN_Nominal.push_back(jet3_SegmentN_Nominal[i]);}//ATH_MSG_INFO("BLS jet3_SegmentN_Nominal: " << jet3_SegmentN_Nominal[i]);}
      for (int i = 0; i < jet4_SegmentN_Nominal.size(); i++) {event_SegmentN_Nominal.push_back(jet4_SegmentN_Nominal[i]);}//ATH_MSG_INFO("BLS jet4_SegmentN_Nominal: " << jet4_SegmentN_Nominal[i]);}
      for (int i = 0; i < jet1_SegmentN_doublebins_Nominal.size(); i++) {event_SegmentN_doublebins_Nominal.push_back(jet1_SegmentN_doublebins_Nominal[i]);}//ATH_MSG_INFO("BLS jet1_SegmentN_doublebins_Nominal: " << jet1_SegmentN_doublebins_Nominal[i]);}
      for (int i = 0; i < jet2_SegmentN_doublebins_Nominal.size(); i++) {event_SegmentN_doublebins_Nominal.push_back(jet2_SegmentN_doublebins_Nominal[i]);}//ATH_MSG_INFO("BLS jet2_SegmentN_doublebins_Nominal: " << jet2_SegmentN_doublebins_Nominal[i]);}
      for (int i = 0; i < jet3_SegmentN_doublebins_Nominal.size(); i++) {event_SegmentN_doublebins_Nominal.push_back(jet3_SegmentN_doublebins_Nominal[i]);}//ATH_MSG_INFO("BLS jet3_SegmentN_doublebins_Nominal: " << jet3_SegmentN_doublebins_Nominal[i]);}
      for (int i = 0; i < jet4_SegmentN_doublebins_Nominal.size(); i++) {event_SegmentN_doublebins_Nominal.push_back(jet4_SegmentN_doublebins_Nominal[i]);}//ATH_MSG_INFO("BLS jet4_SegmentN_doublebins_Nominal: " << jet4_SegmentN_doublebins_Nominal[i]);}


      if (j1trkfound && j2trkfound && j3trkfound && event_pass){//requires tracks in first 3 jets
        nTruthEvents_3HS4trk = 1;
        // ATH_MSG_INFO("multiplier: " << multiplier);
        // ATH_MSG_INFO("event_SegmentN.size(): " << event_SegmentN.size());
        // ATH_MSG_INFO("event_SegmentN_doublebins.size(): " << event_SegmentN_doublebins.size());


        bool pass = false;
        bool jetpass = false;
        for (int i = 0; i < event_SegmentN.size(); i++) {
          // ATH_MSG_INFO("event_SegmentN[i]: " << event_SegmentN[i]);
          if (count(event_SegmentN.begin(), event_SegmentN.end(), event_SegmentN[i]) > 2){
            // ATH_MSG_INFO(event_pass << " foundPV");
          //checking for 3 jet tracks in same window in events with 4 tracks
            pass = true;
            if (multiplier == "1"){foundPVwindow_1xRes = 1;}
            else if (multiplier == "0.1"){foundPVwindow_01xRes = 1;}
            else if (multiplier == "0.5"){foundPVwindow_05xRes = 1;}
            else if (multiplier == "0.05"){foundPVwindow_005xRes = 1;}
            else if (multiplier == "0.005"){foundPVwindow_0005xRes = 1;}
            else if (multiplier == "2.5"){foundPVwindow_25xRes = 1;}
            else if (multiplier == "2"){foundPVwindow_2xRes = 1;}
            else if (multiplier == "3"){foundPVwindow_3xRes = 1;}
            else if (multiplier == "5"){foundPVwindow_5xRes = 1;}
            else if (multiplier == "10"){foundPVwindow_10xRes = 1;}
            else if (multiplier == "12"){foundPVwindow_12xRes = 1;}
            else if (multiplier == "15"){foundPVwindow_15xRes = 1;}
            else if (multiplier == "20"){foundPVwindow_20xRes = 1;}
            else if (multiplier == "4"){foundPVwindow_4xRes = 1;}
            else if (multiplier == "50"){foundPVwindow_50xRes = 1;}
            else if (multiplier == "1.5"){foundPVwindow_150xRes = 1;}
            else if (multiplier == "0.75"){foundPVwindow_075xRes = 1;}
            else if (multiplier == "0.25"){foundPVwindow_025xRes = 1;}        
            else if (multiplier == "0.075"){foundPVwindow_0075xRes = 1;}        
            else if (multiplier == "0.0075"){foundPVwindow_00075xRes = 1;}        
          }
          // else{ATH_MSG_INFO( event_pass << " not foundPV");}
        }

        // in one val is in 3 different jets
        for (int i = 0; i < jet1_SegmentN.size(); i++) {
          if (count(jet2_SegmentN.begin(), jet2_SegmentN.end(), jet1_SegmentN[i]) && (count(jet3_SegmentN.begin(), jet3_SegmentN.end(), jet1_SegmentN[i]))){jetpass = true;}
          if (count(jet2_SegmentN.begin(), jet2_SegmentN.end(), jet1_SegmentN[i]) && (count(jet4_SegmentN.begin(), jet4_SegmentN.end(), jet1_SegmentN[i]))){jetpass = true;}
          if (count(jet3_SegmentN.begin(), jet3_SegmentN.end(), jet1_SegmentN[i]) && (count(jet4_SegmentN.begin(), jet4_SegmentN.end(), jet1_SegmentN[i]))){jetpass = true;}
        }
        for (int i = 0; i < jet2_SegmentN.size(); i++) {
          if (count(jet1_SegmentN.begin(), jet1_SegmentN.end(), jet2_SegmentN[i]) && (count(jet3_SegmentN.begin(), jet3_SegmentN.end(), jet2_SegmentN[i]))){jetpass = true;}
          if (count(jet3_SegmentN.begin(), jet3_SegmentN.end(), jet2_SegmentN[i]) && (count(jet4_SegmentN.begin(), jet4_SegmentN.end(), jet2_SegmentN[i]))){jetpass = true;}
          if (count(jet1_SegmentN.begin(), jet1_SegmentN.end(), jet2_SegmentN[i]) && (count(jet4_SegmentN.begin(), jet4_SegmentN.end(), jet2_SegmentN[i]))){jetpass = true;}
        }
        for (int i = 0; i < jet3_SegmentN.size(); i++) {
          if (count(jet2_SegmentN.begin(), jet2_SegmentN.end(), jet3_SegmentN[i]) && (count(jet1_SegmentN.begin(), jet1_SegmentN.end(), jet3_SegmentN[i]))){jetpass = true;}
          if (count(jet2_SegmentN.begin(), jet2_SegmentN.end(), jet3_SegmentN[i]) && (count(jet4_SegmentN.begin(), jet4_SegmentN.end(), jet3_SegmentN[i]))){jetpass = true;}
          if (count(jet1_SegmentN.begin(), jet1_SegmentN.end(), jet3_SegmentN[i]) && (count(jet4_SegmentN.begin(), jet4_SegmentN.end(), jet3_SegmentN[i]))){jetpass = true;}
        }
        for (int i = 0; i < jet4_SegmentN.size(); i++) {
          if (count(jet2_SegmentN.begin(), jet2_SegmentN.end(), jet4_SegmentN[i]) && (count(jet3_SegmentN.begin(), jet3_SegmentN.end(), jet4_SegmentN[i]))){jetpass = true;}
          if (count(jet2_SegmentN.begin(), jet2_SegmentN.end(), jet4_SegmentN[i]) && (count(jet1_SegmentN.begin(), jet1_SegmentN.end(), jet4_SegmentN[i]))){jetpass = true;}
          if (count(jet3_SegmentN.begin(), jet3_SegmentN.end(), jet4_SegmentN[i]) && (count(jet1_SegmentN.begin(), jet1_SegmentN.end(), jet4_SegmentN[i]))){jetpass = true;}
        }

        // in one val is in 3 different jets
        for (int i = 0; i < jet1_SegmentN_doublebins.size(); i++) {
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
        }
        for (int i = 0; i < jet2_SegmentN_doublebins.size(); i++) {
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
        }
        for (int i = 0; i < jet3_SegmentN_doublebins.size(); i++) {
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
        }
        for (int i = 0; i < jet4_SegmentN_doublebins.size(); i++) {
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
        }

        // in one val +/- 1 is in 2 other jets --> 3 in a row
        for (int i = 0; i < jet1_SegmentN_doublebins.size(); i++) {
          int up = jet1_SegmentN_doublebins[i] + 1;
          int down = jet1_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))) {jetpass = true;}
          
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))) {jetpass = true;}
          
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up)   && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down))) {jetpass = true;}
        }
        for (int i = 0; i < jet2_SegmentN_doublebins.size(); i++) {
          int up = jet2_SegmentN_doublebins[i] + 1;
          int down = jet2_SegmentN_doublebins[i] - 1;
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))) {jetpass = true;}
          
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))) {jetpass = true;}
          
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up)   && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down))) {jetpass = true;}

        }
        for (int i = 0; i < jet3_SegmentN_doublebins.size(); i++) {
          int up = jet3_SegmentN_doublebins[i] + 1;
          int down = jet3_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))) {jetpass = true;}
          
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))) {jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))) {jetpass = true;}
          
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up)   && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down))) {jetpass = true;}

        }
        for (int i = 0; i < jet4_SegmentN_doublebins.size(); i++) {
          int up = jet4_SegmentN_doublebins[i] + 1;
          int down = jet4_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down))) {jetpass = true;}
          
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down))) {jetpass = true;}
          
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up))) {jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down))) {jetpass = true;}

        }

        // in one val is in a jet and +/- 1 is in other jet --> val val +/- 1
        for (int i = 0; i < jet1_SegmentN_doublebins.size(); i++) {
          int up = jet1_SegmentN_doublebins[i] + 1;
          int down = jet1_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))){jetpass = true;}

          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))){jetpass = true;}

          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down))){jetpass = true;}

        }

        for (int i = 0; i < jet2_SegmentN_doublebins.size(); i++) {
          int up = jet2_SegmentN_doublebins[i] + 1;
          int down = jet2_SegmentN_doublebins[i] - 1;
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))){jetpass = true;}

          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))){jetpass = true;}

          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down))){jetpass = true;}

        }

        for (int i = 0; i < jet3_SegmentN_doublebins.size(); i++) {
          int up = jet3_SegmentN_doublebins[i] + 1;
          int down = jet3_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))){jetpass = true;}

          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down))){jetpass = true;}

          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down))){jetpass = true;}

        }

        for (int i = 0; i < jet4_SegmentN_doublebins.size(); i++) {
          int up = jet4_SegmentN_doublebins[i] + 1;
          int down = jet4_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up)   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down))){jetpass = true;}

          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down))){jetpass = true;}

          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up)   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down))){jetpass = true;}

        }


        // in one val is in a jet and +/- 1 is in other jet --> up up val
        for (int i = 0; i < jet1_SegmentN_doublebins.size(); i++) {
          int up = jet1_SegmentN_doublebins[i] + 1;
          int down = jet1_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i])   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
        }

        for (int i = 0; i < jet2_SegmentN_doublebins.size(); i++) {
          int up = jet2_SegmentN_doublebins[i] + 1;
          int down = jet2_SegmentN_doublebins[i] - 1;
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i])   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
        }

        for (int i = 0; i < jet3_SegmentN_doublebins.size(); i++) {
          int up = jet3_SegmentN_doublebins[i] + 1;
          int down = jet3_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), up) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i])   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
        }

        for (int i = 0; i < jet4_SegmentN_doublebins.size(); i++) {
          int up = jet4_SegmentN_doublebins[i] + 1;
          int down = jet4_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), up) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i])   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), up) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i])   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), up) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i])   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
        }

        // in one val is in a jet and +/- 1 is in other jet --> down down val
        for (int i = 0; i < jet1_SegmentN_doublebins.size(); i++) {
          int up = jet1_SegmentN_doublebins[i] + 1;
          int down = jet1_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i])   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet1_SegmentN_doublebins[i]))){jetpass = true;}
        }

        for (int i = 0; i < jet2_SegmentN_doublebins.size(); i++) {
          int up = jet2_SegmentN_doublebins[i] + 1;
          int down = jet2_SegmentN_doublebins[i] - 1;
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i])   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet2_SegmentN_doublebins[i]))){jetpass = true;}
        }

        for (int i = 0; i < jet3_SegmentN_doublebins.size(); i++) {
          int up = jet3_SegmentN_doublebins[i] + 1;
          int down = jet3_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) && (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i])   || count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet4_SegmentN_doublebins.begin(), jet4_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i])   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet3_SegmentN_doublebins[i]))){jetpass = true;}
        }

        for (int i = 0; i < jet4_SegmentN_doublebins.size(); i++) {
          int up = jet4_SegmentN_doublebins[i] + 1;
          int down = jet4_SegmentN_doublebins[i] - 1;
          if (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), down) && (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i])   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i])   || count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
          if (count(jet1_SegmentN_doublebins.begin(), jet1_SegmentN_doublebins.end(), down) && (count(jet2_SegmentN_doublebins.begin(), jet2_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i])   || count(jet3_SegmentN_doublebins.begin(), jet3_SegmentN_doublebins.end(), jet4_SegmentN_doublebins[i]))){jetpass = true;}
        }


        if (jetpass){
            if (multiplier == "1"){foundPVwindow_JetVecs_1xRes = 1;}
            else if (multiplier == "0.1"){foundPVwindow_JetVecs_01xRes = 1;}
            else if (multiplier == "0.5"){foundPVwindow_JetVecs_05xRes = 1;}
            else if (multiplier == "0.05"){foundPVwindow_JetVecs_005xRes = 1;}
            else if (multiplier == "0.005"){foundPVwindow_JetVecs_0005xRes = 1;}
            else if (multiplier == "2.5"){foundPVwindow_JetVecs_25xRes = 1;}
            else if (multiplier == "2"){foundPVwindow_JetVecs_2xRes = 1;}
            else if (multiplier == "3"){foundPVwindow_JetVecs_3xRes = 1;}
            else if (multiplier == "5"){foundPVwindow_JetVecs_5xRes = 1;}
            else if (multiplier == "10"){foundPVwindow_JetVecs_10xRes = 1;}
            else if (multiplier == "12"){foundPVwindow_JetVecs_12xRes = 1;}
            else if (multiplier == "15"){foundPVwindow_JetVecs_15xRes = 1;}
            else if (multiplier == "20"){foundPVwindow_JetVecs_20xRes = 1;}
            else if (multiplier == "4"){foundPVwindow_JetVecs_4xRes = 1;}
            else if (multiplier == "50"){foundPVwindow_JetVecs_50xRes = 1;}
            else if (multiplier == "1.5"){foundPVwindow_JetVecs_150xRes = 1;}
            else if (multiplier == "0.75"){foundPVwindow_JetVecs_075xRes = 1;}
            else if (multiplier == "0.25"){foundPVwindow_JetVecs_025xRes = 1;}        
            else if (multiplier == "0.075"){foundPVwindow_JetVecs_0075xRes = 1;}        
            else if (multiplier == "0.0075"){foundPVwindow_JetVecs_00075xRes = 1;}  
        }
        if (!pass){
          for (int i = 0; i < event_SegmentN_doublebins.size(); i++) {
            // ATH_MSG_INFO("event_SegmentN_doublebins[i]: " << event_SegmentN_doublebins[i]);
            // cout << "double " << event_SegmentN_doublebins[i] << endl;
            int nextval = event_SegmentN_doublebins[i]+1;//cout << "checking for " << nextval << endl;
            int prevval = event_SegmentN_doublebins[i]-1;//cout << "checking for " << prevval << endl;
            if (std::find(event_SegmentN_doublebins.begin(), event_SegmentN_doublebins.end(),nextval)!=event_SegmentN_doublebins.end()){
              if (std::find(event_SegmentN_doublebins.begin(), event_SegmentN_doublebins.end(),prevval)!=event_SegmentN_doublebins.end()){

                // ATH_MSG_INFO("event passes double bins 1");
                if (multiplier == "1"){foundPVwindow_double_1xRes = 1;}
                else if (multiplier == "0.1"){foundPVwindow_double_01xRes = 1;}
                else if (multiplier == "0.5"){foundPVwindow_double_05xRes = 1;}
                else if (multiplier == "0.05"){foundPVwindow_double_005xRes = 1;}
                else if (multiplier == "0.005"){foundPVwindow_double_0005xRes = 1;}
                else if (multiplier == "2.5"){foundPVwindow_double_25xRes = 1;}
                else if (multiplier == "2"){foundPVwindow_double_2xRes = 1;}
                else if (multiplier == "3"){foundPVwindow_double_3xRes = 1;}
                else if (multiplier == "5"){foundPVwindow_double_5xRes = 1;}
                else if (multiplier == "10"){foundPVwindow_double_10xRes = 1;}
                else if (multiplier == "12"){foundPVwindow_double_12xRes = 1;}
                else if (multiplier == "15"){foundPVwindow_double_15xRes = 1;}
                else if (multiplier == "20"){foundPVwindow_double_20xRes = 1;}
                else if (multiplier == "4"){foundPVwindow_double_4xRes = 1;}
                else if (multiplier == "50"){foundPVwindow_double_50xRes = 1;}
                else if (multiplier == "1.5"){foundPVwindow_double_150xRes = 1;}
                else if (multiplier == "0.75"){foundPVwindow_double_075xRes = 1;}
                else if (multiplier == "0.25"){foundPVwindow_double_025xRes = 1;}        
                else if (multiplier == "0.075"){foundPVwindow_double_0075xRes = 1;}        
                else if (multiplier == "0.0075"){foundPVwindow_double_00075xRes = 1;}  
              }
            }
            if ((count(event_SegmentN_doublebins.begin(), event_SegmentN_doublebins.end(), event_SegmentN_doublebins[i]) > 1) && (std::find(event_SegmentN_doublebins.begin(), event_SegmentN_doublebins.end(),nextval)!=event_SegmentN_doublebins.end())){
                // ATH_MSG_INFO("event passes double bins 2");
              if (multiplier == "1"){foundPVwindow_double_1xRes = 1;}
              else if (multiplier == "0.1"){foundPVwindow_double_01xRes = 1;}
              else if (multiplier == "0.5"){foundPVwindow_double_05xRes = 1;}
              else if (multiplier == "0.05"){foundPVwindow_double_005xRes = 1;}
              else if (multiplier == "0.005"){foundPVwindow_double_0005xRes = 1;}
              else if (multiplier == "2.5"){foundPVwindow_double_25xRes = 1;}
              else if (multiplier == "2"){foundPVwindow_double_2xRes = 1;}
              else if (multiplier == "3"){foundPVwindow_double_3xRes = 1;}
              else if (multiplier == "5"){foundPVwindow_double_5xRes = 1;}
              else if (multiplier == "10"){foundPVwindow_double_10xRes = 1;}
              else if (multiplier == "12"){foundPVwindow_double_12xRes = 1;}
              else if (multiplier == "15"){foundPVwindow_double_15xRes = 1;}
              else if (multiplier == "20"){foundPVwindow_double_20xRes = 1;}
              else if (multiplier == "4"){foundPVwindow_double_4xRes = 1;}
              else if (multiplier == "50"){foundPVwindow_double_50xRes = 1;}
              else if (multiplier == "1.5"){foundPVwindow_double_150xRes = 1;}
              else if (multiplier == "0.75"){foundPVwindow_double_075xRes = 1;}
              else if (multiplier == "0.25"){foundPVwindow_double_025xRes = 1;}        
              else if (multiplier == "0.075"){foundPVwindow_double_0075xRes = 1;}        
              else if (multiplier == "0.0075"){foundPVwindow_double_00075xRes = 1;}  
            }
            else if ((count(event_SegmentN_doublebins.begin(), event_SegmentN_doublebins.end(), event_SegmentN_doublebins[i]) > 1) && (std::find(event_SegmentN_doublebins.begin(), event_SegmentN_doublebins.end(),prevval)!=event_SegmentN_doublebins.end())){
                // ATH_MSG_INFO("event passes double bins 3");
              if (multiplier == "1"){foundPVwindow_double_1xRes = 1;}
              else if (multiplier == "0.1"){foundPVwindow_double_01xRes = 1;}
              else if (multiplier == "0.5"){foundPVwindow_double_05xRes = 1;}
              else if (multiplier == "0.05"){foundPVwindow_double_005xRes = 1;}
              else if (multiplier == "0.005"){foundPVwindow_double_0005xRes = 1;}
              else if (multiplier == "2.5"){foundPVwindow_double_25xRes = 1;}
              else if (multiplier == "2"){foundPVwindow_double_2xRes = 1;}
              else if (multiplier == "3"){foundPVwindow_double_3xRes = 1;}
              else if (multiplier == "5"){foundPVwindow_double_5xRes = 1;}
              else if (multiplier == "10"){foundPVwindow_double_10xRes = 1;}
              else if (multiplier == "12"){foundPVwindow_double_12xRes = 1;}
              else if (multiplier == "15"){foundPVwindow_double_15xRes = 1;}
              else if (multiplier == "20"){foundPVwindow_double_20xRes = 1;}
              else if (multiplier == "4"){foundPVwindow_double_4xRes = 1;}
              else if (multiplier == "50"){foundPVwindow_double_50xRes = 1;}
              else if (multiplier == "1.5"){foundPVwindow_double_150xRes = 1;}
              else if (multiplier == "0.75"){foundPVwindow_double_075xRes = 1;}
              else if (multiplier == "0.25"){foundPVwindow_double_025xRes = 1;}        
              else if (multiplier == "0.075"){foundPVwindow_double_0075xRes = 1;}        
              else if (multiplier == "0.0075"){foundPVwindow_double_00075xRes = 1;}  
            }
          }//end loop over double bins
        }//end of check for if it doesn't pass 3 jets in same regular window
        else{ //if passes single window, it passes double windows too 
            if (multiplier == "1"){foundPVwindow_double_1xRes = 1;}
            else if (multiplier == "0.1"){foundPVwindow_double_01xRes = 1;}
            else if (multiplier == "0.5"){foundPVwindow_double_05xRes = 1;}
            else if (multiplier == "0.05"){foundPVwindow_double_005xRes = 1;}
            else if (multiplier == "0.005"){foundPVwindow_double_0005xRes = 1;}
            else if (multiplier == "2.5"){foundPVwindow_double_25xRes = 1;}
            else if (multiplier == "2"){foundPVwindow_double_2xRes = 1;}
            else if (multiplier == "3"){foundPVwindow_double_3xRes = 1;}
            else if (multiplier == "5"){foundPVwindow_double_5xRes = 1;}
            else if (multiplier == "10"){foundPVwindow_double_10xRes = 1;}
            else if (multiplier == "12"){foundPVwindow_double_12xRes = 1;}
            else if (multiplier == "15"){foundPVwindow_double_15xRes = 1;}
            else if (multiplier == "20"){foundPVwindow_double_20xRes = 1;}
            else if (multiplier == "4"){foundPVwindow_double_4xRes = 1;}
            else if (multiplier == "50"){foundPVwindow_double_50xRes = 1;}
            else if (multiplier == "1.5"){foundPVwindow_double_150xRes = 1;}
            else if (multiplier == "0.75"){foundPVwindow_double_075xRes = 1;}
            else if (multiplier == "0.25"){foundPVwindow_double_025xRes = 1;}        
            else if (multiplier == "0.075"){foundPVwindow_double_0075xRes = 1;}        
            else if (multiplier == "0.0075"){foundPVwindow_double_00075xRes = 1;}  
        }//end of if it passes original windows, it passes double windows too
      }//track requirements (first 3 jets)

      if (j1trkfound_Nominal && j2trkfound_Nominal && j3trkfound_Nominal && event_pass){//requires tracks in first 3 jets
        nTruthEvents_3HS4trk_Nominal = 1;
        // ATH_MSG_INFO("Nominal multiplier: " << multiplier);
        // ATH_MSG_INFO("event_SegmentN_Nominal.size(): " << event_SegmentN_Nominal.size());
        // ATH_MSG_INFO("event_SegmentN_doublebins_Nominal.size(): " << event_SegmentN_doublebins_Nominal.size());

        bool pass = false;
        bool jetpass_Nominal = false;
        for (int i = 0; i < event_SegmentN_Nominal.size(); i++) {
          // ATH_MSG_INFO("event_SegmentN_Nominal[i]: " << event_SegmentN_Nominal[i]);
          if (count(event_SegmentN_Nominal.begin(), event_SegmentN_Nominal.end(), event_SegmentN_Nominal[i]) > 2){
            // ATH_MSG_INFO(event_pass << " foundPV");
          //checking for 3 jet tracks in same window in events with 4 tracks
            pass = true;
            if (multiplier == "1"){foundPVwindow_1xRes_Nominal = 1;}
            else if (multiplier == "0.1"){foundPVwindow_01xRes_Nominal = 1;}
            else if (multiplier == "0.5"){foundPVwindow_05xRes_Nominal = 1;}
            else if (multiplier == "0.05"){foundPVwindow_005xRes_Nominal = 1;}
            else if (multiplier == "0.005"){foundPVwindow_0005xRes_Nominal = 1;}
            else if (multiplier == "2.5"){foundPVwindow_25xRes_Nominal = 1;}
            else if (multiplier == "2"){foundPVwindow_2xRes_Nominal = 1;}
            else if (multiplier == "3"){foundPVwindow_3xRes_Nominal = 1;}
            else if (multiplier == "5"){foundPVwindow_5xRes_Nominal = 1;}
            else if (multiplier == "10"){foundPVwindow_10xRes_Nominal = 1;}
            else if (multiplier == "12"){foundPVwindow_12xRes_Nominal = 1;}
            else if (multiplier == "15"){foundPVwindow_15xRes_Nominal = 1;}
            else if (multiplier == "20"){foundPVwindow_20xRes_Nominal = 1;}
            else if (multiplier == "4"){foundPVwindow_4xRes_Nominal = 1;}
            else if (multiplier == "50"){foundPVwindow_50xRes_Nominal = 1;}
            else if (multiplier == "1.5"){foundPVwindow_150xRes_Nominal = 1;}
            else if (multiplier == "0.75"){foundPVwindow_075xRes_Nominal = 1;}
            else if (multiplier == "0.25"){foundPVwindow_025xRes_Nominal = 1;}        
            else if (multiplier == "0.075"){foundPVwindow_0075xRes_Nominal = 1;}        
            else if (multiplier == "0.0075"){foundPVwindow_00075xRes_Nominal = 1;}        
          }
          // else{ATH_MSG_INFO( event_pass << " not foundPV");}
        }

        // in one val is in 3 different jets
        for (int i = 0; i < jet1_SegmentN_Nominal.size(); i++) {
          if (count(jet2_SegmentN_Nominal.begin(), jet2_SegmentN_Nominal.end(), jet1_SegmentN_Nominal[i]) && (count(jet3_SegmentN_Nominal.begin(), jet3_SegmentN_Nominal.end(), jet1_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_Nominal.begin(), jet2_SegmentN_Nominal.end(), jet1_SegmentN_Nominal[i]) && (count(jet4_SegmentN_Nominal.begin(), jet4_SegmentN_Nominal.end(), jet1_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_Nominal.begin(), jet3_SegmentN_Nominal.end(), jet1_SegmentN_Nominal[i]) && (count(jet4_SegmentN_Nominal.begin(), jet4_SegmentN_Nominal.end(), jet1_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
        }
        for (int i = 0; i < jet2_SegmentN_Nominal.size(); i++) {
          if (count(jet1_SegmentN_Nominal.begin(), jet1_SegmentN_Nominal.end(), jet2_SegmentN_Nominal[i]) && (count(jet3_SegmentN_Nominal.begin(), jet3_SegmentN_Nominal.end(), jet2_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_Nominal.begin(), jet3_SegmentN_Nominal.end(), jet2_SegmentN_Nominal[i]) && (count(jet4_SegmentN_Nominal.begin(), jet4_SegmentN_Nominal.end(), jet2_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_Nominal.begin(), jet1_SegmentN_Nominal.end(), jet2_SegmentN_Nominal[i]) && (count(jet4_SegmentN_Nominal.begin(), jet4_SegmentN_Nominal.end(), jet2_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
        }
        for (int i = 0; i < jet3_SegmentN_Nominal.size(); i++) {
          if (count(jet2_SegmentN_Nominal.begin(), jet2_SegmentN_Nominal.end(), jet3_SegmentN_Nominal[i]) && (count(jet1_SegmentN_Nominal.begin(), jet1_SegmentN_Nominal.end(), jet3_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_Nominal.begin(), jet2_SegmentN_Nominal.end(), jet3_SegmentN_Nominal[i]) && (count(jet4_SegmentN_Nominal.begin(), jet4_SegmentN_Nominal.end(), jet3_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_Nominal.begin(), jet1_SegmentN_Nominal.end(), jet3_SegmentN_Nominal[i]) && (count(jet4_SegmentN_Nominal.begin(), jet4_SegmentN_Nominal.end(), jet3_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
        }
        for (int i = 0; i < jet4_SegmentN_Nominal.size(); i++) {
          if (count(jet2_SegmentN_Nominal.begin(), jet2_SegmentN_Nominal.end(), jet4_SegmentN_Nominal[i]) && (count(jet3_SegmentN_Nominal.begin(), jet3_SegmentN_Nominal.end(), jet4_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_Nominal.begin(), jet2_SegmentN_Nominal.end(), jet4_SegmentN_Nominal[i]) && (count(jet1_SegmentN_Nominal.begin(), jet1_SegmentN_Nominal.end(), jet4_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_Nominal.begin(), jet3_SegmentN_Nominal.end(), jet4_SegmentN_Nominal[i]) && (count(jet1_SegmentN_Nominal.begin(), jet1_SegmentN_Nominal.end(), jet4_SegmentN_Nominal[i]))){jetpass_Nominal = true;}
        }

        // in one val is in 3 different jets
        for (int i = 0; i < jet1_SegmentN_doublebins_Nominal.size(); i++) {
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }
        for (int i = 0; i < jet2_SegmentN_doublebins_Nominal.size(); i++) {
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }
        for (int i = 0; i < jet3_SegmentN_doublebins_Nominal.size(); i++) {
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }
        for (int i = 0; i < jet4_SegmentN_doublebins_Nominal.size(); i++) {
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }

        // in one val +/- 1 is in 2 other jets --> 3 in a row
        for (int i = 0; i < jet1_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet1_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet1_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
          
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
          
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up)   && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
        }
        for (int i = 0; i < jet2_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet2_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet2_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
          
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
          
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up)   && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}

        }
        for (int i = 0; i < jet3_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet3_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet3_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
          
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up)   && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}

        }
        for (int i = 0; i < jet4_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet4_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet4_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
          
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}
          
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up))) {jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down))) {jetpass_Nominal = true;}

        }

        // in one val is in a jet and +/- 1 is in other jet --> val val +/- 1
        for (int i = 0; i < jet1_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet1_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet1_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

        }

        for (int i = 0; i < jet2_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet2_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet2_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

        }

        for (int i = 0; i < jet3_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet3_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet3_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

        }

        for (int i = 0; i < jet4_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet4_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet4_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up)   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up)   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down))){jetpass_Nominal = true;}

        }


        // in one val is in a jet and +/- 1 is in other jet --> up up val
        for (int i = 0; i < jet1_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet1_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet1_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i])   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }

        for (int i = 0; i < jet2_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet2_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet2_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i])   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }

        for (int i = 0; i < jet3_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet3_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet3_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), up) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i])   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }

        for (int i = 0; i < jet4_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet4_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet4_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), up) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i])   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), up) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i])   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), up) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i])   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }

        // in one val is in a jet and +/- 1 is in other jet --> down down val
        for (int i = 0; i < jet1_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet1_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet1_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i])   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet1_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }

        for (int i = 0; i < jet2_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet2_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet2_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i])   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet2_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }

        for (int i = 0; i < jet3_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet3_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet3_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) && (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i])   || count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet4_SegmentN_doublebins_Nominal.begin(), jet4_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i])   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet3_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }

        for (int i = 0; i < jet4_SegmentN_doublebins_Nominal.size(); i++) {
          int up = jet4_SegmentN_doublebins_Nominal[i] + 1;
          int down = jet4_SegmentN_doublebins_Nominal[i] - 1;
          if (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), down) && (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i])   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i])   || count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
          if (count(jet1_SegmentN_doublebins_Nominal.begin(), jet1_SegmentN_doublebins_Nominal.end(), down) && (count(jet2_SegmentN_doublebins_Nominal.begin(), jet2_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i])   || count(jet3_SegmentN_doublebins_Nominal.begin(), jet3_SegmentN_doublebins_Nominal.end(), jet4_SegmentN_doublebins_Nominal[i]))){jetpass_Nominal = true;}
        }


        if (jetpass_Nominal){
            if (multiplier == "1"){foundPVwindow_JetVecs_1xRes_Nominal = 1;}
            else if (multiplier == "0.1"){foundPVwindow_JetVecs_01xRes_Nominal = 1;}
            else if (multiplier == "0.5"){foundPVwindow_JetVecs_05xRes_Nominal = 1;}
            else if (multiplier == "0.05"){foundPVwindow_JetVecs_005xRes_Nominal = 1;}
            else if (multiplier == "0.005"){foundPVwindow_JetVecs_0005xRes_Nominal = 1;}
            else if (multiplier == "2.5"){foundPVwindow_JetVecs_25xRes_Nominal = 1;}
            else if (multiplier == "2"){foundPVwindow_JetVecs_2xRes_Nominal = 1;}
            else if (multiplier == "3"){foundPVwindow_JetVecs_3xRes_Nominal = 1;}
            else if (multiplier == "5"){foundPVwindow_JetVecs_5xRes_Nominal = 1;}
            else if (multiplier == "10"){foundPVwindow_JetVecs_10xRes_Nominal = 1;}
            else if (multiplier == "12"){foundPVwindow_JetVecs_12xRes_Nominal = 1;}
            else if (multiplier == "15"){foundPVwindow_JetVecs_15xRes_Nominal = 1;}
            else if (multiplier == "20"){foundPVwindow_JetVecs_20xRes_Nominal = 1;}
            else if (multiplier == "4"){foundPVwindow_JetVecs_4xRes_Nominal = 1;}
            else if (multiplier == "50"){foundPVwindow_JetVecs_50xRes_Nominal = 1;}
            else if (multiplier == "1.5"){foundPVwindow_JetVecs_150xRes_Nominal = 1;}
            else if (multiplier == "0.75"){foundPVwindow_JetVecs_075xRes_Nominal = 1;}
            else if (multiplier == "0.25"){foundPVwindow_JetVecs_025xRes_Nominal = 1;}        
            else if (multiplier == "0.075"){foundPVwindow_JetVecs_0075xRes_Nominal = 1;}        
            else if (multiplier == "0.0075"){foundPVwindow_JetVecs_00075xRes_Nominal = 1;}  
        }


        if (!pass){
          for (int i = 0; i < event_SegmentN_doublebins_Nominal.size(); i++) {
            // cout << "double " << event_SegmentN_doublebins_Nominal[i] << endl;
            // ATH_MSG_INFO("event_SegmentN_doublebins_Nominal[i]: " << event_SegmentN_doublebins_Nominal[i]);
            int nextval = event_SegmentN_doublebins_Nominal[i]+1;//cout << "checking for " << nextval << endl;
            int prevval = event_SegmentN_doublebins_Nominal[i]-1;//cout << "checking for " << prevval << endl;
            if (std::find(event_SegmentN_doublebins_Nominal.begin(), event_SegmentN_doublebins_Nominal.end(),nextval)!=event_SegmentN_doublebins_Nominal.end()){
              if (std::find(event_SegmentN_doublebins_Nominal.begin(), event_SegmentN_doublebins_Nominal.end(),prevval)!=event_SegmentN_doublebins_Nominal.end()){

                // ATH_MSG_INFO("nominal event passes double bins 1");
                if (multiplier == "1"){foundPVwindow_double_1xRes_Nominal = 1;}
                else if (multiplier == "0.1"){foundPVwindow_double_01xRes_Nominal = 1;}
                else if (multiplier == "0.5"){foundPVwindow_double_05xRes_Nominal = 1;}
                else if (multiplier == "0.05"){foundPVwindow_double_005xRes_Nominal = 1;}
                else if (multiplier == "0.005"){foundPVwindow_double_0005xRes_Nominal = 1;}
                else if (multiplier == "2.5"){foundPVwindow_double_25xRes_Nominal = 1;}
                else if (multiplier == "2"){foundPVwindow_double_2xRes_Nominal = 1;}
                else if (multiplier == "3"){foundPVwindow_double_3xRes_Nominal = 1;}
                else if (multiplier == "5"){foundPVwindow_double_5xRes_Nominal = 1;}
                else if (multiplier == "10"){foundPVwindow_double_10xRes_Nominal = 1;}
                else if (multiplier == "12"){foundPVwindow_double_12xRes_Nominal = 1;}
                else if (multiplier == "15"){foundPVwindow_double_15xRes_Nominal = 1;}
                else if (multiplier == "20"){foundPVwindow_double_20xRes_Nominal = 1;}
                else if (multiplier == "4"){foundPVwindow_double_4xRes_Nominal = 1;}
                else if (multiplier == "50"){foundPVwindow_double_50xRes_Nominal = 1;}
                else if (multiplier == "1.5"){foundPVwindow_double_150xRes_Nominal = 1;}
                else if (multiplier == "0.75"){foundPVwindow_double_075xRes_Nominal = 1;}
                else if (multiplier == "0.25"){foundPVwindow_double_025xRes_Nominal = 1;}        
                else if (multiplier == "0.075"){foundPVwindow_double_0075xRes_Nominal = 1;}        
                else if (multiplier == "0.0075"){foundPVwindow_double_00075xRes_Nominal = 1;}  
              }
            }
            if ((count(event_SegmentN_doublebins_Nominal.begin(), event_SegmentN_doublebins_Nominal.end(), event_SegmentN_doublebins_Nominal[i]) > 1) && (std::find(event_SegmentN_doublebins_Nominal.begin(), event_SegmentN_doublebins_Nominal.end(),nextval)!=event_SegmentN_doublebins_Nominal.end())){
                // ATH_MSG_INFO("nominal event passes double bins 2");
              if (multiplier == "1"){foundPVwindow_double_1xRes_Nominal = 1;}
              else if (multiplier == "0.1"){foundPVwindow_double_01xRes_Nominal = 1;}
              else if (multiplier == "0.5"){foundPVwindow_double_05xRes_Nominal = 1;}
              else if (multiplier == "0.05"){foundPVwindow_double_005xRes_Nominal = 1;}
              else if (multiplier == "0.005"){foundPVwindow_double_0005xRes_Nominal = 1;}
              else if (multiplier == "2.5"){foundPVwindow_double_25xRes_Nominal = 1;}
              else if (multiplier == "2"){foundPVwindow_double_2xRes_Nominal = 1;}
              else if (multiplier == "3"){foundPVwindow_double_3xRes_Nominal = 1;}
              else if (multiplier == "5"){foundPVwindow_double_5xRes_Nominal = 1;}
              else if (multiplier == "10"){foundPVwindow_double_10xRes_Nominal = 1;}
              else if (multiplier == "12"){foundPVwindow_double_12xRes_Nominal = 1;}
              else if (multiplier == "15"){foundPVwindow_double_15xRes_Nominal = 1;}
              else if (multiplier == "20"){foundPVwindow_double_20xRes_Nominal = 1;}
              else if (multiplier == "4"){foundPVwindow_double_4xRes_Nominal = 1;}
              else if (multiplier == "50"){foundPVwindow_double_50xRes_Nominal = 1;}
              else if (multiplier == "1.5"){foundPVwindow_double_150xRes_Nominal = 1;}
              else if (multiplier == "0.75"){foundPVwindow_double_075xRes_Nominal = 1;}
              else if (multiplier == "0.25"){foundPVwindow_double_025xRes_Nominal = 1;}        
              else if (multiplier == "0.075"){foundPVwindow_double_0075xRes_Nominal = 1;}        
              else if (multiplier == "0.0075"){foundPVwindow_double_00075xRes_Nominal = 1;}  
            }
            else if ((count(event_SegmentN_doublebins_Nominal.begin(), event_SegmentN_doublebins_Nominal.end(), event_SegmentN_doublebins_Nominal[i]) > 1) && (std::find(event_SegmentN_doublebins_Nominal.begin(), event_SegmentN_doublebins_Nominal.end(),prevval)!=event_SegmentN_doublebins_Nominal.end())){
                // ATH_MSG_INFO("nominal event passes double bins 3");
              if (multiplier == "1"){foundPVwindow_double_1xRes_Nominal = 1;}
              else if (multiplier == "0.1"){foundPVwindow_double_01xRes_Nominal = 1;}
              else if (multiplier == "0.5"){foundPVwindow_double_05xRes_Nominal = 1;}
              else if (multiplier == "0.05"){foundPVwindow_double_005xRes_Nominal = 1;}
              else if (multiplier == "0.005"){foundPVwindow_double_0005xRes_Nominal = 1;}
              else if (multiplier == "2.5"){foundPVwindow_double_25xRes_Nominal = 1;}
              else if (multiplier == "2"){foundPVwindow_double_2xRes_Nominal = 1;}
              else if (multiplier == "3"){foundPVwindow_double_3xRes_Nominal = 1;}
              else if (multiplier == "5"){foundPVwindow_double_5xRes_Nominal = 1;}
              else if (multiplier == "10"){foundPVwindow_double_10xRes_Nominal = 1;}
              else if (multiplier == "12"){foundPVwindow_double_12xRes_Nominal = 1;}
              else if (multiplier == "15"){foundPVwindow_double_15xRes_Nominal = 1;}
              else if (multiplier == "20"){foundPVwindow_double_20xRes_Nominal = 1;}
              else if (multiplier == "4"){foundPVwindow_double_4xRes_Nominal = 1;}
              else if (multiplier == "50"){foundPVwindow_double_50xRes_Nominal = 1;}
              else if (multiplier == "1.5"){foundPVwindow_double_150xRes_Nominal = 1;}
              else if (multiplier == "0.75"){foundPVwindow_double_075xRes_Nominal = 1;}
              else if (multiplier == "0.25"){foundPVwindow_double_025xRes_Nominal = 1;}        
              else if (multiplier == "0.075"){foundPVwindow_double_0075xRes_Nominal = 1;}        
              else if (multiplier == "0.0075"){foundPVwindow_double_00075xRes_Nominal = 1;}  
            }
          }//end loop over double bins
        }//end of check for if it doesn't pass 3 jets in same regular window
        else{ //if passes single window, it passes double windows too 
            if (multiplier == "1"){foundPVwindow_double_1xRes_Nominal = 1;}
            else if (multiplier == "0.1"){foundPVwindow_double_01xRes_Nominal = 1;}
            else if (multiplier == "0.5"){foundPVwindow_double_05xRes_Nominal = 1;}
            else if (multiplier == "0.05"){foundPVwindow_double_005xRes_Nominal = 1;}
            else if (multiplier == "0.005"){foundPVwindow_double_0005xRes_Nominal = 1;}
            else if (multiplier == "2.5"){foundPVwindow_double_25xRes_Nominal = 1;}
            else if (multiplier == "2"){foundPVwindow_double_2xRes_Nominal = 1;}
            else if (multiplier == "3"){foundPVwindow_double_3xRes_Nominal = 1;}
            else if (multiplier == "5"){foundPVwindow_double_5xRes_Nominal = 1;}
            else if (multiplier == "10"){foundPVwindow_double_10xRes_Nominal = 1;}
            else if (multiplier == "12"){foundPVwindow_double_12xRes_Nominal = 1;}
            else if (multiplier == "15"){foundPVwindow_double_15xRes_Nominal = 1;}
            else if (multiplier == "20"){foundPVwindow_double_20xRes_Nominal = 1;}
            else if (multiplier == "4"){foundPVwindow_double_4xRes_Nominal = 1;}
            else if (multiplier == "50"){foundPVwindow_double_50xRes_Nominal = 1;}
            else if (multiplier == "1.5"){foundPVwindow_double_150xRes_Nominal = 1;}
            else if (multiplier == "0.75"){foundPVwindow_double_075xRes_Nominal = 1;}
            else if (multiplier == "0.25"){foundPVwindow_double_025xRes_Nominal = 1;}        
            else if (multiplier == "0.075"){foundPVwindow_double_0075xRes_Nominal = 1;}        
            else if (multiplier == "0.0075"){foundPVwindow_double_00075xRes_Nominal = 1;}  
        }//end of if it passes original windows, it passes double windows too
      }//track requirements (first 3 jets)

/////////////////////////////////////////////////////////////////////////////////////////////////

    }//end multipliers loop

    ntracks_tot = count_ntracks;
    ntracks_tot_Nominal = count_ntracks_Nominal;

    if (event_pass && (j1trkfound + j2trkfound + j3trkfound + j4trkfound == 3 )){ // if less than 3 tracks, which is missing?
      if (!j1trkfound) {hist("hist_missingtrack")->Fill(0);} //ATH_MSG_INFO("missing track is 1");}
      if (!j2trkfound) {hist("hist_missingtrack")->Fill(1);} //ATH_MSG_INFO("missing track is 2");}
      if (!j3trkfound) {hist("hist_missingtrack")->Fill(2);} //ATH_MSG_INFO("missing track is 3");}
      if (!j4trkfound) {hist("hist_missingtrack")->Fill(3);} //ATH_MSG_INFO("missing track is 4");}
    }

    if (event_pass && (j1trkfound_Nominal + j2trkfound_Nominal + j3trkfound_Nominal + j4trkfound_Nominal == 3 )){ // if less than 3 tracks, which is missing?
      if (!j1trkfound_Nominal) {hist("hist_missingtrack_Nominal")->Fill(0);} //ATH_MSG_INFO("missing track is 1");}
      if (!j2trkfound_Nominal) {hist("hist_missingtrack_Nominal")->Fill(1);} //ATH_MSG_INFO("missing track is 2");}
      if (!j3trkfound_Nominal) {hist("hist_missingtrack_Nominal")->Fill(2);} //ATH_MSG_INFO("missing track is 3");}
      if (!j4trkfound_Nominal) {hist("hist_missingtrack_Nominal")->Fill(3);} //ATH_MSG_INFO("missing track is 4");}
    }


    if (j1trkfound) {hist("multijet_cutflow")->Fill(5);hist("multijet_cutflow_jetvec")->Fill(5);}
    if (j1trkfound && j2trkfound) {hist("multijet_cutflow")->Fill(6);hist("multijet_cutflow_jetvec")->Fill(6);}
    if (j1trkfound && j2trkfound && j3trkfound) {hist("multijet_cutflow")->Fill(7);hist("multijet_cutflow_jetvec")->Fill(7);}
    if (j1trkfound && j2trkfound && j3trkfound && j4trkfound) {hist("multijet_cutflow")->Fill(8);hist("multijet_cutflow_jetvec")->Fill(8);}
    if (foundPVwindow_double_01xRes == 1 || foundPVwindow_01xRes == 1) {hist("multijet_cutflow")->Fill(9);hist("multijet_cutflow_jetvec")->Fill(9);}//ATH_MSG_INFO("Passes 0.1");}
    if (foundPVwindow_double_05xRes == 1 || foundPVwindow_05xRes == 1) {hist("multijet_cutflow")->Fill(10);hist("multijet_cutflow_jetvec")->Fill(10);}//ATH_MSG_INFO("Passes 0.5");}
    if (foundPVwindow_double_1xRes == 1 || foundPVwindow_1xRes == 1) {hist("multijet_cutflow")->Fill(11);hist("multijet_cutflow_jetvec")->Fill(11);}//ATH_MSG_INFO("Passes 1");}
    if (foundPVwindow_double_25xRes == 1 || foundPVwindow_25xRes == 1) {hist("multijet_cutflow")->Fill(12);hist("multijet_cutflow_jetvec")->Fill(12);}//ATH_MSG_INFO("Passes 2.5");}
    if (foundPVwindow_double_5xRes == 1 || foundPVwindow_5xRes == 1) {hist("multijet_cutflow")->Fill(13);hist("multijet_cutflow_jetvec")->Fill(13);}//ATH_MSG_INFO("Passes 5");}

    if (j1trkfound_Nominal) {hist("multijet_cutflow_Nominal")->Fill(5);hist("multijet_cutflow_Nominal_jetvec")->Fill(5);}
    if (j1trkfound_Nominal && j2trkfound_Nominal) {hist("multijet_cutflow_Nominal")->Fill(6);hist("multijet_cutflow_Nominal_jetvec")->Fill(6);}
    if (j1trkfound_Nominal && j2trkfound_Nominal && j3trkfound_Nominal) {hist("multijet_cutflow_Nominal")->Fill(7);hist("multijet_cutflow_Nominal_jetvec")->Fill(7);}
    if (j1trkfound_Nominal && j2trkfound_Nominal && j3trkfound_Nominal && j4trkfound_Nominal) {hist("multijet_cutflow_Nominal")->Fill(8);hist("multijet_cutflow_Nominal_jetvec")->Fill(8);}
    if (foundPVwindow_double_01xRes_Nominal == 1 || foundPVwindow_01xRes_Nominal == 1) {hist("multijet_cutflow_Nominal")->Fill(9);hist("multijet_cutflow_Nominal_jetvec")->Fill(9);}//ATH_MSG_INFO("Nominal Passes 0.1");}
    if (foundPVwindow_double_05xRes_Nominal == 1 || foundPVwindow_05xRes_Nominal == 1) {hist("multijet_cutflow_Nominal")->Fill(10);hist("multijet_cutflow_Nominal_jetvec")->Fill(10);}//ATH_MSG_INFO("Nominal Passes 0.5");}
    if (foundPVwindow_double_1xRes_Nominal == 1 || foundPVwindow_1xRes_Nominal == 1) {hist("multijet_cutflow_Nominal")->Fill(11);hist("multijet_cutflow_Nominal_jetvec")->Fill(11);}//ATH_MSG_INFO("Nominal Passes 1");}
    if (foundPVwindow_double_25xRes_Nominal == 1 || foundPVwindow_25xRes_Nominal == 1) {hist("multijet_cutflow_Nominal")->Fill(12);hist("multijet_cutflow_Nominal_jetvec")->Fill(12);}//ATH_MSG_INFO("Nominal Passes 2.5");}
    if (foundPVwindow_double_5xRes_Nominal == 1 || foundPVwindow_5xRes_Nominal == 1) {hist("multijet_cutflow_Nominal")->Fill(13);hist("multijet_cutflow_Nominal_jetvec")->Fill(13);}//ATH_MSG_INFO("Nominal Passes 5");}


  }//end req on having 4 reco + truth jets
  else {
    // nTruthEvents_3HS = -999;
    // nTruthEvents_3HS4trk = -999;    
    foundPVwindow_1xRes = -999;
    foundPVwindow_01xRes = -999;
    foundPVwindow_05xRes = -999;
    foundPVwindow_005xRes = -999;
    foundPVwindow_0005xRes = -999;
    foundPVwindow_25xRes = -999;
    foundPVwindow_2xRes = -999;
    foundPVwindow_3xRes = -999;
    foundPVwindow_5xRes = -999;
    foundPVwindow_10xRes = -999;
    foundPVwindow_12xRes = -999;
    foundPVwindow_15xRes = -999;
    foundPVwindow_4xRes = -999;
    foundPVwindow_20xRes = -999;
    foundPVwindow_50xRes = -999;
    foundPVwindow_150xRes = -999;
    foundPVwindow_075xRes = -999;
    foundPVwindow_025xRes = -999;
    foundPVwindow_0075xRes = -999;
    foundPVwindow_00075xRes = -999;    
    foundPVwindow_double_1xRes = -999;
    foundPVwindow_double_01xRes = -999;
    foundPVwindow_double_05xRes = -999;
    foundPVwindow_double_005xRes = -999;
    foundPVwindow_double_0005xRes = -999;
    foundPVwindow_double_25xRes = -999;
    foundPVwindow_double_2xRes = -999;
    foundPVwindow_double_3xRes = -999;
    foundPVwindow_double_5xRes = -999;
    foundPVwindow_double_10xRes = -999;
    foundPVwindow_double_12xRes = -999;
    foundPVwindow_double_15xRes = -999;
    foundPVwindow_double_4xRes = -999;
    foundPVwindow_double_20xRes = -999;
    foundPVwindow_double_50xRes = -999;
    foundPVwindow_double_150xRes = -999;
    foundPVwindow_double_075xRes = -999;
    foundPVwindow_double_025xRes = -999;
    foundPVwindow_double_0075xRes = -999;
    foundPVwindow_double_00075xRes = -999;

    foundPVwindow_JetVecs_1xRes = -999;
    foundPVwindow_JetVecs_01xRes = -999;
    foundPVwindow_JetVecs_05xRes = -999;
    foundPVwindow_JetVecs_005xRes = -999;
    foundPVwindow_JetVecs_0005xRes = -999;
    foundPVwindow_JetVecs_25xRes = -999;
    foundPVwindow_JetVecs_2xRes = -999;
    foundPVwindow_JetVecs_3xRes = -999;
    foundPVwindow_JetVecs_5xRes = -999;
    foundPVwindow_JetVecs_10xRes = -999;
    foundPVwindow_JetVecs_12xRes = -999;
    foundPVwindow_JetVecs_15xRes = -999;
    foundPVwindow_JetVecs_4xRes = -999;
    foundPVwindow_JetVecs_20xRes = -999;
    foundPVwindow_JetVecs_50xRes = -999;
    foundPVwindow_JetVecs_150xRes = -999;
    foundPVwindow_JetVecs_075xRes = -999;
    foundPVwindow_JetVecs_025xRes = -999;
    foundPVwindow_JetVecs_0075xRes = -999;
    foundPVwindow_JetVecs_00075xRes = -999;

    trk_z0Res_mean_1xRes = -999;
    trk_z0Res_mean_01xRes = -999;
    trk_z0Res_mean_05xRes = -999;
    trk_z0Res_mean_005xRes = -999;
    trk_z0Res_mean_0005xRes = -999;
    trk_z0Res_mean_25xRes = -999;
    trk_z0Res_mean_2xRes = -999;
    trk_z0Res_mean_3xRes = -999;
    trk_z0Res_mean_5xRes = -999;
    trk_z0Res_mean_10xRes = -999;
    trk_z0Res_mean_12xRes = -999;
    trk_z0Res_mean_15xRes = -999;
    trk_z0Res_mean_20xRes = -999;
    trk_z0Res_mean_4xRes = -999;
    trk_z0Res_mean_50xRes = -999;
    trk_z0Res_mean_150xRes = -999;
    trk_z0Res_mean_075xRes = -999;
    trk_z0Res_mean_025xRes = -999;
    trk_z0Res_mean_0075xRes = -999;
    trk_z0Res_mean_00075xRes = -999;


  }
  // ATH_MSG_INFO("final output? foundPVwindow_10xRes: " << foundPVwindow_10xRes << " else foundPVwindow_double_10xRes: " << foundPVwindow_double_10xRes);

  // Fill the event into the tree:
  tree ("CollectionTree")->Fill();

  return StatusCode::SUCCESS;
}


void MultiJetHTTxAODAnalysis::ResetVariables()
{

  j1dr = -999;
  j1dr_Nominal = -999;

  j2dr = -999;
  j2dr_Nominal = -999;

  j3dr = -999;
  j3dr_Nominal = -999;

  j4dr = -999;
  j4dr_Nominal = -999;

  j1trackz0.clear();
  j2trackz0.clear();
  j3trackz0.clear();
  j4trackz0.clear();

  j1trackz0_Nominal.clear();
  j2trackz0_Nominal.clear();
  j3trackz0_Nominal.clear();
  j4trackz0_Nominal.clear();

  j1trackavgz0 = -999.0;
  j2trackavgz0 = -999.0;
  j3trackavgz0 = -999.0;
  j4trackavgz0 = -999.0;

  j1trackavgz0_Nominal = -999.0;
  j2trackavgz0_Nominal = -999.0;
  j3trackavgz0_Nominal = -999.0;
  j4trackavgz0_Nominal = -999.0;

  trk_z0Res.clear();
  trk_z0.clear();
  // zSegments.clear();

  trk_z0Res_Nominal.clear();
  trk_z0_Nominal.clear();
  // zSegments.clear();

  ntracksj4 = 0;
  ntracksj3 = 0;
  ntracksj2 = 0;
  ntracksj1 = 0;

  ntracksj4_Nominal = 0;
  ntracksj3_Nominal = 0;
  ntracksj2_Nominal = 0;
  ntracksj1_Nominal = 0;

  ntracks_tot = 0;
  z0Segment_1xRes.clear();
  z0Segment_01xRes.clear();
  z0Segment_05xRes.clear();
  z0Segment_005xRes.clear();
  z0Segment_0005xRes.clear();
  z0Segment_25xRes.clear();
  z0Segment_12xRes.clear();
  z0Segment_15xRes.clear();
  z0Segment_2xRes.clear();
  z0Segment_3xRes.clear();
  z0Segment_5xRes.clear();
  z0Segment_10xRes.clear();
  z0Segment_20xRes.clear();
  z0Segment_4xRes.clear();
  z0Segment_50xRes.clear();
  z0Segment_150xRes.clear();
  z0Segment_075xRes.clear();
  z0Segment_025xRes.clear();
  z0Segment_0075xRes.clear();
  z0Segment_00075xRes.clear();
  trk_jetmatch.clear();
  trk_type.clear();
  trk_parentID.clear();

  ntracks_tot_Nominal = 0;
  z0Segment_1xRes_Nominal.clear();
  z0Segment_01xRes_Nominal.clear();
  z0Segment_05xRes_Nominal.clear();
  z0Segment_005xRes_Nominal.clear();
  z0Segment_0005xRes_Nominal.clear();
  z0Segment_25xRes_Nominal.clear();
  z0Segment_12xRes_Nominal.clear();
  z0Segment_15xRes_Nominal.clear();
  z0Segment_2xRes_Nominal.clear();
  z0Segment_3xRes_Nominal.clear();
  z0Segment_5xRes_Nominal.clear();
  z0Segment_10xRes_Nominal.clear();
  z0Segment_20xRes_Nominal.clear();
  z0Segment_4xRes_Nominal.clear();
  z0Segment_50xRes_Nominal.clear();
  z0Segment_150xRes_Nominal.clear();
  z0Segment_075xRes_Nominal.clear();
  z0Segment_025xRes_Nominal.clear();
  z0Segment_0075xRes_Nominal.clear();
  z0Segment_00075xRes_Nominal.clear();
  trk_jetmatch_Nominal.clear();


  nTruthEvents_3HS = -999;
  nTruthEvents_3HS4trk = -999;
  foundPVwindow_1xRes = -999;
  foundPVwindow_01xRes = -999;
  foundPVwindow_05xRes = -999;
  foundPVwindow_005xRes = -999;
  foundPVwindow_0005xRes = -999;
  foundPVwindow_25xRes = -999;
  foundPVwindow_2xRes = -999;
  foundPVwindow_3xRes = -999;
  foundPVwindow_5xRes = -999;
  foundPVwindow_10xRes = -999;
  foundPVwindow_12xRes = -999;
  foundPVwindow_15xRes = -999;
  foundPVwindow_20xRes = -999;
  foundPVwindow_4xRes = -999;
  foundPVwindow_50xRes = -999;
  foundPVwindow_150xRes = -999;
  foundPVwindow_075xRes = -999;
  foundPVwindow_025xRes = -999;
  foundPVwindow_0075xRes = -999;
  foundPVwindow_00075xRes = -999;

  foundPVwindow_double_1xRes = -999;
  foundPVwindow_double_01xRes = -999;
  foundPVwindow_double_05xRes = -999;
  foundPVwindow_double_005xRes = -999;
  foundPVwindow_double_0005xRes = -999;
  foundPVwindow_double_25xRes = -999;
  foundPVwindow_double_2xRes = -999;
  foundPVwindow_double_3xRes = -999;
  foundPVwindow_double_5xRes = -999;
  foundPVwindow_double_10xRes = -999;
  foundPVwindow_double_12xRes = -999;
  foundPVwindow_double_15xRes = -999;
  foundPVwindow_double_20xRes = -999;
  foundPVwindow_double_4xRes = -999;
  foundPVwindow_double_50xRes = -999;
  foundPVwindow_double_150xRes = -999;
  foundPVwindow_double_075xRes = -999;
  foundPVwindow_double_025xRes = -999;
  foundPVwindow_double_0075xRes = -999;
  foundPVwindow_double_00075xRes = -999;
  j1pt = 0.0;
  j2pt = 0.0;
  j3pt = 0.0;
  j4pt = 0.0;

  nTruthEvents_3HS_Nominal = -999;
  nTruthEvents_3HS4trk_Nominal = -999;
  
  foundPVwindow_1xRes_Nominal = -999;
  foundPVwindow_01xRes_Nominal = -999;
  foundPVwindow_05xRes_Nominal = -999;
  foundPVwindow_005xRes_Nominal = -999;
  foundPVwindow_0005xRes_Nominal = -999;
  foundPVwindow_25xRes_Nominal = -999;
  foundPVwindow_2xRes_Nominal = -999;
  foundPVwindow_3xRes_Nominal = -999;
  foundPVwindow_5xRes_Nominal = -999;
  foundPVwindow_10xRes_Nominal = -999;
  foundPVwindow_12xRes_Nominal = -999;
  foundPVwindow_15xRes_Nominal = -999;
  foundPVwindow_20xRes_Nominal = -999;
  foundPVwindow_4xRes_Nominal = -999;
  foundPVwindow_50xRes_Nominal = -999;
  foundPVwindow_150xRes_Nominal = -999;
  foundPVwindow_075xRes_Nominal = -999;
  foundPVwindow_025xRes_Nominal = -999;
  foundPVwindow_0075xRes_Nominal = -999;
  foundPVwindow_00075xRes_Nominal = -999;

  foundPVwindow_double_1xRes_Nominal = -999;
  foundPVwindow_double_01xRes_Nominal = -999;
  foundPVwindow_double_05xRes_Nominal = -999;
  foundPVwindow_double_005xRes_Nominal = -999;
  foundPVwindow_double_0005xRes_Nominal = -999;
  foundPVwindow_double_25xRes_Nominal = -999;
  foundPVwindow_double_2xRes_Nominal = -999;
  foundPVwindow_double_3xRes_Nominal = -999;
  foundPVwindow_double_5xRes_Nominal = -999;
  foundPVwindow_double_10xRes_Nominal = -999;
  foundPVwindow_double_12xRes_Nominal = -999;
  foundPVwindow_double_15xRes_Nominal = -999;
  foundPVwindow_double_20xRes_Nominal = -999;
  foundPVwindow_double_4xRes_Nominal = -999;
  foundPVwindow_double_50xRes_Nominal = -999;
  foundPVwindow_double_150xRes_Nominal = -999;
  foundPVwindow_double_075xRes_Nominal = -999;
  foundPVwindow_double_025xRes_Nominal = -999;
  foundPVwindow_double_0075xRes_Nominal = -999;
  foundPVwindow_double_00075xRes_Nominal = -999;

  foundPVwindow_JetVecs_1xRes = -999;
  foundPVwindow_JetVecs_01xRes = -999;
  foundPVwindow_JetVecs_05xRes = -999;
  foundPVwindow_JetVecs_005xRes = -999;
  foundPVwindow_JetVecs_0005xRes = -999;
  foundPVwindow_JetVecs_25xRes = -999;
  foundPVwindow_JetVecs_2xRes = -999;
  foundPVwindow_JetVecs_3xRes = -999;
  foundPVwindow_JetVecs_5xRes = -999;
  foundPVwindow_JetVecs_10xRes = -999;
  foundPVwindow_JetVecs_12xRes = -999;
  foundPVwindow_JetVecs_15xRes = -999;
  foundPVwindow_JetVecs_20xRes = -999;
  foundPVwindow_JetVecs_4xRes = -999;
  foundPVwindow_JetVecs_50xRes = -999;
  foundPVwindow_JetVecs_150xRes = -999;
  foundPVwindow_JetVecs_075xRes = -999;
  foundPVwindow_JetVecs_025xRes = -999;
  foundPVwindow_JetVecs_0075xRes = -999;
  foundPVwindow_JetVecs_00075xRes = -999;

  foundPVwindow_JetVecs_1xRes_Nominal = -999;
  foundPVwindow_JetVecs_01xRes_Nominal = -999;
  foundPVwindow_JetVecs_05xRes_Nominal = -999;
  foundPVwindow_JetVecs_005xRes_Nominal = -999;
  foundPVwindow_JetVecs_0005xRes_Nominal = -999;
  foundPVwindow_JetVecs_25xRes_Nominal = -999;
  foundPVwindow_JetVecs_2xRes_Nominal = -999;
  foundPVwindow_JetVecs_3xRes_Nominal = -999;
  foundPVwindow_JetVecs_5xRes_Nominal = -999;
  foundPVwindow_JetVecs_10xRes_Nominal = -999;
  foundPVwindow_JetVecs_12xRes_Nominal = -999;
  foundPVwindow_JetVecs_15xRes_Nominal = -999;
  foundPVwindow_JetVecs_20xRes_Nominal = -999;
  foundPVwindow_JetVecs_4xRes_Nominal = -999;
  foundPVwindow_JetVecs_50xRes_Nominal = -999;
  foundPVwindow_JetVecs_150xRes_Nominal = -999;
  foundPVwindow_JetVecs_075xRes_Nominal = -999;
  foundPVwindow_JetVecs_025xRes_Nominal = -999;
  foundPVwindow_JetVecs_0075xRes_Nominal = -999;
  foundPVwindow_JetVecs_00075xRes_Nominal = -999;

}

StatusCode MultiJetHTTxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.
  return StatusCode::SUCCESS;
}
