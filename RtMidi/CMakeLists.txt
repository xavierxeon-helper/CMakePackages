cmake_minimum_required(VERSION 3.20)
project(RtMidi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
   set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
else()
   set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib_debug)
endif()

message(STATUS "${PROJECT_NAME} CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

if(APPLE)
   add_compile_definitions(__MACOSX_CORE__)
elseif(WIN32)
   add_compile_definitions(__WINDOWS_MM__)
elseif(UNIX)
   add_compile_definitions(__UNIX_JACK__)
endif()


