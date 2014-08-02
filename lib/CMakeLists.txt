
add_library (risoprint SHARED
	JobFile.cc JobOptions.cc
	RisoInit.cc JobPages.cc Page.cc
	ImageLine.cc
	ImageFile.cc
	MMapFile.cc
	Job.cc
	Helper.cc
)

set(RISOPRINT_VERSION_MAJOR 0)
set(RISOPRINT_VERSION_MINOR 0)
set(RISOPRINT_VERSION_PATCH 1)
set(RISOPRINT_VERSION_STRING ${RISOPRINT_VERSION_MAJOR}.${RISOPRINT_VERSION_MINOR}.${RISOPRINT_VERSION_PATCH})

set_target_properties(risoprint PROPERTIES VERSION ${RISOPRINT_VERSION_STRING}
                                          SOVERSION ${RISOPRINT_VERSION_MAJOR})

install (TARGETS risoprint DESTINATION ${CMAKE_INSTALL_LIBDIR})
