# The name of the package:
atlas_subdir (MultiJetHTTAnalysis)

# Add the shared library:
atlas_add_library (MultiJetHTTAnalysisLib
  MultiJetHTTAnalysis/*.h Root/*.cxx
  PUBLIC_HEADERS MultiJetHTTAnalysis
  LINK_LIBRARIES AnaAlgorithmLib xAODEventInfo xAODJet xAODTracking JetCalibTools xAODCore)# TrkTrack TrkParameters)

atlas_add_component (MultiJetHTTAnalysis
src/components/*.cxx
LINK_LIBRARIES MultiJetHTTAnalysisLib)

# Install files from the package:
atlas_install_joboptions( share/*_jobOptions.py )
atlas_install_scripts( share/*_eljob.py )