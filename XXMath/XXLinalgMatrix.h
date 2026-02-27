#ifndef XXLinalgMatrixH
#define XXLinalgMatrixH

#include "XXMathExportDef.h"

#include <QVector>

#include <QDebug>
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
         struct Cell
         {
            size_t rowIndex;
            size_t columnIndex;
            double value;

            using List = QList<Cell>;
         };

      public:
         bool operator==(const Matrix& other) const;
         bool operator!=(const Matrix& other) const;

         Matrix operator+(const Matrix& other) const;
         Matrix operator-(const Matrix& other) const;
         Matrix operator*(const Matrix& other) const;
         Matrix operator*(const double& value) const;
         Matrix operator/(const double& value) const;

         Matrix& operator+=(const Matrix& other);
         Matrix& operator-=(const Matrix& other);
         Matrix& operator*=(const double& value);
         Matrix& operator/=(const double& value);

         const double& operator()(const size_t& rowIndex, const size_t& columnIndex) const;
         double& operator()(const size_t& rowIndex, const size_t& columnIndex);

      public:
         double getValue(const size_t& rowIndex, const size_t& columnIndex) const;
         void setValue(const size_t& rowIndex, const size_t& columnIndex, const double& value);
         void setValues(const Cell::List& cellList);

         bool sizeMatch(const Matrix& other) const;
         bool isNull() const;

         size_t getRowCount() const;
         size_t getColumnCount() const;

         Matrix transpose() const;
         double determinant() const;

         Matrix inverse() const;
         Matrix cofactor() const;

      private:
         friend XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Matrix& data);
         friend XXMATH_DECLSPEC QTextStream& operator>>(QTextStream& stream, Matrix& data);
         friend XXMATH_DECLSPEC QTextStream& operator<<(QTextStream& stream, const Matrix& data);

      private:
         double subDeterminant(const Matrix& matrix) const;
         size_t dataIndex(const size_t& rowIndex, const size_t& columnIndex) const;

      private:
         const size_t rowCount;
         const size_t columnCount;
         QVector<double> data;
      };

      /*!
         @addtogroup Streaming
         @{
         @ingroup XXMath
         @brief streaming operators for matrix
      */

      XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Matrix& matrix);
      XXMATH_DECLSPEC QTextStream& operator>>(QTextStream& stream, Matrix& matrix);
      XXMATH_DECLSPEC QTextStream& operator<<(QTextStream& stream, const Matrix& matrix);

      //! @}

   } // namespace Linalg
} // namespace XX

#endif // NOT XXLinalgMatrixH
