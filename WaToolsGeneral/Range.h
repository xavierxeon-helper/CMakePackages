#ifndef RangeH
#define RangeH

#include "WaToolsGeneralExportDef.h"

#include <cstddef>
#include <type_traits>

// optional compiler tests
template <typename TestType>
using isIntegerType = typename std::enable_if<std::is_integral<TestType>::value, bool>::type;

template <typename TestType>
using isFloatType = typename std::enable_if<std::is_floating_point<TestType>::value, bool>::type;

template <typename TestType>
using isSigned = typename std::enable_if<std::is_signed<TestType>::value, bool>::type;

template <typename TestType>
using isUnsigned = typename std::enable_if<!std::is_signed<TestType>::value, bool>::type;

struct Range
{
   template <typename DataType>
   class Finder
   {
   public:
      Finder();

   public:
      /// min to datatype max and max to datatype min
      template <typename TestType = DataType, isSigned<TestType> = true>
      void reset();

      /// min to zero and max to datatype min
      template <typename TestType = DataType, isUnsigned<TestType> = true>
      void reset();

      /// min and max to value
      void init(const DataType& value);

      /// test value and update min / mix
      void observe(const DataType& value);

      const DataType& min() const;
      const DataType& max() const;
      DataType diff() const;

      // only for integer types
      template <typename TestType = DataType, isIntegerType<TestType> = true>
      size_t length() const;

      template <typename TestType = DataType, isIntegerType<TestType> = true>
      DataType value(const size_t index) const;

   private:
      DataType minValue;
      DataType maxValue;
   };

   class WATOOLSGENERAL_DECLSPEC Mapper
   {
   public:
      Mapper(const float& minInput, const float& maxInput, const float& minOutput, const float& maxOutput);

   public:
      float operator()(const float& input) const;

      void setMinInput(const float& value);
      void setMaxInput(const float& value);
      void setMinOutput(const float& value);
      void setMaxOutput(const float& value);

   private:
      void updateScale();

   private:
      float minInput;
      float maxInput;
      float minOutput;
      float maxOutput;
      float scale;
   };

   template <typename DataType>
   static const DataType& clamp(const DataType& value, const DataType& min, const DataType& max);

   template <typename DataType>
   static const DataType& min(const DataType& value1, const DataType& value2);

   template <typename DataType>
   static const DataType& max(const DataType& value1, const DataType& value2);
};

#ifndef RangeHPP
#include "Range.hpp"
#endif // NOT RangeHPP

#endif // NOT RangeH
