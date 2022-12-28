# Running the Diphoton + Heavy Flavor Analysis



## Getting started
1. Create MxAODs using HGamCore
2. Create the input histograms from the MxAODs
3. Create individual histogram files as input to TRExFitter
4. Run TRExFitter



### Creating MxAODs

Follow the README in the ```createMxAODs``` subdirectory. This step used HIGG1D1 DAODs to produce MxAODs using the HGamAnalysisFramework. For large files, you should then run the code in the ```skimSysMxAODs``` subdirectory to dump the MxAODs to a flat NTUP to reduce size. This step only saves the branches that are currently being used, so make sure when running it that you have all that you need before deleting the original MxAODs. 

### Creating Histograms

Follow the README in ```createInputHists``` using the MxAODs and NTUPs created in the previous step. This applies 1- and 2-jet selections and creates the histograms (including any CR bins) that will be used for the template fit. It creates histograms that are split by truth-jet flavor (bb, bc, bl, cc, cl, ll, or b, c, l) and is where you can specify overall MET and n-jet cuts and inclusion of the Higgs window. This is done for all nominal and sysemtaic variations. A seperate script is run to create the histograms for jet-fakes including the subtraction than for nominal/sysematics. For fakes, the code used is in ```makeDataHists``` and the subtraction is run from mc using the code in ```makeSubtractionHists```. These two outputs are combined in the next step. 

### Creating TRExFitter Inputs

Follow the README in ```createTRExInputs/``` which will create an individual root file for each input histogram (yes, for every systematic, it's going to be a lot). 

### Running TRExFitter

Checkout the [TRExFitter](https://trexfitter-docs.web.cern.ch/trexfitter-docs/) package and follow their README for compiling. At this point, it's not a bad idea to subscribe to their email list as it is usually quite helpful (I've figured out how to do multiple things through other people's questions) which has the egroup name atlas-phys-stat-tthfitter. The config you use can be created using the the script ```createConfig.py``` in the ```createTRExInputs``` subdirectory. This config sets which inputs to use, how to normalize them, tells TRExFitter how the systematics should be handled, and also sets the final output histogram colors. The order of operations is as follows:

```
trex-fitter h config/yyhf.config #read input histograms (valid only if the proper option is specified in the config file)
trex-fitter w config/yyhf.config #create the RooStats xmls and workspace
trex-fitter f config/yyhf.config #fit the workspace
trex-fitter d config/yyhf.config #draw pre-fit plots
trex-fitter p config/yyhf.config #draw post-fit plots
trex-fitter f config/yyhf.config #fit the workspace
trex-fitter r config/yyhf.config #draw ranking plot
```
The final ranking step usually takes a very long time, it is suggested that you do the ranking in batches for each systemaic then combine them. 
