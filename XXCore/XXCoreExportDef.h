#ifndef XXCoreExportDefH
#define XXCoreExportDefH

/*!
@defgroup XXCore Core 
@includedoc{doc} XXCore/XXCore.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
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
