#ifndef LockerHPP
#define LockerHPP

#include "XXLocker.h"

template <CompileTimeString tag>
bool Locker<tag>::lock = false;

template <CompileTimeString tag>
Locker<tag>::Locker()
{
   lock = true;
}

template <CompileTimeString tag>
Locker<tag>::~Locker()
{
   lock = false;
}

template <CompileTimeString tag>
bool Locker<tag>::engaged()
{
   return lock;
}

template <CompileTimeString tag>
bool Locker<tag>::doOnce()
{
   static bool done = false;
   if (!done)
   {
      done = true;
      return true;
   }
   return false;
}

#endif // NOT LockerHPP
