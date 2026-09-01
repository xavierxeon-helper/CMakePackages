#include "XXCubicCurveCalculatorAbstract.h"

XX::Linalg::Matrix XX::CubicCurve::CalculatorAbstract::calculateParameterMatrix(double parameter, uchar derivativeOrder)
{
   // [1 t t^2 t^3  ] parameterMatrix 0th derivative
   // [0 1 2t  3t^2 ] parameterMatrix 1st derivative
   // [0 0 2   6t   ] parameterMatrix 2nd derivative
   // [0 0 0   6    ] parameterMatrix 3rd derivative

   Linalg::Matrix parameterMatrix(1, 4);
   if (1 == derivativeOrder)
   {
      parameterMatrix[0, 0] = 0;
      parameterMatrix[0, 1] = 1;
      parameterMatrix[0, 2] = 2 * parameter;
      parameterMatrix[0, 3] = 3 * parameter * parameter;
   }
   else if (2 == derivativeOrder)
   {
      parameterMatrix[0, 0] = 0;
      parameterMatrix[0, 1] = 0;
      parameterMatrix[0, 2] = 2;
      parameterMatrix[0, 3] = 6 * parameter;
   }
   else if (3 == derivativeOrder)
   {
      parameterMatrix[0, 0] = 0;
      parameterMatrix[0, 1] = 0;
      parameterMatrix[0, 2] = 0;
      parameterMatrix[0, 3] = 6;
   }
   else
   {
      parameterMatrix[0, 0] = 1;
      parameterMatrix[0, 1] = parameter;
      parameterMatrix[0, 2] = parameter * parameter;
      parameterMatrix[0, 3] = parameter * parameter * parameter;
   }
   return parameterMatrix;
}

XX::Linalg::Matrix XX::CubicCurve::CalculatorAbstract::calculatePointMatrix(const Linalg::Vector3& p0, const Linalg::Vector3& p1, const Linalg::Vector3& p2, const Linalg::Vector3& p3)
{
   Linalg::Matrix pointMatrix(4, 3);
   for (int index = 0; index < 3; ++index)
   {
      pointMatrix[0, index] = p0[index];
      pointMatrix[1, index] = p1[index];
      pointMatrix[2, index] = p2[index];
      pointMatrix[3, index] = p3[index];
   }

   return pointMatrix;
}
