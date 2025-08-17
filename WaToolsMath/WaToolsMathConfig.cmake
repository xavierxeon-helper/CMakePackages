set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WAMATH_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATTOLS_MATHS_INCLUDE_DIRS ${WAMATH_CMAKE_DIR})

include_directories(${WATTOLS_MATHS_INCLUDE_DIRS})

include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

link_libraries(WaToolsMath)
