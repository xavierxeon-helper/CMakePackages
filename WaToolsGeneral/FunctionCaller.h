#ifndef FunctionCallerH
#define FunctionCallerH

#include "CompileTimeString.h"

namespace Function
{
   class AbstrractCaller
   {
   protected:
      AbstrractCaller() = default;
   };

   template <typename T>
   concept CallerClass = requires(T instance) //
   {
      std::is_base_of<AbstrractCaller, T>::value;
   };

   /// @brief allows an instance of derived class to call functions on all other instance (ncluding itself)
   template <CompileTimeString tag>
   class Caller : public AbstrractCaller
   {
   public:
      Caller();
      virtual ~Caller() = 0;

   protected:
      template <CallerClass TargetClass, typename... Args>
      static void callOnAll(void (TargetClass::*function)(Args...), Args... values);

      template <CallerClass TargetClass>
      static void callOnAll(void (TargetClass::*function)());

   private:
      static QList<Caller*> instances;
   };
} // namespace Function

#ifndef FunctionCallerHPP
#include "FunctionCaller.hpp"
#endif // NOT FunctionCallerHPP

#endif // NOT FunctionCallerH
