include_directories(${CMAKE_CURRENT_LIST_DIR})
include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml QuickWidgets)
find_package(WaToolsLog REQUIRED)
link_libraries(Qt6::Widgets Qt6::Xml Qt6::QuickWidgets WaToolsWidgets)

if(APPLE)
   link_libraries("-framework Foundation" "-framework StoreKit")
endif()


