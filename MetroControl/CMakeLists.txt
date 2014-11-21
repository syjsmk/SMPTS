cmake_minimum_required(VERSION 2.8.4)
project(MetroControl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    MetroControl.c
    MetroControl.h
    main.c
    ../CommonImplement/CommunicationDefinition.h
    ../CommonImplement/DailyAccountInformation.h
    ../CommonImplement/PrecompiledHeader.h
    ../CommonImplement/NetworkInterface/NetworkInterface.c
    ../CommonImplement/NetworkInterface/NetworkInterface.h
    ../CommonImplement/FileIoInterface/FileIoInterface.c
    ../CommonImplement/FileIoInterface/FileIoInterface.h
    )

add_executable(main ${SOURCE_FILES})