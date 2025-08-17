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
      static bool useExceptions();

      void setVerbose(bool enabled);
      bool verbose() const;

   private:
      static bool shallUseExceptions;
      bool isVerbose;
   };
} // namespace Network

#endif // NOT NetworkSettingsH
