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
#include "SampleHandler/ScanDir.h"

#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

int main( int argc, char* argv[] ) {

   // Take the input file directory from the input if provided:
   std::string inputFilePath = "";
   if(argc > 1) inputFilePath = argv [ 1 ];

   std::string filetype = "";
   if(argc > 2) filetype = argv [ 2 ];

   // Take the submit directory from the input if provided:
   std::string submitDir = "submitDir";
   if( argc > 3 ) submitDir = argv[ 3 ];

   std::string deltaR = "0.05";
   if( argc > 4 ) deltaR = argv[ 4 ];

   std::string doNtuple = "";
   if( argc > 5 ) doNtuple = argv[ 5 ];

   std::string doMinixAOD = "";
   if( argc > 6 ) doNtuple = argv[ 6 ];

   // Set up the job for xAOD access:
   xAOD::Init().ignore();

   // Construct the samples to run on:
   SH::SampleHandler sh;

   // const char* inputFile = gSystem->ExpandPathName (inputFilePath);
   const char* inputFile = inputFilePath.c_str();


   SH::DiskListLocal list (inputFile);
   //   list.print();
   //   SH::ScanDir (sh, list, "AOD*root");
   //   scanDir.print();

   std::cout << filetype << std::endl;

   if(filetype == "AOD") {SH::ScanDir().filePattern("AOD*roo*").scan (sh, inputFile);} 
   if(filetype == "DAOD") {SH::ScanDir().filePattern("DAOD*roo*").scan (sh, inputFile);} 
   if(filetype == "data") {SH::ScanDir().filePattern("AOD*roo*").scan (sh, inputFile);} 
   if ((filetype != "AOD") && (filetype != "DAOD") && (filetype != "data")) { std::cerr << "invalid file type, use either AOD, DAOD, or data" << std::endl;}
   else {std::cerr << filetype << std::endl;}

   // Set the name of the input TTree. It's always "CollectionTree"
   // for xAOD files.
   sh.setMetaString( "nc_tree", "CollectionTree" );


   // Print what we found:
   sh.print();

 

   // Create an EventLoop job:
   EL::Job job;
   job.sampleHandler( sh );
   job.options()->setDouble (EL::Job::optMaxEvents, -1);
   // job.options()->setDouble (EL::Job::optSkipEvents, 1500);
   // std::cerr << "1500+" << std::endl;
   // job.options()->setDouble (EL::Job::optMaxEvents, 500);

   // Add our analysis to the job:
   FTKxAODAnalysis* alg1 = new FTKxAODAnalysis();

   // std::cerr << "NEW "  <<   alg1->isData << std::endl;

   Float_t dR;
   dR = strtof(deltaR.c_str(),0);
   alg1->SetDeltaR(dR);

   if(filetype == "AOD") {alg1->SetIsData(false); alg1->SetIsAOD(true);}
   // std::cerr << "BRI TEST isAOD 4 is equal to " << value << std::endl;
   // else {alg1->SetIsAOD(false);}

   if(filetype == "data"){alg1->SetIsData(true); alg1->SetIsAOD(false);}
   // else {alg1->SetIsData(false);}
   if(filetype == "DAOD"){alg1->SetIsData(false); alg1->SetIsAOD(false);}


   // std::cerr << "BRI 1TEST isData is equal to " << alg1->isData << std::endl;
   // if (alg1->isData == false){std::cerr << "SIMULATION" << std::endl;}
   // std::cerr << alg1->isAOD << std::endl;

   job.algsAdd( alg1 );

   // Run the job using the local/direct driver:
   EL::DirectDriver driver;
   driver.submit( job, submitDir );

   return 0;
}
