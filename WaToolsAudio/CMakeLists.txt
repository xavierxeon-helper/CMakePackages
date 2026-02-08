cmake_minimum_required(VERSION 3.20)
project(WaToolsAudio LANGUAGES CXX)

if(LINUX AND "aarch64" STREQUAL ${CMAKE_SYSTEM_PROCESSOR})
   message(STATUS "SKIPPING ${PROJECT_NAME} on ARM64 Linux")
   return()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include(../CommonBuild.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core)
set(CMAKE_AUTOMOC ON)

find_package(WaTools REQUIRED COMPONENTS Core Math)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB HEADER_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(GLOB_RECURSE SOURCE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

qt_add_library(${PROJECT_NAME} ${WATOOLS_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})
add_compile_definitions(EXTENSION_WATOOLSAUDIO)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)
