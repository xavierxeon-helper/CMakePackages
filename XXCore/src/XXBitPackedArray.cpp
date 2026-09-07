#include "XXBitPackedArray.h"

#include <bit>
#include <stdexcept>

XX::BitPacked::Array::Array(quint8 bitSize, size_t initialCapacity)
   : bitSize(bitSize)
   , mask()
   , dataCapcity(0)
   , data()
{
   if (bitSize == 0 || bitSize > 32)
      throw std::invalid_argument("Bit size must be between 1 and 32.");

   updateMask(bitSize);

   if (initialCapacity > 0)
      resize(initialCapacity);
}

XX::BitPacked::Array::Array(const QList<quint32>& values)
   : bitSize(0)
   , mask(0)
   , dataCapcity(0)
   , data()
{
   // get max bit size of entries
   for (quint32 value : values)
   {
      quint8 valueBitSize = calculateBitSize(value);
      if (valueBitSize > bitSize)
         bitSize = valueBitSize;
   }

   updateMask(bitSize);
   resize(values.size());

   for (size_t i = 0; i < values.size(); ++i)
      set(i, values[i]);
}

XX::BitPacked::Array::Array(const Array& other)
   : bitSize(other.bitSize)
   , mask(other.mask)
   , dataCapcity(other.dataCapcity)
   , data(other.data)
{
}

quint8 XX::BitPacked::Array::calculateBitSize(uint64_t value)
{
   quint8 safe_bit_size = value == 0 ? 1 : std::bit_width(value);
   return safe_bit_size > 64 ? 64 : safe_bit_size;
}

QList<quint32> XX::BitPacked::Array::toList() const
{
   QList<quint32> list;
   list.reserve(dataCapcity);

   for (size_t i = 0; i < dataCapcity; ++i)
      list.append(get(i));

   return list;
}

void XX::BitPacked::Array::resize(size_t capacity)
{
   dataCapcity = capacity;

   const size_t totalBits = capacity * bitSize;
   const size_t totalBytes = (totalBits + 7) / 8; // Ceiling division
   data.resize(totalBytes, 0);
}

void XX::BitPacked::Array::add(uint64_t value)
{
   size_t index = dataCapcity;
   dataCapcity++;

   size_t requiredBits = dataCapcity * bitSize;
   size_t requiredBytes = (requiredBits + 7) / 8;

   if (data.size() < requiredBytes)
   {
      data.resize(requiredBytes, 0);
   }

   set(index, value);
}

void XX::BitPacked::Array::set(size_t index, quint32 value)
{
   assert(index < dataCapcity && "Index out of bounds");

   value &= mask; // Enforce bit limit

   size_t bitOffset = index * bitSize;
   size_t byteIndex = bitOffset / 8;
   size_t bitShift = bitOffset % 8;

   uint64_t remainingValue = value;
   size_t bitsToWrite = bitSize;

   clearBits(bitOffset, bitSize);

   quint8* const dst = bytes();

   while (bitsToWrite > 0)
   {
      const size_t bitsInCurrentByte = 8 - bitShift;
      const size_t chunkSize = std::min(bitsToWrite, bitsInCurrentByte);
      const quint8 chunkMask = static_cast<quint8>((1U << chunkSize) - 1);
      const quint8 byteVal = static_cast<quint8>(remainingValue & chunkMask);

      dst[byteIndex] |= (byteVal << bitShift);

      remainingValue >>= chunkSize;
      bitsToWrite -= chunkSize;
      byteIndex++;
      bitShift = 0; // Sub-byte alignment only applies to the very first byte
   }
}

quint32 XX::BitPacked::Array::get(size_t index) const
{
   assert(index < dataCapcity && "Index out of bounds");

   size_t bitOffset = index * bitSize;
   size_t byteIndex = bitOffset / 8;
   size_t bitShift = bitOffset % 8;

   uint64_t result = 0;
   size_t bitsRead = 0;

   const quint8* const src = bytes();

   while (bitsRead < bitSize)
   {
      const size_t bitsInCurrentByte = 8 - bitShift;
      const size_t chunkSize = std::min(bitSize - bitsRead, bitsInCurrentByte);
      const quint8 chunkMask = static_cast<quint8>((1U << chunkSize) - 1);
      const quint8 byteVal = (src[byteIndex] >> bitShift) & chunkMask;

      result |= (static_cast<uint64_t>(byteVal) << bitsRead);

      bitsRead += chunkSize;
      byteIndex++;
      bitShift = 0;
   }

   return result;
}

quint32 XX::BitPacked::Array::operator[](size_t index) const
{
   return get(index);
}

XX::BitPacked::Array::Reference XX::BitPacked::Array::operator[](size_t index)
{
   return Reference(this, index);
}

size_t XX::BitPacked::Array::capacity() const
{
   return dataCapcity;
}

quint8 XX::BitPacked::Array::getBitSize() const
{
   return bitSize;
}

void XX::BitPacked::Array::updateMask(quint8 bitSize)
{
   mask = (bitSize == 32) ? ~0U : ((1U << bitSize) - 1U);
}

void XX::BitPacked::Array::clearBits(size_t bitOffset, size_t numBits)
{
   size_t byteIndex = bitOffset / 8;
   size_t bitShift = bitOffset % 8;
   size_t bitsCleared = 0;

   quint8* const dst = bytes();

   while (bitsCleared < numBits)
   {
      const size_t bitsInCurrentByte = 8 - bitShift;
      const size_t chunkSize = std::min(numBits - bitsCleared, bitsInCurrentByte);

      const quint8 chunkMask = static_cast<quint8>(((1U << chunkSize) - 1) << bitShift);
      dst[byteIndex] &= ~chunkMask;

      bitsCleared += chunkSize;
      byteIndex++;
      bitShift = 0;
   }
}

const quint8* XX::BitPacked::Array::bytes() const noexcept
{
   return reinterpret_cast<const quint8*>(data.constData());
}

quint8* XX::BitPacked::Array::bytes() noexcept
{
   return reinterpret_cast<quint8*>(data.data());
}

QDataStream& XX::BitPacked::operator<<(QDataStream& out, const Array& array)
{
   out << array.bitSize;
   out << static_cast<quint64>(array.dataCapcity);
   out << array.data;

   return out;
}

QDataStream& XX::BitPacked::operator>>(QDataStream& in, Array& array)
{
   quint8 inBitSize = 0;
   in >> inBitSize;

   quint64 inDataCapcity = 0;
   in >> inDataCapcity;

   QByteArray inData;
   in >> inData;

   if (inBitSize != array.bitSize)
      throw std::runtime_error("Bit size mismatch during deserialization.");

   array.dataCapcity = static_cast<size_t>(inDataCapcity);
   array.data = std::move(inData);

   return in;
}
