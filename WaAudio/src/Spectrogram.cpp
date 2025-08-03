#include "Spectrogram.h"

#include <QtMath>

#include <QDebug>

Spectrogram::Spectrogram(const uint16_t& frameSize)
   : fft(frameSize)
   , frames()

{
}

void Spectrogram::load(const Sample::Data& data)
{
   frames.clear();

   const size_t frameSize = fft.getSize();
   const size_t frameCount = qCeil(data.size() / frameSize) + 1;
   for (int index = 0; index < frameCount; index++)
   {
      const size_t offset = index * frameSize;
      Sample::Data frameData = data.mid(offset, frameSize);
      if (frameData.size() < frameSize) // pad last frame
      {
         const size_t diffCount = frameSize - frameData.size();
         frameData.append(Sample::Data(diffCount, 0.0));
      }

      FastFourierTransfrom::ComplexData complex = FastFourierTransfrom::convert(frameData);
      fft.forward(complex);

      Sample::Data amplitudes;
      for (FastFourierTransfrom::ComplexType& cartesian : complex)
      {
         FastFourierTransfrom::ComplexType polar = FastFourierTransfrom::cartesianToPolar(cartesian);
         amplitudes.append(polar.real());
      }

      frames.append(amplitudes);
   }
}

size_t Spectrogram::getFrameSize() const
{
   return fft.getSize();
}

size_t Spectrogram::getFrameCount() const
{
   return frames.size();
}

const Sample::Data& Spectrogram::getFrame(const size_t index) const
{
   return frames.at(index);
}
