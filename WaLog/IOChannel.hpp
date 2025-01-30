#ifndef IOChannelHPP
#define IOChannelHPP

#include "IOChannel.h"

#include <QTextStream>

inline IOChannel::IOChannel(QObject* parent)
   : QIODevice(parent)
   , printFunction()
{
   open(QIODevice::WriteOnly);
}

inline IOChannel::IOChannel(QObject* parent, PrintFunction printFunction)
   : IOChannel(parent)

{
   setup(printFunction);
}

inline QTextStream IOChannel::stream()
{
   return QTextStream(this);
}

inline void IOChannel::setup(PrintFunction printFunction)
{
   this->printFunction = printFunction;
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
