// STL include(s):
#include <cstdlib>
#include <iostream>
#include <string>

// EDM include(s):
#include "EventLoop/CondorDriver.h"
#include "EventLoop/DirectDriver.h"
#include "EventLoop/GEDriver.h"
#include "EventLoop/SlurmDriver.h"
#include "SampleHandler/ScanDir.h"
#include "EventLoop/Job.h"
#include "EventLoop/LocalDriver.h"
#include "EventLoopGrid/GridDriver.h"
#include "EventLoopGrid/PrunDriver.h"
#include "PathResolver/PathResolver.h"
#include "SampleHandler/MetaFields.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/SampleLocal.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/ToolsSplit.h"
#include "xAODRootAccess/Init.h"

// ROOT include(s):
#include "TSystem.h"
#include "TString.h"

// Local include(s):
#include "HGamAnalysisFramework/Config.h"
#include "HGamAnalysisFramework/RunUtils.h"


// See header file for documentation

namespace HG {
  TString getHelp(TString progName)
  {
    TString help = "\n  HELP\n    " + progName + " [CONFIG-FILES] [root files] [KEY: VALUE]\n\n";
    help += "    [CONFIG-FILES] TEnv text files (*.cfg or *.config) with settings used both by algortihm and job submission.\n";
    help += "    [root files] if argument is of the form *.root* these will be used as input\n";
    help += "    Some basic config KEYs, which follow the same format as the CONFIG-FILE, are:\n";
    help += "      InputFile:     specifies an input ROOT file. Can be used multiple times\n";
    help += "      InputFileList: specifies a text file containing a list of ROOT files to run over\n";
    help += "      OutputDir:     specifies ouput directory. DATE is replaced by date+time [default: " + progName + "_DATE]\n";
    help += "      SampleName:    specifies sample name, used to label the output files [default: sample]\n";
    help += "      BaseConfig:    overrides the default base configuration file (calibration smearing etc)\n";
    help += "    Config KEYs for running on the Grid:\n";
    help += "      GridDS:        specifies a grid data sample to run over\n";
    help += "      OutputDS:      specifies the grid output dataset name\n";
    help += "    Config KEYs for running on GridEngine batch systems:\n";
    help += "      BatchGE: YES                  Tells the job to run in batch mode\n";
    help += "      nc_EventLoop_EventsPerWorker: Number of events per subjob\n";
    help += "      nc_EventLoop_SubmitFlags:     Submit flags for the SGE system\n";
    help += "    Config KEYs for running on HTCondor batch systems:\n";
    help += "      BatchCondor: YES              Tells the job to run in batch mode\n";
    help += "      nc_EventLoop_EventsPerWorker: Number of events per subjob\n";
    help += "      Condor_shellInit:             Any required shellInit commands\n";
    help += "      optCondorConf:                Configuration lines to be added to the Condor config file\n";
    help += "    Config KEYs for running on Slurm batch systems:\n";
    help += "      BatchSlurm: YES              Tells the job to run on Slurm\n";
    help += "      SlurmAccount:                Slurm account name";
    help += "      SlurmPartition:              Slurm partition";
    help += "      SlurmRunTime:                Slurm max. run time";
    help += "      SlurmJobName:                Slurm job name";
    help += "      SlurmMemory:                 Slurm max. memory";
    help += "      SlurmMail:                   Mail address for notifications";
    help += "      SlurmDatasetDirs:            File with list of dataset directories for Slurm";
    help += "\n  EXAMPLE:\n";
    help += "    " + progName + " InputFileList: ~/myFilelists/ZH_files_on_EOS.list SampleName: ZH OutputDir: ~/data/output/HDM_ZH BaseConfig: HGamAnalysisFramework/HgammaConfig.cfg\n";
    help += "  or\n    " + progName + " HDM_ZH.cfg\n";
    help += "  in the latter case, the above options can all be specified in the config file (HDM_ZH.cfg).\n";
    return help;
  } // getHelp
} // namespace HG


