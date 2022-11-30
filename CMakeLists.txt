cmake_minimum_required(VERSION 3.0.0)
project(DirChecker VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set (CMAKE_CXX_FLAGS "-std=c++17")

file(GLOB HEADERS "src/*.h")
file(GLOB SOURCES "src/*.cc")

add_executable(DirChecker main.cc ${HEADERS} ${SOURCES})