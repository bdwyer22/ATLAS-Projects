################################################################################
# Package: HGamAnalysisFramework
################################################################################

# Declare the package name:
atlas_subdir( HGamAnalysisFramework )

# Set HGamCore version
hgam_version(${AnalysisBase_VERSION} HGamCore_VERSION)
add_definitions( -D__RELEASE__=${HGamCore_VERSION} )

# Temporary directory for XGBoost build results:
set( _xgboostBuildDir ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/XGBoostBuild )

# Set up the variables that the users can pick up XGBoost with:
set( XGBOOST_INCLUDE_DIRS
  $<BUILD_INTERFACE:${_xgboostBuildDir}/include>
  $<INSTALL_INTERFACE:include> )
set( XGBOOST_LIBRARIES
  ${_xgboostBuildDir}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}xgboost${CMAKE_SHARED_LIBRARY_SUFFIX}
  ${_xgboostBuildDir}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}rabit${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${_xgboostBuildDir}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}dmlc${CMAKE_STATIC_LIBRARY_SUFFIX} )

# Set up the build of XGBoost for the build area:
ExternalProject_Add( XGBoost
  PREFIX ${CMAKE_BINARY_DIR}
  INSTALL_DIR ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}
  GIT_REPOSITORY https://github.com/dmlc/xgboost.git
  GIT_TAG 78ec77f
  BUILD_IN_SOURCE 1
  BUILD_COMMAND $(MAKE)
  INSTALL_COMMAND
  ${CMAKE_COMMAND} -E make_directory ${_xgboostBuildDir} &&
  ${CMAKE_COMMAND} -E make_directory ${_xgboostBuildDir}/lib &&
  ${CMAKE_COMMAND} -E make_directory ${_xgboostBuildDir}/include &&
  ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/src/XGBoost/include/xgboost ${_xgboostBuildDir}/include/xgboost &&
  ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/src/XGBoost/rabit/include/rabit ${_xgboostBuildDir}/include/rabit &&
  ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/src/XGBoost/dmlc-core/include/dmlc ${_xgboostBuildDir}/include/dmlc &&
  ${CMAKE_COMMAND} -E copy_if_different lib/${CMAKE_SHARED_LIBRARY_PREFIX}xgboost${CMAKE_SHARED_LIBRARY_SUFFIX} ${_xgboostBuildDir}/lib &&
  ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_STATIC_LIBRARY_PREFIX}rabit${CMAKE_STATIC_LIBRARY_SUFFIX} ${_xgboostBuildDir}/lib &&
  ${CMAKE_COMMAND} -E copy_if_different dmlc-core/${CMAKE_STATIC_LIBRARY_PREFIX}dmlc${CMAKE_STATIC_LIBRARY_SUFFIX} ${_xgboostBuildDir}/lib &&
  ${CMAKE_COMMAND} -E copy_directory ${_xgboostBuildDir}/ <INSTALL_DIR>
  BUILD_BYPRODUCTS ${XGBOOST_LIBRARIES} )

# Install XGBoost
install( DIRECTORY ${_xgboostBuildDir}/
  DESTINATION . USE_SOURCE_PERMISSIONS )

# Clean up:
unset( _xgboostBuildDir )

