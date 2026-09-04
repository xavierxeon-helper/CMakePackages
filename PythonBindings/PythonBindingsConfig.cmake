# pybind stuff
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

execute_process(
   COMMAND ${Python3_EXECUTABLE} -m site --user-site
   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
   OUTPUT_VARIABLE PYTHON_SITE
   OUTPUT_STRIP_TRAILING_WHITESPACE
)
find_package(pybind11 3.0 REQUIRED HINTS ${PYTHON_SITE}/pybind11/share/cmake)

include_directories(${CMAKE_CURRENT_LIST_DIR})
