include_directories(${CMAKE_CURRENT_LIST_DIR})
include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core Network NetworkAuth)
link_libraries(Qt6::Core Qt6::Network Qt6::NetworkAuth XXNetwork)
