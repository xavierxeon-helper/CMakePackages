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
