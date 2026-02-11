#ifndef FunctionCallerH
#define FunctionCallerH

#include "XXCompileTimeString.h"

#include <QList>

namespace Function
{
   class AbstractCaller
   {
   protected:
      AbstractCaller() = default;
   };

   template <typename T>
   concept CallerClass = requires(T instance) //
   {
      std::is_base_of<AbstractCaller, T>::value;
   };

   /// @brief allows an instance of derived class to call functions on all other instance (ncluding itself)

   template <CompileTimeString tag>
   class Caller : public AbstractCaller
   {
   public:
      Caller();
      virtual ~Caller() = 0;

   protected:
      template <CallerClass TargetClass, typename... Args>
      static void callOnAll(void (TargetClass::*function)(Args...), Args... values);

      template <CallerClass TargetClass>
      static void callOnAll(void (TargetClass::*function)());

      static size_t instanceCount();

   private:
      static QList<Caller*> instances;
   };
} // namespace Function

#ifndef FunctionCallerHPP
#include "XXFunctionCaller.hpp"
#endif // NOT FunctionCallerHPP

#endif // NOT FunctionCallerH
