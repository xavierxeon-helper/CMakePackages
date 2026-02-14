#ifndef XXSampleWriterH
#define XXSampleWriterH

#include "XXAudioExportDef.h"
#include "XXSampleWave.h"

namespace XX
{
   namespace Sample
   {
      //! @brief writer for audio samples
      //! wav file only!
      //! @ingroup XXAudio

      class XXAUDIO_DECLSPEC Writer : public Wave
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
} // namespace XX

#endif // NOT XXSampleWriterH
