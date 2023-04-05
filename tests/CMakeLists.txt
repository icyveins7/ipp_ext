cmake_minimum_required(VERSION 3.20)

project(ipp_ext_catch2_tests)

# # Set C++ standard
# set(CMAKE_CXX_STANDARD 11)

# Add Catch2 library
find_package(Catch2 3 REQUIRED)
include_directories(${Catch2_INCLUDE_DIRS})

# Define test executable
add_executable(tests test_vectors.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)