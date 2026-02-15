#ifndef XXWidgetsExportDefH
#define XXWidgetsExportDefH

/*!
@defgroup XXWidgets Widgets
@includedoc{doc} XXWidgets/XXWidgets.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXWIDGETS_DECLSPEC
#else
   #ifdef EXTENSION_XXWIDGETS
      #define XXWIDGETS_DECLSPEC __declspec(dllexport)
   #else
      #define XXWIDGETS_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXWidgetsExportDefH
