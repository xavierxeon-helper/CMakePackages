include_directories(${CMAKE_CURRENT_LIST_DIR})
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

