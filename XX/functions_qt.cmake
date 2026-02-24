# all resource files
function(add_resource_dir SUBPATH)

   cmake_parse_arguments(PARSE_ARGV 1 RESOURCE_ARG "" "RCNAME;PREFIX;" "FILTERS")

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

   file(GLOB RESOURCE_FILES
      RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
      ${RESOURCE_ARG_FILTERS}
   )

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
   add_resource_dir(${SUBPATH} RCNAME ${MARKDOWN_ARG_RCNAME} PREFIX ${MARKDOWN_ARG_PREFIX} FILTERS "*.md" "*.png")

endfunction()

# icon
function(add_icon_dir SUBPATH)

   cmake_parse_arguments(PARSE_ARGV 1 ICON_ARG "" "RCNAME;PREFIX" "")
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


