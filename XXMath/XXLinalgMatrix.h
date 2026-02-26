#ifndef XXLinalgMatrixH
#define XXLinalgMatrixH

#include "XXMathExportDef.h"

#include <QVector>

#include <QTextStream>

namespace XX
{
   namespace Linalg
   {
      //! @brief NxM martix
      //! @ingroup XXMath

      class XXMATH_DECLSPEC Matrix
      {
      public:
         Matrix(const size_t& rowCount = 0, const size_t& columnCount = 0);

      public:
         bool operator==(const Matrix& other) const;
         bool operator!=(const Matrix& other) const;

         Matrix operator+(const Matrix& other) const;
         Matrix operator-(const Matrix& other) const;

         Matrix operator*(const Matrix& other) const;
         Matrix operator*(const double& value) const;

         Matrix& operator+=(const Matrix& other);
         Matrix& operator-=(const Matrix& other);

         Matrix& operator*(const Matrix& other);
         Matrix& operator*(const double& value);

      public:
         double getValue(const size_t& rowIndex, const size_t& columnIndex) const;
         void setValue(const size_t& rowIndex, const size_t& columnIndex, const double& value);

         bool sizeMatch(const Matrix& other) const;
         bool isNull() const;

         size_t getRowCount() const;
         size_t getColumnCount() const;

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

      XXMATH_DECLSPEC QTextStream& operator>>(QTextStream& stream, Matrix& data);
      XXMATH_DECLSPEC QTextStream& operator<<(QTextStream& stream, const Matrix& data);

   } // namespace Linalg
} // namespace XX

#endif // NOT XXLinalgMatrixH
