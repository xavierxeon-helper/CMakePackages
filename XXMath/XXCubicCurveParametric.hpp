#ifndef XXCubicCurveParametricHPP
#define XXCubicCurveParametricHPP

#include "XXCubicCurveParametric.h"

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::CubicCurve::Parametric<CalculatorClass>::Parametric()
   : p0()
   , p1()
   , p2()
   , p3()
{
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::Linalg::Vector3 XX::CubicCurve::Parametric<CalculatorClass>::value(double parameter) const
{
   return CalculatorClass::calculate(parameter, p0, p1, p2, p3);
}

#endif // NOT XXCubicCurveParametricHPP