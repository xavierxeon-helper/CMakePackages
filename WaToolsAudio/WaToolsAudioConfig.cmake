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

if(CMAKE_BUILD_TYPE STREQUAL "Release")
   link_directories(${WATOOLS_AUDIO_CMAKE_DIR}/../lib/release)
else()
   link_directories(${WATOOLS_AUDIO_CMAKE_DIR}/../lib/debug)
endif()

link_libraries(Qt6::Core WaToolsAudio)