namespace HG {
  HG::StrV parseArguments(Config *conf, int argc, char **argv)
  {
    StrV files;

    for (int argi = 1; argi < argc; ++argi) {
      TString arg = argv[argi];

      // 1. Check if argument is a configuration file. If so add it!
      if (arg.EndsWith(".cfg") || arg.EndsWith(".config")) {
        conf->addFile(arg);
        continue;
      }

      // 2. If the argument contains ".root", i.e. *.root*, add it to files to run over
      if (arg.Contains(".root")) {
        files.push_back(arg);
        continue;
      }

      // 3. If the arguemnt ends with colon, add a new argument
      if (arg.EndsWith(":")) {
        TString key(arg);
        key.ReplaceAll(":", "");
        conf->setValue(key, argv[++argi]);
        continue;
      }

      // if we get here, the arguemnt cannot be understood
      HG::fatal("Cannot interpret argument: " + arg + getHelp(argv[0]));
    }

    return files;
  } // parseArguments
} // namespace HG



namespace HG {
  void gridSubmit(SH::SampleHandler sh, EL::Job job, Config conf, TString submitDir)
  {
    /*
     *  Grid submission
     */

    if (getenv("ATLAS_LOCAL_PANDACLIENT_PATH") == NULL)
    { HG::fatal("You must execute \"lsetup panda\" (or \"localSetupPandaClient\") to run on the grid."); }

    // Construct sample to run on
    for (TString sample : conf.getStrV("GridDS"))
    { SH::addGrid(sh, sample.Data()); }

    // add the grid dataset here
    sh.setMetaString("nc_tree", "CollectionTree");

    // hack since a central cmtConfig is hardcoded
    sh.setMetaString("nc_cmtConfig", gSystem->ExpandPathName("$AnalysisBase_PLATFORM"));

    // Set the file pattern, if specified in the config
    if (conf.isDefined("nc_grid_filter"))
    { sh.setMetaString("nc_grid_filter", conf.getStr("nc_grid_filter").Data()); }

    job.sampleHandler(sh);

    if (!conf.isDefined("OutputDS")) {
      fatal("To submit to the grid, you MUST define an OutputDS of the form: user.<UserName>.<UniqueString>");
    }

    // Check for an OutputDS
    TString outDS = conf.getStr("OutputDS");

    printf("  %20s  %s\n", "OutputDS:", outDS.Data());

    EL::PrunDriver driver;
    driver.options()->setString("nc_outputSampleName", outDS.Data());

    for (auto opt : {"nc_nFiles", "nc_nFilesPerJob", "nc_nJobs"})

      if (conf.isDefined(opt))
      { driver.options()->setDouble(opt, conf.getInt(opt)); }

    for (auto opt : {"nc_site", "nc_excludedSite", "nc_EventLoop_SubmitFlags", "nc_mergeOutput", "nc_official", "nc_voms", "nc_destSE"})

      if (conf.isDefined(opt))
      { driver.options()->setString(opt, conf.getStr(opt).Data()); }

    if (conf.getBool("UsexAODMerge", false)) {
      if (conf.isDefined("nc_EventLoop_SubmitFlags"))
      { fatal("You can NOT specify UsexAODMerge and nc_EventLoop_SubmitFlags at the same time. Exiting."); }

      // TODO update this to use PathResolver - will also need an update to CMakeLists to install scripts from scripts/
      driver.options()->setString(EL::Job::optSubmitFlags,
                                  "--mergeScript=__panda_rootCoreWorkDir/HGamAnalysisFramework/scripts/xaodmerge %OUT %IN");
    }

    if (conf.getBool("UseSkimAndSlimToMerge", false)) {
      if (conf.isDefined("nc_EventLoop_SubmitFlags"))
	{ fatal("You can NOT specify UseSkimAndSlimToMerge and nc_EventLoop_SubmitFlags at the same time. Exiting."); }
 
      // TODO: Check if this the best way of doing  this
      driver.options()->setString(EL::Job::optSubmitFlags,
                                  "--mergeScript='skimAndSlimToMerge %OUT %IN'");

    }

    if (conf.getBool("SubmitAndDownload", false)) {
      // this will submit and automatically download the dataset
      // once the job is finished.
      driver.submit(job, submitDir.Data());
    } else {
      // this will only submit the job
      // user will have to download using dq2-get
      driver.submitOnly(job, submitDir.Data());
    }

    // after submitting, we're done.
    return;
  } // gridSubmit
} // namespace HG

