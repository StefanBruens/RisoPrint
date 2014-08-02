cmake_minimum_required (VERSION 2.6) 
project (risoprint) 

set (CMAKE_CXX_FLAGS "-g -O2 -std=c++11")
set (CMAKE_CXX_FLAGS_DEBUG "-g3 -O1 -std=c++11")

set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Installation directory for libraries")

add_subdirectory (lib) 
add_subdirectory (sample)

