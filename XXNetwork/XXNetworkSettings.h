#ifndef XXNetworkSettingsH
#define XXNetworkSettingsH

#include "XXNetworkExportDef.h"

namespace Network
{
   /// @brief Network settings class

   class XXNETWORK_DECLSPEC Settings
   {
   public:
      Settings();

   public:
      static void setUseExceptions(bool enabled);
      static bool useExceptions();

      void setVerbose(bool enabled);
      bool verbose() const;

   private:
      static bool shallUseExceptions;
      bool isVerbose;
   };

} // namespace Network

#endif // NOT XXNetworkSettingsH
