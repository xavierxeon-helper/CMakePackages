#include "XXLinalgMatrix.h"

XX::Linalg::Matrix::Matrix(size_t rowCount, size_t columnCount)
   : columnSize(rowCount)
   , data(columnCount, Column(rowCount, 0.0))
{
}

bool XX::Linalg::Matrix::operator==(const Matrix& other) const
{
   if (!sizeMatch(other))
      return false;

   return true;
}

bool XX::Linalg::Matrix::operator!=(const Matrix& other) const
{
   return !(*this == other);
}

XX::Linalg::Matrix XX::Linalg::Matrix::operator+(const Matrix& other) const
{
}

XX::Linalg::Matrix XX::Linalg::Matrix::operator-(const Matrix& other) const
{
}

XX::Linalg::Matrix& XX::Linalg::Matrix::operator+=(const Matrix& other)
{
}

XX::Linalg::Matrix& XX::Linalg::Matrix::operator-=(const Matrix& other)
{
}

bool XX::Linalg::Matrix::sizeMatch(const Matrix& other) const
{
   if (columnSize != other.columnSize)
      return false;

   if (data.size() != other.data.size())
      return false;

   return true;
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
