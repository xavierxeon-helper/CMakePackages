#ifndef XXPolynomialSegementH
#define XXPolynomialSegementH

#include "XXMathExportDef.h"
#include "XXPolynomial.h"

#include <QList>

namespace XX
{
   //! @brief a polynomial segment
   //! @ingroup XXMath

   class XXMATH_DECLSPEC Polynomial::Segement : public Polynomial
   {
   public:
      using List = QList<Segement>;
      class Bundle;

   public:
      Segement();
   };
} // namespace XX

#endif // NOT XXPolynomialSegementH
