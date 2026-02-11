#ifndef XXByteConversionH
#define XXByteConversionH

#include <QByteArray>

namespace XX
{
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
} // namespace XX

#ifndef XXBytesHPP
#include "XXByteConversion.hpp"
#endif // NOT XXBytesHPP

#endif // NOT XXByteConversionH
