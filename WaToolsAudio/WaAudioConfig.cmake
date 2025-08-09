set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WAAUDIO_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WAAUDIO_INCLUDE_DIRS ${WAAUDIO_CMAKE_DIR})

include_directories(${WAAUDIO_INCLUDE_DIRS})
#include(${WAAUDIO_CMAKE_DIR}/functions.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core)

if(TARGET WaAudio)
   message(STATUS "Re-using Target WaAudio")
   link_libraries(WaAudio)
else()
   # add this package to YOUR project
   add_subdirectory(${WAAUDIO_CMAKE_DIR} WaAudio)
   link_libraries(WaAudio)
endif()

link_libraries(Qt6::Core)
