# crawl through subdirs and include dirs
function(add_all_subdirs_include SUB_DIR_PATH) # args = list of skip directories
   include_directories("${SUB_DIR_PATH}")
   file(GLOB SUB_DIRECTORIES LIST_DIRECTORIES true "${SUB_DIR_PATH}/*")
   list(REMOVE_ITEM SUB_DIRECTORIES ${ARGN})

   foreach(SUB_DIR ${SUB_DIRECTORIES})
      if(NOT IS_DIRECTORY ${SUB_DIR})
         continue()
      endif()

      if(${SUB_DIR} STREQUAL ${PROJECT_SOURCE_DIR}/build)
         continue()
      endif()

      if(EXISTS ${SUB_DIR}/CMakeLists.txt)
         message(STATUS "Skipping directory files: ${SUB_DIR}")
         continue()
      endif()

      message(STATUS "Include directory: ${SUB_DIR}")
      include_directories(${SUB_DIR})
   endforeach()
endfunction()

# add a specific subdir
function(add_sub_dirs_files) # args = list of directories
   foreach(SUB_DIR ${ARGN})
      if(NOT IS_DIRECTORY ${SUB_DIR})
         continue()
      endif()

      if(${SUB_DIR} STREQUAL ${PROJECT_SOURCE_DIR}/build)
         continue()
      endif()

      if(EXISTS ${SUB_DIR}/CMakeLists.txt)
         message(STATUS "Skipping directory files: ${SUB_DIR}")
         continue()
      endif()

      message(STATUS "Include directory files: ${SUB_DIR}")

      include_directories(${SUB_DIR})
      file(GLOB SUBDIR_FILES
         ${SUB_DIR}/*.h
         ${SUB_DIR}/*.hpp
         ${SUB_DIR}/*.cpp
         ${SUB_DIR}/*.ui
         ${SUB_DIR}/*.qrc
      )
      target_sources(${PROJECT_NAME} PRIVATE ${SUBDIR_FILES})
   endforeach()
endfunction()

# crawl through subdirs and add files
function(add_all_subdirs_files SUB_DIR_PATH) # args = list of skip directories
   include_directories("${SUB_DIR_PATH}")
   file(GLOB SUB_DIRECTORIES LIST_DIRECTORIES true "${SUB_DIR_PATH}/*")

   list(REMOVE_ITEM SUB_DIRECTORIES ${ARGN})
   add_sub_dirs_files(${SUB_DIRECTORIES})
endfunction()

# precompiled headers
function(use_named_precompiled_headers HEADER_FILE)
   target_precompile_headers(${PROJECT_NAME} PRIVATE ${HEADER_FILE})
   target_sources(${PROJECT_NAME} PRIVATE ${HEADER_FILE})
endfunction()

function(use_precompiled_headers)
   set(HEADER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.precompiled.h)

   if(NOT EXISTS ${HEADER_FILE})
      message(STATUS "Creating precompiled header file: ${HEADER_FILE}")
      file(WRITE ${HEADER_FILE} "#pragma one\n")
   endif()

   target_precompile_headers(${PROJECT_NAME} PUBLIC ${HEADER_FILE})
   target_sources(${PROJECT_NAME} PRIVATE ${HEADER_FILE})
endfunction()

# os specific files
function(add_os_files SOURCE_SUB_DIR)
   if(APPLE)
      set(MAC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_SUB_DIR}/mac)

      if(NOT EXISTS ${MAC_SOURCE_DIR})
         message(STATUS "Creating macOS source directory: ${MAC_SOURCE_DIR}")
         file(MAKE_DIRECTORY ${MAC_SOURCE_DIR})
      endif()

      file(GLOB OS_FILES
         ${MAC_SOURCE_DIR}/*.h
         ${MAC_SOURCE_DIR}/*.hpp
         ${MAC_SOURCE_DIR}/*.cpp
         ${MAC_SOURCE_DIR}/*.mm
      )
   elseif(WIN32)
      set(WIN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_SUB_DIR}/win)

      if(NOT EXISTS ${WIN_SOURCE_DIR})
         message(STATUS "Creating Windows source directory: ${WIN_SOURCE_DIR}")
         file(MAKE_DIRECTORY ${WIN_SOURCE_DIR})
      endif()

      file(GLOB OS_FILES
         ${WIN_SOURCE_DIR}/*.h
         ${WIN_SOURCE_DIR}/*.hpp
         ${WIN_SOURCE_DIR}/*.cpp
      )
   else()
      set(LINUX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_SUB_DIR}/linux)

      if(NOT EXISTS ${LINUX_SOURCE_DIR})
         message(STATUS "Creating Linux source directory: ${LINUX_SOURCE_DIR}")
         file(MAKE_DIRECTORY ${LINUX_SOURCE_DIR})
      endif()

      file(GLOB OS_FILES
         ${LINUX_SOURCE_DIR}/*.h
         ${LINUX_SOURCE_DIR}/*.hpp
         ${LINUX_SOURCE_DIR}/*.cpp
      )
   endif()

   set(SOURCE_FILES ${SOURCE_FILES} ${OS_FILES} PARENT_SCOPE)
endfunction()
