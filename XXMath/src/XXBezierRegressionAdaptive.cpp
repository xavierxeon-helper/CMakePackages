#include "XXBezierRegressionAdaptive.h"

XX::Bezier::UniformSpline XX::Bezier::RegressionAdaptive::fit(const QVector<XX::Linalg::Vector3>& points, const double errorTolerance)
{
   if (points.size() < 2)
   {
      return XX::Bezier::UniformSpline();
   }

   const XX::Linalg::Vector3 tHat1 = computeLeftTangent(points, 0);
   const XX::Linalg::Vector3 tHat2 = computeRightTangent(points, points.size() - 1);

   const QVector<XX::Linalg::Vector3> segments = fitCubic(points, 0, points.size() - 1, tHat1, tHat2, errorTolerance);

   XX::Bezier::UniformSpline spline(segments[0]);
   for (int i = 0; i < segments.size(); i += 4)
      spline.addCurve(segments[i + 1], segments[i + 2], segments[i + 3]);

   return spline;
}

XX::Linalg::Vector3 XX::Bezier::RegressionAdaptive::evaluateBezier(const Linalg::Vector3 curve[4], double u)
{
   Linalg::Vector3 tmp[4] = {curve[0], curve[1], curve[2], curve[3]};

   for (int level = 1; level <= 3; level++)
   {
      for (int i = 0; i <= 3 - level; i++)
      {
         tmp[i] = tmp[i] * (1.0 - u) + tmp[i + 1] * u;
      }
   }

   return tmp[0];
}

XX::Linalg::Vector3 XX::Bezier::RegressionAdaptive::computeLeftTangent(const QVector<Linalg::Vector3>& d, int end)
{
   return (d[end + 1] - d[end]).norm();
}

XX::Linalg::Vector3 XX::Bezier::RegressionAdaptive::computeRightTangent(const QVector<Linalg::Vector3>& d, int end)
{
   return (d[end - 1] - d[end]).norm();
}

XX::Linalg::Vector3 XX::Bezier::RegressionAdaptive::computeCenterTangent(const QVector<Linalg::Vector3>& d, int center)
{
   const Linalg::Vector3 v1 = d[center - 1] - d[center];
   const Linalg::Vector3 v2 = d[center] - d[center + 1];
   return ((v1 + v2) * 0.5).norm();
}

QVector<double> XX::Bezier::RegressionAdaptive::chordLengthParameterize(const QVector<Linalg::Vector3>& d, int first, int last)
{
   QVector<double> u(last - first + 1);
   u[0] = 0.0;
   for (int i = first + 1; i <= last; i++)
      u[i - first] = u[i - first - 1] + (d[i] - d[i - 1]).length();

   const double total = u.last();
   if (total > 1e-12)
      for (int i = 1; i < u.size(); i++)
         u[i] /= total;

   return u;
}

// Fixes P0/P3 at the digitized endpoints and solves, by least squares, how
// far P1/P2 sit along the given tangent directions.
void XX::Bezier::RegressionAdaptive::generateBezier(const QVector<Linalg::Vector3>& d,
                                                    int first, int last,
                                                    const QVector<double>& u,
                                                    const Linalg::Vector3& tHat1,
                                                    const Linalg::Vector3& tHat2,
                                                    Linalg::Vector3 curve[4])
{
   const int nPts = last - first + 1;
   const Linalg::Vector3 P0 = d[first];
   const Linalg::Vector3 P3 = d[last];

   double C00 = 0.0, C01 = 0.0, C11 = 0.0, X0 = 0.0, X1 = 0.0;

   auto bernstein0 = [&](double u) -> double
   {
      const double v = 1.0 - u;
      return v * v * v;
   };

   auto bernstein1 = [&](double u) -> double
   {
      const double v = 1.0 - u;
      return 3.0 * u * v * v;
   };

   auto bernstein2 = [&](double u) -> double
   {
      const double v = 1.0 - u;
      return 3.0 * u * u * v;
   };

   auto bernstein3 = [&](double u) -> double
   {
      return u * u * u;
   };

   for (int i = 0; i < nPts; i++)
   {
      const Linalg::Vector3 A0 = tHat1 * bernstein1(u[i]);
      const Linalg::Vector3 A1 = tHat2 * bernstein2(u[i]);

      C00 += A0.dot(A0);
      C01 += A0.dot(A1);
      C11 += A1.dot(A1);

      const Linalg::Vector3 shortfall = d[first + i] - (P0 * (bernstein0(u[i]) + bernstein1(u[i])) + P3 * (bernstein2(u[i]) + bernstein3(u[i])));

      X0 += A0.dot(shortfall);
      X1 += A1.dot(shortfall);
   }

   const double det = C00 * C11 - C01 * C01;
   const double segLength = (P3 - P0).length();
   const double fallback = segLength / 3.0;

   double alphaLeft = fallback;
   double alphaRight = fallback;

   if (std::abs(det) > 1e-12)
   {
      alphaLeft = (X0 * C11 - X1 * C01) / det;
      alphaRight = (C00 * X1 - C01 * X0) / det;
   }

   if (alphaLeft < segLength * 1e-6 || alphaRight < segLength * 1e-6)
   {
      alphaLeft = fallback;
      alphaRight = fallback;
   }

   curve[0] = P0;
   curve[1] = P0 + tHat1 * alphaLeft;
   curve[2] = P3 + tHat2 * alphaRight;
   curve[3] = P3;
}

