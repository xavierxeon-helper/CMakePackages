#ifndef FunctionCallerHPP
#define FunctionCallerHPP

#include "FunctionCaller.h"

template <CompileTimeString tag>
QList<Function::Caller<tag>*> Function::Caller<tag>::instances;

template <CompileTimeString tag>
Function::Caller<tag>::Caller()
   : AbstrractCaller()
{
   instances.append(this);
}

template <CompileTimeString tag>
Function::Caller<tag>::~Caller()
{
   instances.removeAll(this);
}

template <CompileTimeString tag>
template <Function::CallerClass TargetClass, typename... Args>
void Function::Caller<tag>::callOnAll(void (TargetClass::*function)(Args...), Args... values)
{
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
   for (Caller* instance : std::as_const(instances))
   {
      TargetClass* target = static_cast<TargetClass*>(instance);
      std::invoke(function, target);
   }
}
#endif // NOT FunctionCallerHPP
