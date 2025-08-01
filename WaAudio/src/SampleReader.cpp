#include "SampleReader.h"

Sample::Reader::Reader(const QString& fileName)
   : Sample::Wave()
   , playhead(0)
{
   load(fileName);
}

const Sample::Meta& Sample::Reader::getMeta() const
{
   return meta;
}

Sample::Data Sample::Reader::get(const size_t& position, const size_t& numberOfSamples)
{
   return Sample::Data();
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

float Sample::Reader::getSound(uint8_t channel)
{
   return get(playhead, 1).front();
}
