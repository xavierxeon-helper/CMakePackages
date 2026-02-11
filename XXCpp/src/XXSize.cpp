#include "XXSize.h"

XX::Size::Size(const uint16_t& width, const uint16_t height)
   : width(width)
   , height(height)
{
}

XX::Size& XX::Size::operator=(const XX::Size& other)
{
   width = other.width;
   height = other.height;

   return *this;
}

bool XX::Size::isZero() const
{
   return (0 == width) || (0 == height);
}
