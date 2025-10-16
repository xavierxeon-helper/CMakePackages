#ifndef WaToolsApplicationExportDefH
#define WaToolsApplicationExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSAPPLICATION_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSAPPLICATION
      #define WATOOLSAPPLICATION_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSAPPLICATION_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsApplicationExportDefH

