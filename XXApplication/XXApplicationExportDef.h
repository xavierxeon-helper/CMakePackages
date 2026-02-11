#ifndef XXApplicationExportDefH
#define XXApplicationExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define XXAPPLICATION_DECLSPEC
#else
   #ifdef EXTENSION_XXAPPLICATION
      #define XXAPPLICATION_DECLSPEC __declspec(dllexport)
   #else
      #define XXAPPLICATION_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXApplicationExportDefH

