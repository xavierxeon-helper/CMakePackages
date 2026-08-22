#ifndef XXBezierH
#define XXBezierH

#include <XXCubicCurveCalculatorParametric.h>

namespace XX
{
   namespace Bezier
   {
      static const double CubicBasisMatrixValues[16] = {1, 0, 0, 0, -3, 3, 0, 0, 3, -6, 3, 0, -1, 3, -3, 1};
      using CubicCurveCalculatror = CubicCurve::CalculatorParametric<CubicBasisMatrixValues, 1.0>;
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierH
