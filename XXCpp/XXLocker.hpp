#ifndef XXLockerHPP
#define XXLockerHPP

#include "XXLocker.h"

template <XX::CompileTimeString tag>
bool XX::Locker<tag>::lock = false;

template <XX::CompileTimeString tag>
XX::Locker<tag>::Locker()
{
   lock = true;
}

template <XX::CompileTimeString tag>
XX::Locker<tag>::~Locker()
{
   lock = false;
}

template <XX::CompileTimeString tag>
bool XX::Locker<tag>::engaged()
{
   return lock;
}

template <XX::CompileTimeString tag>
bool XX::Locker<tag>::doOnce()
{
   static bool done = false;
   if (!done)
   {
      done = true;
      return true;
   }
   return false;
}

#endif // NOT XXLockerHPP
