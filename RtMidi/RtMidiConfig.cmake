set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compute paths
get_filename_component(RTMIDI_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(RTMIDI_INCLUDE_DIRS ${RTMIDI_CMAKE_DIR})

include_directories(${RTMIDI_INCLUDE_DIRS})

include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)

link_libraries(RtMidi)

if(APPLE)
   add_compile_definitions(__MACOSX_CORE__)
   link_libraries(
      "-framework CoreMIDI"
      "-framework CoreAudio"
      "-framework CoreFoundation"
   )
elseif(WIN32)
   add_compile_definitions(__WINDOWS_MM__)
   link_libraries(Winmm)
elseif(UNIX)
   add_compile_definitions(__UNIX_JACK__)
   link_libraries(jack)
endif()

