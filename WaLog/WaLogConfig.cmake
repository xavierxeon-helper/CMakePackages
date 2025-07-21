set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WALOG_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WALOG_INCLUDE_DIRS ${WALOG_CMAKE_DIR})

include_directories(${WALOG_INCLUDE_DIRS})

find_package(Qt6 REQUIRED COMPONENTS Gui)

if(TARGET WaLog)
   message(STATUS "Re-using Target WaLog")
   link_libraries(WaLog)
else()
   # add this package to YOUR project
   add_subdirectory(${WALOG_CMAKE_DIR} WaLog)
   link_libraries(WaLog)
endif()

link_libraries(Qt6::Gui)
