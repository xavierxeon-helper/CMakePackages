set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WAMUSIC_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WAMUSIC_INCLUDE_DIRS ${WAMUSIC_CMAKE_DIR})

include_directories(${WAMUSIC_INCLUDE_DIRS})
#include(${WAMUSIC_CMAKE_DIR}/functions.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core)

if(TARGET WaMusic)
   message(STATUS "Re-using Target WaMusic")
   link_libraries(WaMusic)
else()
   # add this package to YOUR project
   add_subdirectory(${WAMUSIC_CMAKE_DIR} WaMusic)
   link_libraries(WaMusic)
endif()

link_libraries(Qt6::Core)
