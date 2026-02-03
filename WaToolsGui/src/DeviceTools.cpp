#include "DeviceTools.h"

QSize DeviceTools::getSize(const DeviceIdentifier& deviceId)
{
   switch (deviceId)
   {
      case iPadMini:
         return QSize(1133, 695);
      default:
         return QSize(0, 0);
   }
}

void DeviceTools::fixSize(QQmlApplicationEngine* engine, const DeviceIdentifier& deviceId)
{
   QObject* mainWindow = engine->rootObjects().first();

   const QSize size = getSize(deviceId);

   mainWindow->setProperty("minimumWidth", size.width());
   mainWindow->setProperty("maximumWidth", size.width());

   mainWindow->setProperty("minimumHeight", size.height());
   mainWindow->setProperty("maximumHeight", size.height());
}