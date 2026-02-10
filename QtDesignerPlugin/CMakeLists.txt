cmake_minimum_required(VERSION 3.16)
project(WaToolsQtDesigner LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
   message(STATUS "SKIP ${PROJECT_NAME}: only build in release mode")
   return()
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Designer Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(NOT QT6_INSTALL_PREFIX)
   message(STATUS "SKIP ${PROJECT_NAME}: QT6_INSTALL_PREFIX not defined")
   return()
endif()

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Gui)

file(GLOB SOURCE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Gui/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Gui/*.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Gui/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Interface/*.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Interface/*.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Interface/*.cpp
)
qt_add_plugin(${PROJECT_NAME} ${SOURCE_FILES})

file(GLOB XML_FILES
   RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
   ${CMAKE_CURRENT_SOURCE_DIR}/xml/*.xml
)

qt_add_resources(${PROJECT_NAME} XML
    PREFIX "/"
    FILES ${XML_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

set(PCH_FILE ${CMAKE_CURRENT_SOURCE_DIR}/WaToolsQtDesigner.precompiled.h)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${PCH_FILE})
target_sources(${PROJECT_NAME} PRIVATE ${PCH_FILE})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Gui Qt6::Designer Qt6::Widgets)

# install
set(DESIGNER_PLUGIN_DIR "${QT6_INSTALL_PREFIX}/${QT6_INSTALL_PLUGINS}/designer")
message(STATUS "install ${PROJECT_NAME} to ${DESIGNER_PLUGIN_DIR}")

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${DESIGNER_PLUGIN_DIR}"
    BUNDLE DESTINATION "${DESIGNER_PLUGIN_DIR}"
    LIBRARY DESTINATION "${DESIGNER_PLUGIN_DIR}"
)
