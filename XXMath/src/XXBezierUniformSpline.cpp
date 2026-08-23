#include "XXBezierUniformSpline.h"

XX::Bezier::UniformSpline::UniformSpline(const Linalg::Vector3& startKnot)
   : CubicCurve::UniformSpline<CurveCalculatror>(startKnot)
{
}
