#include "XXLinalgMatrix.h"

XX::Linalg::Matrix::Matrix(const size_t& rowCount, const size_t& columnCount)
   : rowCount(rowCount)
   , columnCount(columnCount)
   , data(rowCount * columnCount, 0.0)
{
}

bool XX::Linalg::Matrix::operator==(const Matrix& other) const
{
   if (!sizeMatch(other))
      return false;

   for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
   {
      for (size_t columnIndex = 0; columnIndex < data.size(); columnIndex++)
      {
         const size_t index = dataIndex(rowIndex, columnIndex);
         if (data.at(index) != other.data.at(index))
            return false;
      }
   }

   return true;
}

bool XX::Linalg::Matrix::operator!=(const Matrix& other) const
{
   return !(*this == other);
}

XX::Linalg::Matrix XX::Linalg::Matrix::operator+(const Matrix& other) const
{
   Matrix result = *this;
   result += other;
   return result;
}

XX::Linalg::Matrix XX::Linalg::Matrix::operator-(const Matrix& other) const
{
   Matrix result = *this;
   result -= other;
   return result;
}

// see https://en.wikipedia.org/wiki/Matrix_multiplication
XX::Linalg::Matrix XX::Linalg::Matrix::operator*(const Matrix& other) const
{
   if (columnCount != other.rowCount)
      return Matrix();

   Matrix result(rowCount, other.columnCount);
   for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
   {
      for (size_t columnIndex = 0; columnIndex < other.columnCount; columnIndex++)
      {
         double value = 0.0;
         for (size_t commonIndex = 0; commonIndex < columnCount; commonIndex++)
         {
            value += getValue(rowIndex, commonIndex) * other.getValue(commonIndex, columnIndex);
         }
         result.setValue(rowIndex, columnIndex, value);
      }
   }
   return result;
}

XX::Linalg::Matrix XX::Linalg::Matrix::operator*(const double& value) const
{
   Matrix result = *this;
   result *= value;
   return result;
}

XX::Linalg::Matrix& XX::Linalg::Matrix::operator+=(const Matrix& other)
{
   if (!sizeMatch(other))
      return *this;

   for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
   {
      for (size_t columnIndex = 0; columnIndex < columnCount; columnIndex++)
      {
         const size_t index = dataIndex(rowIndex, columnIndex);
         data[index] += other.data.at(index);
      }
   }

   return *this;
}

XX::Linalg::Matrix& XX::Linalg::Matrix::operator-=(const Matrix& other)
{
   if (!sizeMatch(other))
      return *this;

   for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
   {
      for (size_t columnIndex = 0; columnIndex < columnCount; columnIndex++)
      {
         const size_t index = dataIndex(rowIndex, columnIndex);
         data[index] -= other.data.at(index);
      }
   }

   return *this;
}

XX::Linalg::Matrix& XX::Linalg::Matrix::operator*=(const double& value)
{
   for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
   {
      for (size_t columnIndex = 0; columnIndex < columnCount; columnIndex++)
      {
         const size_t index = dataIndex(rowIndex, columnIndex);
         data[index] *= value;
      }
   }

   return *this;
}

double XX::Linalg::Matrix::getValue(const size_t& rowIndex, const size_t& columnIndex) const
{
   const size_t index = dataIndex(rowIndex, columnIndex);
   if (index >= data.size())
      return 0.0;

   const double& value = data.at(index);
   return value;
}

void XX::Linalg::Matrix::setValue(const size_t& rowIndex, const size_t& columnIndex, const double& value)
{
   const size_t index = dataIndex(rowIndex, columnIndex);
   if (index >= data.size())
      return;

   data[index] = value;
}

bool XX::Linalg::Matrix::sizeMatch(const Matrix& other) const
{
   if (rowCount != other.rowCount)
      return false;

   if (columnCount != other.columnCount)
      return false;

   return true;
}

bool XX::Linalg::Matrix::isNull() const
{
   return (data.size() == 0);
}

size_t XX::Linalg::Matrix::getRowCount() const
{
   return rowCount;
}

size_t XX::Linalg::Matrix::getColumnCount() const
{
   return data.size();
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

// see https://en.wikipedia.org/wiki/Determinant
double XX::Linalg::Matrix::determinant() const
{
   double value = 0.0;
   for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
   {
      for (size_t columnIndex = 0; columnIndex < columnCount; columnIndex++)
      {
         const size_t index = dataIndex(rowIndex, columnIndex);
         value += data.at(index);
      }
   }
   return value;
}

size_t XX::Linalg::Matrix::dataIndex(const size_t& rowIndex, const size_t& columnIndex) const
{
   return (columnIndex * rowCount) + rowIndex;
}

//

QTextStream& XX::Linalg::operator>>(QTextStream& stream, Matrix& data)
{
   return stream;
}

QTextStream& XX::Linalg::operator<<(QTextStream& stream, const Matrix& data)
{
   return stream;
}
