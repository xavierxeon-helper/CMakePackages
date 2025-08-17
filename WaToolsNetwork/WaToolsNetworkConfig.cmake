set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WATOOLS_NETWORK_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATOOLS_NETWORK_INCLUDE_DIRS ${WATOOLS_NETWORK_CMAKE_DIR})

include_directories(${WATOOLS_NETWORK_INCLUDE_DIRS})

find_package(Qt6 REQUIRED COMPONENTS Core Network NetworkAuth)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
   link_directories(${WATOOLS_NETWORK_CMAKE_DIR}/../lib/release)
else()
   link_directories(${WATOOLS_NETWORK_CMAKE_DIR}/../lib/debug)
endif()

link_libraries(Qt6::Core Qt6::Network Qt6::NetworkAuth WaToolsNetwork)
