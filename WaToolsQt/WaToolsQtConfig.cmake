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
find_package(WaToolsLog REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

link_libraries(Qt6::Widgets Qt6::Xml Qt6::QuickWidgets WaToolsQt)

if(APPLE)
   link_libraries("-framework Foundation" "-framework StoreKit")
endif()
