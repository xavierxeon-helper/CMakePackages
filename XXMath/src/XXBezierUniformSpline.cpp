#include "XXBezierUniformSpline.h"

XX::Bezier::UniformSpline::UniformSpline(const Linalg::Vector3& startKnot)
   : CubicCurve::UniformSpline<CurveCalculator>(startKnot)
{
}

void XX::Bezier::UniformSpline::addCurve(const Linalg::Vector3& startControl, const Linalg::Vector3& endControl, const Linalg::Vector3& endKnot)
{
   const Linalg::Vector3 points[3] = {startControl, endControl, endKnot};
   addCurvePoints(points);
}