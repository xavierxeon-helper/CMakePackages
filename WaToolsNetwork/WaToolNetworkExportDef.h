#ifndef WaToolNetworkExportDefH
#define WaToolNetworkExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLNETWORK_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLNETWORK
      #define WATOOLNETWORK_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLNETWORK_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolNetworkExportDefH

