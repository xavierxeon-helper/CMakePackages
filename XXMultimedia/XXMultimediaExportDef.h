#ifndef XXMultimediaExportDefH
#define XXMultimediaExportDefH

/*!
@defgroup XXMultimedia XXMultimedia component
@includedoc{doc} XXMultimedia/XXMultimedia.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXMULTIMEDIA_DECLSPEC
#else
   #ifdef EXTENSION_XXMULTIMEDIA
      #define XXMULTIMEDIA_DECLSPEC __declspec(dllexport)
   #else
      #define XXMULTIMEDIA_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXMultimediaExportDefH

