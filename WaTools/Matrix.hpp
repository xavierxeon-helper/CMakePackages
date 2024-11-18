#ifndef MatrixHPP
#define MatrixHPP

#include "Matrix.h"

template <typename DataType>
inline Matrix<DataType>::Matrix(const Size& size, const DataType& initialValue)
   : QList<QList<DataType>>()
   , size(size)
{
   this->resize(size.width, QList<DataType>(size.height, initialValue));
}

template <typename DataType>
const Size& Matrix<DataType>::getSize() const
{
   return size;
}


#endif // NOT MatrixHPP
