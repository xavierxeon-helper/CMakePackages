#ifndef DeviceToolsH
#define DeviceToolsH

#include "XXGuiExportDef.h"
#include <QObject>

#include <QQmlApplicationEngine>
#include <QSize>

class XXGUI_DECLSPEC DeviceTools
{
   Q_GADGET

public:
   enum DeviceIdentifier
   {
      iPadMini
   };
   Q_ENUM(DeviceIdentifier)

public:
   static QSize getSize(const DeviceIdentifier& deviceId);
   static void fixSize(QQmlApplicationEngine* engine, const DeviceIdentifier& deviceId);

   static void forceDisplayMode(bool light = true);
};

#endif // NOT DeviceToolsH
