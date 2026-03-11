#ifndef XXNetworkOAuthExportDefH
#define XXNetworkOAuthExportDefH

/*!
@defgroup XXNetworkOAuth XXNetworkOAuth component
@includedoc{doc} XXNetworkOAuth/XXNetworkOAuth.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXNETWORKOAUTH_DECLSPEC
#else
   #ifdef EXTENSION_XXNETWORKOAUTH
      #define XXNETWORKOAUTH_DECLSPEC __declspec(dllexport)
   #else
      #define XXNETWORKOAUTH_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXNetworkOAuthExportDefH

