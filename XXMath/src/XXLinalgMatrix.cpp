#include "XXLinalgMatrix.h"

XX::Linalg::Matrix::Matrix(const size_t& rowCount, const size_t& columnCount)
   : rowCount(rowCount)
   , data(columnCount, Column(rowCount, 0.0))
{
}

bool XX::Linalg::Matrix::operator==(const Matrix& other) const
{
   if (!sizeMatch(other))
      return false;

   for (size_t columnIndex = 0; columnIndex < data.size(); columnIndex++)
   {
      const Column& myColumn = data.at(columnIndex);
      const Column& otherColumn = other.data.at(columnIndex);

      for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
      {
         if (myColumn.at(rowIndex) != otherColumn.at(rowIndex))
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
   if (data.size() != other.rowCount)
      return Matrix();

   Matrix result(rowCount, other.data.size());

   for (size_t columnIndex = 0; columnIndex < other.data.size(); columnIndex++)
   {
      Column& resultColumn = result.data[columnIndex];

      for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
      {
         double value = 0.0;
         for (size_t index = 0; index < other.rowCount; index++)
         {
            value += getValue(rowIndex, index) * other.getValue(index, columnIndex);
         }
         resultColumn[rowIndex] = value;
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

   for (size_t columnIndex = 0; columnIndex < data.size(); columnIndex++)
   {
      Column& myColumn = data[columnIndex];
      const Column& otherColumn = other.data.at(columnIndex);

      for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
      {
         myColumn[rowIndex] += otherColumn.at(rowIndex);
      }
   }

   return *this;
}

XX::Linalg::Matrix& XX::Linalg::Matrix::operator-=(const Matrix& other)
{
   if (!sizeMatch(other))
      return *this;

   for (size_t columnIndex = 0; columnIndex < data.size(); columnIndex++)
   {
      Column& myColumn = data[columnIndex];
      const Column& otherColumn = other.data.at(columnIndex);

      for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
      {
         myColumn[rowIndex] -= otherColumn.at(rowIndex);
      }
   }

   return *this;
}

XX::Linalg::Matrix& XX::Linalg::Matrix::operator*=(const double& value)
{
   for (size_t columnIndex = 0; columnIndex < data.size(); columnIndex++)
   {
      Column& myColumn = data[columnIndex];

      for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
      {
         myColumn[rowIndex] *= value;
      }
   }

   return *this;
}

double XX::Linalg::Matrix::getValue(const size_t& rowIndex, const size_t& columnIndex) const
{
   if (columnIndex >= data.size())
      return 0.0;

   const Column& column = data.at(columnIndex);
   if (rowIndex >= column.size())
      return 0.0;

   const double& value = column.at(rowIndex);
   return value;
}

void XX::Linalg::Matrix::setValue(const size_t& rowIndex, const size_t& columnIndex, const double& value)
{
   if (columnIndex >= data.size())
      return;

   Column& column = data[columnIndex];
   if (rowIndex >= column.size())
      return;

   column[rowIndex] = value;
}

bool XX::Linalg::Matrix::sizeMatch(const Matrix& other) const
{
   if (rowCount != other.rowCount)
      return false;

   if (data.size() != other.data.size())
      return false;

   return true;
}

bool XX::Linalg::Matrix::isNull() const
{
   if (rowCount == 0 || data.size() == 0)
      return true;

   return false;
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

//

QTextStream& XX::Linalg::operator>>(QTextStream& stream, Matrix& data)
{
   return stream;
}

QTextStream& XX::Linalg::operator<<(QTextStream& stream, const Matrix& data)
{
   return stream;
}
