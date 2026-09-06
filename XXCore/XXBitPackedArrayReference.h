#ifndef XXBitPackedArrayReferenceH
#define XXBitPackedArrayReferenceH

#include "XXCoreExportDef.h"

#include <cstddef>
#include <cstdint>

namespace XX
{
   namespace BitPacked
   {
      class Array;

      class XXCORE_DECLSPEC ArrayReference
      {
      public:
         operator uint64_t() const;

         ArrayReference& operator=(uint64_t value);
         ArrayReference& operator=(const ArrayReference& other);

      private:
         friend class Array;

      private:
         ArrayReference(Array* array, size_t index) noexcept;

      private:
         Array* array;
         size_t index;
      };

      XXCORE_DECLSPEC void swap(ArrayReference lhs, ArrayReference rhs);

   } // namespace BitPacked
} // namespace XX

#endif // NOT XXBitPackedArrayReferenceH
