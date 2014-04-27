include_directories (${risoprint_SOURCE_DIR}/lib)

link_directories (${risoprint_BINARY_DIR}/lib)

add_executable (risoparser risoparser.cc)
target_link_libraries (risoparser risoprint)

add_executable (risoencode risoencode.cc)
target_link_libraries (risoencode risoprint)
