cmake_minimum_required(VERSION 3.20)
project(XXNetwork LANGUAGES CXX)

include(../CommonBuild.cmake)

find_package(Qt6 REQUIRED COMPONENTS Gui Network NetworkAuth)
set(CMAKE_AUTOMOC ON)

find_package(XX REQUIRED COMPONENTS Cpp Core Log)
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

qt_add_library(${PROJECT_NAME} ${XX_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})
add_compile_definitions(EXTENSION_XXNETWORK)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Gui Qt6::Network Qt6::NetworkAuth)
