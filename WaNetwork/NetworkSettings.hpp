#ifndef NetworkSettingsHPP
#define NetworkSettingsHPP

#include "NetworkSettings.h"

inline bool Network::Settings::shallUseExceptions = false;
inline bool Network::Settings::isVerbose = false;

inline Network::Settings::Settings()
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

inline bool Network::Settings::verbose()
{
   return isVerbose;
}

#endif // NOT NetworkSettingsHPP
