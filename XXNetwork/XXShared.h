#ifndef XXSharedH
#define XXSharedH

#include "XXCompileTimeString.h"

#include <QStandardPaths>

namespace XX
{
   //! @brief tools for shared application
   //! @ingroup XXNetwork

   template <CompileTimeString AppName>
   struct Shared
   {
      static QString appName();
      //! @brief generates a file name for a shared resource
      static QString compileSharedFileName(const QString& suffix, const QStandardPaths::StandardLocation& location = QStandardPaths::HomeLocation);
      //! @brief generates a name for a local socket
      static QString socketName();
      //! @brief check if local server is active
      static bool isServerActive();
      //! @brief starts the application if not already running
      static void startApplication();
   };
} // namespace XX

#ifndef XXSharedHPP
#include "XXShared.hpp"
#endif // NOT XXSharedHPP

#endif // NOT XXSharedH
