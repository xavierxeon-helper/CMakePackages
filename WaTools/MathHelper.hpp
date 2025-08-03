#ifndef MathHelperHPP
#define MathHelperHPP

#include "MathHelper.h"

inline bool MathHelper::isPowerOfTwo(const size_t& num)
{
   // "complement and compare" method
   return num && (!(num & (num - 1)));
}

inline size_t MathHelper::getNearestPowerOfTwo(const size_t& num)
{
   if (num == 0)
      return 1;

   size_t power = 1;
   while (power < num)
      power <<= 1;

   return power;
}

#endif // NOT MathHelperHPP
