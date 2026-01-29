#ifndef WaToolCppExportDefH
#define WaToolCppExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSCPP_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSCPP      
      #define WATOOLSCPP_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSCPP_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolCppExportDefH
