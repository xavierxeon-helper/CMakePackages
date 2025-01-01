#ifndef IOChannelHPP
#define IOChannelHPP

#include "IOChannel.h"

#include <QTextStream>

inline IOChannel::IOChannel(QObject* parent, PrintFunction printFunction)
   : QIODevice(parent)
   , printFunction(printFunction)
{
   open(QIODevice::WriteOnly);
}

inline QTextStream IOChannel::stream()
{
   return QTextStream(this);
}

inline qint64 IOChannel::readData(char* data, qint64 maxSize)
{
   Q_UNUSED(data)
   Q_UNUSED(maxSize)

   return 0;
}

inline qint64 IOChannel::writeData(const char* data, qint64 maxSize)
{
   if (printFunction)
      printFunction(QString::fromUtf8(data));

   return maxSize;
}

#endif // NOT IOChannelHPP
