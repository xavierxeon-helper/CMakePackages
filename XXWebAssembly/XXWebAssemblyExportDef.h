#ifndef XXWebAssemblyExportDefH
#define XXWebAssemblyExportDefH

/*!
@defgroup XXWebAssembly XXWebAssembly component
@includedoc{doc} XXWebAssembly/XXWebAssembly.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXWEBASSEMBLY_DECLSPEC
#else
   #ifdef EXTENSION_XXWEBASSEMBLY
      #define XXWEBASSEMBLY_DECLSPEC __declspec(dllexport)
   #else
      #define XXWEBASSEMBLY_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXWebAssemblyExportDefH

