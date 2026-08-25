#include "XXBezierRegressionAdaptive.h"

namespace
{
   using XX::Linalg::Vector3;

   double bernstein0(double u)
   {
      const double v = 1.0 - u;
      return v * v * v;
   }
   double bernstein1(double u)
   {
      const double v = 1.0 - u;
      return 3.0 * u * v * v;
   }
   double bernstein2(double u)
   {
      const double v = 1.0 - u;
      return 3.0 * u * u * v;
   }
   double bernstein3(double u)
   {
      return u * u * u;
   }

   Vector3 normalized(const Vector3& v)
   {
      const double len = v.length();
      return len < 1e-12 ? v : v * (1.0 / len);
   }

   Vector3 evaluateBezier(const Vector3 curve[4], double u)
   {
      Vector3 tmp[4] = {curve[0], curve[1], curve[2], curve[3]};
      for (int level = 1; level <= 3; level++)
         for (int i = 0; i <= 3 - level; i++)
            tmp[i] = tmp[i] * (1.0 - u) + tmp[i + 1] * u;
      return tmp[0];
   }

   Vector3 computeLeftTangent(const QVector<Vector3>& d, int end)
   {
      return normalized(d[end + 1] - d[end]);
   }

   Vector3 computeRightTangent(const QVector<Vector3>& d, int end)
   {
      return normalized(d[end - 1] - d[end]);
   }

   Vector3 computeCenterTangent(const QVector<Vector3>& d, int center)
   {
      const Vector3 v1 = d[center - 1] - d[center];
      const Vector3 v2 = d[center] - d[center + 1];
      return normalized((v1 + v2) * 0.5);
   }

