cmake_minimum_required(VERSION 2.8.4)
project(SMPTS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)
file(GLOB src HEADERS *.h)
aux_source_directory(src SOURCES)

add_executable(accountsystem src/AccountSystem/main.c ${SOURCES} ${HEADERS})
add_executable(buscontrol src/BusControl/main.c ${SOURCES} ${HEADERS})
add_executable(metrocontrol src/MetroControl/main.c ${SOURCES} ${HEADERS})