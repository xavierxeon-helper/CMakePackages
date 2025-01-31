set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
   set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0") # for Qt
endif()

# Compute paths
get_filename_component(WATOOLS_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATOOLS_INCLUDE_DIRS ${WATOOLS_CMAKE_DIR})

include_directories(${WATOOLS_INCLUDE_DIRS})

# include subdirs
function(add_include_subdirs SUB_DIR_PATH)
   include_directories("${SUB_DIR_PATH}")
   file(GLOB SUB_DIRECTORIES LIST_DIRECTORIES true "${SUB_DIR_PATH}/*")

   foreach(item ${SUB_DIRECTORIES})
      if(IS_DIRECTORY ${item})
         include_directories("${item}")
      endif()
   endforeach()
endfunction()

# precompiled headers
function(use_precompiled_headers HEADER_FILE)
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

# standard release output path
function(set_standrard_release_output_path)
   if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
   endif()

   if(APPLE)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{HOME}/Applications)
   elseif(WIN32)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{LOCALAPPDATA}/${PROJECT_NAME})

   elseif(UNIX)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{HOME}/bin)
   endif()
endfunction()

# qt deploy
function(run_qt_deploy)
   if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
   endif()

   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{LOCALAPPDATA}/${PROJECT_NAME})

   get_target_property(QMAKE_EXE Qt6::qmake IMPORTED_LOCATION)
   get_filename_component(QT_BIN_DIR "${QMAKE_EXE}" DIRECTORY)

   set(QT_QML_DIR ${QT_BIN_DIR}/../qml)

   if(APPLE)
      find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${QT_BIN_DIR}")
      message(STATUS "MACDEPLOY ${MACDEPLOYQT_EXECUTABLE}, QT_QML_DIR ${QT_QML_DIR}")

      add_custom_command(TARGET ${PROJECT_NAME}
         POST_BUILD
         COMMAND "${MACDEPLOYQT_EXECUTABLE}" --qmldir ${QT_QML_DIR} \"$<TARGET_FILE:${PROJECT_NAME}>\"
      )
   elseif(WIN32)
      find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")
      message(STATUS "WINDEPLOY ${WINDEPLOYQT_EXECUTABLE}, QT_QML_DIR ${QT_QML_DIR}")

      add_custom_command(TARGET ${PROJECT_NAME}
         POST_BUILD
         COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-translations --no-system-d3d-compiler --compiler-runtime --qmldir ${QT_QML_DIR} \"$<TARGET_FILE:${PROJECT_NAME}>\"
      )
   endif()
endfunction()

# application icon
function(set_application_icon PATH_TO_ICON)
   if(APPLE)
      set(APP_ICON ${PATH_TO_ICON}.icns)
      message(STATUS "APP_ICON: ${APP_ICON}")

      set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
      set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

      target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON})
   elseif(WIN32)
      set(ICON_RC_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc)

      if(NOT EXISTS ${ICON_RC_FILE})
         file(WRITE ${ICON_RC_FILE} "#include \"winver.h\"\nIDI_ICON1 ICON \"${PATH_TO_ICON}.ico\"\n")
      endif()

      set(APP_ICON "${ICON_RC_FILE}")
      target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON})
   endif()
endfunction()
