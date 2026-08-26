#ifndef XXCubicCurveUniformSplineH
#define XXCubicCurveUniformSplineH

#include <XXCubicCurveCalculatorParametric.h>

#include <QJsonObject>

namespace XX
{
   namespace CubicCurve
   {
      template <CubicCurve::CalculatorClass CalculatorClass>
      class UniformSpline
      {
      public:
         UniformSpline();
         UniformSpline(const Linalg::Vector3& p0);

      public:
         QJsonObject save() const;
         void load(const QJsonObject& data);

         virtual Linalg::Vector3 value(double parameter, uchar derivativeOrder = 0) const;
         int numberOfCurves() const;
         int numberOfPoints() const;

         double findParamter(const double& target, Linalg::Vector3::Index vectorIndex, double tolerance = 1e-9) const;
         Linalg::Vector3 findValue(const double& target, Linalg::Vector3::Index vectorIndex, double tolerance = 1e-9) const;

      protected:
         virtual void setStartPoint(const Linalg::Vector3& p);
         virtual void addCurvePoints(const Linalg::Vector3 p[3]);

      protected:
         QList<Linalg::Vector3> points;
      };
   } // namespace CubicCurve
} // namespace XX

#ifndef XXCubicCurveUniformSplineHPP
#include "XXCubicCurveUniformSpline.hpp"
#endif // NOT XXCubicCurveUniformSplineHPP

#endif // NOT XXCubicCurveUniformSplineH
