#ifndef XXNullDeviceH
#define XXNullDeviceH

#include "XXCoreExportDef.h"
#include <QIODevice>

namespace XX
{
   class XXCORE_DECLSPEC NullDevice : public QIODevice
   {
      Q_OBJECT

   public:
      NullDevice(QObject* parent = nullptr);

   public:
      qint64 readData(char*, qint64) override;
      qint64 writeData(const char*, qint64) override;
   };
} // namespace XX

#endif // NOT XXNullDeviceH
