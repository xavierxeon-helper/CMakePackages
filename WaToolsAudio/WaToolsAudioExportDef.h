#ifndef WaToolsAudioExportDefH
#define WaToolsAudioExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSAUDIO_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSAUDIO
      #define WATOOLSAUDIO_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSAUDIO_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsAudioExportDefH

