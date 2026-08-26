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
         static Linalg::Vector3 evaluateBezier(const Linalg::Vector3 curve[4], double u);
         static Linalg::Vector3 computeLeftTangent(const QVector<Linalg::Vector3>& d, int end);
         static Linalg::Vector3 computeRightTangent(const QVector<Linalg::Vector3>& d, int end);
         static Linalg::Vector3 computeCenterTangent(const QVector<Linalg::Vector3>& d, int center);
         static QVector<double> chordLengthParameterize(const QVector<Linalg::Vector3>& d, int first, int last);

         static void generateBezier(const QVector<Linalg::Vector3>& d,
                                    int first, int last,
                                    const QVector<double>& u,
                                    const Linalg::Vector3& tHat1,
                                    const Linalg::Vector3& tHat2,
                                    Linalg::Vector3 curve[4]);

         static std::tuple<double, int> computeMaxError(const QVector<Linalg::Vector3>& d,
                                                        int first, int last,
                                                        const Linalg::Vector3 curve[4],
                                                        const QVector<double>& u);

         static double newtonRaphsonRootFind(const Linalg::Vector3 curve[4], const Linalg::Vector3& point, double u);

         static QVector<double> reparameterize(const QVector<Linalg::Vector3>& d,
                                               int first, int last,
                                               const QVector<double>& u,
                                               const Linalg::Vector3 curve[4]);

         static void fitCubic(const QVector<Linalg::Vector3>& d,
                              int first, int last,
                              Linalg::Vector3 tHat1,
                              Linalg::Vector3 tHat2,
                              QVector<Linalg::Vector3>& segments,
                              const double errorTolerance);
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierRegressionAdaptiveH
