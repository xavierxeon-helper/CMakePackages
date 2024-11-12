#ifndef CompileTimeStringH
#define CompileTimeStringH

#include <algorithm>

template <size_t N>
struct CompileTimeString
{
   constexpr CompileTimeString(const char (&str)[N]);
   char value[N];
};

#ifndef CompileTimeStringHPP
#include "CompileTimeString.hpp"
#endif // NOT CompileTimeStringHPP

#endif // NOT CompileTimeStringH
