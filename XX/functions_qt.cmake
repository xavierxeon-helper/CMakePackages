# set QT_ARCH
function(set_qt_arch)

   if(QT_ARCH)
      return()
   endif()

   find_package(Qt6 REQUIRED COMPONENTS Core)   
   get_target_property(QT_CORE_LIB Qt6::Core IMPORTED_LOCATION)
   get_filename_component(QT_LIB_DIR "${QT_CORE_LIB}" DIRECTORY)
   get_filename_component(QT_ROOT_DIR "${QT_LIB_DIR}/.." ABSOLUTE)
   get_filename_component(QT_ARCH "${QT_ROOT_DIR}" NAME)

   set(QT_ARCH ${QT_ARCH} PARENT_SCOPE)

endfunction()

# all resource files
function(add_resource_dir SUBPATH)

   cmake_parse_arguments(PARSE_ARGV 1 RESOURCE_ARG "RECURSIVE" "RCNAME;PREFIX;" "FILTERS")

   if(NOT RESOURCE_ARG_RECURSIVE)
      set(RESOURCE_ARG_RECURSIVE FALSE)
   endif()

   if(NOT RESOURCE_ARG_RCNAME)
      set(RESOURCE_ARG_RCNAME "${PROJECT_NAME}_${SUBPATH}")
   endif()

   if(NOT RESOURCE_ARG_PREFIX)
      set(RESOURCE_ARG_PREFIX "/")
   endif()

   if(NOT RESOURCE_ARG_FILTERS)
      set(RESOURCE_ARG_FILTERS "*")
   endif()

   list(TRANSFORM RESOURCE_ARG_FILTERS PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/${SUBPATH}/")

   if(RESOURCE_ARG_RECURSIVE)
      file(GLOB_RECURSE RESOURCE_FILES
         RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
         ${RESOURCE_ARG_FILTERS}
      )
   else()
      file(GLOB RESOURCE_FILES
         RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
         ${RESOURCE_ARG_FILTERS}
      )
   endif()

   qt_add_resources(${PROJECT_NAME} ${RESOURCE_ARG_RCNAME}
      PREFIX ${RESOURCE_ARG_PREFIX}
      FILES ${RESOURCE_FILES}
   )

   message(STATUS "RESOURCE_FILES for ${PROJECT_NAME} found @ ${SUBPATH} = ${RESOURCE_FILES}")   
endfunction()

# qml source
function(add_qml_source_dir SUBPATH)

   add_resource_dir(${SUBPATH} FILTERS "*.qml" "*.svg")

endfunction()

# markdown
function(add_markdown_dir SUBPATH)

   cmake_parse_arguments(PARSE_ARGV 1 MARKDOWN_ARG "" "RCNAME;PREFIX" "")

   if(NOT MARKDOWN_ARG_RCNAME)
      set(MARKDOWN_ARG_RCNAME "${PROJECT_NAME}_${SUBPATH}")
   endif()

   if(NOT MARKDOWN_ARG_PREFIX)
      set(MARKDOWN_ARG_PREFIX "/")
   endif()

   add_resource_dir(${SUBPATH} RCNAME ${MARKDOWN_ARG_RCNAME} PREFIX ${MARKDOWN_ARG_PREFIX} FILTERS "*.md" "*.png")
endfunction()

# icon
function(add_icon_dir SUBPATH)

   cmake_parse_arguments(PARSE_ARGV 1 ICON_ARG "" "RCNAME;PREFIX" "")

   if(NOT ICON_ARG_RCNAME)
      set(ICON_ARG_RCNAME "${PROJECT_NAME}_${SUBPATH}")
   endif()

   if(NOT ICON_ARG_PREFIX)
      set(ICON_ARG_PREFIX "/")
   endif()

   add_resource_dir(${SUBPATH} RCNAME ${ICON_ARG_RCNAME} PREFIX ${ICON_ARG_PREFIX} FILTERS "*.svg")
endfunction()

# qml module
function(add_qml_module_dir SUBPATH)

   cmake_parse_arguments(PARSE_ARGV 1 QML_MODULE_ARG "" "NAME" "LINK")

   if(QML_MODULE_ARG_NAME)
      set(NAME ${QML_MODULE_ARG_NAME})
   else()
      set(NAME ${SUBPATH})
   endif()

   find_package(Qt6 REQUIRED COMPONENTS Qml Quick)

   include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${SUBPATH})

   file(GLOB QML_SOURCE_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/${SUBPATH}/*.h
      ${CMAKE_CURRENT_SOURCE_DIR}/${SUBPATH}/*.cpp
   )

   file(GLOB QML_FILES
      RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
      ${CMAKE_CURRENT_SOURCE_DIR}/${SUBPATH}/*.qml
      ${CMAKE_CURRENT_SOURCE_DIR}/${SUBPATH}/*.js
   )

   qt_policy(SET QTP0004 NEW)

   qt_add_qml_module(${PROJECT_NAME}_QML
      URI ${NAME}
      VERSION 1.0
      STATIC
      RESOURCE_PREFIX "/qt/qml"
      SOURCES ${QML_SOURCE_FILES}
      QML_FILES ${QML_FILES}
      OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${NAME}
   )

   target_link_libraries(${PROJECT_NAME}_QML PUBLIC Qt6::Qml Qt6::Quick)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_QMLplugin)

   if(QML_MODULE_ARG_LINK)
      message(STATUS "QML ${NAME} LINK = ${QML_MODULE_ARG_LINK}")
      target_link_libraries(${PROJECT_NAME}_QML PUBLIC ${QML_MODULE_ARG_LINK})
   endif()

   message(STATUS "MODULE DIR QML_FILES for ${PROJECT_NAME} found @ ${SUBPATH} = ${QML_FILES}")

endfunction()

function (add_camera_permissions)
   find_package(Python COMPONENTS Interpreter)
   if (NOT PYTHON_FOUND)
      message(FATAL_ERROR "Python not found, required for adding camera permissions")
   endif()
   
   if(IOS)
      status(FATAL_ERROR "Camera permissions on iOS no yet implemented, see https://doc.qt.io/qt-6/permissions.html#camera-permissions")
   elseif(APPLE)
      set(CUSTOM_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/macos/Info.plist")
      if(NOT EXISTS "${CUSTOM_INFO_PLIST}")
         set(SOURCE_INFO_PLIST "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Info.plist")
         message(STATUS "SOURCE_INFO_PLIST ${SOURCE_INFO_PLIST}")

         add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMENT "copy info.plist ..."
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOURCE_INFO_PLIST} ${CUSTOM_INFO_PLIST}
            COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/scripts/fix_plist.py ${CUSTOM_INFO_PLIST} "NSCameraUsageDescription" "Camera permission is required"
         )

      else()
         target_sources(${PROJECT_NAME} PRIVATE
            ${CUSTOM_INFO_PLIST}
         )
         set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CUSTOM_INFO_PLIST}")
      endif()
   endif()
endfunction()


