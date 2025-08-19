#ifndef WaToolsMathExportDefH
#define WaToolsMathExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSMATH_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSMATH
      #define WATOOLSMATH_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSMATH_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsMathExportDefH

