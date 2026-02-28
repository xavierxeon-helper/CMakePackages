#ifndef XXQuickExportDefH
#define XXQuickExportDefH

/*!
@defgroup XXQuick Quick
@includedoc{doc} XXQuick/XXQuick.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXQUICK_DECLSPEC
#else
   #ifdef EXTENSION_XXQUICK
      #define XXQUICK_DECLSPEC __declspec(dllexport)
   #else
      #define XXQUICK_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXQuickExportDefH
