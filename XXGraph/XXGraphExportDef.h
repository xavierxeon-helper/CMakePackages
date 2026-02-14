#ifndef XXGraphExportDefH
#define XXGraphExportDefH

//! @addtogroup XXGraph

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define XXGRAPH_DECLSPEC
#else
   #ifdef EXTENSION_XXGRAPH
      #define XXGRAPH_DECLSPEC __declspec(dllexport)
   #else
      #define XXGRAPH_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXGraphExportDefH
