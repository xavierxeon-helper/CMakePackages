#ifndef MatrixH
#define MatrixH

#include <vector>

#include "Size.h"

/// @brief a 2d array
template <typename DataType>
class Matrix : public std::vector<std::vector<DataType>>
{
public:
   Matrix(const Size& size, const DataType& initialValue = DataType());

public:
   const Size& getSize() const;
   void appendRow(const DataType& initialValue = DataType());
   void removeRow(const uint16_t row);

private:
   Size size;
};

#ifndef MatrixHPP
#include "Matrix.hpp"
#endif // NOT MatrixHPP

#endif // NOT MatrixH
