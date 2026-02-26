#ifndef XXLinalgMatrixH
#define XXLinalgMatrixH

#include <QVector>

namespace XX
{
   namespace Linalg
   {
      class Matrix
      {
      public:
         Matrix(size_t rowCount, size_t columnCount);

      public:
         bool operator==(const Matrix& other) const;
         bool operator!=(const Matrix& other) const;

         Matrix operator+(const Matrix& other) const;
         Matrix operator-(const Matrix& other) const;

         Matrix& operator+=(const Matrix& other);
         Matrix& operator-=(const Matrix& other);

      public:
         bool sizeMatch(const Matrix& other) const;

         Matrix inverse() const;
         Matrix transpose() const;
         double determinant() const;

      private:
         using Column = QVector<double>;
         using Data = QVector<Column>;

      private:
         const size_t columnSize;
         Data data;
      };
   } // namespace Linalg
} // namespace XX

#endif // NOT XXLinalgMatrixH
