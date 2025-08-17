set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compute paths
get_filename_component(WATOOLS_GENRAL_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATOOLS_GENRAL_INCLUDE_DIRS ${WATOOLS_GENRAL_CMAKE_DIR})

include_directories(${WATOOLS_GENRAL_INCLUDE_DIRS})
message(STATUS "WaToolsGeneral include directories: ${WATOOLS_GENRAL_INCLUDE_DIRS}")


find_package(Qt6 REQUIRED COMPONENTS Core)

include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

link_libraries(Qt6::Core WaToolsGeneral)