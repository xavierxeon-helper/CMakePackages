#ifndef MatrixH
#define MatrixH

#include "Size.h"

template <typename DataType>
class Matrix : public QList<QList<DataType>>
{
public:
   Matrix(const Size& size, const DataType& initialValue);

public:
   const Size& getSize() const;

private:
   Size size;
};

#ifndef MatrixHPP
#include "Matrix.hpp"
#endif // NOT MatrixHPP

#endif // NOT MatrixH
