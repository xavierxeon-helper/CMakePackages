#include "XXNetworkSettings.h"

bool XX::Network::Settings::shallUseExceptions = false;

XX::Network::Settings::Settings()
   : isVerbose(false)
{
}

void XX::Network::Settings::setUseExceptions(bool enabled)
{
   shallUseExceptions = enabled;
}

void XX::Network::Settings::setVerbose(bool enabled)
{
   isVerbose = enabled;
}

bool XX::Network::Settings::useExceptions()
{
   return shallUseExceptions;
}

bool XX::Network::Settings::verbose() const
{
   return isVerbose;
}
