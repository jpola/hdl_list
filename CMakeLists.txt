project(HDL_List)
cmake_minimum_required(VERSION 2.8)

set(libname hdllist)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic")

aux_source_directory(./src SRC_LIST)

add_library(${libname} ${SRC_LIST})

#if(BUILD_TESTS_AND_BENCHMARKS)
    add_subdirectory(tests)
#endif(BUILD_TESTS_AND_BENCHMARKS)
