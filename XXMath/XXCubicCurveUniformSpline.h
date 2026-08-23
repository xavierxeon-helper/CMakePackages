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
         UniformSpline();

      public:
         virtual Linalg::Vector3 value(double parameter) const;
         int numberOfCures() const;

      protected:
         //QList<CubicCurveType> curves;
      };
   } // namespace CubicCurve
} // namespace XX

#ifndef XXCubicCurveUniformSplineHPP
#include "XXCubicCurveUniformSpline.hpp"
#endif // NOT XXCubicCurveUniformSplineHPP

#endif // NOT XXCubicCurveUniformSplineH
