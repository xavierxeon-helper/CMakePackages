#ifndef XXMatrixHPP
#define XXMatrixHPP

#include "XXMatrix.h"

template <typename DataType>
inline XX::Matrix<DataType>::Matrix(const Size& size, const DataType& initialValue)
   : std::vector<std::vector<DataType>>()
   , size(size)
{
   this->resize(size.width, std::vector<DataType>(size.height, initialValue));
}

template <typename DataType>
const XX::Matrix<DataType>::Size& XX::Matrix<DataType>::getSize() const
{
   return size;
}

template <typename DataType>
void XX::Matrix<DataType>::appendRow(const DataType& initialValue)
{
   this->push_back(std::vector<DataType>(size.height, initialValue));
   size.height += 1;
}

template <typename DataType>
void XX::Matrix<DataType>::removeRow(const uint16_t row)
{
   const auto it = this->cbegin() + row;
   if (this->cend() == it)
      return;

   this->erase(it);
   size.height -= 1;
}

#endif // NOT XXMatrixHPP
