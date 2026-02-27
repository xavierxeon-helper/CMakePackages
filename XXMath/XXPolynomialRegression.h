#ifndef XXPolynomialRegressionH
#define XXPolynomialRegressionH

#include "XXMathExportDef.h"
#include "XXPolynomial.h"

#include "XXPolynomialSegmentBundle.h"

namespace XX
{
   //! @brief fit polynomials to data
   //! @details see https://en.wikipedia.org/wiki/Polynomial_regression
   //! @ingroup XXMath

   class XXMATH_DECLSPEC Polynomial::Regression
   {
   public:
      Regression(size_t size);

   public:
      struct Section
      {
         size_t start;
         size_t end;

         using List = QList<Section>;
      };

   public:
      size_t size() const;

      void setValue(const size_t index, const double& value);
      void clear();

      Segment::Bundle fit(size_t degree, double threshold = 10.0) const;

      Section::List compileSections(double threshold = 10.0) const;
      const QVector<double>& getRawValues() const;

   private:
      QVector<double> values;
   };
} // namespace XX

#endif // NOT XXPolynomialRegressionH
