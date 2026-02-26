#ifndef XXLinalgGeneralHPP
#define XXLinalgGeneralHPP

#include "XXLinalg.h"

template <typename RealType>
std::complex<RealType> XX::Linalg::cartesianToPolar(const std::complex<RealType>& cartesian)
{
   const float x = cartesian.real();
   const float y = cartesian.imag();

   const float r = std::sqrt(x * x + y * y);
   const float theta = std::atan2(y, x);

   std::complex<RealType> result(r, theta);
   return result;
}

template <typename RealType>
std::complex<RealType> XX::Linalg::polarToCartesian(const std::complex<RealType>& polar)
{
   const float r = polar.real();
   const float theta = polar.imag();

   const float x = r * std::cos(theta);
   const float y = r * std::sin(theta);

   std::complex<RealType> result(x, y);
   return result;
}

#endif // NOT XXLinalgGeneralHPP
