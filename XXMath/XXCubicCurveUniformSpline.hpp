#ifndef XXCubicCurveUniformSplineHPP
#define XXCubicCurveUniformSplineHPP

#include "XXCubicCurveUniformSpline.h"

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::CubicCurve::UniformSpline<CalculatorClass>::UniformSpline(const Linalg::Vector3& p0)
   : points()
{
   points.append(p0);
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::Linalg::Vector3 XX::CubicCurve::UniformSpline<CalculatorClass>::value(double parameter) const
{
   if (1 == points.size())
      return points[0];

   int curveIndex = (int)parameter;
   if (curveIndex < 0)
      curveIndex = 0;
   if (curveIndex >= numberOfCures())
      curveIndex = numberOfCures() - 1;

   const double localParameter = parameter - curveIndex;
   const int startIndex = curveIndex * 3;

   const Linalg::Vector3& p0 = points[startIndex + 0];
   const Linalg::Vector3& p1 = points[startIndex + 1];
   const Linalg::Vector3& p2 = points[startIndex + 2];
   const Linalg::Vector3& p3 = points[startIndex + 3];

   return CalculatorClass::calculate(localParameter, p0, p1, p2, p3);
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
int XX::CubicCurve::UniformSpline<CalculatorClass>::numberOfCures() const
{
   return (points.size() - 1) / 3;
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
void XX::CubicCurve::UniformSpline<CalculatorClass>::addCurvePoints(const Linalg::Vector3 p[])
{
   points.append(p[0]);
   points.append(p[1]);
   points.append(p[2]);
}

#endif // NOT XXCubicCurveUniformSplineHPP
