set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WATOOLS_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATOOLS_INCLUDE_DIRS ${WATOOLS_CMAKE_DIR})

include_directories(${WATOOLS_INCLUDE_DIRS})
include(${WATOOLS_CMAKE_DIR}/functions_compile.cmake)
include(${WATOOLS_CMAKE_DIR}/functions_target.cmake)
include(${WATOOLS_CMAKE_DIR}/functions_git.cmake)
