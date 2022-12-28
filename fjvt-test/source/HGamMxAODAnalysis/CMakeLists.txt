# The name of the package:
atlas_subdir (HGamMxAODAnalysis)

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
                          Tracking/TrkEvent/TrkTrack
                          Tracking/TrkEvent/TrkTrackSummary
			                    PhysicsAnalysis/D3PDTools/EventLoop
                          ${extra_deps}
)

find_package( Eigen )
find_package( ROOT COMPONENTS Core RIO Hist Tree )

# Component(s) in the package:
atlas_add_root_dictionary(HGamMxAODAnalysisLib HGamMxAODAnalysisDictSource
                          ROOT_HEADERS HGamMxAODAnalysis/*.h Root/LinkDef.h
                          EXTERNAL_PACKAGES ROOT )

# add the library itself:
atlas_add_library (HGamMxAODAnalysisLib
                   HGamMxAODAnalysis/*.h HGamMxAODAnalysis/*.ihh Root/*.h Root/*.cxx ${HGamMxAODAnalysisDictSource}
                   PUBLIC_HEADERS HGamMxAODAnalysis
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES} ${EIGEN_LIBRARIES} EventLoop EventLoopGrid EventLoopAlgs 
                   xAODTracking xAODTruth xAODJet
                   xAODEventInfo xAODTrigger)# The name of the package:


atlas_add_executable (AnalysisHGam_RunLocal util/AnalysisHGam_RunLocal.cxx LINK_LIBRARIES HGamMxAODAnalysisLib)
