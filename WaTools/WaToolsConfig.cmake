set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WATOOLS_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

include(${WATOOLS_CMAKE_DIR}/functions_compile.cmake)
include(${WATOOLS_CMAKE_DIR}/functions_target.cmake)
include(${WATOOLS_CMAKE_DIR}/functions_git.cmake)

foreach(COMPONENT ${WaTools_FIND_COMPONENTS})
   #message(STATUS "NEED WaTools component: ${COMPONENT}")
   find_package(WaTools${COMPONENT} REQUIRED)
endforeach()