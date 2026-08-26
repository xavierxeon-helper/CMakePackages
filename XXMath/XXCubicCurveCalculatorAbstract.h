#ifndef XXCubicCurveCalculatorAbstractH
#define XXCubicCurveCalculatorAbstractH

#include "XXMathExportDef.h"

#include <XXLinalgVector3.h>

namespace XX
{
   namespace CubicCurve
   {
      class XXMATH_DECLSPEC CalculatorAbstract
      {
      };

      // clang-format off
      template <typename T>
      concept CalculatorClass = std::derived_from<T, CalculatorAbstract> &&
      requires(double parameter, uchar derivativeOrder, const Linalg::Vector3& p0, const Linalg::Vector3& p1, const Linalg::Vector3& p2, const Linalg::Vector3& p3)
      {
         {
            T::calculate(parameter, derivativeOrder, p0, p1, p2, p3)
         } -> std::same_as<Linalg::Vector3>;
      };
      // clang-format on

   } // namespace CubicCurve
} // namespace XX

#endif // NOT XXCubicCurveCalculatorAbstractH
