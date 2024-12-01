# Compute paths
get_filename_component(WAMATH_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WAMATHS_INCLUDE_DIRS ${WAMATH_CMAKE_DIR})

include_directories(${WAMATHS_INCLUDE_DIRS})

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()