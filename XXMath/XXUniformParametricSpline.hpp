#ifndef XXUniformParametricSplineHPP
#define XXUniformParametricSplineHPP

#include "XXUniformParametricSpline.h"

template <XX::CubicCurve::CalculatorClass CubicCurveClass>
XX::UniformParametricSpline<CubicCurveClass>::UniformParametricSpline()
//: curves()
{
}

template <XX::CubicCurve::CalculatorClass CubicCurveClass>
XX::Linalg::Vector3 XX::UniformParametricSpline<CubicCurveClass>::value(double parameter) const
{
   return XX::Linalg::Vector3();
}

template <XX::CubicCurve::CalculatorClass CubicCurveClass>
int XX::UniformParametricSpline<CubicCurveClass>::numberOfCures() const
{
   return 3;
}

#endif // NOT XXUniformParametricSplineHPP
