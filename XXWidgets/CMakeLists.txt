cmake_minimum_required(VERSION 3.20)
project(XXWidgets LANGUAGES CXX)

include(../CommonBuild.cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml QuickWidgets)
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

add_os_files(src_os)

qt_add_library(${PROJECT_NAME} ${XX_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})
add_compile_definitions(EXTENSION_XXWIDGETS)


if(LINUX)
   if("aarch64" STREQUAL ${CMAKE_SYSTEM_PROCESSOR})
      message(STATUS "SKIPPING XX QML")
   else()
      add_qml_module_dir(Gui NAME XXQt)
   endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Xml Qt6::QuickWidgets)


if(APPLE)
   link_libraries("-framework Foundation" 
      "-framework StoreKit"
   )
endif()
