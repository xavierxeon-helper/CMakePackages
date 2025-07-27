#ifndef ConvertorHPP
#define ConvertorHPP

#include "Bytes.h"


template <typename DataType>
QByteArray Bytes<DataType>::toBytes(const DataType& value, bool swap)
{
   Bytes<DataType> convertor;
   convertor.value = value;

   if (swap)
      convertor.swapBytes();

   return convertor.getBytes();
}

template <typename DataType>
DataType Bytes<DataType>::fromBytes(const QByteArray& data, bool swap)
{
   Bytes<DataType> convertor;
   convertor.setBytes(data);

   if (swap)
      convertor.swapBytes();

   return convertor.value;
}

template <typename DataType>
void Bytes<DataType>::setBytes(const QByteArray& input)
{
   if (input.size() != sizeof(DataType))
      return;

   for (int index = 0; index < sizeof(DataType); index++)
      bytes[index] = input[index];
}

template <typename DataType>
QByteArray Bytes<DataType>::getBytes() const
{
   QByteArray output;
   for (int index = 0; index < sizeof(DataType); index++)
      output += bytes[index];

   return output;
}


template <typename DataType>
void Bytes<DataType>::swapBytes()
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
