# The name of the package:
atlas_subdir (HGamTestAnalysis)

set( extra_deps )
if( NOT XAOD_STANDALONE )
   set( extra_deps PRIVATE Event/EventPrimitives )
endif()

atlas_depends_on_subdirs( PUBLIC
                          Event/xAOD/xAODEventInfo
                          Event/xAOD/xAODTruth
                          Event/xAOD/xAODJet
                          Event/xAOD/xAODEgamma
                          Event/xAOD/xAODMuon
			                    PhysicsAnalysis/D3PDTools/EventLoop
                          ${extra_deps}
)

find_package( Eigen )
find_package( ROOT COMPONENTS Core RIO Hist Tree )

# Component(s) in the package:
atlas_add_root_dictionary(HGamTestAnalysisLib HGamTestAnalysisDictSource
                          ROOT_HEADERS HGamTestAnalysis/*.h Root/LinkDef.h
                          EXTERNAL_PACKAGES ROOT )

# add the library itself:
atlas_add_library (HGamTestAnalysisLib
                   HGamTestAnalysis/*.h HGamTestAnalysis/*.ihh Root/*.h Root/*.cxx ${HGamTestAnalysisDictSource}
                   PUBLIC_HEADERS HGamTestAnalysis
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES} ${EIGEN_LIBRARIES} EventLoop EventLoopGrid EventLoopAlgs 
                   xAODEgamma xAODMuon xAODTruth xAODJet
                   xAODEventInfo )# The name of the package:


atlas_add_executable (AnalysisHGam_RunLocal util/AnalysisHGam_RunLocal.cxx LINK_LIBRARIES HGamTestAnalysisLib)

