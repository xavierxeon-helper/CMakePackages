#ifndef XXBitPackedArrayH
#define XXBitPackedArrayH

#include "XXCoreExportDef.h"

#include <cstdint>

#include <QDataStream>
#include <QList>

#include "XXBitPackedArrayReference.h"

namespace XX
{
   namespace BitPacked
   {
      class XXCORE_DECLSPEC Array
      {
      public:
         using Reference = ArrayReference;

      public:
         Array(quint8 bitSize, size_t initialCapacity = 0);
         Array(const QList<quint32>& values);
         Array(const Array& other);

      public:
         static quint8 calculateBitSize(uint64_t value);

         QList<quint32> toList() const;

         void resize(size_t capacity);
         void add(uint64_t value);

         void set(size_t index, quint32 value);
         quint32 get(size_t index) const;

         quint32 operator[](size_t index) const;
         Reference operator[](size_t index);

         size_t capacity() const;
         quint8 getBitSize() const;

      private:
         void clearBits(size_t offset, size_t numBits);
         const quint8* bytes() const noexcept;
         quint8* bytes() noexcept;

         friend XXCORE_DECLSPEC QDataStream& operator<<(QDataStream& out, const Array& array);
         friend XXCORE_DECLSPEC QDataStream& operator>>(QDataStream& in, Array& array);

      private:
         quint8 bitSize;
         quint32 mask;

         size_t dataCapcity;
         QByteArray data;
      };

      XXCORE_DECLSPEC QDataStream& operator<<(QDataStream& out, const Array& array);
      XXCORE_DECLSPEC QDataStream& operator>>(QDataStream& in, Array& array);

   } // namespace BitPacked
} // namespace XX

#endif // NOT XXBitPackedArrayH
