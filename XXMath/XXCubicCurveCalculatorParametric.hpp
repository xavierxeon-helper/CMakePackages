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
                                                                                              const Linalg::Vector3& p0,
                                                                                              const Linalg::Vector3& p1,
                                                                                              const Linalg::Vector3& p2,
                                                                                              const Linalg::Vector3& p3)
{
   Linalg::Matrix parameterMatrix(1, 4);
   parameterMatrix(0, 0) = 1;
   for (int index = 1; index < 4; ++index)
   {
      parameterMatrix(0, index) = parameterMatrix(0, index - 1) * parameter;
   }

   Linalg::Matrix controlMatrix(4, 3);
   for (int index = 0; index < 3; ++index)
   {
      controlMatrix(0, index) = p0[index];
      controlMatrix(1, index) = p1[index];
      controlMatrix(2, index) = p2[index];
      controlMatrix(3, index) = p3[index];
   }

   Linalg::Matrix resultMatrix = parameterMatrix * scale * basisMatrix * controlMatrix;
   Linalg::Vector3 result(resultMatrix(0, 0), resultMatrix(0, 1), resultMatrix(0, 2));

   return result;
}

#endif // NOT XXCubicCurveCalculatorParametricHPP
