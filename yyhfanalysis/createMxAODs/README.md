# Creating MxAODs
You will use the main [HGamAnalysisFramework](https://gitlab.cern.ch/atlas-hgam-sw/HGamCore) package to create MxAODs from HIGG1D1 derivations. Currently, the analysis uses the h026 production tag of HGamCore. The main tool used is the [yyHFTool](https://gitlab.cern.ch/atlas-hgam-sw/HGamCore/-/blob/master/HGamAnalysisFramework/Root/yyHFTool.cxx), though some modifications are needed. 

To start, checkout the main HGamAnalysisFramework as detailed [here](https://hgamdocs.web.cern.ch/Installation.html).
```
mkdir source
cd source
setupATLAS
asetup AnalysisBase,21.2.162,here
git clone --recursive https://:@gitlab.cern.ch:8443/atlas-hgam-sw/HGamCore.git # Assumes Kerberos checkout
cd HGamCore
git checkout v1.10.18-h026
git submodule update --init --recursive # Get proper dependencies
cd -
```

Before compiling, replace the files in the checked out version of HGamCore with those in the createMxAODs/HGamCore directory from this package. Included in the replacement files are:
* The input DAODs and their corresponding PRW files
* Modifications to the yyHFTool to remove the requirement of being outside the Higgs mass window (as this can be required later if desired) and the b-jet container that is passed to the tool (original code uses b-jets with pt > 30 and y < 2.5)
* The GammaORTool which removes the overlap generated events to be used with V+jets, vVy+jets, and Vyy+jets (where V = Z, W, and tt)
* Updates to the HGamAnalysisFramework to remove the cap for myy (isPasses originally requires it to be within 105-160GeV, the update requires 105GeV-13TeV)
* Addition of skimming code that was introduced in h027 to reduce the number of branches saved in systematic MxAODs (also updated to include the yyHFTool branches)

The full list of modified files are as follows:
```
HGamAnalysisFramework/CMakeLists.txt
HGamAnalysisFramework/HGamAnalysisFramework/HgammaAnalysis.h
HGamAnalysisFramework/Root/HgammaAnalysis.cxx
HGamAnalysisFramework/Root/RunUtils.cxx
HGamAnalysisFramework/Root/TruthHandler.cxx
HGamAnalysisFramework/Root/yyHFTool.cxx
HGamAnalysisFramework/data/HGamRel21.config
HGamTools/HGamTools/SkimAndSlim.h
HGamTools/HGamTools/SkimAndSlim.icc
HGamTools/Root/HGamCutflowAndMxAOD.cxx
HGamTools/Root/SkimAndSlim.cxx
HGamTools/data/MxAOD.config
HGamTools/data/MxAODCommon.config
HGamTools/data/MxAODFlavorAllSys1.config
HGamTools/data/MxAODFlavorAllSys2.config
HGamTools/data/MxAODFlavorAllSys3.config
HGamTools/data/MxAODFlavorAllSys4.config
HGamTools/data/MxAODFlavorSys.config
HGamTools/data/MxAODJetSys.config
HGamTools/data/MxAODJetSys1.config
HGamTools/data/MxAODJetSys2.config
HGamTools/data/MxAODJetSys3.config
HGamTools/data/MxAODJetSys4.config
HGamTools/data/MxAODPhotonAllSys1.config
HGamTools/data/MxAODPhotonAllSys2.config
HGamTools/data/MxAODPhotonAllSys3.config
HGamTools/data/MxAODPhotonAllSys4.config
HGamTools/data/MxAODPhotonSys.config
HGamTools/data/input/data_13TeV_HIGG1D1.txt
HGamTools/data/input/mc16a_HIGG1D1.txt
HGamTools/data/input/mc16d_HIGG1D1.txt
HGamTools/data/input/mc16e_HIGG1D1.txt
HGamTools/scripts/MxAODinformations.config
HGamAnalysisFramework/data/MCSamples.config
HGamAnalysisFramework/data/PRW_mc16a_fastSim.root
HGamAnalysisFramework/data/PRW_mc16a_fullSim.root
HGamAnalysisFramework/data/PRW_mc16d_fastSim.root
HGamAnalysisFramework/data/PRW_mc16d_fullSim.root
HGamAnalysisFramework/data/PRW_mc16e_fastSim.root
HGamAnalysisFramework/data/PRW_mc16e_fullSim.root
HGamTools/scripts/submitMxAOD.sh
HGamAnalysisFramework/HGamAnalysisFramework/GammaORTool.h
HGamAnalysisFramework/Root/GammaORTool.cxx
HGamAnalysisFramework/scripts/skimAndSlimToMerge
HGamTools/data/systematicsSkim.config
HGamTools/scripts/listAllSys.sh
```

Then compile the code (which can take a few mins)
```
mkdir build
cd build
cmake ../source
make
source $AnalysisBase_PLATFORM/setup.sh
```

Once compiled, the code can either be run locally for small number of events, or on the grid for the full sample.
The nominal MxAODs use the `HGamTools/data/MxAOD.config` configuration file which is set up to include the yyHFTool but turns off other tools to reduce output file size. 

An example of how to run locally over 1000 events with the nominal config is shown using the sample shortname (as denoted in the input sample text files, e.g. [mc16a_HIGG1D1.txt](https://gitlab.cern.ch/bstamas/yyhfanalysis/-/blob/master/createMxAODs/HGamCore/HGamTools/data/input/mc16a_HIGG1D1.txt)) and one of the DAOD files that was downloaded from the grid:
```
runHGamCutflowAndMxAOD HGamTools/MxAOD.config SampleName: Sherpa2_diphoton_myy_90_175_AF2 InputFile: mc16_13TeV.364352.Sherpa_224_NNPDF30NNLO_Diphoton_myy_90_175.deriv.DAOD_HIGG1D1.e6452_a875_r9364_p4204/DAOD_HIGG1D1.21854241._000001.pool.root.1 NumEvents: 1000
```
Once that has been verified to be successful, then the full sample should be produced on the grid. An example submission script is provided [here](https://gitlab.cern.ch/bstamas/yyhfanalysis/-/blob/master/createMxAODs/Submit.sh).
