#ifndef WaToolsQtExportDefH
#define WaToolsQtExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSQT_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSQT
      #define WATOOLSQT_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSQT_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsQtExportDefH

