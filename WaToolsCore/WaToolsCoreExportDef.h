#ifndef WaToolsCoreExportDefH
#define WaToolsCoreExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSCORE_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSCORE
      #define WATOOLSCORE_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSCORE_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsCoreExportDefH

