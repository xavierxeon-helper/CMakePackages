#include "XXBezierCubicCurve.h"

XX::Bezier::CubicCurve::CubicCurve()
   : ::XX::CubicCurve::Parametric<CubicCurveCalculatror>()
{
}

XX::Bezier::CubicCurve::CubicCurve(const Linalg::Vector3& startKnot, const Linalg::Vector3& endKnot)
   : CubicCurve()
{
   p0 = startKnot;

   const Linalg::Vector3 delta = endKnot - startKnot;
   p1 = startKnot + delta * 0.25;
   p2 = startKnot + delta * 0.75;

   p3 = endKnot;
}

XX::Bezier::CubicCurve::CubicCurve(const Linalg::Vector3& startKnot, const Linalg::Vector3& startControl, const Linalg::Vector3& endControl, const Linalg::Vector3& endKnot)
   : CubicCurve()
{
   p0 = startKnot;
   p1 = startControl;
   p2 = endControl;
   p3 = endKnot;
}

const XX::Linalg::Vector3& XX::Bezier::CubicCurve::startKnot() const
{
   return p0;
}

const XX::Linalg::Vector3& XX::Bezier::CubicCurve::startControl() const
{
   return p1;
}

const XX::Linalg::Vector3& XX::Bezier::CubicCurve::endControl() const
{
   return p2;
}

const XX::Linalg::Vector3& XX::Bezier::CubicCurve::endKnot() const
{
   return p3;
}

XX::Linalg::Vector3& XX::Bezier::CubicCurve::startKnot()
{
   return p0;
}

XX::Linalg::Vector3& XX::Bezier::CubicCurve::startControl()
{
   return p1;
}

XX::Linalg::Vector3& XX::Bezier::CubicCurve::endControl()
{
   return p2;
}

XX::Linalg::Vector3& XX::Bezier::CubicCurve::endKnot()
{
   return p3;
}
