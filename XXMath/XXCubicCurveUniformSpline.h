#ifndef XXCubicCurveUniformSplineH
#define XXCubicCurveUniformSplineH

#include <XXCubicCurveCalculatorParametric.h>
#include <XXCubicCurveUniformSplineAbstract.h>

#include <QJsonObject>

namespace XX
{
   namespace CubicCurve
   {
      template <CubicCurve::CalculatorClass CalculatorClass>
      class UniformSpline : public UniformSplineAbstract
      {
      public:
         UniformSpline();
         UniformSpline(const Linalg::Vector3& p0);

      protected:
         Linalg::Vector3 calculate(double localParameter, int derivativeOrder, const Linalg::Vector3& p0, const Linalg::Vector3& p1, const Linalg::Vector3& p2, const Linalg::Vector3& p3) const override;
      };

   } // namespace CubicCurve
} // namespace XX

#ifndef XXCubicCurveUniformSplineHPP
#include "XXCubicCurveUniformSpline.hpp"
#endif // NOT XXCubicCurveUniformSplineHPP

#endif // NOT XXCubicCurveUniformSplineH
