#ifndef ConvertorHPP
#define ConvertorHPP

#include "ByteConversion.h"


template <typename DataType>
QByteArray ByteConversion<DataType>::toBytes(const DataType& value, bool swap)
{
   ByteConversion<DataType> convertor;
   convertor.value = value;

   if (swap)
      convertor.swapBytes();

   return convertor.getBytes();
}

template <typename DataType>
DataType ByteConversion<DataType>::fromBytes(const QByteArray& data, bool swap)
{
   ByteConversion<DataType> convertor;
   convertor.setBytes(data);

   if (swap)
      convertor.swapBytes();

   return convertor.value;
}

template <typename DataType>
void ByteConversion<DataType>::setBytes(const QByteArray& input)
{
   if (input.size() != sizeof(DataType))
      return;

   for (int index = 0; index < sizeof(DataType); index++)
      bytes[index] = input[index];
}

template <typename DataType>
QByteArray ByteConversion<DataType>::getBytes() const
{
   QByteArray output;
   for (int index = 0; index < sizeof(DataType); index++)
      output += bytes[index];

   return output;
}


template <typename DataType>
void ByteConversion<DataType>::swapBytes()
{
   for (int i = 0; i < sizeof(DataType) / 2; i++)
   {
      const int j = sizeof(DataType) - (i + 1);
      char temp = bytes[i];
      bytes[i] = bytes[j];
      bytes[j] = temp;
   }
}

#endif // NOT ConvertorHPP
