#include "XXNetworkTools.h"

#include <QNetworkInterface>

bool XX::Network::Tools::isInSubnet(const QString& ipAddress, int netmask)
{
   const QHostAddress network(ipAddress);
   for (const QHostAddress& address : QNetworkInterface::allAddresses())
   {
      if (address.isInSubnet(network, netmask))
         return true;
   }

   return false;
}
