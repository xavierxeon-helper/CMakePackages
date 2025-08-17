#include "MathGeneral.h"

#include <math.h>

double Math::deg2Rad(const double& degrees)
{
   const double radians = degrees * (M_PI / 180);
   return radians;
}

double Math::rad2Deg(const double& radians)
{
   const double degrees = radians * (180 / M_PI);
   return degrees;
}

bool Math::signChange(const double& value1, const double& value2)
{
   if (value1 < 0.0 && value2 >= 0.0)
      return true;
   else if (value1 >= 0.0 && value2 < 0.0)
      return true;
   else
      return false;
}
