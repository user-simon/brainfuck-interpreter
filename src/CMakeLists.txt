# CMakeList.txt : CMake project for torx, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

# Add source to this project's executable.

file(GLOB_RECURSE torx_src CONFIGURE_DEPENDS "*.h" "*.cpp")

add_executable (torx ${torx_src})
target_include_directories(torx PRIVATE ".")
source_group(TREE "." FILES ${torx_src})
