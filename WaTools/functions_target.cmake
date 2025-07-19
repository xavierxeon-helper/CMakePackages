# standard release output path
function(set_standrard_release_output_path)
   if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
   endif()

   get_property(TARGET_TEST DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)

   if(TARGET_TEST)
      message(FATAL_ERROR "The function 'set_standrard_release_output_path' must be called before any target is created")
      return()
   endif()

   if(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
      message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY is already set to: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
      return()
   endif()

   if(APPLE)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{HOME}/Applications PARENT_SCOPE)
   elseif(WIN32)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{LOCALAPPDATA}/${PROJECT_NAME} PARENT_SCOPE)
   elseif(UNIX)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{HOME}/bin PARENT_SCOPE)
   endif()
endfunction()

# application icon
function(set_application_icon PATH_TO_ICON)

   if(APPLE)
      set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
      set(APP_ICON ${PATH_TO_ICON}.icns)
      message(STATUS "APP_ICON: ${APP_ICON}")

      set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns PARENT_SCOPE)
      set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

      target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON})
   elseif(WIN32)
      set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
      set(ICON_RC_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.rc)

      if(NOT EXISTS ${ICON_RC_FILE})
         file(WRITE ${ICON_RC_FILE} "#include \"winver.h\"\nIDI_ICON1 ICON \"${PATH_TO_ICON}.ico\"\n")
      endif()

      set(APP_ICON "${ICON_RC_FILE}")
      message(STATUS "APP_ICON: ${APP_ICON}")

      target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON})
   endif()
endfunction()
