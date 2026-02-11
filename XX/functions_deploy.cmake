function(run_xx_deploy)
   if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
   endif()

   if(IOS OR ANDROID)
      return()
   endif()

   if(APPLE)
      file(GLOB XX_FILES
         ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../lib/release/*.dylib
      )
   elseif(WIN32)
      file(GLOB XX_FILES
         ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../lib/release/*.dll
      )
   elseif(UNIX)
      file(GLOB XX_FILES
         ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../lib/release/*.so
      )
   else()
      message(FATAL_ERROR "Unsupported platform for xx deployment")
   endif()

   add_custom_command(TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMENT "copy xx ..."
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${XX_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}>
   )

endfunction()


# qt deploy , see https://www.qt.io/blog/cmake-deployment-api
function(run_qt_deploy)
   if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
      return()
   endif()

   if(IOS OR ANDROID)
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
