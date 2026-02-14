#ifndef XXWaToolCppExportDefH
#define XXWaToolCppExportDefH

//! @addtogroup XXCpp

// clang-format off
#if defined(__unix) || defined(__QNXNTO__) || defined(__APPLE__)
   #define XXCPP_DECLSPEC
#else
   #ifdef EXTENSION_XXCPP      
      #define XXCPP_DECLSPEC __declspec(dllexport)
   #else
      #define XXCPP_DECLSPEC __declspec(dllimport)
   #endif
#endif
// clang-format on

#endif // NOT XXWaToolCppExportDefH
