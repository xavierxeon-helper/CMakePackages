#ifndef XXMathH
#define XXMathH

#include "XXMathExportDef.h"

#include <cmath>
#include <QVector>

namespace XX
{
   namespace Math
   {
      static const double pi = 2.0 * std::asin(1.0);
      static const double epsilon = 1e-12;

      XXMATH_DECLSPEC double deg2Rad(const double& degrees);
      XXMATH_DECLSPEC double rad2Deg(const double& radians);

      XXMATH_DECLSPEC bool signChange(const double& value1, const double& value2);

      XXMATH_DECLSPEC size_t getNearestPowerOfTwo(const size_t& num);
      XXMATH_DECLSPEC bool isPowerOfTwo(const size_t& num);

      XXMATH_DECLSPEC QVector<double> derivative(const QVector<double>& values, uint8_t order);

   } // namespace Math
} // namespace XX

#endif // NOT XXMathH
