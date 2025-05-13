cmake_minimum_required(VERSION 3.20)

project(ipp_ext_examples)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64") # Need this to work with intel stuff for m1/m2
    message("CMAKE_OSX_ARCHITECTURES is " ${CMAKE_OSX_ARCHITECTURES})
endif()

# Do this to include all the IPP paths for headers, assumed to be done by the normal vars.bat provided by oneAPI
include_directories($ENV{INCLUDE} $ENV{CPATH} ${CMAKE_CURRENT_SOURCE_DIR}/../include/)
# On linux it's CPATH, on win it's INCLUDE

# Define the library paths for IPP
if (WIN32)
    message("Finding IPP libraries for Windows...")
    find_library(ippcorelib NAMES ippcore ENV LIBRARY_PATH)
    find_library(ippslib NAMES ipps ENV LIBRARY_PATH) # Did i actually need HINTS here too?
    find_library(ippilib NAMES ippi ENV LIBRARY_PATH)
    message("Libpath: " ${ippcorelib})
    message("Libpath: " ${ippslib})
    message("Libpath: " ${ippilib})
elseif (APPLE)
    message("Finding IPP libraries for MacOS...")
    find_library(ippcorelib NAMES libippcore.a HINTS ENV DYLD_LIBRARY_PATH) # on mac it seems like it's here, even though it's linux based
    find_library(ippslib NAMES libipps.a HINTS ENV DYLD_LIBRARY_PATH)
    find_library(ippvmlib NAMES libippvm.a HINTS ENV DYLD_LIBRARY_PATH)
    find_library(ippilib NAMES ippi HINTS ENV DYLD_LIBRARY_PATH)
    message("Libpath: " ${ippcorelib})
    message("Libpath: " ${ippslib})
    message("Libpath: " ${ippvmlib})
    message("Libpath: " ${ippilib})
else ()
    message("Finding IPP libraries for Linux...")
    find_library(ippcorelib NAMES libippcore ippcore HINTS ENV LD_LIBRARY_PATH)
    find_library(ippslib NAMES libipps ipps HINTS ENV LD_LIBRARY_PATH)
    find_library(ippilib NAMES ippi HINTS ENV LIBRARY_PATH)
    message("Libpath: " ${ippcorelib})
    message("Libpath: " ${ippslib})
    message("Libpath: " ${ippilib})
endif()

### Define the executables
###########################################################
add_executable(vector_example vector_example.cpp)
target_link_libraries(vector_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib})

###########################################################
add_executable(filter_example filter_example.cpp)
target_link_libraries(filter_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib})

###########################################################
add_executable(dft_example dft_example.cpp)
target_link_libraries(dft_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib})

###########################################################
add_executable(matrix_example matrix_example.cpp)
target_link_libraries(matrix_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib})

###########################################################
add_executable(sample_updown_example sample_updown_example.cpp)
target_link_libraries(sample_updown_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib})

###########################################################
add_executable(heap_overflow_example heap_overflow_example.cpp)
target_link_libraries(heap_overflow_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib})
target_compile_options(heap_overflow_example PUBLIC -fsanitize=address)
target_link_options(heap_overflow_example PUBLIC -fsanitize=address)

###########################################################
add_executable(image_example image_example.cpp)
target_link_libraries(image_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib} ${ippilib})
target_compile_options(image_example PUBLIC -fsanitize=address)
target_link_options(image_example PUBLIC -fsanitize=address)

###########################################################
add_executable(image_dft_example image_dft_example.cpp)
target_link_libraries(image_dft_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib} ${ippilib})

###########################################################
add_executable(heap_overflow_image_example heap_overflow_image_example.cpp)
target_link_libraries(heap_overflow_image_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib} ${ippilib})
target_compile_options(heap_overflow_image_example PUBLIC -fsanitize=address)
target_link_options(heap_overflow_image_example PUBLIC -fsanitize=address)

###########################################################
add_executable(remap_example remap_example.cpp)
target_link_libraries(remap_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib} ${ippilib})

###########################################################
add_executable(image_filtermedian_example image_filtermedian_example.cpp)
target_link_libraries(image_filtermedian_example PUBLIC ${ippcorelib} ${ippslib} ${ippvmlib} ${ippilib})
