#ifndef XXPolynomialH
#define XXPolynomialH

#include "XXMathExportDef.h"

#include <QDebug>
#include <QList>

namespace XX
{
   //! @brief n th degree polynomials
   /*!
      @detail see https://en.wikipedia.org/wiki/Polynomial
      coeeficients are in decending order i.e. a(n), a(n-1), ... , a1, a0
   */
   //! @ingroup XXMath

   class XXMATH_DECLSPEC Polynomial
   {
   public:
      class Regression;
      class Segment;

   public:
      Polynomial(size_t degree = 0);
      Polynomial(QVector<double> coefficents);
      Polynomial(const Polynomial& other);

   public:
      Polynomial& operator=(const Polynomial& other);
      double operator()(const double& x) const;

      bool operator==(const Polynomial& other) const;
      bool operator!=(const Polynomial& other) const;

      Polynomial operator+(const Polynomial& other) const;
      Polynomial operator-(const Polynomial& other) const;

      Polynomial& operator+=(const Polynomial& other);
      Polynomial& operator-=(const Polynomial& other);

   public:
      virtual double value(const double& x) const;

      void setDegree(size_t degree);
      size_t getDegree() const;
      const QVector<double>& getCoeficents() const;
      void setCoefficient(size_t index, const double& value);

   private:
      friend XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Polynomial& polynomial);

   private:
      QVector<double> coefficents;
   };

   /*!
      @addtogroup Streaming
      @{
      @ingroup XXMath
      @brief streaming operators for polynomials
   */

   XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Polynomial& polynomial);

   //! @}

} // namespace XX

#endif // NOT XXPolynomialH
