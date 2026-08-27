#ifndef XXCubicCurveCalculatorParametricH
#define XXCubicCurveCalculatorParametricH

#include <XXCubicCurveCalculatorAbstract.h>

#include <XXLinalgMatrix.h>

// see https://www.cs.helsinki.fi/group/goa/mallinnus/curves/curves.html

namespace XX
{
   namespace CubicCurve
   {
      template <const std::array<double, 16> basisMatrixValues, const double scale>
      class CalculatorParametric : public CalculatorAbstract
      {
      public:
         static Linalg::Vector3 calculate(double parameter,
                                          uchar derivativeOrder,
                                          const Linalg::Vector3& p0,
                                          const Linalg::Vector3& p1,
                                          const Linalg::Vector3& p2,
                                          const Linalg::Vector3& p3);

      private:
         static const Linalg::Matrix basisMatrix;
      };
   } // namespace CubicCurve
} // namespace XX

#ifndef XXCubicCurveCalculatorParametricHPP
#include "XXCubicCurveCalculatorParametric.hpp"
#endif // NOT XXCubicCurveCalculatorParametricHPP

#endif // NOT XXCubicCurveCalculatorParametricH
