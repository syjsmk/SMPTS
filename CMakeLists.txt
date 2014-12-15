cmake_minimum_required(VERSION 2.8.4)
project(SMPTS C CXX)

find_package (Threads)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)
aux_source_directory(src SOURCES)

add_library(smpts STATIC ${SOURCES})
target_link_libraries(smpts ${CMAKE_THREAD_LIBS_INIT})
add_executable(accountsystem src/AccountSystem/main.c)
target_link_libraries(accountsystem smpts)
add_executable(buscontrol src/BusControl/main.c)
target_link_libraries(buscontrol smpts)
add_executable(metrocontrol src/MetroControl/main.c)
target_link_libraries(metrocontrol smpts)

include_directories(test test/unittest++)
aux_source_directory(test TEST_SOURCES)
aux_source_directory(test/unittest++ UNITTEST_SOURCES)
aux_source_directory(test/unittest++/Posix POSIX_UNITTEST_SOURCES)
add_executable(testandcheck ${TEST_SOURCES} ${UNITTEST_SOURCES} ${POSIX_UNITTEST_SOURCES})
target_link_libraries(testandcheck smpts)

