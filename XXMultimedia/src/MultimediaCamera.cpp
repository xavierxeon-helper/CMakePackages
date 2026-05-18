#include "MultimediaCamera.h"

#include <QGuiApplication>
#include <QMediaDevices>
#include <QPermissions>

const QList<int> Multimedia::Camera::formatList = {
   QVideoFrameFormat::Format_YUYV,
   QVideoFrameFormat::Format_NV12};

Multimedia::Camera::Camera(QObject* parent)
   : QMediaCaptureSession(parent)
   , cameraList(QMediaDevices::videoInputs())
   , camera(nullptr)
{
   camera = new QCamera(this);
   setCamera(camera);
}

void Multimedia::Camera::setDeviceIndex(const QString& path, const QSize& size)
{
   auto createCamera = [&, path, size](const QPermission& permission)
   {
      if (Qt::PermissionStatus::Granted != permission.status())
      {
         qWarning() << "camera permission not granted";
         return;
      }

      for (const QCameraDevice& cameraDevice : cameraList)
      {
         const QString testPath = cameraDevice.id();
         if (testPath != path)
            continue;

         for (const QCameraFormat& format : cameraDevice.videoFormats())
         {
            const QVideoFrameFormat::PixelFormat pixelFormat = format.pixelFormat();
            if (!formatList.contains(pixelFormat))
               continue;

            const QSize testSize = format.resolution();
            if (testSize != size)
               continue;

            camera->setCameraDevice(cameraDevice);
            camera->setCameraFormat(format);

            camera->start();

            qDebug() << "camera started";
            return;
         }
      }
   };

   QGuiApplication::instance()->requestPermission(QCameraPermission{}, createCamera);
}

QStandardItemModel* Multimedia::Camera::compileDeviceModel()
{
   QStandardItemModel* model = new QStandardItemModel(this);

   int index = 0;

   auto itemExists = [&](const QString& text)
   {
      for (int row = 0; row < model->invisibleRootItem()->rowCount(); row++)
      {
         QStandardItem* test = model->invisibleRootItem()->child(row, 0);
         if (test->text() == text)
            return true;
      }
      return false;
   };

   for (const QCameraDevice& cameraDevice : cameraList)
   {
      const QString path = cameraDevice.id();
      const QString name = cameraDevice.description();

      for (const QCameraFormat& format : cameraDevice.videoFormats())
      {
         const QVideoFrameFormat::PixelFormat pixelFormat = format.pixelFormat();
         if (!formatList.contains(pixelFormat))
            continue;

         const QSize size = format.resolution();
         const QString text = QString("%1 [%2x%3]").arg(name).arg(size.width()).arg(size.height());
         if (itemExists(text))
            continue;

         QStandardItem* item = new QStandardItem(text);
         item->setData(path, PathRole);
         item->setData(size, ResRole);
         item->setData(pixelFormat, FormatRole);

         model->invisibleRootItem()->appendRow(item);
      }

      index++;
   }

   return model;
}
