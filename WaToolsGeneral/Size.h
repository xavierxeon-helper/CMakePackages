#ifndef SizeH
#define SizeH

#include <inttypes.h>

struct Size
{
   uint16_t width;
   uint16_t height;

   Size(const uint16_t& width = 0, const uint16_t height = 0);
   Size& operator=(const Size& other);

   bool isZero() const;
};

#endif // NOT SizeH
