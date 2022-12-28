# Skimming the yyHF Systematic MxAODs

This needs to be done for all variations of the ```Sherpa2_diphoton_myy_90_175_AF2``` samples as they are too large to otherwise store. 

This method is a bit cumbersome, but due to memory constraints, each systematic type (JetSys1,2,3,4, PhotonAllSys1,2,3,4, etc.) needs to be ran seperately as it's not possible to load the entire script if all branches for all possible systematics are in the script (I tried). 

## Creating Inputs
As the MxAODs have hundreds of subfiles, you'll want to combine them into only a few NTUPs. This is done by creating a text file which lists all of the inputs that will go into each file, called ```createInputs.sh```. This script creates and fills a text file with up to 100 input files. When running this, be sure to change the directory of your MxAOD inputs (lines 4-6). 

## Setting Branches
The script ```getBranches.py``` is what I used to set all the varibales in the skimming code that change depending on the systematic. Each (currently commented) section prints out what should be copy/pasted into the yyHFSkim.cxx and yyHFSkim.h scripts. You can use this if you want, your choice, it was just a quick script I whipped up to not have to write everything out myself. This script should set things up so all branches (including truth information, which *may not be saved in all systematics, particularly in PhotonAllSys*) and the corresponding variations are saved. 

## Submitting the script
Use ```submit.sh``` to run the skimming code on the batch system. Be sure to modify it and the ```submit_job.sh``` script according to your own directories and the batch system you're using. The code is currently set up for FlavorSys1 sysematic variations. Be sure to create a project_archive that you recreate any time you make changes to the code using ```tar -czf project_archive.tgz  ../source/```.

Each batch job will create a build directory, compile, and run the code. To test locally first, create a build directory in the same way as was done to create the MxAODs with HGamCore, then the script can be run using ```yyHFSkim_RunLocal $filename $sampleType $sysType $outputname``` where $filename is the input text file with the path of each file, $sampleType is the mc campaign, $sysType is the systematic variation, and $outputname is the name of the output file. 

I've also included an example script I wrote to move all the batch outputs to the same directory ```moveFile.sh```. 

