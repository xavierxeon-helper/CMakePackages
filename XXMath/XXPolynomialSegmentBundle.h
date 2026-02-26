#ifndef XXPolynomialSegmentBundleH
#define XXPolynomialSegmentBundleH

#include "XXMathExportDef.h"
#include "XXPolynomialSegment.h"

namespace XX
{
   //! @brief a collection of polynomial segments
   //! @ingroup XXMath

   class XXMATH_DECLSPEC Polynomial::Segment::Bundle : public Segment::List
   {
   public:
      Bundle();
   };
} // namespace XX

#endif // NOT XXPolynomialSegmentBundleH
