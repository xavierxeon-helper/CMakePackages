#ifndef XXNetworkExportDefH
#define XXNetworkExportDefH

/// @addtogroup XXNetwork

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define XXNETWORK_DECLSPEC
#else
   #ifdef EXTENSION_XXNETWORK
      #define XXNETWORK_DECLSPEC __declspec(dllexport)
   #else
      #define XXNETWORK_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXNetworkExportDefH
