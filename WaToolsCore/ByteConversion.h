#ifndef ByteConversionH
#define ByteConversionH

#include <QByteArray>

template <typename DataType>
class ByteConversion
{
public:
   static QByteArray toBytes(const DataType& value, bool swap);
   static DataType fromBytes(const QByteArray& data, bool swap);

private:
   void setBytes(const QByteArray& input);
   QByteArray getBytes() const;
   void swapBytes();

private:
   union
   {
      DataType value = DataType{};
      char bytes[sizeof(DataType)];
   };
};

#ifndef BytesHPP
#include "ByteConversion.hpp"
#endif // NOT BytesHPP

#endif // NOT BytesH
