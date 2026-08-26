#ifndef XXCubicCurveUniformSplineHPP
#define XXCubicCurveUniformSplineHPP

#include "XXCubicCurveUniformSpline.h"

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::CubicCurve::UniformSpline<CalculatorClass>::UniformSpline()
   : points()
{
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::CubicCurve::UniformSpline<CalculatorClass>::UniformSpline(const Linalg::Vector3& p0)
   : UniformSpline()
{
   points.append(p0);
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
QJsonObject XX::CubicCurve::UniformSpline<CalculatorClass>::save() const
{
   QJsonArray pointArray;
   for (size_t index = 0; index < points.size(); index++)
   {
      const Linalg::Vector3& point = points[index];
      pointArray.append(point.save());
   }

   QJsonObject data;
   data["count"] = points.size();
   data["points"] = pointArray;

   return data;
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
void XX::CubicCurve::UniformSpline<CalculatorClass>::load(const QJsonObject& data)
{
   const int count = data["count"].toInt();
   points.resize(count, Linalg::Vector3());

   QJsonArray pointArray = data["points"].toArray();
   for (int index = 0; index < count; index++)
   {
      const QJsonArray pointData = pointArray[index].toArray();
      points[index].load(pointData);
   }
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::Linalg::Vector3 XX::CubicCurve::UniformSpline<CalculatorClass>::value(double parameter) const
{
   if (1 == points.size())
      return points[0];

   int curveIndex = (int)parameter;
   if (curveIndex < 0)
      curveIndex = 0;
   if (curveIndex >= numberOfCurves())
      curveIndex = numberOfCurves() - 1;

   const double localParameter = parameter - curveIndex;
   const int startIndex = curveIndex * 3;

   const Linalg::Vector3& p0 = points[startIndex + 0];
   const Linalg::Vector3& p1 = points[startIndex + 1];
   const Linalg::Vector3& p2 = points[startIndex + 2];
   const Linalg::Vector3& p3 = points[startIndex + 3];

   return CalculatorClass::calculate(localParameter, p0, p1, p2, p3);
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
int XX::CubicCurve::UniformSpline<CalculatorClass>::numberOfCurves() const
{
   return (points.size() - 1) / 3;
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
int XX::CubicCurve::UniformSpline<CalculatorClass>::numberOfPoints() const
{
   return points.size();
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
double XX::CubicCurve::UniformSpline<CalculatorClass>::findParamter(const double& target, Linalg::Vector3::Index vectorIndex, double tolerance) const
{
   auto curveAt = [&](double t)
   {
      return value(t)[vectorIndex];
   };

   double tLo = 0.0;
   double tHi = (double)numberOfCurves();

   // assumes curveAt(tLo) <= target <= curveAt(tHi) (monotonic increasing x)
   for (int i = 0; i < 100 && (tHi - tLo) > tolerance; ++i)
   {
      const double tMid = 0.5 * (tLo + tHi);
      if (curveAt(tMid) < target)
         tLo = tMid;
      else
         tHi = tMid;
   }
   return 0.5 * (tLo + tHi);
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
XX::Linalg::Vector3 XX::CubicCurve::UniformSpline<CalculatorClass>::findValue(const double& target, Linalg::Vector3::Index vectorIndex, double tolerance) const
{
   double param = findParamter(target, vectorIndex, tolerance);
   return value(param);
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
void XX::CubicCurve::UniformSpline<CalculatorClass>::setStartPoint(const Linalg::Vector3& p)
{
   points.append(p);
}

template <XX::CubicCurve::CalculatorClass CalculatorClass>
void XX::CubicCurve::UniformSpline<CalculatorClass>::addCurvePoints(const Linalg::Vector3 p[])
{
   points.append(p[0]);
   points.append(p[1]);
   points.append(p[2]);
}

#endif // NOT XXCubicCurveUniformSplineHPP
