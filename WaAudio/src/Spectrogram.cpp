#include "Spectrogram.h"

#include <MathHelper.h>

#include <QDebug>

Spectrogram::Spectrogram(const uint16_t& frameSize, const uint16_t& _windowOffset)
   : fft(frameSize)
   , windowOffset(getNearestPowerOfTwo(_windowOffset))
   , windowData(frameSize, 0)
   , frames()
{
   if (windowOffset > frameSize)
      windowOffset = frameSize;

   // seee https://en.wikipedia.org/wiki/Window_function
   // blackmann-harris window
   const float a0 = 0.35975;
   const float a1 = 0.48829;
   const float a2 = 0.14128;
   const float a3 = 0.01168;

   static const double pi = 2.0 * std::asin(1.0);

   for (size_t index = 0; index < frameSize; index++)
   {
      float indexValue = (pi * index) / frameSize;
      float value = a0 - a1 * qCos(2.0 * indexValue) + a2 * qCos(4.0 * indexValue) - a3 * qCos(6.0 * indexValue);
      windowData[index] = value;
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
         FastFourierTransfrom::ComplexType polar = cartesianToPolar(cartesian);
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
