#ifndef XXFunctionCallerHPP
#define XXFunctionCallerHPP

#include "XXFunctionCaller.h"

#include <iostream>

#include "XXLocker.h"

template <XX::CompileTimeString tag>
QList<XX::Function::Caller<tag>*> XX::Function::Caller<tag>::instances;

template <XX::CompileTimeString tag>
XX::Function::Caller<tag>::Caller()
   : AbstractCaller()
{
   if (Locker<tag>::engaged())
      std::cerr << "LOCKED: Function::Caller<" << tag.text() << "> " << this << " will not be registered." << std::endl;
   else
      instances.append(this);
}

template <XX::CompileTimeString tag>
XX::Function::Caller<tag>::~Caller()
{
   if (Locker<tag>::engaged())
      std::cerr << "LOCKED: Function::Caller<" << tag.text() << "> " << this << " will not be unregistered." << std::endl;
   else
      instances.removeAll(this);
}

template <XX::CompileTimeString tag>
template <XX::Function::CallerClass TargetClass, typename... Args>
void XX::Function::Caller<tag>::callOnAll(void (TargetClass::*function)(Args...), Args... values)
{
   Locker<tag> locker; // prevent removal or additions of instances while iterating
   for (Caller* instance : std::as_const(instances))
   {
      TargetClass* target = static_cast<TargetClass*>(instance);
      std::invoke(function, target, values...);
   }
}

template <XX::CompileTimeString tag>
template <XX::Function::CallerClass TargetClass>
void XX::Function::Caller<tag>::callOnAll(void (TargetClass::*function)())
{
   Locker<tag> locker; // prevent removal or additions of instances while iterating
   for (Caller* instance : std::as_const(instances))
   {
      TargetClass* target = static_cast<TargetClass*>(instance);
      std::invoke(function, target);
   }
}

template <XX::CompileTimeString tag>
size_t XX::Function::Caller<tag>::instanceCount()
{
   return instances.size();
}

#endif // NOT XXFunctionCallerHPP
