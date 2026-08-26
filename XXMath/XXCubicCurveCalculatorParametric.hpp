#ifndef XXCubicCurveCalculatorParametricHPP
#define XXCubicCurveCalculatorParametricHPP

#include "XXCubicCurveCalculatorParametric.h"

template <const double basisMatrixValues[16], const double scale>
const XX::Linalg::Matrix XX::CubicCurve::CalculatorParametric<basisMatrixValues, scale>::basisMatrix = []()
{
   Linalg::Matrix m(4, 4);

   for (int row = 0; row < 4; ++row)
   {
      for (int col = 0; col < 4; ++col)
      {
         m(row, col) = basisMatrixValues[row * 4 + col];
      }
   }

   return m;
}();

template <const double basisMatrixValues[16], const double scale>
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

   Linalg::Matrix controlMatrix(4, 3);
   for (int index = 0; index < 3; ++index)
   {
      controlMatrix(0, index) = p0[index];
      controlMatrix(1, index) = p1[index];
      controlMatrix(2, index) = p2[index];
      controlMatrix(3, index) = p3[index];
   }

   Linalg::Matrix resultMatrix = parameterMatrix * basisMatrix * controlMatrix;
   Linalg::Vector3 result(resultMatrix(0, 0), resultMatrix(0, 1), resultMatrix(0, 2));

   return result * scale;
}

#endif // NOT XXCubicCurveCalculatorParametricHPP
