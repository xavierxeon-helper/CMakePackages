#ifndef XXGuiExportDefH
#define XXGuiExportDefH

/*!
@defgroup XXGui Gui 
@includedoc{doc} XXGui/XXGui.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXGUI_DECLSPEC
#else
   #ifdef EXTENSION_XXGUI
      #define XXGUI_DECLSPEC __declspec(dllexport)
   #else
      #define XXGUI_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXGuiExportDefH
