#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>

#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoop/OutputStream.h>

#include "HGamMxAODAnalysis/HGamMxAODAnalysis.h"
#include "EventLoopGrid/PrunDriver.h"
#include "SampleHandler/ScanDir.h"

#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

int main( int argc, char* argv[] ) {

   // Take the input file directory from the input if provided:
   std::string inputFilePath = "";
   if(argc > 1) inputFilePath = argv [ 1 ];


   // Take the data type (mc or data)
   std::string filetype = "";
   if(argc > 2) filetype = argv [ 2 ];

    // Get the cutflow name:
   std::string cutflow_type = "";
   if( argc > 3 ) cutflow_type = argv[ 3 ];

    // Take the submit directory from the input if provided:
   std::string submitDir = "submitDir";
   if( argc > 4 ) submitDir = argv[ 4 ];
   // Set up the job for xAOD access:
   xAOD::Init().ignore();

   // Construct the samples to run on:
   SH::SampleHandler sh;

   // const char* inputFile = gSystem->ExpandPathName (inputFilePath);
   const char* inputFile = inputFilePath.c_str();
   // const char* cutflow_name = cutflow_input.c_str();

   // std::cout<< "header cutflow_input " << cutflow_input << std::endl;
   // std::cout<< "header cutflow_name" << cutflow_name << std::endl;



   SH::DiskListLocal list (inputFile);

   SH::ScanDir().filePattern("user.bstamas*roo*").scan (sh, inputFile);
   SH::ScanDir().filePattern("mc*roo*").scan (sh, inputFile);
   // SH::ScanDir().filePattern("mc*roo*").scan (sh, inputFile);
   // SH::ScanDir().filePattern("mc16a.PowhegPy8_NNLOPS_ggH125.MxAODDetailed.e5607_s3126_r9364_p3665.h024.root").scan (sh, inputFile);
   // SH::ScanDir().filePattern("mc16a.PowhegPy8_NNPDF30_VBFH125.MxAODDetailed.e5720_s3126_r9364_p3665.h024.root").scan (sh, inputFile);

   // if(cutflow_type == "vbf"){SH::ScanDir().filePattern("mc16a.PowhegPy8_NNPDF30_VBFH125.MxAODDetailed.e5720_s3126_r9364_p3665.h024.root").scan (sh, inputFile);}
   // if(cutflow_type == "ggh"){SH::ScanDir().filePattern("mc16a.PowhegPy8_NNLOPS_ggH125.MxAODDetailed.e5607_s3126_r9364_p3665.h024.root").scan (sh, inputFile);}
   // if(cutflow_type == "sherpa"){alg1->SetIsSherpa(true); alg1->SetIsVBF(false); alg1->SetIsggh(false);std::cout << "setting to sherpa" << std::endl;}


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
   // job.options()->setDouble (EL::Job::optMaxEvents, 5);
   // if(cutflow_type == "vbf"){job.options()->setDouble (EL::Job::optMaxEvents, 1045651); //VBF}
   // if(cutflow_type == "ggh"){job.options()->setDouble (EL::Job::optMaxEvents, 2546184); //gg125}
   // job.options()->setDouble (EL::Job::optMaxEvents, 2546184); //gg125
   // job.options()->setDouble (EL::Job::optMaxEvents, 1045651); //VBF 
   // job.options()->setDouble (EL::Job::optMaxEvents, 5778624); //sherpa
   // Add our analysis to the job:
   HGamMxAODAnalysis* alg1 = new HGamMxAODAnalysis();

   // alg1->SetCutflow(cutflow_name);

   if(filetype == "data"){alg1->SetIsData(true); alg1->SetIsMCa(false); alg1->SetIsMCd(false); alg1->SetIsMCe(false); alg1->SetIsMCde(false);}
   if(filetype == "mc16a") {alg1->SetIsData(false); alg1->SetIsMCa(true); alg1->SetIsMCd(false); alg1->SetIsMCe(false); alg1->SetIsMCde(false);}
   if(filetype == "mc16d") {alg1->SetIsData(false); alg1->SetIsMCa(false); alg1->SetIsMCd(true); alg1->SetIsMCe(false); alg1->SetIsMCde(false);}
   if(filetype == "mc16e") {alg1->SetIsData(false); alg1->SetIsMCa(false); alg1->SetIsMCd(false); alg1->SetIsMCe(true); alg1->SetIsMCde(false);}
   if(filetype == "mc16de") {alg1->SetIsData(false); alg1->SetIsMCa(false); alg1->SetIsMCd(false); alg1->SetIsMCe(false); alg1->SetIsMCde(true);}
   std::cout << "cutflow_type" << cutflow_type << std::endl;
   if(cutflow_type == "vbf"){alg1->SetIsSherpa(false); alg1->SetIsVBF(true); alg1->SetIsggh(false);std::cout << "setting to vbf" << std::endl;}
   if(cutflow_type == "ggh"){alg1->SetIsSherpa(false); alg1->SetIsVBF(false); alg1->SetIsggh(true);std::cout << "setting to ggh" << std::endl;}
   if(cutflow_type == "sherpa"){alg1->SetIsSherpa(true); alg1->SetIsVBF(false); alg1->SetIsggh(false);std::cout << "setting to sherpa" << std::endl;}

   job.algsAdd( alg1 );

   // Run the job using the local/direct driver:
   EL::DirectDriver driver;
   driver.submit( job, submitDir );

   return 0;
}
