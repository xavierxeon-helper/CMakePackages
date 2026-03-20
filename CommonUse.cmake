set_qt_arch()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
   link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/${QT_ARCH}/release)
else()
   link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/${QT_ARCH}/debug)
endif()

