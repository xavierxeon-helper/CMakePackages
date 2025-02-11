#ifndef IOChannelHPP
#define IOChannelHPP

#include "IOChannel.h"

#include <QTextStream>

inline IOChannel::IOChannel(QObject* parent)
   : QIODevice(parent)
   , printFunctions()
{
   open(QIODevice::WriteOnly);
}

inline IOChannel::IOChannel(QObject* parent, PrintFunction printFunction)
   : IOChannel(parent)

{
   addPrinter(printFunction);
}

inline QTextStream IOChannel::stream()
{
   return QTextStream(this);
}

inline void IOChannel::addPrinter(PrintFunction printFunction)
{
   printFunctions.append(printFunction);
}

inline qint64 IOChannel::readData(char* data, qint64 maxSize)
{
   Q_UNUSED(data)
   Q_UNUSED(maxSize)

   return 0;
}

inline qint64 IOChannel::writeData(const char* data, qint64 maxSize)
{
   const QString message = QString::fromUtf8(data);
   for (const PrintFunction& printFunction : printFunctions)
      printFunction(message);

   return maxSize;
}

#endif // NOT IOChannelHPP
