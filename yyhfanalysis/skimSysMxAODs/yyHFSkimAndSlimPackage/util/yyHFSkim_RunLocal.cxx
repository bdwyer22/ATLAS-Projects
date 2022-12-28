#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <SampleHandler/ToolsDiscovery.h> 
#include <TSystem.h>

#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoop/OutputStream.h>

#include "yyHFSkim/yyHFSkim.h"

#include "EventLoopGrid/PrunDriver.h"
#include "SampleHandler/ScanDir.h"

#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

int main( int argc, char* argv[] ) {

   // Set the input file directory:
   std::string inputFilePath = "";
   if(argc > 1) inputFilePath = argv [ 1 ];


   // Take the mc type (mc16a, mc16d, mc16e):
   std::string mc_type = "";
   if(argc > 2) mc_type = argv [ 2 ];


    // Get the sys_type name:
   std::string sys_type = "";
   if( argc > 3 ) sys_type = argv[ 3 ];

    // Set the output directory name:
   std::string submitDir = "submitDir";
   if( argc > 4 ) submitDir = argv[ 4 ];

   
   xAOD::Init().ignore();
   SH::SampleHandler sh;
   const char* inputFile = inputFilePath.c_str();


   SH::DiskListLocal list (inputFile);

   // SH::ScanDir().filePattern("*.roo*").scan (sh, inputFile);

   SH::readFileList (sh, "sample", "testfile.txt");

   std::cout << "sys_type " << sys_type << std::endl;
   sh.setMetaString( "nc_tree", "CollectionTree" );
   sh.print();

   EL::Job job;
   job.sampleHandler( sh );
   job.options()->setDouble (EL::Job::optMaxEvents, -1);
   // job.options()->setDouble (EL::Job::optSkipEvents, 1500);
   // job.options()->setDouble (EL::Job::optMaxEvents, 5);
   
yyHFSkim* alg1 = new yyHFSkim();

   alg1->SetIsData(false);
   alg1->SetPeriod(0);

   if(mc_type == "mc16a")       alg1->SetPeriod(0);
   else if(mc_type == "mc16d")  alg1->SetPeriod(1);
   else if(mc_type == "mc16e")  alg1->SetPeriod(2);
   else {
     std::cout << "No Period Set "<< std::endl;
     return 1;
   }


   job.algsAdd( alg1 );

   EL::DirectDriver driver;
   driver.submit( job, submitDir );

   return 0;
}

