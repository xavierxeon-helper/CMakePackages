#ifndef FunctionCallerHPP
#define FunctionCallerHPP

#include "FunctionCaller.h"

#include <iostream>

#include "Locker.h"

template <CompileTimeString tag>
QList<Function::Caller<tag>*> Function::Caller<tag>::instances;

template <CompileTimeString tag>
Function::Caller<tag>::Caller()
   : AbstractCaller()
{
   if (Locker<tag>::engaged())
      std::cerr << "LOCKED: Function::Caller<" << tag.text() << "> " << this << " will not be registered." << std::endl;
   else
      instances.append(this);
}

template <CompileTimeString tag>
Function::Caller<tag>::~Caller()
{
   if (Locker<tag>::engaged())
      std::cerr << "LOCKED: Function::Caller<" << tag.text() << "> " << this << " will not be unregistered." << std::endl;
   else
      instances.removeAll(this);
}

template <CompileTimeString tag>
template <Function::CallerClass TargetClass, typename... Args>
void Function::Caller<tag>::callOnAll(void (TargetClass::*function)(Args...), Args... values)
{
   Locker<tag> locker; // prevent removal or additions of instances while iterating
   for (Caller* instance : std::as_const(instances))
   {
      TargetClass* target = static_cast<TargetClass*>(instance);
      std::invoke(function, target, values...);
   }
}

template <CompileTimeString tag>
template <Function::CallerClass TargetClass>
void Function::Caller<tag>::callOnAll(void (TargetClass::*function)())
{
   Locker<tag> locker; // prevent removal or additions of instances while iterating
   for (Caller* instance : std::as_const(instances))
   {
      TargetClass* target = static_cast<TargetClass*>(instance);
      std::invoke(function, target);
   }
}

template <CompileTimeString tag>
size_t Function::Caller<tag>::instanceCount()
{
   return instances.size();
}

#endif // NOT FunctionCallerHPP
