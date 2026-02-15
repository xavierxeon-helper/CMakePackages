#ifndef XXNetworkExportDefH
#define XXNetworkExportDefH

/*!
@defgroup XXNetwork Network
@includedoc{doc} XXNetwork/XXNetwork.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
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
