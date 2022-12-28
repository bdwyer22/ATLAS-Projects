#ifndef MultiJetHTTAnalysis_MultiJetHTTxAODAnalysis_H
#define MultiJetHTTAnalysis_MultiJetHTTxAODAnalysis_H
#include <TH1.h>
#include <TTree.h>
#include <vector>
#include <AnaAlgorithm/AnaAlgorithm.h>
#include "AthenaBaseComps/AthHistogramAlgorithm.h"
#include <random> // uniform_real_distribution, random_generator
#include "xAODTracking/TrackParticleContainer.h" 
#include "xAODTracking/TrackParticleAuxContainer.h" 
#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/VertexContainer.h" 
// #include "TrkTrack/TrackCollection.h"
// #include "TrkParameters/TrackParameters.h"
#include "JetCalibTools/JetCalibrationTool.h"

class MultiJetHTTxAODAnalysis : public EL::AnaAlgorithm
{
public:
  // this is a standard algorithm constructor
  MultiJetHTTxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);

  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;


private:
  // Configuration, and any other types of variables go here.
  //float m_cutValue;
  //TTree *m_myTree;
  //TH1 *m_myHist;

  JetCalibrationTool *m_JetCalibrationTool; //!
  TString m_CalibPath;

  unsigned int m_runNumber = 0; ///< Run number
  unsigned long long m_eventNumber = 0; ///< Event number
  double j1pt = 0.0;
  double j2pt = 0.0;
  double j3pt = 0.0;
  double j4pt = 0.0;

  std::vector<double> j1trackz0;
  std::vector<double> j2trackz0;
  std::vector<double> j3trackz0;
  std::vector<double> j4trackz0;

  double j1trackavgz0 = -999.0;
  double j2trackavgz0 = -999.0;
  double j3trackavgz0 = -999.0;
  double j4trackavgz0 = -999.0;

  int recotruthmatch;

  int nEventPassJetReq = -99;


  std::vector<double> j1trackz0_Nominal;
  std::vector<double> j2trackz0_Nominal;
  std::vector<double> j3trackz0_Nominal;
  std::vector<double> j4trackz0_Nominal;

  double j1trackavgz0_Nominal = -999.0;
  double j2trackavgz0_Nominal = -999.0;
  double j3trackavgz0_Nominal = -999.0;
  double j4trackavgz0_Nominal = -999.0;

  int recotruthmatch_Nominal;

  int nEventPassJetReq_Nominal = -99;

 // {0.005, 0.05, 0.10, 0.5, 1., 2., 2.5, 5., 10., 12, 15, 20, 30, 50, 100, 10000};} // fixed window sizes

  int foundPVwindow_01xRes = -99;
  int foundPVwindow_15xRes = -99;
  int foundPVwindow_0005xRes = -99;
  int foundPVwindow_005xRes = -99;
  int foundPVwindow_12xRes = -99;
  int foundPVwindow_4xRes = -99;
  int foundPVwindow_25xRes = -99;
  int foundPVwindow_05xRes = -99;
  int foundPVwindow_1xRes = -99;
  int foundPVwindow_2xRes = -99;
  int foundPVwindow_3xRes = -99;
  int foundPVwindow_5xRes = -99;
  int foundPVwindow_10xRes = -99;
  int foundPVwindow_20xRes = -99;
  int foundPVwindow_50xRes = -99;
  int foundPVwindow_150xRes = -99;
  int foundPVwindow_075xRes = -99;
  int foundPVwindow_025xRes = -99;
  int foundPVwindow_0075xRes = -99;
  int foundPVwindow_00075xRes = -99;

  int foundPVwindow_double_01xRes = -99;
  int foundPVwindow_double_15xRes = -99;
  int foundPVwindow_double_0005xRes = -99;
  int foundPVwindow_double_005xRes = -99;
  int foundPVwindow_double_12xRes = -99;
  int foundPVwindow_double_4xRes = -99;
  int foundPVwindow_double_25xRes = -99;
  int foundPVwindow_double_05xRes = -99;
  int foundPVwindow_double_1xRes = -99;
  int foundPVwindow_double_2xRes = -99;
  int foundPVwindow_double_3xRes = -99;
  int foundPVwindow_double_5xRes = -99;
  int foundPVwindow_double_10xRes = -99;
  int foundPVwindow_double_20xRes = -99;
  int foundPVwindow_double_50xRes = -99;
  int foundPVwindow_double_150xRes = -99;
  int foundPVwindow_double_075xRes = -99;
  int foundPVwindow_double_025xRes = -99;
  int foundPVwindow_double_0075xRes = -99;
  int foundPVwindow_double_00075xRes = -99;

  int foundPVwindow_JetVecs_01xRes = -99;
  int foundPVwindow_JetVecs_15xRes = -99;
  int foundPVwindow_JetVecs_0005xRes = -99;
  int foundPVwindow_JetVecs_005xRes = -99;
  int foundPVwindow_JetVecs_12xRes = -99;
  int foundPVwindow_JetVecs_4xRes = -99;
  int foundPVwindow_JetVecs_25xRes = -99;
  int foundPVwindow_JetVecs_05xRes = -99;
  int foundPVwindow_JetVecs_1xRes = -99;
  int foundPVwindow_JetVecs_2xRes = -99;
  int foundPVwindow_JetVecs_3xRes = -99;
  int foundPVwindow_JetVecs_5xRes = -99;
  int foundPVwindow_JetVecs_10xRes = -99;
  int foundPVwindow_JetVecs_20xRes = -99;
  int foundPVwindow_JetVecs_50xRes = -99;
  int foundPVwindow_JetVecs_150xRes = -99;
  int foundPVwindow_JetVecs_075xRes = -99;
  int foundPVwindow_JetVecs_025xRes = -99;
  int foundPVwindow_JetVecs_0075xRes = -99;
  int foundPVwindow_JetVecs_00075xRes = -99;

  std::vector<int> z0Segment_1xRes;
  std::vector<int> z0Segment_01xRes;
  std::vector<int> z0Segment_05xRes;
  std::vector<int> z0Segment_005xRes;
  std::vector<int> z0Segment_0005xRes;
  std::vector<int> z0Segment_25xRes;
  std::vector<int> z0Segment_12xRes;
  std::vector<int> z0Segment_15xRes;
  std::vector<int> z0Segment_2xRes;
  std::vector<int> z0Segment_3xRes;
  std::vector<int> z0Segment_5xRes;
  std::vector<int> z0Segment_10xRes;
  std::vector<int> z0Segment_20xRes;
  std::vector<int> z0Segment_4xRes;
  std::vector<int> z0Segment_50xRes;
  std::vector<int> z0Segment_150xRes;
  std::vector<int> z0Segment_075xRes;
  std::vector<int> z0Segment_025xRes;
  std::vector<int> z0Segment_0075xRes;
  std::vector<int> z0Segment_00075xRes;


  int foundPVwindow_01xRes_Nominal = -99;
  int foundPVwindow_15xRes_Nominal = -99;
  int foundPVwindow_0005xRes_Nominal = -99;
  int foundPVwindow_005xRes_Nominal = -99;
  int foundPVwindow_12xRes_Nominal = -99;
  int foundPVwindow_4xRes_Nominal = -99;
  int foundPVwindow_25xRes_Nominal = -99;
  int foundPVwindow_05xRes_Nominal = -99;
  int foundPVwindow_1xRes_Nominal = -99;
  int foundPVwindow_2xRes_Nominal = -99;
  int foundPVwindow_3xRes_Nominal = -99;
  int foundPVwindow_5xRes_Nominal = -99;
  int foundPVwindow_10xRes_Nominal = -99;
  int foundPVwindow_20xRes_Nominal = -99;
  int foundPVwindow_50xRes_Nominal = -99;
  int foundPVwindow_150xRes_Nominal = -99;
  int foundPVwindow_075xRes_Nominal = -99;
  int foundPVwindow_025xRes_Nominal = -99;
  int foundPVwindow_0075xRes_Nominal = -99;
  int foundPVwindow_00075xRes_Nominal = -99;

  int foundPVwindow_double_01xRes_Nominal = -99;
  int foundPVwindow_double_15xRes_Nominal = -99;
  int foundPVwindow_double_0005xRes_Nominal = -99;
  int foundPVwindow_double_005xRes_Nominal = -99;
  int foundPVwindow_double_12xRes_Nominal = -99;
  int foundPVwindow_double_4xRes_Nominal = -99;
  int foundPVwindow_double_25xRes_Nominal = -99;
  int foundPVwindow_double_05xRes_Nominal = -99;
  int foundPVwindow_double_1xRes_Nominal = -99;
  int foundPVwindow_double_2xRes_Nominal = -99;
  int foundPVwindow_double_3xRes_Nominal = -99;
  int foundPVwindow_double_5xRes_Nominal = -99;
  int foundPVwindow_double_10xRes_Nominal = -99;
  int foundPVwindow_double_20xRes_Nominal = -99;
  int foundPVwindow_double_50xRes_Nominal = -99;
  int foundPVwindow_double_150xRes_Nominal = -99;
  int foundPVwindow_double_075xRes_Nominal = -99;
  int foundPVwindow_double_025xRes_Nominal = -99;
  int foundPVwindow_double_0075xRes_Nominal = -99;
  int foundPVwindow_double_00075xRes_Nominal = -99;

  int foundPVwindow_JetVecs_01xRes_Nominal = -99;
  int foundPVwindow_JetVecs_15xRes_Nominal = -99;
  int foundPVwindow_JetVecs_0005xRes_Nominal = -99;
  int foundPVwindow_JetVecs_005xRes_Nominal = -99;
  int foundPVwindow_JetVecs_12xRes_Nominal = -99;
  int foundPVwindow_JetVecs_4xRes_Nominal = -99;
  int foundPVwindow_JetVecs_25xRes_Nominal = -99;
  int foundPVwindow_JetVecs_05xRes_Nominal = -99;
  int foundPVwindow_JetVecs_1xRes_Nominal = -99;
  int foundPVwindow_JetVecs_2xRes_Nominal = -99;
  int foundPVwindow_JetVecs_3xRes_Nominal = -99;
  int foundPVwindow_JetVecs_5xRes_Nominal = -99;
  int foundPVwindow_JetVecs_10xRes_Nominal = -99;
  int foundPVwindow_JetVecs_20xRes_Nominal = -99;
  int foundPVwindow_JetVecs_50xRes_Nominal = -99;
  int foundPVwindow_JetVecs_150xRes_Nominal = -99;
  int foundPVwindow_JetVecs_075xRes_Nominal = -99;
  int foundPVwindow_JetVecs_025xRes_Nominal = -99;
  int foundPVwindow_JetVecs_0075xRes_Nominal = -99;
  int foundPVwindow_JetVecs_00075xRes_Nominal = -99;

  std::vector<int> z0Segment_1xRes_Nominal;
  std::vector<int> z0Segment_01xRes_Nominal;
  std::vector<int> z0Segment_05xRes_Nominal;
  std::vector<int> z0Segment_005xRes_Nominal;
  std::vector<int> z0Segment_0005xRes_Nominal;
  std::vector<int> z0Segment_25xRes_Nominal;
  std::vector<int> z0Segment_12xRes_Nominal;
  std::vector<int> z0Segment_15xRes_Nominal;
  std::vector<int> z0Segment_2xRes_Nominal;
  std::vector<int> z0Segment_3xRes_Nominal;
  std::vector<int> z0Segment_5xRes_Nominal;
  std::vector<int> z0Segment_10xRes_Nominal;
  std::vector<int> z0Segment_20xRes_Nominal;
  std::vector<int> z0Segment_4xRes_Nominal;
  std::vector<int> z0Segment_50xRes_Nominal;
  std::vector<int> z0Segment_150xRes_Nominal;
  std::vector<int> z0Segment_075xRes_Nominal;
  std::vector<int> z0Segment_025xRes_Nominal;
  std::vector<int> z0Segment_0075xRes_Nominal;
  std::vector<int> z0Segment_00075xRes_Nominal;

  int nTruthEvents_3HS = -999;
  int nTruthEvents_3HS4trk = -999;

  int nTruthEvents_3HS_Nominal = -999;
  int nTruthEvents_3HS4trk_Nominal = -999;

  int ntracksj1;
  int ntracksj2;
  int ntracksj3;
  int ntracksj4;
  int ntracks_tot;

  double j1dr;
  double j2dr;
  double j3dr;
  double j4dr;


  int ntracksj1_Nominal;
  int ntracksj2_Nominal;
  int ntracksj3_Nominal;
  int ntracksj4_Nominal;
  int ntracks_tot_Nominal;

  double j1dr_Nominal;
  double j2dr_Nominal;
  double j3dr_Nominal;
  double j4dr_Nominal;

  unsigned int m_d0sigma_idx;
  unsigned int m_z0sigma_idx;

  std::uniform_real_distribution<float> m_flat;
  std::default_random_engine m_generator;

  std::vector<double> trk_z0Res;
  std::vector<double> trk_z0;
  std::vector<double> trk_z0Res_Nominal;
  std::vector<double> trk_z0_Nominal;
  std::vector<int> trk_parentID;
  std::vector<int> trk_type;

  std::vector<int> trk_jetmatch;
  std::vector<int> trk_jetmatch_Nominal;

  std::vector<std::vector<int>> zSegments;
  std::vector<std::vector<int>> zSegments_Nominal;


  double trk_z0Res_mean_1xRes;
  double trk_z0Res_mean_15xRes;
  double trk_z0Res_mean_12xRes;
  double trk_z0Res_mean_05xRes;
  double trk_z0Res_mean_005xRes;
  double trk_z0Res_mean_0005xRes;
  double trk_z0Res_mean_01xRes;
  double trk_z0Res_mean_25xRes;
  double trk_z0Res_mean_2xRes;
  double trk_z0Res_mean_3xRes;
  double trk_z0Res_mean_5xRes;
  double trk_z0Res_mean_10xRes;
  double trk_z0Res_mean_20xRes;
  double trk_z0Res_mean_4xRes;
  double trk_z0Res_mean_50xRes;
  double trk_z0Res_mean_150xRes;
  double trk_z0Res_mean_075xRes;
  double trk_z0Res_mean_025xRes;
  double trk_z0Res_mean_0075xRes;
  double trk_z0Res_mean_00075xRes;

  float m_flatTrackInefficiency; 
  float m_trackptcut;
  float m_smearFactor;
  std::string m_geometry;
  bool m_useparameterisation;
  bool m_issignal;
  bool m_isfixedwindow;
  bool m_isHTTtracks;
  bool m_isleadingtracks;
  std::string m_outputTrackContainerName;
  bool m_randomSeed;
  bool m_fakeKiller;



  // void smearTrack( xAOD::TrackParticle * trk);
  void ResetVariables();




};

#endif