# Compute paths
get_filename_component(WALOG_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WALOG_INCLUDE_DIRS ${WALOG_CMAKE_DIR})

include_directories(${WALOG_INCLUDE_DIRS})

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()