
message(STATUS "${PROJECT_NAME}common use")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
   link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/release)
else()
   link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/debug)
endif()
