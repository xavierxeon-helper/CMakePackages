#include "XXDeviceTools.h"

#include <QGuiApplication>
#include <QStyleHints>

#include <XXSettings.h>

QSize XX::DeviceTools::getSize(const DeviceIdentifier& deviceId)
{
   switch (deviceId)
   {
      case iPadMini:
         return QSize(1133, 687);
      case iPadPro13:
         return QSize(1376, 975);
      case NoteAir5C:
         return QSize(1323, 992);
      default:
         return QSize(0, 0);
   }
}

void XX::DeviceTools::fixSize(QQmlApplicationEngine* engine, const DeviceIdentifier& deviceId)
{
   const QList<QObject*> objectList = engine->rootObjects();
   if (objectList.isEmpty())
      return;

   QObject* mainWindow = objectList.first();

   const QSize size = getSize(deviceId);

   mainWindow->setProperty("minimumWidth", size.width());
   mainWindow->setProperty("maximumWidth", size.width());

   mainWindow->setProperty("minimumHeight", size.height());
   mainWindow->setProperty("maximumHeight", size.height());
}

void XX::DeviceTools::fixSize(QWindow* window, const DeviceIdentifier& deviceId)
{
   const QSize size = getSize(deviceId);

   window->setMinimumSize(size);
   window->setMaximumSize(size);
}

void XX::DeviceTools::forceDisplayMode(bool light)
{
   const Qt::ColorScheme scheme = light ? Qt::ColorScheme::Light : Qt::ColorScheme::Dark;
   QGuiApplication::styleHints()->setColorScheme(scheme);
}

void XX::DeviceTools::restorePostions(QWindow* window)
{
   XX::Settings settings;
   const int x = settings.value("Window/x", window->x()).toInt();
   const int y = settings.value("Window/y", window->y()).toInt();
   window->setPosition(x, y);
}

void XX::DeviceTools::savePostions(QWindow* window)
{
   XX::Settings settings;
   settings.setValue("Window/x", window->x());
   settings.setValue("Window/y", window->y());
}
