cmake_minimum_required(VERSION 3.20)
project(WaToolsAudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include(../CommonBuild.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core)
set(CMAKE_AUTOMOC ON)

find_package(WaTools REQUIRED COMPONENTS General)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_os_files("src")

qt_add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)
