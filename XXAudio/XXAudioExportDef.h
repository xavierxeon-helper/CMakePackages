#ifndef XXAudioExportDefH
#define XXAudioExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define XXAUDIO_DECLSPEC
#else
   #ifdef EXTENSION_XXAUDIO
      #define XXAUDIO_DECLSPEC __declspec(dllexport)
   #else
      #define XXAUDIO_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXAudioExportDefH
