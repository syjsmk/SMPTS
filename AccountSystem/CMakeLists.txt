cmake_minimum_required(VERSION 2.8.4)
project(AccountSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(C:/cygwin64)

set(SOURCE_FILES
    AccountSystem.c
    AccountSystem.h
    CommunicationDefinition.h
    DailyAccountInformation.h
    main.c
    PrecompiledHeader.h
    TerminalInterface/TerminalInterface.c
    TerminalInterface/TerminalInterface.h)

add_executable(main ${SOURCE_FILES})