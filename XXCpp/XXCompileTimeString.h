#ifndef XXCompileTimeStringH
#define XXCompileTimeStringH

#include <string>

template <size_t N>
struct CompileTimeString
{
   constexpr CompileTimeString(const char (&str)[N]);
   char value[N];

   std::string text() const;
};

#ifndef XXCompileTimeStringHPP
#include "CompileTimeString.hpp"
#endif // NOT XXCompileTimeStringHPP

#endif // NOT XXCompileTimeStringH
