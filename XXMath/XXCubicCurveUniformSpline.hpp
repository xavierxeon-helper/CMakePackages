#ifndef XXCubicCurveUniformSplineHPP
#define XXCubicCurveUniformSplineHPP

#include "XXCubicCurveUniformSpline.h"

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::CubicCurve::UniformSpline<CalculatorClass>::UniformSpline()
//: curves()
{
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::Linalg::Vector3 XX::CubicCurve::UniformSpline<CalculatorClass>::value(double parameter) const
{
   return XX::Linalg::Vector3();
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
int XX::CubicCurve::UniformSpline<CalculatorClass>::numberOfCures() const
{
   return 3;
}

#endif // NOT XXCubicCurveUniformSplineHPP
