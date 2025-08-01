#include "SampleReader.h"

Sample::Reader::Reader(const QString& fileName)
   : Sample::Wave()
   , playhead(0)
   , channels()
{
   load(fileName);

   channels = deinterlace(interlacedContent, meta.noOfChannels);
}

const Sample::Meta& Sample::Reader::getMeta() const
{
   return meta;
}

Sample::Data Sample::Reader::get(const size_t& position, const size_t& numberOfSamples, const uint8_t& channel) const
{
   const Data& target = channels[channel];
   const Data chunk = target.mid(position, numberOfSamples);
   return chunk;
}

size_t Sample::Reader::getPlayhead() const
{
   return playhead;
}

void Sample::Reader::resetPlayhead()
{
   playhead = 0;
}

bool Sample::Reader::atEnd() const
{
   return false;
}

void Sample::Reader::advancePlayhead()
{
   playhead++;
}

float Sample::Reader::getSound(const uint8_t& channel) const
{
   return get(playhead, 1, channel).front();
}
