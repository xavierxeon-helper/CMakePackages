#ifndef XXDeviceToolsH
#define XXDeviceToolsH

#include "XXGuiExportDef.h"
#include <QObject>

#include <QQmlApplicationEngine>
#include <QSize>

namespace XX
{
   class XXGUI_DECLSPEC DeviceTools
   {
      Q_GADGET

   public:
      enum DeviceIdentifier
      {
         iPadMini,
         iPadPro13
      };
      Q_ENUM(DeviceIdentifier)

   public:
      static QSize getSize(const DeviceIdentifier& deviceId);
      static void fixSize(QQmlApplicationEngine* engine, const DeviceIdentifier& deviceId);

      static void forceDisplayMode(bool light = true);
   };
} // namespace XX

#endif // NOT XXDeviceToolsH
