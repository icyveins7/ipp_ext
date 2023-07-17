cmake_minimum_required(VERSION 3.20)

project(ipp_ext_examples)

# Add compile options so instruction sets are explicitly enabled
if (MSVC)
    add_compile_options(/arch:AVX2)
else()
    add_compile_options(-mavx2 -O3)
    add_compile_definitions(NDEBUG)
endif()

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

### Define the executables
###########################################################
add_executable(vector_example vector_example.cpp)
target_link_libraries(vector_example PUBLIC ${ippcorelib} ${ippslib})

if (MSVC)
    target_compile_options(vector_example PUBLIC /arch:AVX2 /EHsc)
else()
    target_compile_options(vector_example PUBLIC -mavx2 -O3)
endif()

###########################################################
add_executable(filter_example filter_example.cpp)
target_link_libraries(filter_example PUBLIC ${ippcorelib} ${ippslib})

if (MSVC)
    target_compile_options(filter_example PUBLIC /arch:AVX2 /EHsc)
else()
    target_compile_options(filter_example PUBLIC -mavx2 -O3)
endif()
