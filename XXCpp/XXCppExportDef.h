#ifndef XXWaToolCppExportDefH
#define XXWaToolCppExportDefH

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXCPP_DECLSPEC
#else
   #ifdef EXTENSION_XXCPP      
      #define XXCPP_DECLSPEC __declspec(dllexport)
   #else
      #define XXCPP_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXWaToolCppExportDefH
