#ifndef SizeHPP
#define SizeHPP

#include "Size.h"

inline Size::Size(const uint16_t& width, const uint16_t height)
   : width(width)
   , height(height)
{

}

inline Size& Size::operator=(const Size& other)
{
   width = other.width;
   height = other.height;

   return *this;
}

inline bool Size::isZero() const
{
   return (0 == width) || (0 == height);
}

#endif // NOT SizeHPP
