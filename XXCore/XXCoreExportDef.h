#ifndef XXCoreExportDefH
#define XXCoreExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define XXCORE_DECLSPEC
#else
   #ifdef EXTENSION_XXCORE
      #define XXCORE_DECLSPEC __declspec(dllexport)
   #else
      #define XXCORE_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXCoreExportDefH

