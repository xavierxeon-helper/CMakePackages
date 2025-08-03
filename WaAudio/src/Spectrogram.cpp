#include "Spectrogram.h"

#include <QtMath>

#include <QDebug>

Spectrogram::Spectrogram(const uint16_t& frameSize, const uint16_t& windowOffset)
   : fft(frameSize)
   , windowOffset(windowOffset)
   , windowData(frameSize, 0)
   , frames()
{
   if (!FastFourierTransfrom::isPowerOfTwo(windowOffset))
      throw new FastFourierTransfrom::Exception("Window Offset size must be a power of two");

   if (windowOffset > frameSize)
      throw new FastFourierTransfrom::Exception("Window Offset size must not be greater than Frame Size");

   for (size_t index = 0; index < frameSize / 2; index++)
   {
      const float value = static_cast<float>(2 * index) / frameSize;
      windowData[index] = value;
      windowData[frameSize - (index + 1)] = value;
   }
}

// see https://www.nti-audio.com/en/support/know-how/fast-fourier-transform-fft
void Spectrogram::load(const Sample::Data& data)
{
   frames.clear();

   const size_t frameSize = fft.getSize();

   auto windowedFrameData = [&](const size_t start)
   {
      Sample::Data frameData = data.mid(start, frameSize);
      if (frameData.size() < frameSize) // pad last frame
      {
         const size_t diffCount = frameSize - frameData.size();
         frameData.append(Sample::Data(diffCount, 0.0));
      }

      for (size_t index = 0; index < frameData.size(); index++)
      {
         // apply window function
         frameData[index] *= windowData[index];
      }

      return frameData;
   };

   const size_t windowCount = qCeil(data.size() / windowOffset) + 1;
   for (int index = 0; index < windowCount; index++)
   {
      const size_t offset = index * windowOffset;
      Sample::Data frameData = windowedFrameData(offset);

      FastFourierTransfrom::ComplexData complex = FastFourierTransfrom::fill(frameData);
      fft.forward(complex);
      //break;

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
