#ifndef XXToolCppExportDefH
#define XXToolCppExportDefH

/*!
@defgroup XXCpp Cpp 
@includedoc{doc} XXCpp/XXCpp.md

@defgroup CompilerTests
@{
@ingroup XXCpp
@brief template test functions
@}

@defgroup Functions
@{
@ingroup XXCpp
@brief Helper functions
@}
*/

// clang-format off
#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)
   #define XXCPP_DECLSPEC
#else
   #ifdef EXTENSION_XXCPP      
      #define XXCPP_DECLSPEC __declspec(dllexport)
   #else
      #define XXCPP_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXToolCppExportDefH
