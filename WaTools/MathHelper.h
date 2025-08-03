#ifndef MathHelperH
#define MathHelperH

#include <cinttypes>
#include <cstddef>

#include <QtMath>

class MathHelper
{
public:
   static bool isPowerOfTwo(const size_t& num);
   static size_t getNearestPowerOfTwo(const size_t& num);
};

#ifndef MathHelperHPP
#include "MathHelper.hpp"
#endif // NOT MathHelperHPP

#endif // NOT MathHelperHPP
