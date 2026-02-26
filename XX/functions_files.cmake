# standard release output path
function(set_standrard_release_output_path)
   if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
   endif()

   if(ANDROID OR IOS OR EMSCRIPTEN)
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

   cmake_parse_arguments(PARSE_ARGV 1 APP_ICON_ARG "" "NAME" "")

   if(NOT APP_ICON_ARG_NAME)
      set(APP_ICON_ARG_NAME ${PROJECT_NAME})
   endif()

   if(ANDROID)
      # see https://creativefreedom.co.uk/icon-designers-blog/android-icon-sizes/
      if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/android/res)
         file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/android/res)
      endif()

      set_target_properties(${PROJECT_NAME}
        PROPERTIES
            QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/android"
            QT_ANDROID_APP_ICON "@mipmap/icon"
      )      
   elseif(IOS)
      # see https://doc.qt.io/qt-6/ios-platform-notes.html#launch-screens-and-launch-images
      set(ASSET_CATALOG_PATH "${PATH_TO_ICON}/Assets.xcassets")
      if(NOT EXISTS ${ASSET_CATALOG_PATH})
         file(MAKE_DIRECTORY ${ASSET_CATALOG_PATH})
      endif()

      if(NOT EXISTS ${ASSET_CATALOG_PATH}/AppIcon.appiconset)
         file(COPY ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/resources/Contents.json DESTINATION ${ASSET_CATALOG_PATH}/AppIcon.appiconset)
      endif()

      target_sources(${PROJECT_NAME} PRIVATE "${ASSET_CATALOG_PATH}")
      set_source_files_properties(${ASSET_CATALOG_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
      set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon)
   elseif(APPLE)
      set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
      set(APP_ICON ${PATH_TO_ICON}/${APP_ICON_ARG_NAME}.icns)
      message(STATUS "APP_ICON: ${APP_ICON}")

      set(MACOSX_BUNDLE_ICON_FILE ${APP_ICON_ARG_NAME}.icns PARENT_SCOPE)
      set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

      target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON})
   elseif(WIN32)
      set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
      set(ICON_RC_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.rc)
      set(APP_ICON ${PATH_TO_ICON}/${APP_ICON_ARG_NAME}.ico)

      if(NOT EXISTS ${ICON_RC_FILE})         
         file(WRITE ${ICON_RC_FILE} "#include \"winver.h\"\nIDI_ICON1 ICON \"${APP_ICON}\"\n")
      endif()

      message(STATUS "APP_ICON: ${APP_ICON} @ ${ICON_RC_FILE}")

      target_sources(${PROJECT_NAME} PRIVATE ${ICON_RC_FILE})
   endif()
endfunction()

# application without icon
function(set_application_no_icon)
   if(IOS)
      set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
   elseif(APPLE)
      set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
   elseif(WIN32)
      set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
   endif()
endfunction()


# build version
function(auto_build_version)
   
   set(BUILD_VERSION_CACHE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/AppVersionNumber.txt")
   set(BUILD_VERSION_VERSION_SOURCE_FILE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/resources/AppVersionNumber.h.in")

   include(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/scripts/set_build_timestamp.cmake) # initialize build number
   
   add_custom_target(
      BUILD_VERSION_INCREMENT
      COMMAND ${CMAKE_COMMAND}
      -DBUILD_VERSION_CACHE_FILE=${BUILD_VERSION_CACHE_FILE}
      -DBUILD_VERSION_VERSION_SOURCE_FILE=${BUILD_VERSION_VERSION_SOURCE_FILE}
      -P "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/scripts/set_build_timestamp.cmake"
   )
   add_dependencies(${PROJECT_NAME} BUILD_VERSION_INCREMENT)
   target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

endfunction()

