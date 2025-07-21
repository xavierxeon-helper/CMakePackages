set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WAQT_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WAQT_INCLUDE_DIRS ${WAQT_CMAKE_DIR})

include_directories(${WAQT_INCLUDE_DIRS})
include(${WAQT_CMAKE_DIR}/functions.cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml)

if(TARGET WaQt)
   message(STATUS "Re-using Target WaQt")
   link_libraries(WaQt)
else()
   # add this package to YOUR project
   add_subdirectory(${WAQT_CMAKE_DIR} WaQt)
   link_libraries(WaQt)
endif()

link_libraries(Qt6::Widgets Qt6::Xml)

if(APPLE)
   link_libraries("-framework Foundation" "-framework StoreKit")
endif()
