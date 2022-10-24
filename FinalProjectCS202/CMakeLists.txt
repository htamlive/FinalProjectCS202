# CMakeList.txt : CMake project for FinalProjectCS202, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (FinalProjectCS202 "FinalProjectCS202.cpp" "FinalProjectCS202.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FinalProjectCS202 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
