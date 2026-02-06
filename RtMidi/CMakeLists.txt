cmake_minimum_required(VERSION 3.20)
project(RtMidi LANGUAGES CXX)

if(LINUX AND "aarch64" STREQUAL ${CMAKE_SYSTEM_PROCESSOR})
   message(STATUS "SKIPPING ${PROJECT_NAME} on ARM64 Linux")
   return()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include(../CommonBuild.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
add_compile_definitions(RTMIDI_EXPORT JACK_HAS_PORT_RENAME)

if(APPLE)
   add_compile_definitions(__MACOSX_CORE__)
elseif(WIN32)
   add_compile_definitions(__WINDOWS_MM__)
elseif(UNIX)
   add_compile_definitions(__UNIX_JACK__)
endif()


