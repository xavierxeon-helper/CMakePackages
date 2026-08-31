#include "XXCubicCurveUniformSplineAbstract.h"

XX::CubicCurve::UniformSplineAbstract::UniformSplineAbstract()
   : points()
{
}

XX::CubicCurve::UniformSplineAbstract::UniformSplineAbstract(const Linalg::Vector3& p0)
   : UniformSplineAbstract()
{
   points.append(p0);
}

QJsonObject XX::CubicCurve::UniformSplineAbstract::save() const
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

void XX::CubicCurve::UniformSplineAbstract::load(const QJsonObject& data)
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

XX::Linalg::Vector3 XX::CubicCurve::UniformSplineAbstract::value(double parameter, uchar derivativeOrder) const
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

   return calculate(localParameter, derivativeOrder, p0, p1, p2, p3);
}

int XX::CubicCurve::UniformSplineAbstract::numberOfCurves() const
{
   return (points.size() - 1) / 3;
}

int XX::CubicCurve::UniformSplineAbstract::numberOfPoints() const
{
   return points.size();
}

double XX::CubicCurve::UniformSplineAbstract::findParamter(const double& target, Linalg::Vector3::Index vectorIndex, double tolerance) const
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

XX::Linalg::Vector3 XX::CubicCurve::UniformSplineAbstract::findValue(const double& target, Linalg::Vector3::Index vectorIndex, uchar derivativeOrder, double tolerance) const
{
   double param = findParamter(target, vectorIndex, tolerance);
   return value(param, derivativeOrder);
}

void XX::CubicCurve::UniformSplineAbstract::setStartPoint(const Linalg::Vector3& p)
{
   points.append(p);
}

void XX::CubicCurve::UniformSplineAbstract::addCurvePoints(const Linalg::Vector3 p[])
{
   points.append(p[0]);
   points.append(p[1]);
   points.append(p[2]);
}

QDebug XX::CubicCurve::operator<<(QDebug stream, const UniformSplineAbstract& spline)
{
   stream << "[" << spline.numberOfCurves() << "curves, " << spline.numberOfPoints() << "points";
   stream << "]";

   return stream;
}