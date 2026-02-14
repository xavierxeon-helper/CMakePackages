#ifndef XXSampleAbstractH
#define XXSampleAbstractH

#include "XXAudioExportDef.h"

#include <QList>
#include <QString>

namespace XX
{
   namespace Sample
   {
      //! @ingroup XXAudio
      using Data = QList<float>;
      using Channels = QList<Data>;

      //! @brief meta data of audio sample
      //! @ingroup XXAudio

      struct XXAUDIO_DECLSPEC Meta
      {
         uint8_t noOfChannels = 1;
         uint16_t sampleRate = 1;
         size_t numberOfSamples = 0;

         size_t noOfSamplesPerChannel() const;
         double totalLength() const;
      };

      //! @brief abstract base class for audio samples
      //! @ingroup XXAudio

      class XXAUDIO_DECLSPEC Abstract
      {
      public:
         Abstract();

      protected:
         virtual bool load(const QString& fileName) = 0;
         virtual bool save(const QString& fileName) = 0;

         static Data interlace(const Channels& input);
         static Channels deinterlace(const Data& input, const uint8_t numberOfChannels = 2);

      protected:
         Data interlacedContent;
         Meta meta;
      };
   } // namespace Sample
} // namespace XX

#endif // NOT XXSampleAbstractH