   QVector<double> chordLengthParameterize(const QVector<Vector3>& d, int first, int last)
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
   void generateBezier(const QVector<Vector3>& d, int first, int last, const QVector<double>& u,
                       const Vector3& tHat1, const Vector3& tHat2, Vector3 curve[4])
   {
      const int nPts = last - first + 1;
      const Vector3 P0 = d[first];
      const Vector3 P3 = d[last];

      double C00 = 0.0, C01 = 0.0, C11 = 0.0, X0 = 0.0, X1 = 0.0;

      for (int i = 0; i < nPts; i++)
      {
         const Vector3 A0 = tHat1 * bernstein1(u[i]);
         const Vector3 A1 = tHat2 * bernstein2(u[i]);

         C00 += A0.dot(A0);
         C01 += A0.dot(A1);
         C11 += A1.dot(A1);

         const Vector3 shortfall = d[first + i] - (P0 * (bernstein0(u[i]) + bernstein1(u[i])) + P3 * (bernstein2(u[i]) + bernstein3(u[i])));

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

   double computeMaxError(const QVector<Vector3>& d, int first, int last, const Vector3 curve[4],
                          const QVector<double>& u, int* splitPoint)
   {
      *splitPoint = (last - first + 1) / 2;
      double maxDist = 0.0;

      for (int i = first + 1; i < last; i++)
      {
         const double dist = (evaluateBezier(curve, u[i - first]) - d[i]).length();
         if (dist > maxDist)
         {
            maxDist = dist;
            *splitPoint = i;
         }
      }

      return maxDist;
   }

   double newtonRaphsonRootFind(const Vector3 curve[4], const Vector3& point, double u)
   {
      Vector3 qDeriv1[3];
      for (int i = 0; i < 3; i++)
         qDeriv1[i] = (curve[i + 1] - curve[i]) * 3.0;

      Vector3 qDeriv2[2];
      for (int i = 0; i < 2; i++)
         qDeriv2[i] = (qDeriv1[i + 1] - qDeriv1[i]) * 2.0;

      const Vector3 q = evaluateBezier(curve, u);

      Vector3 q1tmp[3] = {qDeriv1[0], qDeriv1[1], qDeriv1[2]};
      for (int i = 0; i <= 1; i++)
         q1tmp[i] = q1tmp[i] * (1.0 - u) + q1tmp[i + 1] * u;
      const Vector3 q1 = q1tmp[0];

      const Vector3 q2 = qDeriv2[0] * (1.0 - u) + qDeriv2[1] * u;

      const double numerator = (q - point).dot(q1);
      const double denominator = q1.dot(q1) + (q - point).dot(q2);

      return std::abs(denominator) < 1e-12 ? u : u - numerator / denominator;
   }

   QVector<double> reparameterize(const QVector<Vector3>& d, int first, int last,
                                  const QVector<double>& u, const Vector3 curve[4])
   {
      QVector<double> result(u.size());
      for (int i = first; i <= last; i++)
         result[i - first] = newtonRaphsonRootFind(curve, d[i], u[i - first]);
      return result;
   }

   // Appends one or more accepted 4-control-point Bezier segments to `segments`
   // (flattened: P0,P1,P2,P3,P0,P1,P2,P3,...), recursively subdividing until
   // every segment fits within errorTolerance pixels.
   void fitCubic(const QVector<Vector3>& d, int first, int last, Vector3 tHat1, Vector3 tHat2,
                 double errorTolerance, QVector<Vector3>& segments)
   {
      const int nPts = last - first + 1;

      if (nPts == 2)
      {
         const double dist = (d[last] - d[first]).length() / 3.0;
         segments.append(d[first]);
         segments.append(d[first] + tHat1 * dist);
         segments.append(d[last] + tHat2 * dist);
         segments.append(d[last]);
         return;
      }

      QVector<double> u = chordLengthParameterize(d, first, last);
      Vector3 curve[4];
      generateBezier(d, first, last, u, tHat1, tHat2, curve);

      int splitPoint = 0;
      double maxError = computeMaxError(d, first, last, curve, u, &splitPoint);

      if (maxError < errorTolerance)
      {
         segments.append(curve[0]);
         segments.append(curve[1]);
         segments.append(curve[2]);
         segments.append(curve[3]);
         return;
      }

      if (maxError < errorTolerance * 4.0)
      {
         for (int iteration = 0; iteration < 4; iteration++)
         {
            const QVector<double> uPrime = reparameterize(d, first, last, u, curve);
            generateBezier(d, first, last, uPrime, tHat1, tHat2, curve);
            maxError = computeMaxError(d, first, last, curve, uPrime, &splitPoint);

            if (maxError < errorTolerance)
            {
               segments.append(curve[0]);
               segments.append(curve[1]);
               segments.append(curve[2]);
               segments.append(curve[3]);
               return;
            }

            u = uPrime;
         }
      }

      const Vector3 tHatCenter = computeCenterTangent(d, splitPoint);
      fitCubic(d, first, splitPoint, tHat1, tHatCenter, errorTolerance, segments);
      fitCubic(d, splitPoint, last, tHatCenter * -1.0, tHat2, errorTolerance, segments);
   }
} // namespace

XX::Bezier::RegressionAdaptive::RegressionAdaptive(size_t size)
   : XX::Regression::Container2D(size)
{
}

XX::Bezier::UniformSpline XX::Bezier::RegressionAdaptive::fit() const
{
   QVector<XX::Linalg::Vector3> points;
   points.reserve(getValues().size());
   for (int x = 0; x < getValues().size(); x++)
   {
      const double value = getValues().at(x);
      if (std::isnan(value))
         continue;

      points.append(XX::Linalg::Vector3(x, value, 0.0));
   }

   return fit(points);
}

XX::Bezier::UniformSpline XX::Bezier::RegressionAdaptive::fit(const QVector<XX::Linalg::Vector3>& points) const
{
   if (points.size() < 2)
   {
      return XX::Bezier::UniformSpline();
   }

   QVector<XX::Linalg::Vector3> segments;
   const XX::Linalg::Vector3 tHat1 = computeLeftTangent(points, 0);
   const XX::Linalg::Vector3 tHat2 = computeRightTangent(points, points.size() - 1);

   const double errorTolerance = 2.0; // max fit error, in pixels — tune to taste
   fitCubic(points, 0, points.size() - 1, tHat1, tHat2, errorTolerance, segments);

   XX::Bezier::UniformSpline spline(segments[0]);
   for (int i = 0; i < segments.size(); i += 4)
      spline.addCurve(segments[i + 1], segments[i + 2], segments[i + 3]);

   return spline;
}