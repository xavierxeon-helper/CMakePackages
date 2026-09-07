#include "XXNullDevice.h"

XX::NullDevice::NullDevice(QObject* parent)
   : QIODevice(parent)
{
   open(QIODevice::ReadWrite);
}

qint64 XX::NullDevice::readData(char*, qint64)
{
   // Always EOF
   return 0;
}

qint64 XX::NullDevice::writeData(const char*, qint64 len)
{
   // Discard data, report success
   return len;
}
