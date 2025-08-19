cmake_minimum_required(VERSION 3.20)
project(WaToolsQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include(../CommonBuild.cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml QuickWidgets)
set(CMAKE_AUTOMOC ON)

#QML -> will be statically linked into this library
file(GLOB QML_FILES
   RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
   ${CMAKE_CURRENT_SOURCE_DIR}/Gui/*.qml
   ${CMAKE_CURRENT_SOURCE_DIR}/Gui/*.js
)

message(STATUS "QML_FILES for ${PROJECT_NAME} found @ Gui = ${QML_FILES}")

#see https://doc.qt.io/qt-6/qt-add-qml-module.html
qt_add_qml_module(${PROJECT_NAME}_QML
    URI "WaToolsQt"
    STATIC
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES ${QML_FILES}
)
# C++
find_package(WaTools REQUIRED COMPONENTS Log)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_os_files("src")

qt_add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
add_compile_definitions(EXTENSION_WATOOLSQT)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Xml Qt6::QuickWidgets WaToolsQt_QMLplugin)
