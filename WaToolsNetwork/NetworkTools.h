#ifndef NetworkToolsH
#define NetworkToolsH

#include "WaToolsNetworkExportDef.h"

#include <QString>

namespace Network
{
   struct WATOOLSNETWORK_DECLSPEC Tools
   {
      static bool isInSubnet(const QString& ipAddress, int netmask = 24);
   };
} // namespace Network

#endif // NOT NetworkToolsH