namespace HG {
  void batchSubmitSlurm(EL::Job job, Config conf, TString submitDir)
  {

    EL::SlurmDriver driver;
    SH::SampleHandler sh;
    SH::ScanDir scanner;
    // don't use partialy downloaded files
    scanner.fileRegex("^((?!part).)*$");
    std::ifstream myfile(conf.getStr("SlurmDatasetDirs").Data());


    std::string line;

    while (std::getline(myfile, line)) {
      if (!line.empty() && line.at(0) != '#') {
        scanner.scan(sh, line);
      }
    }

    sh.print();

    // Set the collection tree name
    sh.setMetaString("nc_tree", "CollectionTree");

    job.sampleHandler(sh);


    std::string mailuser = conf.getStr("SlurmMail", "").Data();

    if (mailuser != "") {
      mailuser = Form("\n#SBATCH --mail-user %s\n#SBATCH --mail-type END", mailuser.c_str());
    }

    driver.SetJobName(conf.getStr("SlurmJobName", "HGamJob").Data());
    // hack to set the mailuser property
    driver.SetAccount((conf.getStr("SlurmAccount", "") + mailuser).Data());
    driver.SetPartition(conf.getStr("SlurmPartition", "").Data());
    driver.SetRunTime(conf.getStr("SlurmRunTime", "").Data());
    driver.SetMemory(conf.getStr("SlurmMemory", "2583").Data());

    driver.submit(job, submitDir.Data());
    return;

  } // slurmSubmit
} // namespace HG

namespace HG {
  void batchSubmitGE(SH::SampleHandler sh, EL::Job job, Config conf, TString submitDir)
  {

    EL::GEDriver driver;

    // Set the collection tree name
    sh.setMetaString("nc_tree", "CollectionTree");

    SH::scanNEvents(sh);
    int maxEvents = conf.getNum("nc_EventLoop_EventsPerWorker", -1);

    if (maxEvents < 0)
    { HG::fatal("Error: To run in batch mode, you must specify nc_EventLoop_EventsPerWorker"); }

    sh.setMetaDouble(EL::Job::optEventsPerWorker, maxEvents);

    TString details;

    for (auto sample : sh) {
      int numEvents = sample->meta()->castDouble(SH::MetaFields::numEvents, -1);
      details = Form("Sample \"%s\" has %d entries (nc_EventLoop_EventsPerWorker=%d, meaning %d jobs)",
                     sample->name().c_str(), numEvents, maxEvents, int(ceil(numEvents / float(maxEvents))));
      std::cout << details << std::endl;
    }

    job.sampleHandler(sh);

    // Check your own system for what flags are necessary.
    // -V is needed to transfer the environment variables to the jobs
    TString sge_flags = conf.getStr("nc_EventLoop_SubmitFlags",
                                    "-q default.q,short.q,long.q -l h_vmem=4G -V");
    driver.options()->setString(EL::Job::optSubmitFlags, sge_flags.Data());

    std::cout << "Sumitting jobs to GridEngine batch system using options \""
              << sge_flags << "\"" << " (set using nc_EventLoop_SubmitFlags)" << std::endl;

    bool submitanddownload = conf.getBool("SubmitAndDownload", false);

    bool reSubmit = conf.getBool("ReSubmit", false);

    if (reSubmit) {
      std::cout << "Will try to resubmit the jobs" << std::endl;
      driver.resubmit(submitDir.Data(), "ALL_MISSING");
    } else {

      if (submitanddownload) { driver.submit(job, submitDir.Data()); }
      else { driver.submitOnly(job, submitDir.Data()); }

    }

    return;

  } // batchSubmitGE
} // namespace HG




