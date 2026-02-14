#ifndef XXMathExportDefH
#define XXMathExportDefH

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXMATH_DECLSPEC
#else
   #ifdef EXTENSION_XXMATH
      #define XXMATH_DECLSPEC __declspec(dllexport)
   #else
      #define XXMATH_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXMathExportDefH
