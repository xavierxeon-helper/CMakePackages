#ifndef XXBezierUniformSplineH
#define XXBezierUniformSplineH

#include "XXMathExportDef.h"
#include <XXCubicCurveCalculatorParametric.h>
#include <XXCubicCurveUniformSpline.h>

namespace XX
{
   namespace Bezier
   {
      inline constexpr double CubicBasisMatrixValues[16] = {1, 0, 0, 0,
                                                            -3, 3, 0, 0,
                                                            3, -6, 3, 0,
                                                            -1, 3, -3, 1};
      using CurveCalculator = CubicCurve::CalculatorParametric<CubicBasisMatrixValues, 1.0>;

      class XXMATH_DECLSPEC UniformSpline : public CubicCurve::UniformSpline<CurveCalculator>
      {
      public:
         enum class Tangent
         {
            Split,
            Aligned,
            Mirrored
         };

      public:
         UniformSpline();
         UniformSpline(const Linalg::Vector3& startKnot);

      public:
         void addCurve(const Linalg::Vector3& startControl, const Linalg::Vector3& endControl, const Linalg::Vector3& endKnot);
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierUniformSplineH
