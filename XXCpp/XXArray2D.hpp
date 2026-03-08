#ifndef XXArray2DHPP
#define XXArray2DHPP

#include "XXArray2D.h"

template <typename DataType>
inline XX::Array2D<DataType>::Array2D(const Size& size, const DataType& initialValue)
   : std::vector<std::vector<DataType>>()
   , size(size)
{
   this->resize(size.width, std::vector<DataType>(size.height, initialValue));
}

template <typename DataType>
const XX::Size& XX::Array2D<DataType>::getSize() const
{
   return size;
}

template <typename DataType>
void XX::Array2D<DataType>::appendRow(const DataType& initialValue)
{
   this->push_back(std::vector<DataType>(size.height, initialValue));
   size.height += 1;
}

template <typename DataType>
void XX::Array2D<DataType>::removeRow(const uint16_t row)
{
   const auto it = this->cbegin() + row;
   if (this->cend() == it)
      return;

   this->erase(it);
   size.height -= 1;
}

#endif // NOT XXArray2DHPP
