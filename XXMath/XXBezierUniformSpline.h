#ifndef XXBezierUniformSplineH
#define XXBezierUniformSplineH

#include <XXBezier.h>
#include <XXCubicCurveCalculatorParametric.h>
#include <XXUniformParametricSpline.h>

namespace XX
{
   namespace Bezier
   {
      class XXMATH_DECLSPEC UniformSpline : public UniformParametricSpline<CubicCurveCalculatror>
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
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierUniformSplineH
