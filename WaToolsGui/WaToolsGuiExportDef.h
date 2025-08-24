#ifndef WaToolsGuiExportDefH
#define WaToolsGuiExportDefH

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define WATOOLSGUI_DECLSPEC
#else
   #ifdef EXTENSION_WATOOLSGUI
      #define WATOOLSGUI_DECLSPEC __declspec(dllexport)
   #else
      #define WATOOLSGUI_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT WaToolsGuiExportDefH

