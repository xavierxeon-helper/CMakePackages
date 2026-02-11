#ifndef XXCompileTimeStringH
#define XXCompileTimeStringH

#include <string>

namespace XX
{
   template <size_t N>
   struct CompileTimeString
   {
      constexpr CompileTimeString(const char (&str)[N]);
      char value[N];

      std::string text() const;
   };
} // namespace XX

#ifndef XXCompileTimeStringHPP
#include "CompileTimeString.hpp"
#endif // NOT XXCompileTimeStringHPP

#endif // NOT XXCompileTimeStringH
