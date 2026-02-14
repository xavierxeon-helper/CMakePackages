#ifndef XXMusicExportDefH
#define XXMusicExportDefH

//! @addtogroup XXAudio

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
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
