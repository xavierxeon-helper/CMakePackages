#include "XXBitPackedArray.h"

#include <bit>

XX::BitPacked::Array::Array(size_t bitSize, size_t initialCapacity)
   : bitSize(bitSize)
   , mask()
   , elementCount(0)
   , data()
{
   if (bitSize == 0 || bitSize > 64)
      throw std::invalid_argument("Bit size must be between 1 and 64.");

   mask = (bitSize == 64) ? ~0ULL : ((1ULL << bitSize) - 1ULL);

   if (initialCapacity > 0)
      resize(initialCapacity);
}

size_t XX::BitPacked::Array::calculateBitSize(uint64_t value)
{
   size_t safe_bit_size = value == 0 ? 1 : std::bit_width(value);
   return safe_bit_size > 64 ? 64 : safe_bit_size;
}

void XX::BitPacked::Array::resize(size_t capacity)
{
   const size_t totalBits = capacity * bitSize;
   const size_t totalBytes = (totalBits + 7) / 8; // Ceiling division
   data.resize(totalBytes, 0);
}

void XX::BitPacked::Array::add(uint64_t value)
{
   size_t index = elementCount;
   elementCount++;

   size_t requiredBits = elementCount * bitSize;
   size_t requiredBytes = (requiredBits + 7) / 8;

   if (data.size() < requiredBytes)
      data.resize(requiredBytes, 0);

   set(index, value);
}

void XX::BitPacked::Array::set(size_t index, uint64_t value)
{
   assert(index < elementCount && "Index out of bounds");

   value &= mask; // Enforce bit limit

   size_t bitOffset = index * bitSize;
   size_t byteIndex = bitOffset / 8;
   size_t bitShift = bitOffset % 8;

   uint64_t remainingValue = value;
   size_t bitsToWrite = bitSize;

   clearBits(bitOffset, bitSize);

   uint8_t* const dst = bytes();

   while (bitsToWrite > 0)
   {
      const size_t bitsInCurrentByte = 8 - bitShift;
      const size_t chunkSize = std::min(bitsToWrite, bitsInCurrentByte);
      const uint8_t chunkMask = static_cast<uint8_t>((1U << chunkSize) - 1);
      const uint8_t byteVal = static_cast<uint8_t>(remainingValue & chunkMask);

      dst[byteIndex] |= (byteVal << bitShift);

      remainingValue >>= chunkSize;
      bitsToWrite -= chunkSize;
      byteIndex++;
      bitShift = 0; // Sub-byte alignment only applies to the very first byte
   }
}

uint64_t XX::BitPacked::Array::get(size_t index) const
{
   assert(index < elementCount && "Index out of bounds");

   size_t bitOffset = index * bitSize;
   size_t byteIndex = bitOffset / 8;
   size_t bitShift = bitOffset % 8;

   uint64_t result = 0;
   size_t bitsRead = 0;

   const uint8_t* const src = bytes();

   while (bitsRead < bitSize)
   {
      const size_t bitsInCurrentByte = 8 - bitShift;
      const size_t chunkSize = std::min(bitSize - bitsRead, bitsInCurrentByte);
      const uint8_t chunkMask = static_cast<uint8_t>((1U << chunkSize) - 1);
      const uint8_t byteVal = (src[byteIndex] >> bitShift) & chunkMask;

      result |= (static_cast<uint64_t>(byteVal) << bitsRead);

      bitsRead += chunkSize;
      byteIndex++;
      bitShift = 0;
   }

   return result;
}

uint64_t XX::BitPacked::Array::operator[](size_t index) const
{
   return get(index);
}

XX::BitPacked::Array::Reference XX::BitPacked::Array::operator[](size_t index)
{
   return Reference(this, index);
}

size_t XX::BitPacked::Array::size() const
{
   return elementCount;
}

size_t XX::BitPacked::Array::getBitSize() const
{
   return bitSize;
}

void XX::BitPacked::Array::clearBits(size_t bitOffset, size_t numBits)
{
   size_t byteIndex = bitOffset / 8;
   size_t bitShift = bitOffset % 8;
   size_t bitsCleared = 0;

   uint8_t* const dst = bytes();

   while (bitsCleared < numBits)
   {
      const size_t bitsInCurrentByte = 8 - bitShift;
      const size_t chunkSize = std::min(numBits - bitsCleared, bitsInCurrentByte);

      const uint8_t chunkMask = static_cast<uint8_t>(((1U << chunkSize) - 1) << bitShift);
      dst[byteIndex] &= ~chunkMask;

      bitsCleared += chunkSize;
      byteIndex++;
      bitShift = 0;
   }
}

const uint8_t* XX::BitPacked::Array::bytes() const noexcept
{
   return reinterpret_cast<const uint8_t*>(data.constData());
}

uint8_t* XX::BitPacked::Array::bytes() noexcept
{
   return reinterpret_cast<uint8_t*>(data.data());
}

QDataStream& XX::BitPacked::operator<<(QDataStream& out, const Array& array)
{
   out << static_cast<quint64>(array.bitSize);
   out << static_cast<quint64>(array.elementCount);
   out << array.data;

   return out;
}

QDataStream& XX::BitPacked::operator>>(QDataStream& in, Array& array)
{
   quint64 inBitSize = 0;
   in >> inBitSize;

   quint64 inEleemntCount = 0;
   in >> inEleemntCount;

   QByteArray inData;
   in >> inData;

   if (inBitSize != array.bitSize)
      throw std::runtime_error("Bit size mismatch during deserialization.");

   array.elementCount = static_cast<size_t>(inEleemntCount);
   array.data = std::move(inData);

   return in;
}
