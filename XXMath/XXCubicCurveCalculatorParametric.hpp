#ifndef XXCubicCurveCalculatorParametricHPP
#define XXCubicCurveCalculatorParametricHPP

#include "XXCubicCurveCalculatorParametric.h"

template <const std::array<double, 16> basisMatrixValues, const double scale>
const XX::Linalg::Matrix XX::CubicCurve::CalculatorParametric<basisMatrixValues, scale>::basisMatrix = []()
{
   Linalg::Matrix m(4, 4, std::span<const double>{basisMatrixValues});
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
   // [1 t t^2 t^3  ] parameterMatrix 0th derivative
   // [0 1 2t  3t^2 ] parameterMatrix 1st derivative
   // [0 0 2   6t   ] parameterMatrix 2nd derivative
   // [0 0 0   6    ] parameterMatrix 3rd derivative

   Linalg::Matrix parameterMatrix(1, 4);
   if (1 == derivativeOrder)
   {
      parameterMatrix(0, 0) = 0;
      parameterMatrix(0, 1) = 1;
      parameterMatrix(0, 2) = 2 * parameter;
      parameterMatrix(0, 3) = 3 * parameter * parameter;
   }
   else if (2 == derivativeOrder)
   {
      parameterMatrix(0, 0) = 0;
      parameterMatrix(0, 1) = 0;
      parameterMatrix(0, 2) = 2;
      parameterMatrix(0, 3) = 6 * parameter;
   }
   else if (3 == derivativeOrder)
   {
      parameterMatrix(0, 0) = 0;
      parameterMatrix(0, 1) = 0;
      parameterMatrix(0, 2) = 0;
      parameterMatrix(0, 3) = 6;
   }
   else
   {
      parameterMatrix(0, 0) = 1;
      parameterMatrix(0, 1) = parameter;
      parameterMatrix(0, 2) = parameter * parameter;
      parameterMatrix(0, 3) = parameter * parameter * parameter;
   }

   Linalg::Matrix pointMatrix(4, 3);
   for (int index = 0; index < 3; ++index)
   {
      pointMatrix(0, index) = p0[index];
      pointMatrix(1, index) = p1[index];
      pointMatrix(2, index) = p2[index];
      pointMatrix(3, index) = p3[index];
   }

   Linalg::Matrix resultMatrix = parameterMatrix * basisMatrix * pointMatrix;
   Linalg::Vector3 result(resultMatrix(0, 0), resultMatrix(0, 1), resultMatrix(0, 2));

   return result * scale;
}

#endif // NOT XXCubicCurveCalculatorParametricHPP
