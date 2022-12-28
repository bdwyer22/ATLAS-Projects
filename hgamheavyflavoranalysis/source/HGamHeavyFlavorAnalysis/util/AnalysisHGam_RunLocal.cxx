#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>

#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoop/OutputStream.h>

#include "HGamHeavyFlavorAnalysis/HGamHeavyFlavorAnalysis.h"
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


    // Get the file_type name:
   std::string file_type = "";
   if( argc > 3 ) file_type = argv[ 3 ];

    // Set the output directory name:
   std::string submitDir = "submitDir";
   if( argc > 4 ) submitDir = argv[ 4 ];
   xAOD::Init().ignore();
   SH::SampleHandler sh;
   const char* inputFile = inputFilePath.c_str();


   SH::DiskListLocal list (inputFile);
   if (file_type == "TMP_PowhegPy8_ttH125"){SH::ScanDir().filePattern("TMP_PowhegPy8_ttH125").scan (sh, inputFile);}
   if (file_type == "TMP_PowhegPy8_NNLOPS_ggH125"){SH::ScanDir().filePattern("TMP_PowhegPy8_NNLOPS_ggH125").scan (sh, inputFile);}


   if(file_type == "PowhegPy8EG_NNPDF30_VBFH125"){SH::ScanDir().filePattern("PowhegPy8EG_NNPDF30_VBFH125").scan (sh, inputFile);}
   
   if(file_type == "PowhegPy8_NNLOPS_ggH125" && mc_type == "mc16e"){SH::ScanDir().filePattern("mc16*.PowhegPy8_NNLOPS_ggH125*.root").scan (sh, inputFile);}
   else if (file_type == "PowhegPy8_NNLOPS_ggH125"){SH::ScanDir().filePattern("PowhegPy8_NNLOPS_ggH125").scan (sh, inputFile);}

   if(file_type == "PowhegH713_NNLOPS_ggH125"){SH::ScanDir().filePattern("mc16*.PowhegH713_NNLOPS_ggH125*.root").scan (sh, inputFile);}

   if(file_type == "PowhegPy8_WmH125J"){SH::ScanDir().filePattern("PowhegPy8_WmH125J").scan (sh, inputFile);}
   if(file_type == "PowhegPy8_WpH125J"){SH::ScanDir().filePattern("PowhegPy8_WpH125J").scan (sh, inputFile);}
   if(file_type == "PowhegPy8_ZH125J"){SH::ScanDir().filePattern("PowhegPy8_ZH125J").scan (sh, inputFile);}
   if(file_type == "PowhegPy8_bbH125"){SH::ScanDir().filePattern("PowhegPy8_bbH125").scan (sh, inputFile);}
   if(file_type == "PowhegPy8_ggZH125"){SH::ScanDir().filePattern("PowhegPy8_ggZH125").scan (sh, inputFile);}
   
   if(file_type == "PowhegPy8_ttH125"){SH::ScanDir().filePattern("mc16*.PowhegPy8_ttH125_fixweight*.root").scan (sh, inputFile);}
   // if(file_type == "PowhegPy8_ttH125"){SH::ScanDir().filePattern("PowhegPy8_ttH125").scan (sh, inputFile);}

   if(file_type == "aMCnloHwpp_tWH125_yt_plus1"){SH::ScanDir().filePattern("aMCnloHwpp_tWH125_yt_plus1").scan (sh, inputFile);}
   if(file_type == "aMCnloPy8_tWH125_MxAOD"){SH::ScanDir().filePattern("aMCnloPy8_tWH125_MxAOD").scan (sh, inputFile);}

   // if(file_type == "aMCnloPy8_tWH125"){SH::ScanDir().filePattern("aMCnloPy8_tWH125").scan (sh, inputFile);}
   if(file_type == "Sherpa2_diphoton_myy_90_175" && mc_type == "mc16a"){SH::ScanDir().filePattern("mc16a.Sherpa2_diphoton_myy_90_175.MxAODDetailed*").scan (sh, inputFile);}
   if(file_type == "Sherpa2_diphoton_myy_90_175" && mc_type == "mc16d"){SH::ScanDir().filePattern("mc16d.Sherpa2_diphoton_myy_90_175.MxAODDetailed*").scan (sh, inputFile);}
   if(file_type == "Sherpa2_diphoton_myy_90_175" && mc_type == "mc16e"){SH::ScanDir().filePattern("mc16e.Sherpa2_diphoton_myy_90_175.MxAODDetailed*").scan (sh, inputFile);}
   // if(file_type == "other"){SH::ScanDir().filePattern("*.root").scan (sh, inputFile);}
   // else{SH::ScanDir().filePattern(file_type).scan (sh, inputFile);}
   
   std::cout << "file_type " << file_type << std::endl;
   sh.setMetaString( "nc_tree", "CollectionTree" );
   sh.print();

   EL::Job job;
   job.sampleHandler( sh );
   job.options()->setDouble (EL::Job::optMaxEvents, -1);
   // job.options()->setDouble (EL::Job::optSkipEvents, 1500);
   // job.options()->setDouble (EL::Job::optMaxEvents, 100);


   HGamHeavyFlavorAnalysis* alg1 = new HGamHeavyFlavorAnalysis();

   alg1->SetIsData(false);
   alg1->SetIsMCa(false);
   alg1->SetIsMCd(false);
   alg1->SetIsMCe(false);
   alg1->SetIsMCde(false);
   // alg1->SetIs_PowhegPy8EG_NNPDF30_VBFH125(false);
   // alg1->SetIs_PowhegPy8_NNLOPS_ggH125(false);
   // alg1->SetIs_PowhegPy8_WmH125J(false);
   // alg1->SetIs_PowhegPy8_WpH125J(false);
   // alg1->SetIs_PowhegPy8_ZH125J(false);
   // alg1->SetIs_PowhegPy8_ggZH125(false);
   // alg1->SetIs_PowhegPy8_bbH125(false);
   // alg1->SetIs_PowhegPy8_ttH125(false);
   // alg1->SetIs_aMCnloHwpp_tWH125_yt_plus1(false);

   if(mc_type == "mc16a") {alg1->SetIsMCa(true);}
   if(mc_type == "mc16d") {alg1->SetIsMCd(true);}
   if(mc_type == "mc16e") {alg1->SetIsMCe(true);}
   if(mc_type == "mc16de") {alg1->SetIsMCde(true);}

   // std::cout << "file_type" << file_type << std::endl;

   // if(file_type == "PowhegPy8EG_NNPDF30_VBFH125"){alg1->SetIs_PowhegPy8EG_NNPDF30_VBFH125(true);}
   // if(file_type == "PowhegPy8_NNLOPS_ggH125"){alg1->SetIs_PowhegPy8_NNLOPS_ggH125(true);}
   // if(file_type == "PowhegPy8_WmH125J"){alg1->SetIs_PowhegPy8_WmH125J(true);}
   // if(file_type == "PowhegPy8_WpH125J"){alg1->SetIs_PowhegPy8_WpH125J(true);}
   // if(file_type == "PowhegPy8_ZH125J"){alg1->SetIs_PowhegPy8_ZH125J(true);}
   // if(file_type == "PowhegPy8_bbH125"){alg1->SetIs_PowhegPy8_bbH125(true);}
   // if(file_type == "PowhegPy8_ggZH125"){alg1->SetIs_PowhegPy8_ggZH125(true);}
   // if(file_type == "PowhegPy8_ttH125"){alg1->SetIs_PowhegPy8_ttH125(true);}
   // if(file_type == "aMCnloHwpp_tWH125_yt_plus1"){alg1->SetIs_aMCnloHwpp_tWH125_yt_plus1(true);}

   job.algsAdd( alg1 );

   EL::DirectDriver driver;
   driver.submit( job, submitDir );

   return 0;
}

