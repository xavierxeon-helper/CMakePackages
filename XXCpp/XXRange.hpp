#ifndef XXRangeHPP
#define XXRangeHPP

#include "XXRange.h"

#include <limits>

// Mapper

template <typename DataType>
XX::Range::Finder<DataType>::Finder()
   : minValue()
   , maxValue()
{
   reset();
}

template <typename DataType>
template <typename TestType, XX::isSigned<TestType>>
void XX::Range::Finder<DataType>::reset()
{
   minValue = std::numeric_limits<DataType>::max();
   maxValue = -std::numeric_limits<DataType>::max();
}

template <typename DataType>
template <typename TestType, XX::isUnsigned<TestType>>
void XX::Range::Finder<DataType>::reset()
{
   minValue = std::numeric_limits<DataType>::max();
   maxValue = DataType(0);
}

template <typename DataType>
void XX::Range::Finder<DataType>::init(const DataType& value)
{
   minValue = value;
   maxValue = value;
}

template <typename DataType>
void XX::Range::Finder<DataType>::observe(const DataType& value)
{
   if (value < minValue)
      minValue = value;
   if (value > maxValue)
      maxValue = value;
}

template <typename DataType>
const DataType& XX::Range::Finder<DataType>::min() const
{
   return minValue;
}

template <typename DataType>
const DataType& XX::Range::Finder<DataType>::max() const
{
   return maxValue;
}

template <typename DataType>
DataType XX::Range::Finder<DataType>::diff() const
{
   return maxValue - minValue;
}

template <typename DataType>
template <typename TestType, XX::isIntegerType<TestType>>
size_t XX::Range::Finder<DataType>::length() const
{
   return 1 + (maxValue - minValue);
}

template <typename DataType>
template <typename TestType, XX::isIntegerType<TestType>>
DataType XX::Range::Finder<DataType>::value(const size_t index) const
{
   if (index >= length())
      return maxValue;

   return minValue + index;
}

// Other

template <typename DataType>
const DataType& XX::Range::clamp(const DataType& value, const DataType& min, const DataType& max)
{
   if (value < min)
      return min;
   if (value > max)
      return max;

   return value;
}

template <typename DataType>
const DataType& XX::Range::min(const DataType& value1, const DataType& value2)
{
   if (value1 < value2)
      return value1;

   return value2;
}

template <typename DataType>
const DataType& XX::Range::max(const DataType& value1, const DataType& value2)
{
   if (value1 < value2)
      return value2;

   return value1;
}

#endif // NOT XXRangeHPP
