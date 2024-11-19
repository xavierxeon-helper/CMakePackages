#ifndef MatrixH
#define MatrixH

#include <vector>

#include "Size.h"

template <typename DataType>
class Matrix : public std::vector<std::vector<DataType>>
{
public:
   Matrix(const Size& size, const DataType& initialValue = DataType());

public:
   const Size& getSize() const;

private:
   Size size;
};

#ifndef MatrixHPP
#include "Matrix.hpp"
#endif // NOT MatrixHPP

#endif // NOT MatrixH
