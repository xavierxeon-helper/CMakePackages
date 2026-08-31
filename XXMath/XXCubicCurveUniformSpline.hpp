#ifndef XXCubicCurveUniformSplineHPP
#define XXCubicCurveUniformSplineHPP

#include "XXCubicCurveUniformSpline.h"

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::CubicCurve::UniformSpline<CalculatorClass>::UniformSpline()
   : UniformSplineAbstract()
{
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::CubicCurve::UniformSpline<CalculatorClass>::UniformSpline(const Linalg::Vector3& p0)
   : UniformSpline()
{
   points.append(p0);
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::Linalg::Vector3 XX::CubicCurve::UniformSpline<CalculatorClass>::calculate(double localParameter, int derivativeOrder, const Linalg::Vector3& p0, const Linalg::Vector3& p1, const Linalg::Vector3& p2, const Linalg::Vector3& p3) const
{
   return CalculatorClass::calculate(localParameter, derivativeOrder, p0, p1, p2, p3);
}

#endif // NOT XXCubicCurveUniformSplineHPP
