#include "XXBezierRegressionAdaptive.h"

XX::Bezier::UniformSpline XX::Bezier::RegressionAdaptive::fit(const QVector<XX::Linalg::Vector3>& points, const double errorTolerance)
{
   if (points.size() < 2)
   {
      return XX::Bezier::UniformSpline();
   }

   RegressionAdaptive fitter(points, errorTolerance);

   const XX::Linalg::Vector3 tangent1 = fitter.computeLeftTangent(0);
   const XX::Linalg::Vector3 tangent2 = fitter.computeRightTangent(points.size() - 1);

   const QVector<XX::Linalg::Vector3> segments = fitter.fitCubic(Chord{0, (int)points.size() - 1}, tangent1, tangent2);

   XX::Bezier::UniformSpline spline(segments[0]);
   for (int i = 0; i < segments.size(); i += 4)
      spline.addCurve(segments[i + 1], segments[i + 2], segments[i + 3]);

   return spline;
}

XX::Bezier::RegressionAdaptive::RegressionAdaptive(const QVector<Linalg::Vector3>& points, const double errorTolerance)
   : points(points)
   , errorTolerance(errorTolerance)
{
}

XX::Linalg::Vector3 XX::Bezier::RegressionAdaptive::computeLeftTangent(int end) const
{
   return (points[end + 1] - points[end]).norm();
}

XX::Linalg::Vector3 XX::Bezier::RegressionAdaptive::computeRightTangent(int end) const
{
   return (points[end - 1] - points[end]).norm();
}

XX::Linalg::Vector3 XX::Bezier::RegressionAdaptive::computeCenterTangent(int center) const
{
   const Linalg::Vector3 v1 = points[center - 1] - points[center];
   const Linalg::Vector3 v2 = points[center] - points[center + 1];
   return ((v1 + v2) * 0.5).norm();
}

XX::Linalg::Vector3 XX::Bezier::RegressionAdaptive::evaluateBezier(const Curve& curve, double u) const
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

// Fixes P0/P3 at the digitized endpoints and solves, by least squares, how far P1/P2 sit along the given tangent directions.
XX::Bezier::RegressionAdaptive::Curve XX::Bezier::RegressionAdaptive::generateBezier(const Chord& chord, const QVector<double>& u, const Linalg::Vector3& tangent1, const Linalg::Vector3& tangent2) const
{
   const int nPts = chord.last - chord.first + 1;
   const Linalg::Vector3 P0 = points[chord.first];
   const Linalg::Vector3 P3 = points[chord.last];

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
      const Linalg::Vector3 A0 = tangent1 * bernstein1(u[i]);
      const Linalg::Vector3 A1 = tangent2 * bernstein2(u[i]);

      C00 += A0.dot(A0);
      C01 += A0.dot(A1);
      C11 += A1.dot(A1);

      const Linalg::Vector3 shortfall = points[chord.first + i] - (P0 * (bernstein0(u[i]) + bernstein1(u[i])) + P3 * (bernstein2(u[i]) + bernstein3(u[i])));

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

   Curve curve;

   curve[0] = P0;
   curve[1] = P0 + tangent1 * alphaLeft;
   curve[2] = P3 + tangent2 * alphaRight;
   curve[3] = P3;

   return curve;
}

QVector<double> XX::Bezier::RegressionAdaptive::chordLengthParameterize(const Chord& chord) const
{
   QVector<double> u(chord.last - chord.first + 1);
   u[0] = 0.0;
   for (int i = chord.first + 1; i <= chord.last; i++)
      u[i - chord.first] = u[i - chord.first - 1] + (points[i] - points[i - 1]).length();

   const double total = u.last();
   if (total > 1e-12)
      for (int i = 1; i < u.size(); i++)
         u[i] /= total;

   return u;
}

double XX::Bezier::RegressionAdaptive::newtonRaphsonRootFind(const Curve& curve, const Linalg::Vector3& point, double u) const
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

QVector<double> XX::Bezier::RegressionAdaptive::reparameterize(const Chord& chord, const QVector<double>& u, const Curve& curve) const
{
   QVector<double> result(u.size());
   for (int i = chord.first; i <= chord.last; i++)
      result[i - chord.first] = newtonRaphsonRootFind(curve, points[i], u[i - chord.first]);
   return result;
}

// Appends one or more accepted 4-control-point Bezier segments to `segments`
// (flattened: P0,P1,P2,P3,P0,P1,P2,P3,...), recursively subdividing until
// every segment fits within errorTolerance pixels.
QVector<XX::Linalg::Vector3> XX::Bezier::RegressionAdaptive::fitCubic(const Chord& chord, Linalg::Vector3 tangent1, Linalg::Vector3 tangent2) const
{
   QVector<Linalg::Vector3> segments;
   double maxError = 0.0;
   int splitPoint = 0;

   auto computeMaxError = [&](const Chord& chord, const Curve& curve, const QVector<double>& u)
   {
      splitPoint = (chord.last - chord.first + 1) / 2;
      maxError = 0.0;

      for (int i = chord.first + 1; i < chord.last; i++)
      {
         const double dist = (evaluateBezier(curve, u[i - chord.first]) - points[i]).length();
         if (dist > maxError)
         {
            maxError = dist;
            splitPoint = i;
         }
      }
   };

   auto addCurveToSegents = [&](const Curve& curve)
   {
      segments.append(curve[0]);
      segments.append(curve[1]);
      segments.append(curve[2]);
      segments.append(curve[3]);
   };

   const int nPts = chord.last - chord.first + 1;
   if (nPts == 2)
   {
      const double dist = (points[chord.last] - points[chord.first]).length() / 3.0;

      const Curve curve = {points[chord.first],
                           points[chord.first] + tangent1 * dist,
                           points[chord.last] + tangent2 * dist,
                           points[chord.last]};

      addCurveToSegents(curve);
      return segments;
   }

   QVector<double> u = chordLengthParameterize(chord);
   Curve curve = generateBezier(chord, u, tangent1, tangent2);
   computeMaxError(chord, curve, u);

   if (maxError < errorTolerance)
   {
      addCurveToSegents(curve);
      return segments;
   }

   if (maxError < errorTolerance * 4.0)
   {
      for (int iteration = 0; iteration < 4; iteration++)
      {
         const QVector<double> uPrime = reparameterize(chord, u, curve);
         curve = generateBezier(chord, uPrime, tangent1, tangent2);
         computeMaxError(chord, curve, uPrime);

         if (maxError < errorTolerance)
         {
            addCurveToSegents(curve);
            return segments;
         }

         u = uPrime;
      }
   }

   const Linalg::Vector3 tangentCenter = computeCenterTangent(splitPoint);
   segments += fitCubic(Chord{chord.first, splitPoint}, tangent1, tangentCenter);
   segments += fitCubic(Chord{splitPoint, chord.last}, tangentCenter * -1.0, tangent2);

   return segments;
}
