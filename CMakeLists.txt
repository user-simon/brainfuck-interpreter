# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)
set (CMAKE_CXX_STANDARD 20)

project ("torx")

# Include sub-projects.
add_subdirectory ("src")
