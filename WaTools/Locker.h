#ifndef LockerH
#define LockerH

#include "CompileTimeString.h"

template <CompileTimeString tag>
class Locker
{
public:
   Locker();
   ~Locker();

public:
   static bool engaged();
   static bool doOnce();

private:
   static bool lock;
};

#ifndef LockerHPP
#include "Locker.hpp"
#endif // NOT LockerHPP

#endif // NOT LockerH
