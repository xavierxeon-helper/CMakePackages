set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compute paths
get_filename_component(WATOOLS_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(WATOOLS_INCLUDE_DIRS ${WATOOLS_CMAKE_DIR})

include_directories(${WATOOLS_INCLUDE_DIRS})
