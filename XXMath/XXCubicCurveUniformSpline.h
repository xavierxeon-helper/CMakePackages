#ifndef XXCubicCurveUniformSplineH
#define XXCubicCurveUniformSplineH

#include <XXCubicCurveCalculatorParametric.h>

namespace XX
{
   namespace CubicCurve
   {
      template <CubicCurve::CalculatorClass CalculatorClass>
      class UniformSpline
      {
      public:
         UniformSpline(const Linalg::Vector3& p0);

      public:
         virtual Linalg::Vector3 value(double parameter) const;
         int numberOfCures() const;

         virtual void addCurve(const Linalg::Vector3& p1, const Linalg::Vector3& p2, const Linalg::Vector3& p3);

      protected:
         QList<Linalg::Vector3> points;
      };
   } // namespace CubicCurve
} // namespace XX

#ifndef XXCubicCurveUniformSplineHPP
#include "XXCubicCurveUniformSpline.hpp"
#endif // NOT XXCubicCurveUniformSplineHPP

#endif // NOT XXCubicCurveUniformSplineH
