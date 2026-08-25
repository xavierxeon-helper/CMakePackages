#ifndef XXCatmullRomUnifromSplineH
#define XXCatmullRomUnifromSplineH

#include "XXMathExportDef.h"
#include <XXCubicCurveCalculatorParametric.h>
#include <XXCubicCurveUniformSpline.h>

// see https://en.wikipedia.org/wiki/Catmull%E2%80%93Rom_spline

namespace XX
{
   namespace CatmullRom
   {
      inline constexpr double CubicBasisMatrixValues[16] = {0, 2, 0, 0,
                                                            -1, 0, 1, 0,
                                                            2, -5, 4, -1,
                                                            -1, 3, -3, 1};
      using CurveCalculator = CubicCurve::CalculatorParametric<CubicBasisMatrixValues, 0.5>;

      class XXMATH_DECLSPEC UnifromSpline : public CubicCurve::UniformSpline<CurveCalculator>
      {
      public:
         UnifromSpline(const Linalg::Vector3& startKnot);
      };
   } // namespace CatmullRom
} // namespace XX

#endif // NOT XXCatmullRomUnifromSplineH