namespace HG {
  void batchSubmitCondor(SH::SampleHandler sh, EL::Job job, Config conf, TString submitDir)
  {

    EL::CondorDriver driver;

    // Set the collection tree name
    sh.setMetaString("nc_tree", "CollectionTree");

    SH::scanNEvents(sh);
    int maxEvents = conf.getNum("nc_EventLoop_EventsPerWorker", -1);

    if (maxEvents < 0)
    { HG::fatal("Error: To run in batch mode, you must specify nc_EventLoop_EventsPerWorker"); }

    sh.setMetaDouble(EL::Job::optEventsPerWorker, maxEvents);

    TString details;

    for (auto sample : sh) {
      int numEvents = sample->meta()->castDouble(SH::MetaFields::numEvents, -1);
      details = Form("Sample \"%s\" has %d entries (nc_EventLoop_EventsPerWorker=%d, meaning %d jobs)",
                     sample->name().c_str(), numEvents, maxEvents, int(ceil(numEvents / float(maxEvents))));
      std::cout << details << std::endl;
    }

    job.sampleHandler(sh);

    // Your system might also need a specific "shell init"
    driver.shellInit = conf.getStr("Condor_shellInit", "");

    TString optCondorConf = "getEnv = True";

    // Possibility to add items to optCondorConf
    if (conf.getStr("optCondorConf", "").Length()) {
      optCondorConf += "\n";
      optCondorConf += conf.getStr("optCondorConf", "");
    }

    job.options()->setString(EL::Job::optCondorConf, optCondorConf.Data());

    std::cout << "Sumitting jobs to Condor batch system using options\n"
              << "shellInit: \"" << driver.shellInit << "\" (set using Condor_shellInit),\n"
              << "optCondorConf: \"" << optCondorConf << "\" (set using optCondorConf)." << std::endl;

    bool submitanddownload = conf.getBool("SubmitAndDownload", false);

    if (submitanddownload) { driver.submit(job, submitDir.Data()); }
    else { driver.submitOnly(job, submitDir.Data()); }

    return;

  } // batchSubmitCondor
} // namespace HG




