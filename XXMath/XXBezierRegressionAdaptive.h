#ifndef XXBezierRegressionAdaptiveH
#define XXBezierRegressionAdaptiveH

#include "XXMathExportDef.h"
#include "XXRegressionContainer2D.h"

#include "XXBezierUniformSpline.h"

namespace XX
{
   namespace Bezier
   {
      // use "An Algorithm for Automatically Fitting Digitized Curves" (Graphics Gems, 1990)

      class XXMATH_DECLSPEC RegressionAdaptive : public XX::Regression::Container2D
      {
      public:
         RegressionAdaptive(size_t size);

      public:
         XX::Bezier::UniformSpline fit() const;
         XX::Bezier::UniformSpline fit(const QVector<XX::Linalg::Vector3>& points) const;
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierRegressionAdaptiveH
