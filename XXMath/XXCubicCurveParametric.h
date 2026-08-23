#ifndef XXCubicCurveParametricH
#define XXCubicCurveParametricH

#include <XXCubicCurveCalculatorParametric.h>

namespace XX
{
   namespace CubicCurve
   {
      template <CubicCurve::CalculatorClass CalculatorClass>
      class Parametric
      {
      public:
         Parametric();

      public:
         Linalg::Vector3 value(double parameter) const;

      protected:
         Linalg::Vector3 p0;
         Linalg::Vector3 p1;
         Linalg::Vector3 p2;
         Linalg::Vector3 p3;
      };
   } // namespace CubicCurve
} // namespace XX

#ifndef XXCubicCurveParametricHPP
#include "XXCubicCurveParametric.hpp"
#endif // NOT XXCubicCurveParametricHPP

#endif // NOT XXCubicCurveParametricH
