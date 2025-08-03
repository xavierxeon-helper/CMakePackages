#ifndef MathHelperH
#define MathHelperH

#include <complex>
#include <cstddef>

#include <QtMath>

size_t getNearestPowerOfTwo(const size_t& num);
bool isPowerOfTwo(const size_t& num);

template <typename RealType = float>
std::complex<RealType> cartesianToPolar(const std::complex<RealType>& cartesian);

template <typename RealType = float>
std::complex<RealType> polarToCartesian(const std::complex<RealType>& polar);

#ifndef MathHelperHPP
#include "MathHelper.hpp"
#endif // NOT MathHelperHPP

#endif // NOT MathHelperHPP
