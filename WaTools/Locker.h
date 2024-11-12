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

private:
   static bool lock;
};

#ifndef LockerHPP
#include "Locker.hpp"
#endif // NOT LockerHPP

#endif // NOT LockerH
