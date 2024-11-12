#ifndef CompileTimeStringHPP
#define CompileTimeStringHPP

#include "CompileTimeString.h"

template <size_t N>
constexpr CompileTimeString<N>::CompileTimeString(const char (&str)[N])
{
   std::copy_n(str, N, value);
}

#endif // NOT CompileTimeStringHPP