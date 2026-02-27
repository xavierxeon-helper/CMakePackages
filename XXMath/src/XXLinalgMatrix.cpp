#include "XXLinalgMatrix.h"

#include "XXMath.h"

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

void XX::Linalg::Matrix::setValues(const Cell::List& cellList)
{
   for (const Cell& cell : cellList)
   {
      const size_t index = dataIndex(cell.rowIndex, cell.columnIndex);
      if (index >= data.size())
         continue;

      data[index] = cell.value;
   }
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
   return columnCount;
}

// see https://en.wikipedia.org/wiki/Invertible_matrix
XX::Linalg::Matrix XX::Linalg::Matrix::inverse() const
{
   return Matrix();
}

// see https://en.wikipedia.org/wiki/Transpose
XX::Linalg::Matrix XX::Linalg::Matrix::transpose() const
{
   Matrix result(columnCount, rowCount);
   for (size_t rowIndex = 0; rowIndex < rowCount; rowIndex++)
   {
      for (size_t columnIndex = 0; columnIndex < columnCount; columnIndex++)
      {
         const double value = getValue(rowIndex, columnIndex);
         result.setValue(columnIndex, rowIndex, value);
      }
   }
   return result;
}

// see https://en.wikipedia.org/wiki/Determinant
double XX::Linalg::Matrix::determinant() const
{
   if (0 == data.size())
      return 0.0;

   if (rowCount != columnCount)
      return 0.0;

   // https://en.wikipedia.org/wiki/Laplace_expansion
   std::function<double(const Matrix& matrix)> subDeterminant = [&](const Matrix& matrix)
   {
      const int n = matrix.rowCount;
      if (1 == n)
         return matrix.getValue(0, 0);

      double value = 0.0;
      for (int column = 0; column < n; column++)
      {
         Matrix subMatrix(n - 1, n - 1);

         int columnIndex = 0;
         for (int i = 1; i < n; i++)
         {
            int rowIndex = 0;
            for (int j = 0; j < n; j++)
            {
               if (j != column) // exclude the current column
               {
                  const double entry = matrix.getValue(i, j);
                  subMatrix.setValue(rowIndex, columnIndex, entry);
                  rowIndex++;
               }
            }
            columnIndex++;
         }

         const int sign = (column % 2 == 0) ? 1 : -1;
         value += sign * matrix.getValue(0, column) * subDeterminant(subMatrix);
      }

      return value;
   };

   const double value = subDeterminant(*this);
   return value;
}

size_t XX::Linalg::Matrix::dataIndex(const size_t& rowIndex, const size_t& columnIndex) const
{
   return (columnIndex * rowCount) + rowIndex;
}

//

QDebug XX::Linalg::operator<<(QDebug stream, const Matrix& matrix)
{
   stream << "[" << matrix.rowCount << "rows," << matrix.columnCount << "solumns]=";

   for (int rowIndex = 0; rowIndex < matrix.rowCount; rowIndex++)
   {
      stream << "(";
      for (size_t columnIndex = 0; columnIndex < matrix.columnCount; columnIndex++)
      {
         if (0 != columnIndex)
            stream << ",";

         const size_t index = matrix.dataIndex(rowIndex, columnIndex);
         const double value = matrix.data.at(index);

         stream << value;
      }
      stream << ")";
   }
   return stream;
}

QTextStream& XX::Linalg::operator>>(QTextStream& stream, Matrix& matrix)
{
   return stream;
}

QTextStream& XX::Linalg::operator<<(QTextStream& stream, const Matrix& matrix)
{
   return stream;
}
