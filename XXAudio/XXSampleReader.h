#ifndef XXSampleOscilatorH
#define XXSampleOscilatorH

#include "XXAudioExportDef.h"
#include "XXSampleWave.h"

#include <QString>

namespace XX
{
   namespace Sample
   {
      // wav file only!
      class XXAUDIO_DECLSPEC Reader : public Wave
      {
      public:
         Reader(const QString& fileName);

      public:
         const Meta& getMeta() const;
         Data getChannel(const uint8_t& channel) const;
         Data get(const size_t& position, const size_t& numberOfSamples, const uint8_t& channel) const;

         size_t getPlayhead() const;
         void resetPlayhead();
         bool atEnd() const;
         void advancePlayhead();

         float getSound(const uint8_t& channel) const;

      private:
         Channels channels;
         size_t playhead;
      };
   } // namespace Sample
} // namespace XX

#endif // NOT XXSampleOscilatorH
