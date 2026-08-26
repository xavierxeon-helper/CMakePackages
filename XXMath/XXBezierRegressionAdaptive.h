#ifndef XXBezierRegressionAdaptiveH
#define XXBezierRegressionAdaptiveH

#include "XXMathExportDef.h"

#include "XXBezierUniformSpline.h"

namespace XX
{
   namespace Bezier
   {
      // uses "An Algorithm for Automatically Fitting Digitized Curves" (Graphics Gems, 1990)

      class XXMATH_DECLSPEC RegressionAdaptive
      {
      public:
         static XX::Bezier::UniformSpline fit(const QVector<Linalg::Vector3>& points, const double errorTolerance);

      private:
         RegressionAdaptive(const QVector<Linalg::Vector3>& points, const double errorTolerance);

      private:
         struct Chord
         {
            int first;
            int last;
         };

         using Curve = std::array<Linalg::Vector3, 4>;

      private:
         Linalg::Vector3 computeLeftTangent(int end) const;
         Linalg::Vector3 computeRightTangent(int end) const;
         Linalg::Vector3 computeCenterTangent(int center) const;

         Linalg::Vector3 evaluateBezier(const Curve& curve, double u) const;
         Curve generateBezier(const Chord& chord, const QVector<double>& u, const Linalg::Vector3& tHat1, const Linalg::Vector3& tHat2) const;

         QVector<double> chordLengthParameterize(const Chord& chord) const;
         double newtonRaphsonRootFind(const Curve& curve, const Linalg::Vector3& point, double u) const;
         QVector<double> reparameterize(const Chord& chord, const QVector<double>& u, const Curve& curve) const;
         QVector<Linalg::Vector3> fitCubic(const Chord& chord, Linalg::Vector3 tHat1, Linalg::Vector3 tHat2) const;

      private:
         const QVector<Linalg::Vector3>& points;
         const double errorTolerance;
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierRegressionAdaptiveH
