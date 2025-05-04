cmake_minimum_required(VERSION 3.20)

project(ipp_ext)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

if (UNIX)
  add_compile_options(-fdiagnostics-color -Wall)
elseif(WIN32)
  add_compile_options(/W4) # level 4 is better than Wall for MSVC, otherwise a lot of irrelevant warnings
endif()

# Add the separate parts
add_subdirectory(benchmarks)
add_subdirectory(examples)
add_subdirectory(tests)
