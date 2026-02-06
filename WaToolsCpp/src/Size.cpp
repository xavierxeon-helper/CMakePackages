#include "Size.h"

Size::Size(const uint16_t& width, const uint16_t height)
   : width(width)
   , height(height)
{
}

Size& Size::operator=(const Size& other)
{
   width = other.width;
   height = other.height;

   return *this;
}

bool Size::isZero() const
{
   return (0 == width) || (0 == height);
}
