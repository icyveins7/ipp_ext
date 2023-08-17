cmake_minimum_required(VERSION 3.20)

project(ipp_ext_catch2_tests)

# # Set C++ standard
# set(CMAKE_CXX_STANDARD 11)

# Check for user-specified CMAKE_PREFIX_PATH, otherwise generate it from VCPKG_DIR environment variable
if (NOT DEFINED CMAKE_PREFIX_PATH)
    message("CMAKE_PREFIX_PATH not defined. Searching for env var VCPKG_DIR..")
    if (DEFINED ENV{VCPKG_DIR})
        message("VCPKG_DIR is " $ENV{VCPKG_DIR})
        # Set CMAKE_PREFIX_PATH to the VCPKG_DIR
        if (WIN32)
            if ((CMAKE_SIZEOF_VOID_P GREATER 4))
                set(CMAKE_PREFIX_PATH $ENV{VCPKG_DIR}\\installed\\x64-windows\\share) # This is the place to find the packages usually
            else()
                set(CMAKE_PREFIX_PATH $ENV{VCPKG_DIR}\\installed\\x86-windows\\share)
            endif()
        endif()
        message("CMAKE_PREFIX_PATH is " ${CMAKE_PREFIX_PATH})
    else()
        message("VCPKG_DIR not found.")
    endif()
else()
    message("CMAKE_PREFIX_PATH specified by user: " ${CMAKE_PREFIX_PATH})
endif()

# Add Catch2 library
find_package(Catch2 3 REQUIRED)
include_directories(${Catch2_INCLUDE_DIRS})

 # Do this to include all the IPP paths for headers, assumed to be done by the normal vars.bat provided by oneAPI
include_directories($ENV{INCLUDE} $ENV{CPATH} ${CMAKE_CURRENT_SOURCE_DIR}/../include/)
# On linux it's CPATH, on win it's INCLUDE

# Define the library paths for IPP
if (WIN32)
    message("Finding IPP libraries for Windows...")
    find_library(ippcorelib NAMES ippcore ENV LIBRARY_PATH)
    find_library(ippslib NAMES ipps ENV LIBRARY_PATH) # Did i actually need HINTS here too?
    message("Libpath: " ${ippcorelib})
    message("Libpath: " ${ippslib})
else ()
    message("Finding IPP libraries for Linux...")
    find_library(ippcorelib NAMES libippcore ippcore HINTS ENV LD_LIBRARY_PATH)
    find_library(ippslib NAMES libipps ipps HINTS ENV LD_LIBRARY_PATH)
    message("Libpath: " ${ippcorelib})
    message("Libpath: " ${ippslib})
endif()

# Define test executable for vectors
add_executable(test_vecs test_vectors.cpp test_vectors_encapsulation.cpp)
target_link_libraries(test_vecs PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

# Define test executable for dfts
add_executable(test_dfts test_dft.cpp)
target_link_libraries(test_dfts PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

# Define test executable for filters
add_executable(test_filters test_filters.cpp)
target_link_libraries(test_filters PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

# Define test executable for matrices
add_executable(test_matrices test_matrices.cpp)
target_link_libraries(test_matrices PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

# Define test executable for math
add_executable(test_math test_math.cpp)
target_link_libraries(test_math PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

# Define test executable for random
add_executable(test_random test_random.cpp)
target_link_libraries(test_random PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

# Define test executable for random
add_executable(test_generators test_generators.cpp)
target_link_libraries(test_generators PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

# Define test executable for random
add_executable(test_convert test_convert.cpp)
target_link_libraries(test_convert PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(test_vecs)
catch_discover_tests(test_dfts)
catch_discover_tests(test_filters)
catch_discover_tests(test_matrices)
catch_discover_tests(test_math)
catch_discover_tests(test_random)
catch_discover_tests(test_generators)
catch_discover_tests(test_convert)