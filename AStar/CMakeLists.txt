cmake_minimum_required(VERSION 2.8)
project(AStar)


#路径设置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

#编译选项设置
set(CMAKE_BUILD_TYPE Debug)
#set (CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O2 -Wall -g -ggdb")
#set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -O2 -Wall")

set(APP AStar)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SRC_DIR})

aux_source_directory(${SRC_DIR} SRC_LIST)

add_executable(${APP} ${SRC_LIST})
