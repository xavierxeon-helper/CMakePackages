cmake_minimum_required(VERSION 3.20)
project(WaTools LANGUAGES CXX)

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE)

add_subdirectory(RtMidi)
add_subdirectory(WaToolsAudio)
add_subdirectory(WaToolsGeneral)
add_subdirectory(WaToolsLog)
add_subdirectory(WaToolsMath)
add_subdirectory(WaToolsMusic)
add_subdirectory(WaToolsNetwork)
add_subdirectory(WaToolsQt)
