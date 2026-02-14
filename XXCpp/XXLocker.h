#ifndef XXLockerH
#define XXLockerH

#include "XXCompileTimeString.h"

namespace XX
{
   //! @brief a locker class to prevent executions of code
   //! @ingroup XXCpp

   template <CompileTimeString tag>
   class Locker
   {
   public:
      //! @brief set the locker active
      Locker();
      ~Locker();

   public:
      //! @brief check if some instance of a locker is active
      static bool engaged();
      //! @brief gives the ability to do something once
      static bool doOnce();

   private:
      static bool lock;
   };
} // namespace XX

#ifndef XXLockerHPP
#include "XXLocker.hpp"
#endif // NOT XXLockerHPP

#endif // NOT XXLockerH
