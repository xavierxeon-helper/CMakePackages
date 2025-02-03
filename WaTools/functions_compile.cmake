# include subdirs
function(add_subdirs_include SUB_DIR_PATH)
   include_directories("${SUB_DIR_PATH}")
   file(GLOB SUB_DIRECTORIES LIST_DIRECTORIES true "${SUB_DIR_PATH}/*")

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

# include suibdir files
function(add_subdirs_files SUB_DIR_PATH)
   include_directories("${SUB_DIR_PATH}")
   file(GLOB SUB_DIRECTORIES LIST_DIRECTORIES true "${SUB_DIR_PATH}/*")

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

# precompiled headers
function(use_named_precompiled_headers HEADER_FILE)
   target_precompile_headers(${PROJECT_NAME} PUBLIC ${HEADER_FILE})
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
