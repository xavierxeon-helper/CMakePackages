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
         Array(size_t bitSize, size_t initialCapacity = 0);

      public:
         static size_t calculateBitSize(uint64_t value);

         void resize(size_t capacity);
         void add(uint64_t value);

         void set(size_t index, uint64_t value);
         uint64_t get(size_t index) const;

         uint64_t operator[](size_t index) const;
         Reference operator[](size_t index);

         size_t size() const;
         size_t getBitSize() const;

      private:
         void clearBits(size_t offset, size_t numBits);
         const uint8_t* bytes() const noexcept;
         uint8_t* bytes() noexcept;

         friend XXCORE_DECLSPEC QDataStream& operator<<(QDataStream& out, const Array& array);
         friend XXCORE_DECLSPEC QDataStream& operator>>(QDataStream& in, Array& array);

      private:
         size_t bitSize;
         uint64_t mask;

         size_t elementCount;
         QByteArray data;
      };

      XXCORE_DECLSPEC QDataStream& operator<<(QDataStream& out, const Array& array);
      XXCORE_DECLSPEC QDataStream& operator>>(QDataStream& in, Array& array);

   } // namespace BitPacked
} // namespace XX

#endif // NOT XXBitPackedArrayH
