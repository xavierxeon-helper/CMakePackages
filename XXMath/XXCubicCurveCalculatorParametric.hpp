#ifndef XXCubicCurveCalculatorParametricHPP
#define XXCubicCurveCalculatorParametricHPP

#include "XXCubicCurveCalculatorParametric.h"

template <const std::array<double, 16> basisMatrixValues, const double scale>
const XX::Linalg::Matrix XX::CubicCurve::CalculatorParametric<basisMatrixValues, scale>::basisMatrix = []()
{
   Linalg::Matrix m(4, 4, std::span<const double>{basisMatrixValues});
   m *= scale;
   return m;
}();

template <const std::array<double, 16> basisMatrixValues, const double scale>
XX::Linalg::Vector3 XX::CubicCurve::CalculatorParametric<basisMatrixValues, scale>::calculate(double parameter,
                                                                                              uchar derivativeOrder,
                                                                                              const Linalg::Vector3& p0,
                                                                                              const Linalg::Vector3& p1,
                                                                                              const Linalg::Vector3& p2,
                                                                                              const Linalg::Vector3& p3)
{
   const Linalg::Matrix parameterMatrix = calculateParameterMatrix(parameter, derivativeOrder);
   const Linalg::Matrix pointMatrix = calculatePointMatrix(p0, p1, p2, p3);

   Linalg::Matrix resultMatrix = parameterMatrix * basisMatrix * pointMatrix;
   Linalg::Vector3 result(resultMatrix(0, 0), resultMatrix(0, 1), resultMatrix(0, 2));

   return result;
}

#endif // NOT XXCubicCurveCalculatorParametricHPP
