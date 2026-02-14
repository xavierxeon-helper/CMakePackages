#ifndef XXNetworkToolsH
#define XXNetworkToolsH

#include "XXNetworkExportDef.h"

#include <QString>

namespace XX
{
   namespace Network
   {
      //! @brief Network utility functions

      struct XXNETWORK_DECLSPEC Tools
      {
         static bool isInSubnet(const QString& ipAddress, int netmask = 24);
      };
   } // namespace Network
} // namespace XX

#endif // NOT XXNetworkToolsH
