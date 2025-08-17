set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WATOOLS_AUDIO_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATOOLS_AUDIO_INCLUDE_DIRS ${WATOOLS_AUDIO_CMAKE_DIR})

include_directories(${WATOOLS_AUDIO_INCLUDE_DIRS})

find_package(Qt6 REQUIRED COMPONENTS Core)

include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

link_libraries(Qt6::Core WaToolsAudio)
