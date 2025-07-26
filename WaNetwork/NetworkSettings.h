#ifndef NetworkSettingsH
#define NetworkSettingsH

namespace Network
{
   class Settings
   {
   public:
      Settings();

   public:
      static void setUseExceptions(bool enabled);
      static void setVerbose(bool enabled);

      static bool useExceptions();
      static bool verbose();

   private:
      static bool shallUseExceptions;
      static bool isVerbose;
   };
} // namespace Network

#ifndef NetworkSettingsHPP
#include "NetworkSettings.hpp"
#endif // NOT NetworkSettingsHPP

#endif // NOT NetworkSettingsH
