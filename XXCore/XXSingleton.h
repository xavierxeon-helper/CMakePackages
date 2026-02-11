#ifndef XXSingletonH
#define XXSingletonH

namespace XX
{
   template <typename InstanceClass>
   class Singleton
   {
   public:
      Singleton();
      virtual ~Singleton();

   public:
      static InstanceClass* instance();

   private:
      static InstanceClass* me;
   };
} // namespace XX

#ifndef XXSingletonHPP
#include "XXSingleton.hpp"
#endif // NOT XXSingletonHPP

#endif // NOT XXSingletonH
