#include "XXLinalgMatrix.h"

XX::Linalg::Matrix::Matrix()
{
}

// see https://en.wikipedia.org/wiki/Invertible_matrix
XX::Linalg::Matrix XX::Linalg::Matrix::inverse() const
{
   return Matrix();
}

// see https://en.wikipedia.org/wiki/Transpose
XX::Linalg::Matrix XX::Linalg::Matrix::transpose() const
{
   return Matrix();
}

double XX::Linalg::Matrix::determinant() const
{
   return 0.0;
}
