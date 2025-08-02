#include "FastFourierTransfrom.h"

// see https://en.wikipedia.org/wiki/Cooley–Tukey_FFT_algorithm

//

FastFourierTransfrom::Exception::Exception(const QString& message)
   : QException()
   , message(message)
{
}

//

FastFourierTransfrom::FastFourierTransfrom(const size_t size)
   : size(size)
{
   if (!isPowerOfTwo(size))
      throw new Exception("FFT size must be a power of two");
}

FastFourierTransfrom::ComplexData FastFourierTransfrom::convert(const Sample::Data& data)
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

const size_t& FastFourierTransfrom::getSize() const
{
   return size;
}

FastFourierTransfrom::ComplexData FastFourierTransfrom::forward(const ComplexData& input)
{
   if (size != input.size())
      throw new Exception(QString("Data size must be %1 samples").arg(size));

   ComplexData data = input;
   transform(data, true);

   return data;
}

FastFourierTransfrom::ComplexData FastFourierTransfrom::inverse(const ComplexData& input)
{
   if (size != input.size())
      throw new Exception(QString("Data size must be %1 samples").arg(size));

   ComplexData data = input;
   transform(data, false);

   const int maxIndex = static_cast<int>(size);
   for (int index = 0; index < maxIndex; index++)
      data[index] /= size;

   return data;
}

bool FastFourierTransfrom::isPowerOfTwo(const size_t num) const
{
   // "complement and compare" method
   return num && (!(num & (num - 1)));
}

void FastFourierTransfrom::prepareData(ComplexData& data) const
{
   ComplexType buf;

   auto swap = [&](const size_t& indexFrom, const size_t& indexTo)
   {
      buf = data[indexFrom];
      data[indexFrom] = data[indexTo];
      data[indexTo] = buf;
   };

   size_t targetIndex = 0;
   size_t bitMask = size;

   for (size_t index = 0; index < size; index++)
   {
      if (targetIndex > index)
         swap(targetIndex, index);

      // Initialize the bit mask
      bitMask = size;

      // While bit is 1
      while (targetIndex & (bitMask >>= 1)) // bitMask = bitMask >> 1
      {
         // Drop bit:
         // & is bitwise AND,
         // ~ is bitwise NOT
         targetIndex &= ~bitMask; // targetIndex = targetIndex & (~bitMask)
      }

      // | is bitwise OR
      targetIndex |= bitMask; // targetIndex = targetIndex | bitMask
   }
}

void FastFourierTransfrom::transform(ComplexData& data, bool forward) const
{
   prepareData(data);

   static const double pi = 2.0 * std::asin(1.0);
   double localPi = forward ? -pi : pi;

   // declare variables to cycle the bits of initial signal
   size_t next, match;
   float sine;
   float delta;
   ComplexType mult, factor, product;

   // cycle for all bit positions of initial signal
   for (size_t i = 1; i < size; i <<= 1)
   {
      next = i << 1;                // getting the next bit
      delta = localPi / i;          // angle increasing
      sine = std::sin(0.5 * delta); // supplementary sin

      // multiplier for trigonometric recurrence
      mult = ComplexType(-2.0 * sine * sine, std::sin(delta));
      factor = 1.0; // start transform factor

      for (size_t j = 0; j < i; j++) // iterations through groupswith different transform factors
      {
         for (size_t k = j; k < size; k += next) // iterations through pairs within group
         {
            match = k + i;

            product = data[match] * factor;
            data[match] = data[k] - product;
            data[k] += product;
         }
         factor = mult * factor + factor;
      }
   }
}
