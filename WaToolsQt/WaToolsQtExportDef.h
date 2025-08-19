#ifndef WaToolsQtExportDefH
#define WaToolsQtExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLS_QT_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLS_QT
      #define WATOOLS_QT_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLS_QT_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsQtExportDefH
