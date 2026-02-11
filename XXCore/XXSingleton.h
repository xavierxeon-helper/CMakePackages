#ifndef SingletonH
#define SingletonH

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

#ifndef SingletonHPP
#include "XXSingleton.hpp"
#endif // NOT SingletonHPP

#endif // NOT SingletonH
