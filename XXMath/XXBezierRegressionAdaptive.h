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
            const QVector<Linalg::Vector3>& points;
            int first;
            int last;
         };

      private:
         static Linalg::Vector3 computeLeftTangent(const QVector<Linalg::Vector3>& d, int end);
         static Linalg::Vector3 computeRightTangent(const QVector<Linalg::Vector3>& d, int end);
         static Linalg::Vector3 computeCenterTangent(const QVector<Linalg::Vector3>& d, int center);

         static Linalg::Vector3 evaluateBezier(const Linalg::Vector3 curve[4], double u);
         static void generateBezier(Chord chord, const QVector<double>& u, const Linalg::Vector3& tHat1, const Linalg::Vector3& tHat2, Linalg::Vector3 curve[4]);

         static QVector<double> chordLengthParameterize(Chord chord);
         static std::tuple<double, int> computeMaxError(Chord chord, const Linalg::Vector3 curve[4], const QVector<double>& u);
         static double newtonRaphsonRootFind(const Linalg::Vector3 curve[4], const Linalg::Vector3& point, double u);
         static QVector<double> reparameterize(Chord chord, const QVector<double>& u, const Linalg::Vector3 curve[4]);
         static QVector<Linalg::Vector3> fitCubic(Chord chord, Linalg::Vector3 tHat1, Linalg::Vector3 tHat2, const double errorTolerance);
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierRegressionAdaptiveH
