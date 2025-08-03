#include "FastFourierTransfrom.h"

//

#include <QDebug>

#include <MathHelper.h>

FastFourierTransfrom::FastFourierTransfrom(const size_t size)
   : size(MathHelper::getNearestPowerOfTwo(size))
{
}

FastFourierTransfrom::ComplexData FastFourierTransfrom::fill(const Sample::Data& data)
{
   ComplexData result;

   for (const float& value : data)
      result.append(ComplexType(value, 0.0));

   return result;
}

Sample::Data FastFourierTransfrom::strip(const ComplexData& data)
{
   Sample::Data result;

   for (const ComplexType& value : data)
      result.append(static_cast<float>(value.real()));

   return result;
}

FastFourierTransfrom::ComplexType FastFourierTransfrom::cartesianToPolar(const ComplexType& cartesian)
{
   const float x = cartesian.real();
   const float y = cartesian.imag();

   const float r = std::sqrt(x * x + y * y);
   const float theta = std::atan2(y, x);

   ComplexType result(r, theta);
   return result;
}

FastFourierTransfrom::ComplexType FastFourierTransfrom::polarToCartesian(const ComplexType& polar)
{
   const float r = polar.real();
   const float theta = polar.imag();

   const float x = r * std::cos(theta);
   const float y = r * std::sin(theta);

   ComplexType result(x, y);
   return result;
}

const size_t& FastFourierTransfrom::getSize() const
{
   return size;
}

FastFourierTransfrom::ComplexData FastFourierTransfrom::forward(const ComplexData& input)
{
   if (size != input.size())
      return ComplexData();

   ComplexData data = input;
   transform(data, true);

   return data;
}

FastFourierTransfrom::ComplexData FastFourierTransfrom::inverse(const ComplexData& input)
{
   if (size != input.size())
      return ComplexData();

   ComplexData data = input;
   transform(data, false);

   const int maxIndex = static_cast<int>(size);
   for (int index = 0; index < maxIndex; index++)
      data[index] /= size;

   return data;
}

void FastFourierTransfrom::bitReverse(ComplexData& data) const
{
   auto swap = [&](const size_t& indexFrom, const size_t& indexTo)
   {
      const ComplexType buf = data[indexFrom];
      data[indexFrom] = data[indexTo];
      data[indexTo] = buf;
   };

   size_t targetIndex = 0;
   for (size_t index = 0; index < size; index++)
   {
      if (targetIndex > index)
         swap(targetIndex, index);

      size_t bitMask = size;
      while (targetIndex & (bitMask >>= 1)) // shift bitmask
         targetIndex &= ~bitMask;           // dop bits  in bitMask

      targetIndex |= bitMask;
   }
}

// see https://en.wikipedia.org/wiki/Cooley–Tukey_FFT_algorithm

/*
algorithm iterative-fft is
    input: Array a of n complex values where n is a power of 2.
    output: Array A the DFT of a.

    bit-reverse-copy(a, A)
    n ← a.length
    for s = 1 to log(n) do
        m ← 2s
        ωm ← exp(−2πi/m)
        for k = 0 to n-1 by m do
            ω ← 1
            for j = 0 to m/2 – 1 do
                u ← A[k + j]
                t ← ω A[k + j + m/2]
                A[k + j] ← u + t
                A[k + j + m/2] ← u – t
                ω ← ω ωm

    return A
*/
void FastFourierTransfrom::transform(ComplexData& data, bool forward) const
{
   bitReverse(data);

   static const double pi = 2.0 * std::asin(1.0);
   const float twoPi = forward ? -2 * pi : 2 * pi;

   const size_t n = data.size();
   for (size_t s = 1; s < log(n); s++)
   {
      const size_t m = 1 << s;                               // 2^s
      const size_t m2 = m >> 1;                              // m/2
      const ComplexType wm(cos(twoPi / m), -sin(twoPi / m)); // e^(-2πi/m))
      for (size_t k = 0; k < n; k += m)                      // loop through the groups
      {
         ComplexType w(1.0, 0.0);        // start multiplier
         for (size_t j = 0; j < m2; j++) // loop through the pairs
         {
            const size_t index1 = k + j;
            const size_t index2 = index1 + m2;

            // butterfly operation
            const ComplexType t = w * data[index2];
            const ComplexType u = data[index1];
            data[index1] = u + t;
            data[index2] = u - t;

            w *= wm; // update multiplier
         }
      }
   }
}
