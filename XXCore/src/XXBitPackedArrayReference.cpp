#include "XXBitPackedArrayReference.h"

#include "XXBitPackedArray.h"

XX::BitPacked::ArrayReference::ArrayReference(Array* array, size_t index) noexcept
   : array(array)
   , index(index)
{
}

XX::BitPacked::ArrayReference::operator quint32() const
{
   return array->get(index);
}

XX::BitPacked::ArrayReference& XX::BitPacked::ArrayReference::operator=(quint32 value)
{
   array->set(index, value);
   return *this;
}

// NOTE: value assignment, not rebinding. Without this, the
// compiler-generated copy-assign would repoint the proxy and
// `a[i] = a[j]` would silently do nothing.
XX::BitPacked::ArrayReference& XX::BitPacked::ArrayReference::operator=(const ArrayReference& other)
{
   return *this = static_cast<quint32>(other);
}

// Taken by value: proxies from operator[] are prvalues, so
// std::swap (which wants T&) cannot bind them. ADL finds this.
void XX::BitPacked::swap(Array::Reference lhs, Array::Reference rhs)
{
   const uint64_t tmp = lhs;
   lhs = static_cast<uint64_t>(rhs);
   rhs = tmp;
}