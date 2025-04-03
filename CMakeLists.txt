cmake_minimum_required(VERSION 3.20)

project(ipp_ext)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

if (UNIX)
  add_compile_options(-fdiagnostics-color -Wall)
endif()

# Add the separate parts
add_subdirectory(benchmarks)
add_subdirectory(examples)
add_subdirectory(tests)
