#ifndef XXLogExportDefH
#define XXLogExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define XXLOG_DECLSPEC
#else
   #ifdef EXTENSION_XXLOG
      #define XXLOG_DECLSPEC __declspec(dllexport)
   #else
      #define XXLOG_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXLogExportDefH

