#ifndef XXGraphExportDefH
#define XXGraphExportDefH

/*!
@defgroup XXGraph Graph 
@includedoc{doc} XXGraph/XXGraph.md
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
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
