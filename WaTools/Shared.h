#ifndef SharedH
#define SharedH

#include "CompileTimeString.h"

template <CompileTimeString AppName>
struct Shared
{
   static QString appName();
   static QString compileSharedFileName(const QString& suffix);

   static bool isServerActive();
   static void startApplication();
};

#ifndef SharedHPP
#include "Shared.hpp"
#endif // NOT SharedHPP

#endif // NOT SharedH
