#ifndef RtMidiExportDefH
#define RtMidiExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define RTMIDI_DECLSPEC
#else
   #ifdef EXTENSION_RTMIDI
      #define RTMIDI_DECLSPEC __declspec(dllexport)
   #else
      #define RTMIDI_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT RtMidiExportDefH

