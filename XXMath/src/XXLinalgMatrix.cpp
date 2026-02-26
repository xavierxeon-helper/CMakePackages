#include "XXLinalgMatrix.h"

XX::Linalg::Matrix::Matrix(size_t rowCount, size_t columnCount)
   : columnSize(rowCount)
   , data(columnCount, Column(rowCount, 0.0))
{
}

// see https://en.wikipedia.org/wiki/Invertible_matrix
XX::Linalg::Matrix XX::Linalg::Matrix::inverse() const
{
   return Matrix(0, 0);
}

// see https://en.wikipedia.org/wiki/Transpose
XX::Linalg::Matrix XX::Linalg::Matrix::transpose() const
{
   return Matrix(0, 0);
}

double XX::Linalg::Matrix::determinant() const
{
   return 0.0;
}
