#ifndef XXSpectrogramH
#define XXSpectrogramH

#include "XXAudioExportDef.h"

#include "XXFastFourierTransfrom.h"
#include "XXSampleAbstract.h"

namespace XX
{
   //! @brief create spectrogram from audio sample data
   //! @ingroup XXAudio

   class XXAUDIO_DECLSPEC Spectrogram
   {
   public:
      using Frames = QList<Sample::Data>;

   public:
      Spectrogram(const uint16_t& frameSize = 2048, const uint16_t& hopFactor = 4);

   public:
      void load(const Sample::Data& data);
      size_t getFrameSize() const;
      size_t getFrameCount() const;
      const Sample::Data& getFrame(const size_t index) const;

   private:
      FastFourierTransfrom fft;
      uint16_t windowOffset;
      Sample::Data windowData;
      Frames frames;
   };
} // namespace XX

#endif // NOT XXSpectrogramH
