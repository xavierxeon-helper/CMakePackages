#include "SampleAbstract.h"

Sample::Abstract::Abstract()
   : interlacedContent()
   , meta()
{
}

Sample::Data Sample::Abstract::interlace(const Channels& input)
{
   const uint8_t numberOfChannels = input.size();
   const size_t numberOfSamples = input.at(0).size();

   Data output;
   for (size_t inIndex = 0; inIndex < numberOfSamples; inIndex++)
   {
      for (uint8_t channel = 0; channel < numberOfChannels; channel++)
      {
         const Data& channelData = input.at(channel);
         const float value = channelData.at(inIndex);
         output.push_back(value);
      }
   }
   return output;
}

Sample::Channels Sample::Abstract::deinterlace(const Data& input, const uint8_t numberOfChannels)
{
   Channels output(numberOfChannels, Data());
   if (0 != input.size() % numberOfChannels)
      return output;

   const size_t numberOfSamples = input.size() / numberOfChannels;
   for (size_t outIndex = 0; outIndex < numberOfSamples; outIndex++)
   {
      for (uint8_t channel = 0; channel < numberOfChannels; channel++)
      {
         const size_t inIndex = channel + (outIndex * numberOfChannels);
         const float value = input[inIndex];
         output[channel].push_back(value);
      }
   }

   return output;
}
