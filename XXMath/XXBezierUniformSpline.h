#ifndef XXBezierUniformSplineH
#define XXBezierUniformSplineH

#include "XXMathExportDef.h"
#include <XXCubicCurveCalculatorParametric.h>
#include <XXCubicCurveUniformSpline.h>

namespace XX
{
   namespace Bezier
   {
      static const double CubicBasisMatrixValues[16] = {1, 0, 0, 0, -3, 3, 0, 0, 3, -6, 3, 0, -1, 3, -3, 1};
      using CurveCalculatror = CubicCurve::CalculatorParametric<CubicBasisMatrixValues, 1.0>;

      class XXMATH_DECLSPEC UniformSpline : public CubicCurve::UniformSpline<CurveCalculatror>
      {
      public:
         enum class Tangent
         {
            Split,
            Aligned,
            Mirrored
         };

      public:
         UniformSpline(const Linalg::Vector3& startKnot);
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierUniformSplineH
