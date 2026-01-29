#ifndef SizeH
#define SizeH

#include "WaToolsCppExportDef.h"

#include <inttypes.h>

/// @brief simple size structure, to be used where QSize is not available
struct WATOOLSCPP_DECLSPEC Size
{
   uint16_t width;
   uint16_t height;

   Size(const uint16_t& width = 0, const uint16_t height = 0);
   Size& operator=(const Size& other);

   bool isZero() const;
};

#endif // NOT SizeH
