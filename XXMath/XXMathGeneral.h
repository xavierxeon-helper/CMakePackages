#ifndef XXMathGeneralH
#define XXMathGeneralH

#include "XXMathExportDef.h"

#include <cmath>
#include <complex>
#include <cstddef>

namespace XX
{
   namespace Math
   {
      static const double pi = 2.0 * std::asin(1.0);

      XXMATH_DECLSPEC double deg2Rad(const double& degrees);
      XXMATH_DECLSPEC double rad2Deg(const double& radians);

      XXMATH_DECLSPEC bool signChange(const double& value1, const double& value2);

      XXMATH_DECLSPEC size_t getNearestPowerOfTwo(const size_t& num);
      XXMATH_DECLSPEC bool isPowerOfTwo(const size_t& num);

      // for 3d version see Math::Vector3
      template <typename RealType = float>
      std::complex<RealType> cartesianToPolar(const std::complex<RealType>& cartesian);

      template <typename RealType = float>
      std::complex<RealType> polarToCartesian(const std::complex<RealType>& polar);

   } // namespace Math
} // namespace XX

#ifndef XXMathGeneralHPP
#include "XXMathGeneral.hpp"
#endif // NOT XXMathGeneralHPP

#endif // NOT XXMathGeneralH
