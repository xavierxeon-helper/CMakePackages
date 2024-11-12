#ifndef LockerHPP
#define LockerHPP

#include "Locker.h"

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

#endif // NOT LockerHPP
