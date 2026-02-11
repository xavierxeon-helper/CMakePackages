#include "XXSampleWriter.h"

#include <QDebug>

Sample::Writer::Writer(const uint8_t& numerOfChannels)
   : Wave()
   , numerOfChannels(numerOfChannels)
   , buffer()
{
   clear();
}

void Sample::Writer::clear()
{
   buffer = Sample::Channels(numerOfChannels, Sample::Data());
}

void Sample::Writer::append(const Channels& channels)
{
   if (channels.size() != buffer.size())
   {
      qWarning() << __FUNCTION__ << "channels size mismatch: expected" << buffer.size() << "got" << channels.size();
      return;
   }

   size_t dataLength = 0;
   for (int channelIndex = 0; channelIndex < buffer.size(); channelIndex++)
   {
      const Sample::Data& data = channels[channelIndex];
      if (0 == channelIndex)
      {
         dataLength = data.size();
      }
      else if (data.size() != dataLength)
      {
         qWarning() << __FUNCTION__ << "data size mismatch for channel" << channelIndex << ": expected" << dataLength << "got" << data.size();
      }

      buffer[channelIndex].append(data);
   }
}

void Sample::Writer::save(const QString& fileName, const uint16_t sampleRate)
{
   meta.sampleRate = sampleRate;
   meta.noOfChannels = numerOfChannels;
   meta.numberOfSamples = buffer[0].size();

   interlacedContent = interlace(buffer);
   Wave::save(fileName);
}
