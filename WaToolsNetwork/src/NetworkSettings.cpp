#include "NetworkSettings.h"

bool Network::Settings::shallUseExceptions = false;

Network::Settings::Settings()
   : isVerbose(false)
{
}

void Network::Settings::setUseExceptions(bool enabled)
{
   shallUseExceptions = enabled;
}

void Network::Settings::setVerbose(bool enabled)
{
   isVerbose = enabled;
}

bool Network::Settings::useExceptions()
{
   return shallUseExceptions;
}

bool Network::Settings::verbose() const
{
   return isVerbose;
}
