#ifndef IOChannelHPP
#define IOChannelHPP

#include "IOChannel.h"

inline IOChannel::IOChannel(Target* target, int channelId)
   : QIODevice(nullptr)
   , target(target)
   , channelId(channelId)
{
   open(QIODevice::WriteOnly);
}

inline qint64 IOChannel::readData(char* data, qint64 maxSize)
{
   Q_UNUSED(data)
   Q_UNUSED(maxSize)

   return 0;
}

inline qint64 IOChannel::writeData(const char* data, qint64 maxSize)
{
   target->print(data, channelId);
   return maxSize;
}

#endif // NOT IOChannelHPP
