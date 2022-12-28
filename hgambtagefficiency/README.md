Uses asetup AnalysisBase,21.2.56,here  
  
  
Run using submit_all.sh which gives the input file name in listOfSamples (you will need to change sampleDir though). To add new files to run over, you can add them to the run script in util. Currently it's set up to pull specific root files when they're all in the same directory, if you don't want to add a new file to util script, you can just set the sampleDir to the correct directory and use the sample name as "other" so that any file with the .root extension will be ran over.