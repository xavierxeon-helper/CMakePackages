#ifndef WaToolsNetworkExportDefH
#define WaToolsNetworkExportDefH

/// @addtogroup WaToolsNetwork

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSNETWORK_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSNETWORK
      #define WATOOLSNETWORK_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSNETWORK_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsNetworkExportDefH
