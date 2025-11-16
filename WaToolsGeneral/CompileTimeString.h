#ifndef CompileTimeStringH
#define CompileTimeStringH

#include <string>

template <size_t N>
struct CompileTimeString
{
   constexpr CompileTimeString(const char (&str)[N]);
   char value[N];

   std::string text() const;
};

#ifndef CompileTimeStringHPP
#include "CompileTimeString.hpp"
#endif // NOT CompileTimeStringHPP

#endif // NOT CompileTimeStringH
