include_directories(${CMAKE_CURRENT_LIST_DIR})
include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core)
link_libraries(Qt6::Core WaToolsGraph)

