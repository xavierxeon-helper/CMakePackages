#ifndef NetworkToolsH
#define NetworkToolsH

#include "WaToolsNetworkExportDef.h"

#include <QString>

namespace Network
{
   /// @brief Network utility functions

   struct WATOOLSNETWORK_DECLSPEC Tools
   {
      static bool isInSubnet(const QString& ipAddress, int netmask = 24);
   };
} // namespace Network

#endif // NOT NetworkToolsH
