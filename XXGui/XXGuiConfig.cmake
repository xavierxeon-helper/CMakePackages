include_directories(${CMAKE_CURRENT_LIST_DIR})
include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

find_package(Qt6 REQUIRED COMPONENTS Gui Qml Quick)
link_libraries(Qt6::Gui Qt6::Qml Qt6::Quick XXGui)
