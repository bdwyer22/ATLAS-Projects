
## Creating TRExFitter Inputs

The inputs for TRExFitter are currently given as individual root files for each sample and systematic. To create these, the following scripts are used (all you have to do is update the file paths). Note that the inputs are already combined for the same sample (meaning the m_yy slices are added into one file for the diphoton sample, the leptonic and hadronic ttgammagamma are added as one file, and the Zyy samples are added. This is done using the moveFile.sh scripts on the outputs of the previous steps.)

* ```makeTrexInputs.py``` creates the inputs for all nominal samples, seperated by signal and background. Single samples templates are saved for each truth flavor combination while background are one single inclusive template for each sample. 
* ```makeSysTRExInputs.py``` creates the inputs for all systematics for the signal samples.
* ```makeFakeTRExInputs.py``` and ```makeFakeTRExInputs_SingleJet.py``` create the fake templates using the data templates and subtracts the mc templates.

When finished, to create the config file for TRExFitter, you can use ```createConfig.py``` since there's a lot of repetition for each systematic. 
