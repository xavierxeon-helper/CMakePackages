#ifndef XXPolynomialRegressionH
#define XXPolynomialRegressionH

#include "XXMathExportDef.h"
#include "XXPolynomial.h"
#include "XXRegressionContainer2D.h"

#include "XXPolynomialSegmentBundle.h"

namespace XX
{
   //! @brief fit polynomials to data
   //! @details see https://en.wikipedia.org/wiki/Polynomial_regression
   //! @ingroup XXMath

   class XXMATH_DECLSPEC Polynomial::Regression : public XX::Regression::Container2D
   {
   public:
      Regression(size_t size);

   public:
      Segment::Bundle fit(size_t degree, double threshold, size_t overFit = 2, size_t maxSegmentLength = 50) const;
   };
} // namespace XX

#endif // NOT XXPolynomialRegressionH
