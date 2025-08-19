cmake_minimum_required(VERSION 3.20)
project(RtMidi LANGUAGES CXX)

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
add_compile_definitions(RTMIDI_EXPORT)

if(APPLE)
   add_compile_definitions(__MACOSX_CORE__)
elseif(WIN32)
   add_compile_definitions(__WINDOWS_MM__)
elseif(UNIX)
   add_compile_definitions(__UNIX_JACK__)
endif()


