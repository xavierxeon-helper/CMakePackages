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
   if(IOS)
      set(ASSET_CATALOG_PATH "Icons/Assets.xcassets")
      if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_CATALOG_PATH})
         file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_CATALOG_PATH}/AppIcon.appiconset)
         file(COPY ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/Contents.json DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_CATALOG_PATH}/AppIcon.appiconset)
      endif()
      target_sources(${PROJECT_NAME} PRIVATE "${ASSET_CATALOG_PATH}")
      set_source_files_properties(${ASSET_CATALOG_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
      set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon)
   elseif(APPLE)
      set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
      set(APP_ICON ${PATH_TO_ICON}/${PROJECT_NAME}.icns)
      message(STATUS "APP_ICON: ${APP_ICON}")

      set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns PARENT_SCOPE)
      set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

      target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON})
   elseif(WIN32)
      set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
      set(ICON_RC_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.rc)

      if(NOT EXISTS ${ICON_RC_FILE})
         file(WRITE ${ICON_RC_FILE} "#include \"winver.h\"\nIDI_ICON1 ICON \"${PATH_TO_ICON}/${PROJECT_NAME}.ico\"\n")
      endif()

      set(APP_ICON "${ICON_RC_FILE}")
      message(STATUS "APP_ICON: ${APP_ICON}")

      target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON})   
   endif()
endfunction()

# application without icon
function(set_application_no_icon)
   if(APPLE)
      set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
   elseif(WIN32)
      set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
   endif()
endfunction()

# build number
function(auto_build_number)
   
   set(BUILD_NUMBER_CACHE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/AppVersionNumber.txt")
   set(BUILD_NUMBER_VERSION_FILE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/AppVersionNumber.h.in")

   include(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/increment_build_number.cmake) # initialize build number   
   
   add_custom_target(
      BUILD_NUMBER_INCREMENT
      COMMAND ${CMAKE_COMMAND} -DBUILD_NUMBER_CACHE_FILE=${BUILD_NUMBER_CACHE_FILE} -DBUILD_NUMBER_VERSION_FILE=${BUILD_NUMBER_VERSION_FILE} -P "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/increment_build_number.cmake"
   )
   add_dependencies(${PROJECT_NAME} BUILD_NUMBER_INCREMENT)
   target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

endfunction()

