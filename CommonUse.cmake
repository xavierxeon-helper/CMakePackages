if(CMAKE_BUILD_TYPE STREQUAL "Release")
   link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/${XX_SYSTEM_ID}/release)
else()
   link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/${XX_SYSTEM_ID}/debug)
endif()

