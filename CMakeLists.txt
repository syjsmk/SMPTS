cmake_minimum_required(VERSION 2.8.4)
project(SMPTS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    AccountSystem/.idea/scopes/scope_settings.xml
    AccountSystem/.idea/.name
    AccountSystem/.idea/AccountSystem.iml
    AccountSystem/.idea/encodings.xml
    AccountSystem/.idea/misc.xml
    AccountSystem/.idea/modules.xml
    AccountSystem/.idea/vcs.xml
    AccountSystem/.idea/workspace.xml
    CommonImplement/TerminalInterface/TerminalInterface.c
    CommonImplement/TerminalInterface/TerminalInterface.h
    AccountSystem/AccountSystem.c
    AccountSystem/AccountSystem.h
    AccountSystem/CMakeLists.txt
    CommonImplement/CommunicationDefinition.h
    CommonImplement/DailyAccountInformation.h
    AccountSystem/main.c
    AccountSystem/main.exe
    AccountSystem/Makefile
    CommonImplement/PrecompiledHeader.h
    BusControl/.idea/scopes/scope_settings.xml
    BusControl/.idea/.name
    BusControl/.idea/BusControl.iml
    BusControl/.idea/encodings.xml
    BusControl/.idea/misc.xml
    BusControl/.idea/modules.xml
    BusControl/.idea/vcs.xml
    BusControl/.idea/workspace.xml
    BusControl/CMakeLists.txt
    BusControl/main.c
    BusControl/Makefile
    .gitignore
    REAMDE)

add_executable(SMPTS ${SOURCE_FILES})