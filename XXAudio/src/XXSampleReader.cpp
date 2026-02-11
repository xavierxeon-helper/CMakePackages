#include "XXSampleReader.h"

XX::Sample::Reader::Reader(const QString& fileName)
   : Sample::Wave()
   , playhead(0)
   , channels()
{
   load(fileName);

   channels = deinterlace(interlacedContent, meta.noOfChannels);
}

const XX::Sample::Meta& XX::Sample::Reader::getMeta() const
{
   return meta;
}

XX::Sample::Data XX::Sample::Reader::getChannel(const uint8_t& channel) const
{
   const Data& target = channels[channel];
   return target;
}

XX::Sample::Data XX::Sample::Reader::get(const size_t& position, const size_t& numberOfSamples, const uint8_t& channel) const
{
   const Data& target = channels[channel];
   const Data chunk = target.mid(position, numberOfSamples);
   return chunk;
}

size_t XX::Sample::Reader::getPlayhead() const
{
   return playhead;
}

void XX::Sample::Reader::resetPlayhead()
{
   playhead = 0;
}

bool XX::Sample::Reader::atEnd() const
{
   return false;
}

void XX::Sample::Reader::advancePlayhead()
{
   playhead++;
}

float XX::Sample::Reader::getSound(const uint8_t& channel) const
{
   return get(playhead, 1, channel).front();
}
