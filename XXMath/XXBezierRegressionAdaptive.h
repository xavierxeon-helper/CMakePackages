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

         using Curve = Linalg::Vector3[4];

      private:
         Linalg::Vector3 computeLeftTangent(int end) const;
         Linalg::Vector3 computeRightTangent(int end) const;
         Linalg::Vector3 computeCenterTangent(int center) const;

         Linalg::Vector3 evaluateBezier(const Linalg::Vector3 curve[4], double u) const;
         void generateBezier(Chord chord, const QVector<double>& u, const Linalg::Vector3& tHat1, const Linalg::Vector3& tHat2, Linalg::Vector3 curve[4]) const;

         QVector<double> chordLengthParameterize(Chord chord) const;
         std::tuple<double, int> computeMaxError(Chord chord, const Linalg::Vector3 curve[4], const QVector<double>& u) const;
         double newtonRaphsonRootFind(const Linalg::Vector3 curve[4], const Linalg::Vector3& point, double u) const;
         QVector<double> reparameterize(Chord chord, const QVector<double>& u, const Linalg::Vector3 curve[4]) const;
         QVector<Linalg::Vector3> fitCubic(Chord chord, Linalg::Vector3 tHat1, Linalg::Vector3 tHat2) const;

      private:
         const QVector<Linalg::Vector3> points;
         const double errorTolerance;
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierRegressionAdaptiveH
