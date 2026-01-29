include_directories(${CMAKE_CURRENT_LIST_DIR})
include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml)
find_package(WaTools REQUIRED COMPONENTS Cpp Core Log)

link_libraries(Qt6::Widgets Qt6::Xml WaToolsApplication)

