#ifndef MathHelperHPP
#define MathHelperHPP

#include "MathHelper.h"

inline size_t getNearestPowerOfTwo(const size_t& num)
{
   if (num == 0)
      return 1;

   size_t powerOfTwo = 1;
   while (powerOfTwo < num)
      powerOfTwo <<= 1;

   return powerOfTwo;
}

inline bool isPowerOfTwo(const size_t& num)
{
   return (num == getNearestPowerOfTwo(num));
}

template <typename RealType>
inline std::complex<RealType> cartesianToPolar(const std::complex<RealType>& cartesian)
{
   const float x = cartesian.real();
   const float y = cartesian.imag();

   const float r = std::sqrt(x * x + y * y);
   const float theta = std::atan2(y, x);

   std::complex<RealType> result(r, theta);
   return result;
}

template <typename RealType>
inline std::complex<RealType> polarToCartesian(const std::complex<RealType>& polar)
{
   const float r = polar.real();
   const float theta = polar.imag();

   const float x = r * std::cos(theta);
   const float y = r * std::sin(theta);

   std::complex<RealType> result(x, y);
   return result;
}

#endif // NOT MathHelperHPP
