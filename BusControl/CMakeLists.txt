cmake_minimum_required(VERSION 2.8.4)
project(BusControl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Makefile)

add_executable(BusControl ${SOURCE_FILES})