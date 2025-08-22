#ifndef SharedH
#define SharedH

#include "CompileTimeString.h"

#include <QStandardPaths>

template <CompileTimeString AppName>
struct Shared
{
   static QString appName();
   /// @brief generates a file name for a shared resource
   static QString compileSharedFileName(const QString& suffix, const QStandardPaths::StandardLocation& location = QStandardPaths::HomeLocation);
   /// @brief generates a name for a local socket
   static QString socketName();
   /// @brief check if local server is active
   static bool isServerActive();
   /// @brief starts the application if not already running
   static void startApplication();
};

#ifndef SharedHPP
#include "Shared.hpp"
#endif // NOT SharedHPP

#endif // NOT SharedH
