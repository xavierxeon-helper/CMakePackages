#ifndef WaToolsGeneralExportDefH
#define WaToolsGeneralExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSGENERAL_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSGENERAL
      #define WATOOLSGENERAL_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSGENERAL_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsGeneralExportDefH

