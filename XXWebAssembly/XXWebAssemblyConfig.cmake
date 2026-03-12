include_directories(${CMAKE_CURRENT_LIST_DIR})
include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core)
link_libraries(Qt6::Core XXWebAssembly)

if(EMSCRIPTEN)
   link_libraries(idbfs.js)
   add_link_options(-sASYNCIFY=1)
endif()
