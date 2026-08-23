#ifndef XXBezierCubicCurveH
#define XXBezierCubicCurveH

#include "XXMathExportDef.h"
#include <XXBezierUniformSpline.h>
#include <XXCubicCurveParametric.h>

// see https://en.wikipedia.org/wiki/Bézier_curve

namespace XX
{
   namespace Bezier
   {
      class XXMATH_DECLSPEC CubicCurve : public ::XX::CubicCurve::Parametric<CubicCurveCalculatror>
      {
      public:
         CubicCurve();
         CubicCurve(const Linalg::Vector3& startKnot, const Linalg::Vector3& endKnot);
         CubicCurve(const Linalg::Vector3& startKnot, const Linalg::Vector3& startControl, const Linalg::Vector3& endControl, const Linalg::Vector3& endKnot);

      public:
         const Linalg::Vector3& startKnot() const;
         const Linalg::Vector3& startControl() const;
         const Linalg::Vector3& endControl() const;
         const Linalg::Vector3& endKnot() const;

         Linalg::Vector3& startKnot();
         Linalg::Vector3& startControl();
         Linalg::Vector3& endControl();
         Linalg::Vector3& endKnot();
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierCubicCurveH
