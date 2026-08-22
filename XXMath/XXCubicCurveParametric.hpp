#ifndef XXCubicCurveParametricHPP
#define XXCubicCurveParametricHPP

#include "XXCubicCurveParametric.h"

template <XX::CubicCurve::CalculatorClass CubicCurveClass>
XX::CubicCurve::Parametric<CubicCurveClass>::Parametric()
   : p0()
   , p1()
   , p2()
   , p3()
{
}

template <XX::CubicCurve::CalculatorClass CubicCurveClass>
XX::Linalg::Vector3 XX::CubicCurve::Parametric<CubicCurveClass>::value(double parameter) const
{
   return CubicCurveClass::calculate(parameter, p0, p1, p2, p3);
}

#endif // NOT XXCubicCurveParametricHPP