# Declare the package's dependencies:
atlas_depends_on_subdirs( PUBLIC
                            Control/AthContainers
                            Control/AthToolSupport/AsgTools
                            Control/xAODRootAccess
                            Control/xAODRootAccessInterfaces
                            DataQuality/GoodRunsLists
                            Event/FourMomUtils
                            Event/xAOD/xAODBase
                            Event/xAOD/xAODEgamma
                            Event/xAOD/xAODEventInfo
                            Event/xAOD/xAODJet
                            Event/xAOD/xAODTau
                            Event/xAOD/xAODMetaDataCnv
                            Event/xAOD/xAODMissingET
                            Event/xAOD/xAODMuon
                            Event/xAOD/xAODTracking
                            Event/xAOD/xAODTruth
                            Event/xAOD/xAODTruthCnv
                            InnerDetector/InDetRecTools/InDetTrackSelectionTool
			    PhysicsAnalysis/AnalysisCommon/AssociationUtils
                            PhysicsAnalysis/AnalysisCommon/PATInterfaces
                            PhysicsAnalysis/D3PDTools/EventLoop
                            PhysicsAnalysis/ElectronPhotonID/ElectronEfficiencyCorrection
                            PhysicsAnalysis/ElectronPhotonID/ElectronPhotonFourMomentumCorrection
                            PhysicsAnalysis/ElectronPhotonID/ElectronPhotonSelectorTools
                            PhysicsAnalysis/ElectronPhotonID/PhotonEfficiencyCorrection
                            PhysicsAnalysis/ElectronPhotonID/PhotonVertexSelection
                            PhysicsAnalysis/Interfaces/AsgAnalysisInterfaces
                            PhysicsAnalysis/Interfaces/EgammaAnalysisInterfaces
                            PhysicsAnalysis/Interfaces/FTagAnalysisInterfaces
                            PhysicsAnalysis/Interfaces/TriggerAnalysisInterfaces
                            PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonEfficiencyCorrections
                            PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonMomentumCorrections
                            PhysicsAnalysis/MuonID/MuonSelectorTools
                            PhysicsAnalysis/TruthWeightTools
                            PhysicsAnalysis/TauID/TauAnalysisTools
                            Reconstruction/Jet/JetCPInterfaces
                            Reconstruction/Jet/JetCalibTools
                            Reconstruction/Jet/JetInterface
                            Reconstruction/Jet/JetJvtEfficiency
                            Reconstruction/Jet/JetResolution
                            Reconstruction/MET/METInterface
                            Reconstruction/MET/METUtilities
                            Reconstruction/RecoTools/IsolationTool
                            Tools/PathResolver
                            Trigger/TrigAnalysis/TrigAnalysisInterfaces
                            Trigger/TrigAnalysis/TrigDecisionTool
                            Trigger/TrigAnalysis/TriggerMatchingTool
                            Trigger/TrigConfiguration/TrigConfxAOD
                          PRIVATE
                            AsgExternal/Asg_MCUtils
                            Event/xAOD/xAODMetaData
                            PhysicsAnalysis/AnalysisCommon/IsolationSelection
                            PhysicsAnalysis/AnalysisCommon/VertexPositionReweighting
                            PhysicsAnalysis/D3PDTools/EventLoopAlgs
                            PhysicsAnalysis/D3PDTools/EventLoopGrid
                            PhysicsAnalysis/D3PDTools/SampleHandler
                            PhysicsAnalysis/ElectronPhotonID/ElectronPhotonShowerShapeFudgeTool
                            PhysicsAnalysis/JetTagging/JetTagPerformanceCalibration/xAODBTaggingEfficiency
                            PhysicsAnalysis/MCTruthClassifier
                            Reconstruction/Jet/JetRec
                            Reconstruction/Jet/JetReclustering
                            Reconstruction/egamma/egammaLayerRecalibTool
                            Reconstruction/egamma/egammaMVACalib
                            Trigger/TrigAnalysis/TrigBunchCrossingTool
                            Reconstruction/MVAUtils
                          )


# Find the needed external(s):
find_package( ROOT COMPONENTS Core RIO Hist Tree )
find_package( lwtnn )

# build a CINT dictionary for the library
atlas_add_root_dictionary ( HGamAnalysisFrameworkLib HGamAnalysisFrameworkCintDict
                            ROOT_HEADERS HGamAnalysisFramework/HgammaAnalysis.h HGamAnalysisFramework/Config.h Root/LinkDef.h
                            EXTERNAL_PACKAGES ROOT
)

# build a shared library
atlas_add_library( HGamAnalysisFrameworkLib
                   HGamAnalysisFramework/*.h Root/*.cxx ${HGamAnalysisFrameworkCintDict}
                   PUBLIC_HEADERS HGamAnalysisFramework
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${XGBOOST_INCLUDE_DIRS} ${LWTNN_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES} ${XGBOOST_LIBRARIES} ${LWTNN_LIBRARIES}
                      AsgTools
		      AssociationUtilsLib
                      ElectronEfficiencyCorrectionLib
                      ElectronPhotonFourMomentumCorrectionLib
                      ElectronPhotonSelectorToolsLib
                      EventLoop
                      FTagAnalysisInterfacesLib
                      GoodRunsListsLib
                      InDetTrackSelectionToolLib
                      IsolationToolLib
                      JetCPInterfaces
                      JetCalibToolsLib
                      JetJvtEfficiencyLib
                      JetResolutionLib
                      METUtilitiesLib
                      MuonEfficiencyCorrectionsLib
                      MuonMomentumCorrectionsLib
                      MuonSelectorToolsLib
                      TauAnalysisToolsLib
                      PATInterfaces
                      PathResolver
                      PhotonEfficiencyCorrectionLib
                      PhotonVertexSelectionLib
                      TrigConfxAODLib
                      TrigDecisionToolLib
                      TriggerMatchingToolLib
                      xAODBase
                      xAODEgamma
                      xAODEventInfo
                      xAODTau
                      xAODJet
                      xAODMetaDataCnv
                      xAODTruthCnvLib
                      xAODMissingET
                      xAODMuon
                      xAODRootAccess
                      xAODTracking
                      xAODTruth
		      KinematicFitToolLib
                   PRIVATE_LINK_LIBRARIES
                      gomp
                      ElectronPhotonShowerShapeFudgeToolLib
                      EventLoopGrid
                      IsolationSelectionLib
                      JetRecLib
                      MCTruthClassifierLib
                      SampleHandler
                      TrigBunchCrossingTool
                      VertexPositionReweighting
                      egammaLayerRecalibTool
                      egammaMVACalibLib
                      hhTruthWeightToolsLib
                      xAODBTaggingEfficiencyLib
                      xAODMetaData
                      TruthWeightToolsLib
                      MVAUtils
		      BJetCalibrationToolLib
                  )

add_dependencies( HGamAnalysisFrameworkLib XGBoost )

# Install files from the package:
atlas_install_data( data/* )

# Install scripts from the package:
atlas_install_scripts( scripts/*.sh scripts/*.py scripts/make_hgam_pkg scripts/add_hgam_alg_to_pkg scripts/skimAndSlimToMerge )


