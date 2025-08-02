#ifndef SampleWriterH
#define SampleWriterH

#include "SampleWave.h"

namespace Sample
{
   class Writer : public Wave
   {
   public:
      Writer(const uint8_t& numerOfChannels);

   public:
      void clear();
      void append(const Channels& channels);
      void save(const QString& fileName, const uint16_t sampleRate = 48000);

   private:
      const uint8_t numerOfChannels;
      Channels buffer;
   };
} // namespace Sample

#endif // NOT SampleWriterH
