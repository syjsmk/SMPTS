cmake_minimum_required(VERSION 2.8.4)
project(AccountSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(C:/cygwin64)

set(SOURCE_FILES
    AccountSystem.c
    AccountSystem.h
    main.c
    ../CommonImplement/CommunicationDefinition.h
    ../CommonImplement/DailyAccountInformation.h
    ../CommonImplement/PrecompiledHeader.h
    ../CommonImplement/NetworkInterface/NetworkInterface.c
    ../CommonImplement/NetworkInterface/NetworkInterface.h)

add_executable(main ${SOURCE_FILES})