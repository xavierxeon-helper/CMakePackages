#ifndef MathGeneralH
#define MathGeneralH

#include "WaToolsMathExportDef.h"

#include <cmath>
#include <complex>
#include <cstddef>

namespace Math
{
   static const double pi = 2.0 * std::asin(1.0);

   WATOOLSMATH_DECLSPEC double deg2Rad(const double& degrees);
   WATOOLSMATH_DECLSPEC double rad2Deg(const double& radians);

   WATOOLSMATH_DECLSPEC bool signChange(const double& value1, const double& value2);

   WATOOLSMATH_DECLSPEC size_t getNearestPowerOfTwo(const size_t& num);
   WATOOLSMATH_DECLSPEC bool isPowerOfTwo(const size_t& num);

   // for 3d version see Math::Vector3
   template <typename RealType = float>
   std::complex<RealType> cartesianToPolar(const std::complex<RealType>& cartesian);

   template <typename RealType = float>
   std::complex<RealType> polarToCartesian(const std::complex<RealType>& polar);

} // namespace Math

#ifndef MathGeneralHPP
#include "MathGeneral.hpp"
#endif // NOT MathGeneralHPP

#endif // NOT MathGeneralH
