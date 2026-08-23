#include "XXBezierCurve.h"

XX::Bezier::Curve::Curve(const Linalg::Vector3& startKnot, const Linalg::Vector3& endKnot)
   : ::XX::CubicCurve::Parametric<CurveCalculatror>()
{
   p0 = startKnot;

   const Linalg::Vector3 delta = endKnot - startKnot;
   p1 = startKnot + delta * 0.25;
   p2 = startKnot + delta * 0.75;

   p3 = endKnot;
}

XX::Bezier::Curve::Curve(const Linalg::Vector3& startKnot, const Linalg::Vector3& startControl, const Linalg::Vector3& endControl, const Linalg::Vector3& endKnot)
   : ::XX::CubicCurve::Parametric<CurveCalculatror>()
{
   p0 = startKnot;
   p1 = startControl;
   p2 = endControl;
   p3 = endKnot;
}

const XX::Linalg::Vector3& XX::Bezier::Curve::startKnot() const
{
   return p0;
}

const XX::Linalg::Vector3& XX::Bezier::Curve::startControl() const
{
   return p1;
}

const XX::Linalg::Vector3& XX::Bezier::Curve::endControl() const
{
   return p2;
}

const XX::Linalg::Vector3& XX::Bezier::Curve::endKnot() const
{
   return p3;
}

XX::Linalg::Vector3& XX::Bezier::Curve::startKnot()
{
   return p0;
}

XX::Linalg::Vector3& XX::Bezier::Curve::startControl()
{
   return p1;
}

XX::Linalg::Vector3& XX::Bezier::Curve::endControl()
{
   return p2;
}

XX::Linalg::Vector3& XX::Bezier::Curve::endKnot()
{
   return p3;
}
