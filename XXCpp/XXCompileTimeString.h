#ifndef XXCompileTimeStringH
#define XXCompileTimeStringH

#include <string>

namespace XX
{
   //! @brief use a string as a template arguemnt
   //! @ingroup XXCpp

   template <size_t N>
   struct CompileTimeString
   {
      constexpr CompileTimeString(const char (&str)[N]);
      char value[N];

      std::string text() const;
   };
} // namespace XX

#ifndef XXCompileTimeStringHPP
#include "XXCompileTimeString.hpp"
#endif // NOT XXCompileTimeStringHPP

#endif // NOT XXCompileTimeStringH
