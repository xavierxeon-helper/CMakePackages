#ifndef XXBezierRegressionAdaptiveH
#define XXBezierRegressionAdaptiveH

#include "XXMathExportDef.h"
#include "XXRegressionContainer2D.h"

#include "XXBezierUniformSpline.h"

namespace XX
{
   namespace Bezier
   {
      // use "An Algorithm for Automatically Fitting Digitized Curves" (Graphics Gems, 1990)

      class XXMATH_DECLSPEC RegressionAdaptive : public XX::Regression::Container2D
      {
      public:
         RegressionAdaptive(size_t size);

      public:
         XX::Bezier::UniformSpline fit() const;
         XX::Bezier::UniformSpline fit(const QVector<Linalg::Vector3>& points) const;

      private:
         double bernstein0(double u) const;
         double bernstein1(double u) const;
         double bernstein2(double u) const;
         double bernstein3(double u) const;

         Linalg::Vector3 evaluateBezier(const Linalg::Vector3 curve[4], double u) const;
         Linalg::Vector3 computeLeftTangent(const QVector<Linalg::Vector3>& d, int end) const;
         Linalg::Vector3 computeRightTangent(const QVector<Linalg::Vector3>& d, int end) const;
         Linalg::Vector3 computeCenterTangent(const QVector<Linalg::Vector3>& d, int center) const;
         QVector<double> chordLengthParameterize(const QVector<Linalg::Vector3>& d, int first, int last) const;

         void generateBezier(const QVector<Linalg::Vector3>& d,
                             int first, int last,
                             const QVector<double>& u,
                             const Linalg::Vector3& tHat1,
                             const Linalg::Vector3& tHat2,
                             Linalg::Vector3 curve[4]) const;
         double computeMaxError(const QVector<Linalg::Vector3>& d,
                                int first, int last,
                                const Linalg::Vector3 curve[4],
                                const QVector<double>& u,
                                int* splitPoint) const;

         double newtonRaphsonRootFind(const Linalg::Vector3 curve[4], const Linalg::Vector3& point, double u) const;

         QVector<double> reparameterize(const QVector<Linalg::Vector3>& d,
                                        int first, int last,
                                        const QVector<double>& u,
                                        const Linalg::Vector3 curve[4]) const;
         void fitCubic(const QVector<Linalg::Vector3>& d,
                       int first, int last,
                       Linalg::Vector3 tHat1,
                       Linalg::Vector3 tHat2,
                       double errorTolerance,
                       QVector<Linalg::Vector3>& segments) const;
      };
   } // namespace Bezier
} // namespace XX

#endif // NOT XXBezierRegressionAdaptiveH
