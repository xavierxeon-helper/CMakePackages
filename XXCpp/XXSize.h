#ifndef XXSizeH
#define XXSizeH

#include "XXCppExportDef.h"

#include <inttypes.h>

namespace XX
{
   //! @brief simple size structure, to be used where QSize is not available
   //! @ingroup XXCpp

   struct XXCPP_DECLSPEC Size
   {
      uint16_t width;
      uint16_t height;

      Size(const uint16_t& width = 0, const uint16_t height = 0);
      Size& operator=(const Size& other);

      bool isZero() const;
   };
} // namespace XX

#endif // NOT XXSizeH
