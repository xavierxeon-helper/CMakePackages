cmake_minimum_required(VERSION 3.20)
project(XX LANGUAGES CXX)

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE)

find_package(Qt6 REQUIRED COMPONENTS Core)
include(XX/functions_qt.cmake)
set_qt_arch()

set(VERSION_FILE ${CMAKE_CURRENT_LIST_DIR}/lib/${QT_ARCH}/versions.txt)
file(WRITE ${VERSION_FILE} "CMake ${CMAKE_VERSION}\n")
file(APPEND ${VERSION_FILE} "Qt6 ${Qt6_VERSION}\n")

set(MODULE_FILE ${CMAKE_CURRENT_LIST_DIR}/lib/${QT_ARCH}/modules.txt)
string(TIMESTAMP MODULE_TIMESTAMP "%Y-%m-%d %H:%M:%S")
file(WRITE ${MODULE_FILE} "${MODULE_TIMESTAMP}\n")

file(GLOB SUB_DIRECTORIES 
   LIST_DIRECTORIES true 
   RELATIVE ${CMAKE_CURRENT_LIST_DIR}/
   "${CMAKE_CURRENT_LIST_DIR}/*"
)

foreach(SUB_DIR ${SUB_DIRECTORIES})
   if(NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUB_DIR})
      continue()
   endif()

   if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${SUB_DIR}/CMakeLists.txt)
      file(APPEND ${MODULE_FILE} " * ${SUB_DIR}\n")
      add_subdirectory(${SUB_DIR})
   endif()
endforeach()
