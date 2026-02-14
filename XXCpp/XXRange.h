#ifndef XXRangeH
#define XXRangeH

#include "XXCppExportDef.h"

#include <cstddef>
#include <iterator> // For std::forward_iterator_tag
#include <type_traits>

namespace XX
{
   // optional compiler tests

   /*! 
      @addtogroup CompilerTests
      @{
      @ingroup XXCpp
      @brief template test functions
      @details test if a type is an integer, float, signed or unsigned type
   */

   template <typename TestType>
   using isIntegerType = typename std::enable_if<std::is_integral<TestType>::value, bool>::type;

   template <typename TestType>
   using isFloatType = typename std::enable_if<std::is_floating_point<TestType>::value, bool>::type;

   template <typename TestType>
   using isSigned = typename std::enable_if<std::is_signed<TestType>::value, bool>::type;

   template <typename TestType>
   using isUnsigned = typename std::enable_if<!std::is_signed<TestType>::value, bool>::type;

   //! @}

   struct Range
   {
      //! @brief find min and max values in a set of data
      //! @ingroup XXCpp

      template <typename DataType>
      class Finder
      {
      public:
         Finder();

      public:
         //! @brief min to datatype max and max to datatype min
         template <typename TestType = DataType, isSigned<TestType> = true>
         void reset();

         //! @brief min to zero and max to datatype min
         template <typename TestType = DataType, isUnsigned<TestType> = true>
         void reset();

         //! @brief min and max to value
         void init(const DataType& value);

         //! @brief test value and update min / max
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

      //! @brief map a value from one range to another
      //! @ingroup XXCpp

      class XXCPP_DECLSPEC Mapper
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

      //! @brief generate a iterateable sequence of numbers with a start, end and step
      //! @ingroup XXCpp

      class Spread
      {
      public:
         class Iterator
         {
         public: // for std:algorithm
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = int;
            using pointer = void;
            using reference = void;

         public:
            int operator*() const;
            Iterator& operator++();

            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;

         private:
            Iterator(int startValue, int step); // start iterator
            Iterator(int endValue);             // end iterator

         private:
            friend class Spread;

         private:
            int number;
            const int step;
            const bool isEnd;
         };

      public:
         Spread(int max);
         Spread(int min, int max, int step = 1);

      public:
         Iterator begin();
         Iterator end();

      private:
         const int min;
         const int max;
         const int step;
      };

      /*! 
         @addtogroup Functions
         @{
         @ingroup XXCpp
         @brief template test functions
      */

      //! @brief clamp a value to a range defined by a min and max value

      template <typename DataType>
      static const DataType& clamp(const DataType& value, const DataType& min, const DataType& max);

      //! @brief return the minimum of two values

      template <typename DataType>
      static const DataType& min(const DataType& value1, const DataType& value2);

      //! @brief return the maximum of two values

      template <typename DataType>
      static const DataType& max(const DataType& value1, const DataType& value2);

      //! @}
   };
} // namespace XX

#ifndef XXRangeHPP
#include "XXRange.hpp"
#endif // NOT XXRangeHPP

#endif // NOT XXRangeH
