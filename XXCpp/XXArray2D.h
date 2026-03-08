#ifndef XXArray2DH
#define XXArray2DH

#include <vector>

#include "XXSize.h"

namespace XX
{
   //! @brief a 2d array
   //! @ingroup XXCpp

   template <typename DataType>
   class Array2D : public std::vector<std::vector<DataType>>
   {
   public:
      Array2D(const Size& size, const DataType& initialValue = DataType());

   public:
      const Size& getSize() const;
      void appendRow(const DataType& initialValue = DataType());
      void removeRow(const uint16_t row);

   private:
      Size size;
   };
} // namespace XX

#ifndef XXArray2DHPP
#include "XXArray2D.hpp"
#endif // NOT XXArray2DHPP

#endif // NOT XXArray2DH
