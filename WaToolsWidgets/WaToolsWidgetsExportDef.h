#ifndef WaToolsWidgetsExportDefH
#define WaToolsWidgetsExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSWIDGETS_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSWIDGETS
      #define WATOOLSWIDGETS_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSWIDGETS_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsWidgetsExportDefH

