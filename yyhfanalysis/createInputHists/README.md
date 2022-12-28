
## Creating the Histogram Templates

This code creates the templates that will be given to TRExFitter. There are 4 main steps:
1. Run over the nominal and systemtic samples using ```makeAllHists.py```
2. Run over the very large (90-175) diphton NTUP files created previously using the ```fastHists_$SYS.C``` scripts
3. Run over the data to obtain the templates for jets faking photons using code in the ```makeDataHists``` directory
4. Run over the diphoton simulation samples for jets faking photons that will be subtracted from the data templates using the code in the ```makeSubtractionHists``` directory


In addition, I've included a few useful scripts:
* ```checkKinematics.py``` runs over a given sample and just plots some kinematics (photon/jet pt, eta, phi, myy, pt_jj, etc)
* ```create_cutflows.py``` is needed for making the templates as the inputs cutflows are split per file and would results in an inaccurate sum of weights for simulation, this script loops over all inputs for a given sample and adds the histograms together in a single root file
* ```moveFile.sh``` is a quick script (copied a few places) that just moves and merges the outputs from the batch area (it also sums samples when needed if split by mass ranges or decay process)

### Nominal and Systematics
To run locally, run the python script giving (in order) the name of the individual input file, the name you want the output file to have, the sample short name, the mc campaign, and the systemtic type. For example:

```python makeAllHists.py newInputs/Sherpa_tt_dilepton/Nominal/mc16a/user.bstamas.28469264._000001.MxAOD.root yyHF_inputHistMaker_Sherpa_tt_dilepton_Nominal_mc16a.root Sherpa_tt_dilepton mc16a Nominal```

The script is set up to create histograms with and without the higgs mass window included. There is a MET cut currently in the control bin 25. 

The scripts ```submit.sh``` and ```submit_job.sh``` are set up to submit on the NICADD cluster batch system. If using this, be sure to change your input and output directories. 

The code is set up to use the cutflows from a seperate, summed root file as created by ```create_cutflows.py```. These should be stored in the same directory as the python scripts (called "cutflows") that is split first by systematic type, then has each sample as a seperate root file for each mc campaign (i.e. called ```mc16e.CutFlow_Sherpa_tt_dilepton.root``` in a directory ```cutflows/Nominal```).

### Large Diphoton Samples

As the NTUPs are too large and python is too slow, the scripts ```fastHists_$SYS.C``` must be used. Again, as with when creating the skimmed files, I wasn't sure how to do this without totally filling memory, so each systematic is seperate. It's a pain when making changes to control regions, but it is what it is. 

### Obtianing Jet Fake Templates

Run the ```makeDataHists.py``` and ```makeDataHists_singlejet.py``` python scripts from the ```makeDataHists``` directory to obtain dijet and single-jet templates. No control regions are in these templates, so this should only need to be done once when changes are made to the code in HGamCore. This is, as the directory name suggests, run on 2015-2018 data. The batch submission scripts are in that directory. 

### Obtianing MC Subtraction Fake Templates

Run the ```makeDecompSubtractHist.py``` python script from the ```makeSubtractionHists``` directory. This is run over the nominal diphoton sample for all diphoton mass ranges. The batch submission scripts are in that directory. 
