# IBMGraphBLAS, IBM, (c) 2018, All Rights Reserved.
# https://github.ibm.com/scalable-systems/ibm-graphblas   See LICENSE for license.
#
# CMakeLists.txt: instructions for cmake to build IBMGraphBLAS.
#
# If necessary, to change your compiler, for example:
#
#   CC=icc cmake ..
#   CC=xlc cmake ..
#   CC=gcc cmake ..
#
# To remove all compiled files and libraries (except installed ones):
#
#   cd build
#   rm -rf *

# cmake 3.0 is required.
cmake_minimum_required ( VERSION 3.0.0 )

set(PROJECT_NAME_STR ibmgraphblas)

project ( ${PROJECT_NAME_STR} C CXX)

if ( CMAKE_VERSION VERSION_GREATER "3.0" )
    cmake_policy ( SET CMP0042 NEW )
endif ( )

if (NOT CMAKE_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE Release )
endif ( )

# For development only:
set ( CMAKE_BUILD_TYPE Debug )

set ( CMAKE_INCLUDE_CURRENT_DIR ON )

# include directories for both ibmgraphblas, ibmgraphblasdemo, and ibmgraphblasalgo libraries
include_directories ( include Algo/Include)

# check which compiler is being used.  If you need to make
# compiler-specific modifications, here is the place to do it.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#    set (CMAKE_C_FLAGS  "-lm -pedantic-errors")
    set (CMAKE_CXX_FLAGS  "-fno-elide-constructors -fdump-tree-original -Wall -pedantic-errors -std=c++11")
    set (CMAKE_CXX_FLAGS_DEBUG "-g -O2")
    set (CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    if (CMAKE_C_COMPILER_VERSION VERSION_LESS 4.9)
        message (FATAL_ERROR "gcc version must be at least 4.9")
    endif ( )
#elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
#    # options for icc: also needs -std=c11
#    set (CMAKE_C_FLAGS  "-std=c11")
#    if (CMAKE_C_COMPILER_VERSION VERSION_LESS 18.0)
#        message (FATAL_ERROR "icc version must be at least 18.0")
#    endif ( )
#elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
#    # options for clang
#    if (CMAKE_C_COMPILER_VERSION VERSION_LESS 3.3)
#        message (FATAL_ERROR "clang version must be at least 3.3")
#    endif ( )
#elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
#    # options for MicroSoft Visual Studio
endif ( )

# create the ibmgraphblas library.  Requires ANSI C11++
file ( GLOB PLUGGRAPHBLAS_SOURCES "src/*.cc" )
add_library ( ibmgraphblas SHARED ${PLUGGRAPHBLAS_SOURCES} )
SET_TARGET_PROPERTIES ( ibmgraphblas PROPERTIES VERSION 0.0.1
    SOVERSION 1
    CXX_STANDARD_REQUIRED ON
    PUBLIC_HEADER "include/GraphBLAS.h" )
set_property ( TARGET ibmgraphblas PROPERTY CXX_STANDARD 11 )

# ibmgraphblas installation location
install ( TARGETS ibmgraphblas
    LIBRARY       DESTINATION /usr/local/lib
    ARCHIVE       DESTINATION /usr/local/lib
    PUBLIC_HEADER DESTINATION /usr/local/include )

# Demo library
#file ( GLOB DEMO_SOURCES "Demo/Source/*.c" )
#add_library ( ibmgraphblasdemo SHARED ${DEMO_SOURCES} )
#SET_TARGET_PROPERTIES ( ibmgraphblasdemo PROPERTIES
#    C_STANDARD_REQUIRED 11 )
#set_property ( TARGET graphblasdemo PROPERTY C_STANDARD 11 )

#target_link_libraries ( ibmgraphblasdemo  ibmgraphblas )

# Demo programs
#add_executable ( bfs_demo      "Demo/Program/bfs_demo.c" )
#add_executable ( tri_demo      "Demo/Program/tri_demo.c" )
#add_executable ( mis_demo      "Demo/Program/mis_demo.c" )
#add_executable ( complex_demo  "Demo/Program/complex_demo.c" )
#add_executable ( simple_demo   "Demo/Program/simple_demo.c" )
#add_executable ( wildtype_demo "Demo/Program/wildtype_demo.c" )

# Libraries required for Demo programs
#target_link_libraries ( bfs_demo      ibmgraphblas ibmgraphblasdemo )
#target_link_libraries ( tri_demo      ibmgraphblas ibmgraphblasdemo )
#target_link_libraries ( mis_demo      ibmgraphblas ibmgraphblasdemo )
#target_link_libraries ( complex_demo  ibmgraphblas ibmgraphblasdemo )
#target_link_libraries ( simple_demo   ibmgraphblasdemo )
#target_link_libraries ( wildtype_demo ibmgraphblas )

# :bh:
# Algo library
file ( GLOB ALGO_SOURCES "Algo/Source/*.c" )
add_library ( ibmgraphblasalgo SHARED ${ALGO_SOURCES} )
SET_TARGET_PROPERTIES ( ibmgraphblasalgo PROPERTIES
    C_STANDARD_REQUIRED ON )
set_property ( TARGET ibmgraphblasalgo PROPERTY C_STANDARD 11 )

target_link_libraries ( ibmgraphblasalgo  ibmgraphblas )

# Algo programs
add_executable ( algo_sssp_dist_main      "Algo/Program/algo_sssp_dist_main.c" )
add_executable ( algo_sssp_path_main      "Algo/Program/algo_sssp_path_main.c" )

# Libraries required for Algo programs
target_link_libraries ( algo_sssp_dist_main ibmgraphblas ibmgraphblasalgo )
target_link_libraries ( algo_sssp_path_main ibmgraphblas ibmgraphblasalgo )
# :bh:

#-------------------
# Test
#-------------------

find_package(Threads REQUIRED)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/gtest)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/src/*.cc)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)

target_link_libraries(${PROJECT_TEST_NAME}
    ${GTEST_LIBS_DIR}/libgtest.a
    ${GTEST_LIBS_DIR}/libgtest_main.a
    ibmgraphblas
    ${CMAKE_THREAD_LIBS_INIT}
    )
    
add_test(test1 ${PROJECT_TEST_NAME})
