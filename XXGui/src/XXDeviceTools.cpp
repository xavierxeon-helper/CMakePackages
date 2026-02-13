#include "XXDeviceTools.h"

#include <QGuiApplication>
#include <QStyleHints>

QSize XX::DeviceTools::getSize(const DeviceIdentifier& deviceId)
{
   switch (deviceId)
   {
      case iPadMini:
         return QSize(1133, 695);
      case iPadPro13:
         return QSize(1376, 975);
      default:
         return QSize(0, 0);
   }
}

void XX::DeviceTools::fixSize(QQmlApplicationEngine* engine, const DeviceIdentifier& deviceId)
{
   QObject* mainWindow = engine->rootObjects().first();

   const QSize size = getSize(deviceId);

   mainWindow->setProperty("minimumWidth", size.width());
   mainWindow->setProperty("maximumWidth", size.width());

   mainWindow->setProperty("minimumHeight", size.height());
   mainWindow->setProperty("maximumHeight", size.height());
}

void XX::DeviceTools::forceDisplayMode(bool light)
{
   const Qt::ColorScheme scheme = light ? Qt::ColorScheme::Light : Qt::ColorScheme::Dark;
   QGuiApplication::styleHints()->setColorScheme(scheme);
}
