cmake_minimum_required(VERSION 3.20)

project(ipp_ext_catch2_benchmarks)

# # Set C++ standard
# set(CMAKE_CXX_STANDARD 11)

# Add compile options so instruction sets are explicitly enabled
if (MSVC)
    add_compile_options(/arch:AVX2)
else()
    add_compile_options(-mavx2 -O3)
endif()

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

# Define benchmarks executable for dfts
add_executable(benchmark_dft benchmark_dft.cpp)

# We only need pthreads for unix-based OSes
if (WIN32)
    target_link_libraries(benchmark_dft PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)
else()
    target_link_libraries(benchmark_dft PUBLIC ${ippcorelib} ${ippslib} pthread Catch2::Catch2WithMain)
endif()

# We check if Eigen exists
if (DEFINED ENV{EIGEN_DIR})
    message("Found Eigen. Compiling benchmark against Eigen...")
    add_compile_definitions(EIGEN_NO_MALLOC) # Ensure run time errors if benchmark allocates memory

    include_directories($ENV{EIGEN_DIR})
    add_executable(compare_eigen compare_eigen.cpp)
    target_link_libraries(compare_eigen PUBLIC ${ippcorelib} ${ippslib} Catch2::Catch2WithMain)
endif()

include(CTest)
include(Catch)
# catch_discover_tests(benchmark_dft) # don't need to add this because we running each individually