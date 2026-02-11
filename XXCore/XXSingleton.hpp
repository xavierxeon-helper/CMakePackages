#ifndef XXSingletonHPP
#define XXSingletonHPP

#include "XXSingleton.h"

template <typename InstanceClass>
InstanceClass* XX::Singleton<InstanceClass>::me = nullptr;

template <typename InstanceClass>
XX::Singleton<InstanceClass>::Singleton()
{
   me = static_cast<InstanceClass*>(this);
}

template <typename InstanceClass>
XX::Singleton<InstanceClass>::~Singleton()
{
   me = nullptr;
}

template <typename InstanceClass>
InstanceClass* XX::Singleton<InstanceClass>::instance()
{
   return me;
}

#endif // NOT XXSingletonHPP
