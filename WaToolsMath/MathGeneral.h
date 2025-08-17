#ifndef MathGeneralH
#define MathGeneralH

#include <cmath>

namespace Math
{
   double deg2Rad(const double& degrees);
   double rad2Deg(const double& radians);

   bool signChange(const double& value1, const double& value2);

   static const double pi = 2.0 * std::asin(1.0);
   ;
} // namespace Math

#endif // NOT MathGeneralH
