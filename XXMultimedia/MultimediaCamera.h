#ifndef MultimediaCameraH
#define MultimediaCameraH

#include "XXMultimediaExportDef.h"
#include <QMediaCaptureSession>

#include <QCamera>
#include <QStandardItemModel>

namespace Multimedia
{
   //! @brief provide access to the system cameras
   //! @ingroup XXMultimedia

   class XXMULTIMEDIA_DECLSPEC Camera : public QMediaCaptureSession
   {
      Q_OBJECT

   public:
      enum Roles
      {
         PathRole = Qt::UserRole + 1,
         ResRole,
         FormatRole
      };

   public:
      Camera(QObject* parent);

   public:
      void setDeviceIndex(const QString& path, const QSize& size);
      QStandardItemModel* compileDeviceModel();

   private:
      static const QList<int> formatList;
      const QList<QCameraDevice> cameraList;
      QCamera* camera;
   };
} // namespace Multimedia

#endif // NOT MultimediaCameraH
