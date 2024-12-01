#ifndef LocalServerH
#define LocalServerH

#include "CompileTimeString.h"

template <CompileTimeString Tag>
struct LocalServer
{
   static QString tagName();
   static QString compileSharedFileName();
   static QString compileSocketName();
   static bool isServerActive();
   static void startApplication();
};

#ifndef LocalServerHPP
#include "LocalServer.hpp"
#endif // NOT LocalServerHPP

#endif // NOT LocalServerH
