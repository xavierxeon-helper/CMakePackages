#ifndef NetworkSettingsHPP
#define NetworkSettingsHPP

#include "NetworkSettings.h"

inline bool Network::Settings::shallUseExceptions = false;

inline Network::Settings::Settings()
   : isVerbose(false)
{
}

inline void Network::Settings::setUseExceptions(bool enabled)
{
   shallUseExceptions = enabled;
}

inline void Network::Settings::setVerbose(bool enabled)
{
   isVerbose = enabled;
}

inline bool Network::Settings::useExceptions()
{
   return shallUseExceptions;
}

inline bool Network::Settings::verbose() const
{
   return isVerbose;
}

#endif // NOT NetworkSettingsHPP
