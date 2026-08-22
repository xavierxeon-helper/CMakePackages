#ifndef XXUniformParametricSplineH
#define XXUniformParametricSplineH

#include <XXCubicCurveCalculatorParametric.h>

namespace XX
{
   template <CubicCurve::CalculatorClass CubicCurveClass>
   class UniformParametricSpline
   {
   public:
      UniformParametricSpline();

   public:
      virtual Linalg::Vector3 value(double parameter) const;
      int numberOfCures() const;

   protected:
      //QList<CubicCurveType> curves;
   };
} // namespace XX

#ifndef XXUniformParametricSplineHPP
#include "XXUniformParametricSpline.hpp"
#endif // NOT XXUniformParametricSplineHPP

#endif // NOT XXUniformParametricSplineH
