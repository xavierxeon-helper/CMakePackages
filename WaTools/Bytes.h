#ifndef BytesH
#define BytesH

#include <QByteArray>

template <typename DataType>
class Bytes
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
      DataType value = 0;
      char bytes[sizeof(DataType)];
   };
};

#ifndef BytesHPP
#include "Bytes.hpp"
#endif // NOT BytesHPP

#endif // NOT BytesH
