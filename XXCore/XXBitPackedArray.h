#ifndef XXBitPackedArrayH
#define XXBitPackedArrayH

#include "XXCoreExportDef.h"

#include <cstdint>
#include <iterator>

#include <QDataStream>
#include <QList>

namespace XX
{
   namespace BitPacked
   {
      class XXCORE_DECLSPEC Array
      {
      public:
         Array(size_t bitSize, size_t initialCapacity = 0);

      public:
         static size_t calculateBitSize(uint64_t value);

         void resize(size_t capacity);
         void add(uint64_t value);

         void set(size_t index, uint64_t value);
         uint64_t get(size_t index) const;

         size_t size() const;
         size_t getBitSize() const;

         QDataStream& operator<<(QDataStream& out) const;
         QDataStream& operator>>(QDataStream& in);

      private:
         void clearBits(size_t offset, size_t numBits);

      private:
         const size_t bitSize;
         uint64_t mask;

         size_t elementCount;
         QList<uint8_t> data;
      };
   } // namespace BitPacked
} // namespace XX

#endif // NOT XXBitPackedArrayH
