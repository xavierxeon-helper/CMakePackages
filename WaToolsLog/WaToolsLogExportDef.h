#ifndef WaToolsLogExportDefH
#define WaToolsLogExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSLOG_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSLOG
      #define WATOOLSLOG_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSLOG_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsLogExportDefH

