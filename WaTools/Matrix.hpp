#ifndef MatrixHPP
#define MatrixHPP

#include "Matrix.h"

template <typename DataType>
inline Matrix<DataType>::Matrix(const quint16& width, const quint16& height, const DataType& initialValue)
   : QList<QList<DataType>>()
   , width(width)
   , height(height)
{
   this->resize(width, QList<DataType>(height, initialValue));
}

template <typename DataType>
const quint16& Matrix<DataType>::getWidth() const
{
   return width;
}

template <typename DataType>
const quint16& Matrix<DataType>::getHeight() const
{
   return height;
}

#endif // NOT MatrixHPP