std::tuple<double, int> XX::Bezier::RegressionAdaptive::computeMaxError(const QVector<Linalg::Vector3>& d,
                                                                        int first, int last,
                                                                        const Linalg::Vector3 curve[4],
                                                                        const QVector<double>& u)
{
   int splitPoint = (last - first + 1) / 2;
   double maxDist = 0.0;

   for (int i = first + 1; i < last; i++)
   {
      const double dist = (evaluateBezier(curve, u[i - first]) - d[i]).length();
      if (dist > maxDist)
      {
         maxDist = dist;
         splitPoint = i;
      }
   }

   return std::make_tuple(maxDist, splitPoint);
}

double XX::Bezier::RegressionAdaptive::newtonRaphsonRootFind(const Linalg::Vector3 curve[4], const Linalg::Vector3& point, double u)
{
   Linalg::Vector3 qDeriv1[3];
   for (int i = 0; i < 3; i++)
      qDeriv1[i] = (curve[i + 1] - curve[i]) * 3.0;

   Linalg::Vector3 qDeriv2[2];
   for (int i = 0; i < 2; i++)
      qDeriv2[i] = (qDeriv1[i + 1] - qDeriv1[i]) * 2.0;

   const Linalg::Vector3 q = evaluateBezier(curve, u);

   Linalg::Vector3 q1tmp[3] = {qDeriv1[0], qDeriv1[1], qDeriv1[2]};
   for (int i = 0; i <= 1; i++)
      q1tmp[i] = q1tmp[i] * (1.0 - u) + q1tmp[i + 1] * u;
   const Linalg::Vector3 q1 = q1tmp[0];

   const Linalg::Vector3 q2 = qDeriv2[0] * (1.0 - u) + qDeriv2[1] * u;

   const double numerator = (q - point).dot(q1);
   const double denominator = q1.dot(q1) + (q - point).dot(q2);

   return std::abs(denominator) < 1e-12 ? u : u - numerator / denominator;
}

QVector<double> XX::Bezier::RegressionAdaptive::reparameterize(const QVector<Linalg::Vector3>& d, int first, int last,
                                                               const QVector<double>& u, const Linalg::Vector3 curve[4])
{
   QVector<double> result(u.size());
   for (int i = first; i <= last; i++)
      result[i - first] = newtonRaphsonRootFind(curve, d[i], u[i - first]);
   return result;
}

// Appends one or more accepted 4-control-point Bezier segments to `segments`
// (flattened: P0,P1,P2,P3,P0,P1,P2,P3,...), recursively subdividing until
// every segment fits within errorTolerance pixels.
QVector<XX::Linalg::Vector3> XX::Bezier::RegressionAdaptive::fitCubic(const QVector<Linalg::Vector3>& d,
                                                                      int first, int last,
                                                                      Linalg::Vector3 tHat1,
                                                                      Linalg::Vector3 tHat2,
                                                                      const double errorTolerance)
{
   QVector<Linalg::Vector3> segments;
   const int nPts = last - first + 1;

   if (nPts == 2)
   {
      const double dist = (d[last] - d[first]).length() / 3.0;
      segments.append(d[first]);
      segments.append(d[first] + tHat1 * dist);
      segments.append(d[last] + tHat2 * dist);
      segments.append(d[last]);
      return segments;
   }

   QVector<double> u = chordLengthParameterize(d, first, last);
   Linalg::Vector3 curve[4];
   generateBezier(d, first, last, u, tHat1, tHat2, curve);

   double maxError = 0.0;
   int splitPoint = 0;
   std::tie(maxError, splitPoint) = computeMaxError(d, first, last, curve, u);

   if (maxError < errorTolerance)
   {
      segments.append(curve[0]);
      segments.append(curve[1]);
      segments.append(curve[2]);
      segments.append(curve[3]);
      return segments;
   }

   if (maxError < errorTolerance * 4.0)
   {
      for (int iteration = 0; iteration < 4; iteration++)
      {
         const QVector<double> uPrime = reparameterize(d, first, last, u, curve);
         generateBezier(d, first, last, uPrime, tHat1, tHat2, curve);
         std::tie(maxError, splitPoint) = computeMaxError(d, first, last, curve, uPrime);

         if (maxError < errorTolerance)
         {
            segments.append(curve[0]);
            segments.append(curve[1]);
            segments.append(curve[2]);
            segments.append(curve[3]);
            return segments;
         }

         u = uPrime;
      }
   }

   const Linalg::Vector3 tHatCenter = computeCenterTangent(d, splitPoint);
   segments += fitCubic(d, first, splitPoint, tHat1, tHatCenter, errorTolerance);
   segments += fitCubic(d, splitPoint, last, tHatCenter * -1.0, tHat2, errorTolerance);

   return segments;
}
