function(add_module_dir PATH NAME)

   include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${PATH})

   file(GLOB QML_SOURCE_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/${PATH}/*.h
      ${CMAKE_CURRENT_SOURCE_DIR}/${PATH}/*.cpp
   )

   qt_add_qml_module(${PROJECT_NAME}_QML
      URI ${NAME}
      VERSION 1.0
      STATIC
      RESOURCE_PREFIX "/qt/qml"
      SOURCES ${QML_SOURCE_FILES}
   )

   target_link_libraries(${PROJECT_NAME}_QML PUBLIC Qt6::Quick)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_QMLplugin)
endfunction()

function(add_qml_sources SUBPATH)

   file(GLOB QML_FILES
      RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
      ${CMAKE_CURRENT_SOURCE_DIR}/${SUBPATH}/*.qml
      ${CMAKE_CURRENT_SOURCE_DIR}/${SUBPATH}/*.js
   )

   message(STATUS "QML_FILES for ${PROJECT_NAME} found @ ${SUBPATH} = ${QML_FILES}")

   qt6_add_resources(${PROJECT_NAME} "${PROJECT_NAME}_${SUBPATH}"
       PREFIX "/"
       FILES ${QML_FILES}
   )
endfunction()

