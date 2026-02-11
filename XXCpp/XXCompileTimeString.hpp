#ifndef XXCompileTimeStringHPP
#define XXCompileTimeStringHPP

#include "XXCompileTimeString.h"

#include <algorithm>

template <size_t N>
constexpr XX::CompileTimeString<N>::CompileTimeString(const char (&str)[N])
{
   std::copy_n(str, N, value);
}

template <size_t N>
std::string XX::CompileTimeString<N>::text() const
{
   return std::string(value);
}

#endif // NOT XXCompileTimeStringHPP
