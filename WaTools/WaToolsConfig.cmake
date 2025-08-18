include(${CMAKE_CURRENT_LIST_DIR}/functions_compile.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/functions_target.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/functions_git.cmake)

foreach(COMPONENT ${WaTools_FIND_COMPONENTS})
   #message(STATUS "NEED WaTools component: ${COMPONENT}")
   find_package(WaTools${COMPONENT} REQUIRED)
endforeach()