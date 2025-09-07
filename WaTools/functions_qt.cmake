function(add_qml_module_dir SUBPATH NAME)

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

   qt_add_qml_module(${PROJECT_NAME}_QML
      URI ${NAME}
      VERSION 1.0
      STATIC
      RESOURCE_PREFIX "/qt/qml"
      SOURCES ${QML_SOURCE_FILES}
      QML_FILES ${QML_FILES}
      OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${NAME}
   )

   target_link_libraries(${PROJECT_NAME}_QML PUBLIC Qt6::Quick)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_QMLplugin)
endfunction()

function(add_qml_source_dir SUBPATH)

   file(GLOB_RECURSE QML_FILES
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

function(run_watools_deploy)
   if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
   endif()

   if(APPLE)
      file(GLOB WATOOLS_FILES
         ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../lib/release/*.so
      )
   elseif(WIN32)
      file(GLOB WATOOLS_FILES
         ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../lib/release/*.dll
      )
   endif()

   add_custom_command(TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMENT "copy watools ..."
      COMMAND ${CMAKE_COMMAND} -E copy ${WATOOLS_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}>
   )

endfunction()


# qt deploy , see https://www.qt.io/blog/cmake-deployment-api
function(run_qt_deploy)
   if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
   endif()
   
   get_target_property(QMAKE_EXE Qt6::qmake IMPORTED_LOCATION)
   get_filename_component(QT_BIN_DIR "${QMAKE_EXE}" DIRECTORY)

   set(QT_QML_DIR ${QT_BIN_DIR}/../qml)

   if(APPLE)
      find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${QT_BIN_DIR}")
      message(STATUS "MACDEPLOY ${MACDEPLOYQT_EXECUTABLE}, QT_QML_DIR =  ${QT_QML_DIR}")

      add_custom_command(TARGET ${PROJECT_NAME}
         POST_BUILD
         COMMENT "Running macdeployqt..."
         COMMAND "${MACDEPLOYQT_EXECUTABLE}"  $<TARGET_BUNDLE_DIR:${PROJECT_NAME}> -qmldir ${QT_QML_DIR}
      )
   elseif(WIN32)
      find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS " ${QT_BIN_DIR} ")
      message(STATUS " WINDEPLOY ${WINDEPLOYQT_EXECUTABLE}, QT_QML_DIR ${QT_QML_DIR} ")

      add_custom_command(TARGET ${PROJECT_NAME}
         POST_BUILD
         COMMENT "Running windeployqt... "
         COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-translations --no-system-d3d-compiler --compiler-runtime --qmldir ${QT_QML_DIR} $<TARGET_FILE:${PROJECT_NAME}>
      )
   endif()

endfunction()
