#ifndef XXWidgetsExportDefH
#define XXWidgetsExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define XXWIDGETS_DECLSPEC
#else
   #ifdef EXTENSION_XXWIDGETS
      #define XXWIDGETS_DECLSPEC __declspec(dllexport)
   #else
      #define XXWIDGETS_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXWidgetsExportDefH

