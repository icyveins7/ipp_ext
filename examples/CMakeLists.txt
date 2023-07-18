cmake_minimum_required(VERSION 3.20)

project(ipp_ext_examples)

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

###########################################################
add_executable(filter_example filter_example.cpp)
target_link_libraries(filter_example PUBLIC ${ippcorelib} ${ippslib})

###########################################################
add_executable(dft_example dft_example.cpp)
target_link_libraries(dft_example PUBLIC ${ippcorelib} ${ippslib})

###########################################################
add_executable(matrix_example matrix_example.cpp)
target_link_libraries(matrix_example PUBLIC ${ippcorelib} ${ippslib})