set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WATOOLS_QT_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATOOLS_QT_INCLUDE_DIRS ${WATOOLS_QT_CMAKE_DIR})

include_directories(${WATOOLS_QT_INCLUDE_DIRS})
include(${WATOOLS_QT_CMAKE_DIR}/functions.cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml QuickWidgets)
find_package(WaTools REQUIRED COMPONENTS Log)

if(TARGET WaToolsQt)
   message(STATUS "Re-using Target WaToolsQt")
   link_libraries(WaToolsQt)
else()
   # add this package to YOUR project
   add_subdirectory(${WATOOLS_QT_CMAKE_DIR} WaToolsQt)
   link_libraries(WaToolsQt)
endif()

link_libraries(Qt6::Widgets Qt6::Xml Qt6::QuickWidgets)

if(APPLE)
   link_libraries("-framework Foundation" "-framework StoreKit")
endif()
