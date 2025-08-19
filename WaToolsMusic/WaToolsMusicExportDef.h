#ifndef WaToolsMusicExportDefH
#define WaToolsMusicExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSMUSIC_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSMUSIC
      #define WATOOLSMUSIC_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSMUSIC_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsMusicExportDefH

