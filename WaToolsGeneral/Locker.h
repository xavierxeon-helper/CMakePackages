#ifndef LockerH
#define LockerH

#include "CompileTimeString.h"

template <CompileTimeString tag>
class Locker
{
public:
   /// @brief set the locker active
   Locker();
   ~Locker();

public:
   /// @brief check if some instance of a locker is active
   static bool engaged();
   /// @brief gives the ability to do something once
   static bool doOnce();

private:
   static bool lock;
};

#ifndef LockerHPP
#include "Locker.hpp"
#endif // NOT LockerHPP

#endif // NOT LockerH
