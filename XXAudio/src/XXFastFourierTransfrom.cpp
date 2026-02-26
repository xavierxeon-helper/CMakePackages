#include "XXFastFourierTransfrom.h"

//

#include <QDebug>

#include <XXMath.h>

XX::FastFourierTransfrom::FastFourierTransfrom(const size_t size)
   : size(Math::getNearestPowerOfTwo(size))
{
}

XX::FastFourierTransfrom::ComplexData XX::FastFourierTransfrom::fill(const Sample::Data& data)
{
   ComplexData result;

   for (const float& value : data)
      result.append(ComplexType(value, 0.0));

   return result;
}

XX::Sample::Data XX::FastFourierTransfrom::strip(const ComplexData& data)
{
   Sample::Data result;

   for (const ComplexType& value : data)
      result.append(static_cast<float>(value.real()));

   return result;
}

const size_t& XX::FastFourierTransfrom::getSize() const
{
   return size;
}

XX::FastFourierTransfrom::ComplexData XX::FastFourierTransfrom::forward(const ComplexData& input)
{
   if (size != input.size())
      return ComplexData();

   ComplexData data = input;
   transform(data, true);

   return data;
}

XX::FastFourierTransfrom::ComplexData XX::FastFourierTransfrom::inverse(const ComplexData& input)
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

// see https://cp-algorithms.com/algebra/fft.html

void XX::FastFourierTransfrom::bitReverse(ComplexData& data) const
{
   auto swap = [&](const size_t& indexFrom, const size_t& indexTo)
   {
      const ComplexType buf = data[indexFrom];
      data[indexFrom] = data[indexTo];
      data[indexTo] = buf;
   };

   for (int i = 1, j = 0; i < size; i++)
   {
      int bit = size >> 1;
      for (; j & bit; bit >>= 1)
         j ^= bit;
      j ^= bit;

      if (i < j)
         swap(i, j);
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
void XX::FastFourierTransfrom::transformB(ComplexData& data, bool forward) const
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

void XX::FastFourierTransfrom::transform(ComplexData& data, bool forward) const
{
   bitReverse(data);

   static const double pi = 2.0 * std::asin(1.0);
   const float twoPi = forward ? -2 * pi : 2 * pi;

   for (size_t len = 2; len <= size; len <<= 1)
   {
      const double ang = twoPi / len;
      const ComplexType wlen(cos(ang), sin(ang));
      for (int i = 0; i < size; i += len)
      {
         ComplexType w(1);
         for (size_t j = 0; j < len / 2; j++)
         {
            const ComplexType u = data[i + j];
            const ComplexType v = data[i + j + len / 2] * w;
            data[i + j] = u + v;
            data[i + j + len / 2] = u - v;
            w *= wlen;
         }
      }
   }
}
