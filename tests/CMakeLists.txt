cmake_minimum_required(VERSION 3.20)

project(ipp_ext_catch2_tests)

# # Set C++ standard
# set(CMAKE_CXX_STANDARD 11)

# Add Catch2 library
find_package(Catch2 3 REQUIRED)
include_directories(${Catch2_INCLUDE_DIRS})

 # Do this to include all the IPP paths for headers, assumed to be done by the normal vars.bat provided by oneAPI
include_directories($ENV{INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

# Define the library paths for IPP
find_library(ippcorelib NAMES ippcore ENV LIBRARY_PATH)
find_library(ippslib NAMES ipps ENV LIBRARY_PATH)
message("Libpath: " ${ippcorelib})
message("Libpath: " ${ippslib})


# Define test executable for vectors
add_executable(test_vecs test_vectors.cpp)
target_link_libraries(test_vecs PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

# Define test executable for dfts
add_executable(test_dfts test_dft.cpp)
target_link_libraries(test_dfts PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(test_vecs)
catch_discover_tests(test_dfts)