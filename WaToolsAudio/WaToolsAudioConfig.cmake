set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WATOOLS_AUDIO_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATOOLS_AUDIO_INCLUDE_DIRS ${WATOOLS_AUDIO_CMAKE_DIR})

include_directories(${WATOOLS_AUDIO_INCLUDE_DIRS})
#include(${WATOOLS_AUDIO_CMAKE_DIR}/functions.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core)

if(TARGET WaToolsAudio)
   message(STATUS "Re-using Target WaToolsAudio")
   link_libraries(WaToolsAudio)
else()
   # add this package to YOUR project
   add_subdirectory(${WATOOLS_AUDIO_CMAKE_DIR} WaToolsAudio)
   link_libraries(WaToolsAudio)
endif()

link_libraries(Qt6::Core)
