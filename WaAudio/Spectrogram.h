#ifndef SpectrogramH
#define SpectrogramH

#include "FastFourierTransfrom.h"
#include "SampleAbstract.h"

class Spectrogram
{
public:
   using Frames = QList<Sample::Data>;

public:
   Spectrogram(const uint16_t& frameSize);

public:
   void load(const Sample::Data& data);
   size_t getFrameSize() const;
   size_t getFrameCount() const;
   const Sample::Data& getFrame(const size_t index) const;

private:
   FastFourierTransfrom fft;
   Frames frames;
};

#endif // NOT SpectrogramH
