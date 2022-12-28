#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>

#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoop/OutputStream.h>
#include "FTKxAODAnalysis/FTKxAODAnalysis.h"
#include "EventLoopGrid/PrunDriver.h"

int main( int argc, char* argv[] ) {

   // Take the submit directory from the input if provided:
   std::string outputFilePath = "";
   if(argc > 1) outputFilePath = argv [ 1 ];

   std::string submitDir = "gridSubmitDir_366805";
   if( argc > 2) submitDir = argv[ 2 ];

   std::string deltaR = "0.05";
   if( argc > 3) deltaR = argv[ 3 ];


   const char* outFile = outputFilePath.c_str();
   // Set up the job for xAOD access:
   xAOD::Init().ignore();

   // Construct the samples to run on:
   SH::SampleHandler sh;
   SH::scanRucio (sh, "data18_hi.00366805.physics_FTK.merge.AOD.f1026_m2048");

   // Set the name of the input TTree. It's always "CollectionTree"
   // for xAOD files.
   sh.setMetaString( "nc_tree", "CollectionTree" );
   sh.setMetaString( "nc_grid_filter", "*f1026_m2048._lb0*");
   sh.setMetaString( "nc_nFilesPerJob", "2");

   // Print what we found:
   sh.print();

   // Create an EventLoop job:
   EL::Job job;
   job.sampleHandler( sh );
   //   job.options()->setDouble (EL::Job::optMaxEvents, 5000);
   job.options()->setDouble (EL::Job::optMaxEvents, -1); 

   // Add our analysis to the job:
   FTKxAODAnalysis* alg1 = new FTKxAODAnalysis();


   alg1->SetIsData(true); 
   alg1->SetIsAOD(false);
  
   Float_t dR;
   dR = strtof(deltaR.c_str(),0);
   alg1->SetDeltaR(dR);

   job.algsAdd( alg1 );

   // alg1->outputName = "testNtupleOutputAlg1";
   // alg1->outputxAODName = "testxAODOutputAlg1";

   // Run the job using the local/direct driver:
   EL::PrunDriver driver;
   //   driver.options()->setDouble(EL::Job::optGridNFiles, 1);
   driver.options()->setDouble(EL::Job::optGridNFiles, -1);

   // optGridNFilesPerJob = "nc_nFilesPerJob"

// user.bstamas.data18_13TeV.00363400.physics_FTK.merge.AOD.f994_m2032.v2
   driver.options()->setString("nc_outputSampleName", outFile);

   driver.submitOnly( job, submitDir );


   return 0;
}
