# The name of the package:
atlas_subdir (yyHFSkim)

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
atlas_add_root_dictionary(yyHFSkimLib yyHFSkimDictSource
                          ROOT_HEADERS yyHFSkim/*.h Root/LinkDef.h
                          EXTERNAL_PACKAGES ROOT )

# add the library itself:
atlas_add_library (yyHFSkimLib
                   yyHFSkim/*.h yyHFSkim/*.ihh Root/*.h Root/*.cxx ${yyHFSkimDictSource}
                   PUBLIC_HEADERS yyHFSkim
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES} ${EIGEN_LIBRARIES} EventLoop EventLoopGrid EventLoopAlgs 
                   xAODEgamma xAODMuon xAODTruth xAODJet
                   xAODEventInfo )# The name of the package:


atlas_add_executable (yyHFSkim_RunLocal util/yyHFSkim_RunLocal.cxx LINK_LIBRARIES yyHFSkimLib)

