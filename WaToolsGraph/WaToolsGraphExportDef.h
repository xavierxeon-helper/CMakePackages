#ifndef WaToolsGraphExportDefH
#define WaToolsGraphExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSGRAPH_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSGRAPH
      #define WATOOLSGRAPH_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSGRAPH_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsGraphExportDefH

