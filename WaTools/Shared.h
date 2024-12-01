#ifndef SharedH
#define SharedH

#include "CompileTimeString.h"

#include <QStandardPaths>


template <CompileTimeString AppName>
struct Shared
{
   static QString appName();
   static QString compileSharedFileName(const QString& suffix, const QStandardPaths::StandardLocation& location = QStandardPaths::HomeLocation);

   static bool isServerActive();
   static void startApplication();
};

#ifndef SharedHPP
#include "Shared.hpp"
#endif // NOT SharedHPP

#endif // NOT SharedH
