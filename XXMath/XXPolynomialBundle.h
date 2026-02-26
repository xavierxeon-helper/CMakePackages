#ifndef XXPolynomialBundleH
#define XXPolynomialBundleH

#include "XXMathExportDef.h"
#include "XXPolynomialSegement.h"

namespace XX
{
   //! @brief a collection of polynomial segments
   //! @ingroup XXMath

   class XXMATH_DECLSPEC Polynomial::Segement::Bundle : public Segement::List
   {
   public:
      Bundle();
   };
} // namespace XX

#endif // NOT XXPolynomialBundleH
