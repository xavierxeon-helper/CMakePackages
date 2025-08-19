#ifndef MathGeneralH
#define MathGeneralH

#include "WaToolsMathExportDef.h"

#include <cmath>

namespace Math
{
   WATOOLSMATH_DECLSPEC double deg2Rad(const double& degrees);
   WATOOLSMATH_DECLSPEC double rad2Deg(const double& radians);

   WATOOLSMATH_DECLSPEC bool signChange(const double& value1, const double& value2);

   static const double pi = 2.0 * std::asin(1.0);

} // namespace Math

#endif // NOT MathGeneralH
