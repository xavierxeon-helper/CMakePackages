#ifndef XXMusicExportDefH
#define XXMusicExportDefH

/*!
@defgroup XXMusic Music
@includedoc{doc} XXMusic/XXMusic.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXMUSIC_DECLSPEC
#else
   #ifdef EXTENSION_XXMUSIC
      #define XXMUSIC_DECLSPEC __declspec(dllexport)
   #else
      #define XXMUSIC_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXMusicExportDefH
