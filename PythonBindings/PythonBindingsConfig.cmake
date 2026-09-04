# pybind stuff
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

execute_process(
   COMMAND ${Python3_EXECUTABLE} -m pybind11 --cmakedir
   OUTPUT_VARIABLE pybind11_DIR
   OUTPUT_STRIP_TRAILING_WHITESPACE
)
file(TO_CMAKE_PATH "${pybind11_DIR}" pybind11_DIR)
find_package(pybind11 3.0 REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR})

function(copy_python_qt_dependenies)
   add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
      COMMAND_EXPAND_LISTS
   )
endfunction()