void HG::runJob(HgammaAnalysis *alg, int argc, char **argv)
{
  /*
   *  Fetch the program name and create a help
   */
  TString help = getHelp(argv[0]);

  /*
   *   1. Let's read the configuration
   */

  Config conf;
  // Files are added if they are standalone arguments ending in ".root"
  StrV files = parseArguments(&conf, argc, argv);

  // TEnv uses value from first file it's specified in.
  // If specified, read in additional configuration
  if (conf.isDefined("Include"))
    for (TString cfg : conf.getStrV("Include"))
    { conf.addFile(cfg); }

  // Fill unspecified values from default config, specified here.
  if (!conf.isDefined("BaseConfig")) {
    HG::fatal("You must specify a base configuration file, option: BaseConfig. Exiting." + help);
  } else {
    conf.addFile(PathResolverFindCalibFile(conf.getStr("BaseConfig").Data()));
  }

  // what's the sample name ?
  TString progName = argv[0];
  TString sampleName = conf.getStr("SampleName", "sample");
  TString submitDir  = conf.getStr("OutputDir", progName + "_DATE");

  if (submitDir.Contains("DATE")) {
    TDatime now = TDatime();
    submitDir.ReplaceAll("DATE", Form("%d.%.2d.%.2d_%.2d.%.2d.%.2d",
                                      now.GetYear(), now.GetMonth(), now.GetDay(),
                                      now.GetHour(), now.GetMinute(), now.GetSecond()));
    conf.setValue("OutputDir", submitDir.Data());
  }

#if __RELEASE__ >= HGAM_VERSION(21,0,0)
  printf("  Code setup assumes release 21 input. That is, you should be using AnalysisBase,21.2.X\n");
#else
  printf("  This base release isn't known to the code. Proceed at your own risk!\n");
#endif

  printf("\n");
  printf("  %20s  %s\n", "SampleName:", sampleName.Data());
  printf("  %20s  %s\n", "OutputDir:", submitDir.Data());

  bool doReSubmit = conf.getBool("ReSubmit", false);

  if (HG::fileExist(submitDir) && !doReSubmit)
    fatal("Output directory " + submitDir + " already exists.\n" +
          "  Rerun after deleting it, or specify a new one, like below.\n" +
          "    OutputDir: NEWDIR");

  // Add the confiuration to the algorithm!
  alg->setConfig(conf);

  /*
   * Initiate SH::SampleHandler and EL::Job
   */

  // create a new sample handler to describe the data files we use
  SH::SampleHandler sh;

  // this is the basic description of our job
  EL::Job job;

  // Set to branch access mode
  TString accessMode = conf.getStr("xAODAccessMode", "class");

  if (accessMode == "branch") {
    job.options()->setString(EL::Job::optXaodAccessMode, EL::Job::optXaodAccessMode_branch);
  } else if (accessMode == "class") {
    job.options()->setString(EL::Job::optXaodAccessMode, EL::Job::optXaodAccessMode_class);
  } else if (accessMode == "athena") {
    job.options()->setString(EL::Job::optXaodAccessMode, EL::Job::optXaodAccessMode_athena);
  } else {
    fatal("xAODAccessMode not recognized, should be on of: class, branch, athena");
  }

  // Add our algorithm to the job
  job.algsAdd(alg);



  /*
   * Non-local submission (Grid)
   */

  if (conf.isDefined("GridDS")) {
    gridSubmit(sh, job, conf, submitDir);
    return;
  }



  /*
   * Handle input files
   */

  // add to the input file list if specified
  if (conf.isDefined("InputFile")) {
    for (auto file : conf.getStrV("InputFile")) { files.push_back(file); }
  }

  if (files.size()) {
    // If one or several root files are specified as arugment, run over these
    std::auto_ptr<SH::SampleLocal> sample(new SH::SampleLocal(sampleName.Data()));
    printf("\n  %s\n", "InputFiles:");

    for (TString file : files) {
      printf("    %s\n", file.Data());
      sample->add(file.Data());
    }

    printf("\n");

    // add the files to the sample handler
    sh.add(sample.release());

  } else if (conf.isDefined("InputFaxDS")) {
    SH::addGrid(sh, conf.getStr("InputFaxDS").Data());
  } else if (conf.isDefined("SlurmDatasetDirs")) {
  } else if (conf.isDefined("InputFileList")) {

    TString fileList = conf.getStr("InputFileList");
    printf("  %20s  %s\n", "InputFileList:", fileList.Data());

    if (!HG::fileExist(fileList)) {
      // fileList = gSystem->ExpandPathName(("$ROOTCOREBIN/data/"+fileList).Data());
      fileList = PathResolverFindDataFile(fileList.Data());
    }

    if (!HG::fileExist(fileList)) {
      HG::fatal("The input file-list specified: " + conf.getStr("InputFileList") + " doesn't exist.");
    }

    SH::readFileList(sh, sampleName.Data(), fileList.Data());
    // print out the files
    sh.print();
  } else {
    fatal("No input specified!" + help);
  }


  // Set number of events to be processed
  if (conf.isDefined("NumEvents"))
  { job.options()->setDouble(EL::Job::optMaxEvents, conf.getInt("NumEvents")); }

  // Set number of events to be skipped
  if (conf.isDefined("SkipEvents"))
  { job.options()->setDouble(EL::Job::optSkipEvents, conf.getInt("SkipEvents")); }


  /*
   * GE driver (Grid Engine batch system)
   */
  if (conf.getBool("BatchGE", false)) {
    batchSubmitGE(sh, job, conf, submitDir);
    return;
  }

  /*
   * Condor driver (HTCondor batch system)
   */
  if (conf.getBool("BatchCondor", false)) {
    batchSubmitCondor(sh, job, conf, submitDir);
    return;
  }

  /*
   * Slurm driver
   */
  if (conf.getBool("BatchSlurm", false)) {
    batchSubmitSlurm(job, conf, submitDir);
    return;
  }

  /*
   * Local running
   */

  // set the name of the tree in our files
  // in the xAOD the TTree containing the EDM containers is "CollectionTree"
  // what does "nc_tree" mean??
  sh.setMetaString("nc_tree", "CollectionTree");
  job.sampleHandler(sh);

  // Determine if more than one CPU should be used
  Int_t numWorkers = 1;

  // First check whether ROOTCORE is set to use multiple CPUs
  // Since it's buggy on lxplus, force user to specify in config file for now
  // TString var = gSystem->ExpandPathName("$ROOTCORE_NCPUS");
  // if (var != "") numWorkers = atoi(var.Data());

  // Check if a different number is specified in configuration
  numWorkers = conf.getNum("NumberOfProofWorkers", numWorkers);

  // Run analysis
  if (numWorkers != 1) {
    HG::fatal("Proof is no longer supported in release 21, contact ASG if you'd like to volunteer :-)");
    // printf("\nUsing PROOF lite on %d worker nodes.\n\n", numWorkers);
    // EL::ProofDriver driver;
    // driver.numWorkers = numWorkers;
    // driver.submit(job, submitDir.Data());
  } else {
    EL::DirectDriver driver;
    driver.submit(job, submitDir.Data());
  }

  //-----------------------------------------------------------------

  printf("\n  Output directory: %s\n", submitDir.Data());
  printf("  xAOD output in:   %s/data-MxAOD\n\n", submitDir.Data());

} // HG::runJob
