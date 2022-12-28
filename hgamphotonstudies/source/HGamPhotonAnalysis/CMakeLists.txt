# The name of the package:
atlas_subdir (HGamPhotonAnalysis)

set( extra_deps )
if( NOT XAOD_STANDALONE )
   set( extra_deps PRIVATE Event/EventPrimitives )
endif()

atlas_depends_on_subdirs( PUBLIC
                          Event/xAOD/xAODEventInfo
                          Event/xAOD/xAODTrigger
                          Event/xAOD/xAODTruth
                          Event/xAOD/xAODTracking
                          Event/xAOD/xAODJet
                          Event/xAOD/xAODEgamma
                          PhysicsAnalysis/ElectronPhotonID/ElectronPhotonSelectorTools
                          Tracking/TrkEvent/TrkTrack
                          Tracking/TrkEvent/TrkTrackSummary
			                    PhysicsAnalysis/D3PDTools/EventLoop
                          ${extra_deps}
)

find_package( Eigen )
find_package( ROOT COMPONENTS Core RIO Hist Tree )

# Component(s) in the package:
atlas_add_root_dictionary(HGamPhotonAnalysisLib HGamPhotonAnalysisDictSource
                          ROOT_HEADERS HGamPhotonAnalysis/*.h Root/LinkDef.h
                          EXTERNAL_PACKAGES ROOT )

# add the library itself:
atlas_add_library (HGamPhotonAnalysisLib
                   HGamPhotonAnalysis/*.h HGamPhotonAnalysis/*.ihh Root/*.h Root/*.cxx ${HGamPhotonAnalysisDictSource}
                   PUBLIC_HEADERS HGamPhotonAnalysis
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES} ${EIGEN_LIBRARIES} EventLoop EventLoopGrid EventLoopAlgs 
                   xAODTracking xAODTruth xAODJet
                   xAODEventInfo xAODTrigger)# The name of the package:


atlas_add_executable (AnalysisHGam_RunLocal util/AnalysisHGam_RunLocal.cxx LINK_LIBRARIES HGamPhotonAnalysisLib)
#atlas_add_executable (AnalysisHGam_PyRun util/PhotonStudies_run.py LINK_LIBRARIES HGamPhotonAnalysisLib)
#atlas_install_joboptions( util/*_jobOptions.py )
atlas_install_scripts( util/*_run.py )