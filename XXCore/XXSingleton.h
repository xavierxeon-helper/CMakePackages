#ifndef XXSingletonH
#define XXSingletonH

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

#ifndef XXSingletonHPP
#include "XXSingleton.hpp"
#endif // NOT XXSingletonHPP

#endif // NOT XXSingletonH
