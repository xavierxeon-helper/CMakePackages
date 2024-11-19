#ifndef MatrixHPP
#define MatrixHPP

#include "Matrix.h"

template <typename DataType>
inline Matrix<DataType>::Matrix(const Size& size, const DataType& initialValue)
   : std::vector<std::vector<DataType>>()
   , size(size)
{
   this->resize(size.width, std::vector<DataType>(size.height, initialValue));
}

template <typename DataType>
const Size& Matrix<DataType>::getSize() const
{
   return size;
}


#endif // NOT MatrixHPP
