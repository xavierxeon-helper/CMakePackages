#ifndef XXTimeCodeH
#define XXTimeCodeH

#include "XXMusicExportDef.h"

#include <limits>

#include <QString>

namespace XX
{
   //! @brief time code
   //! @ingroup XXMusic

   class XXMUSIC_DECLSPEC TimeCode
   {
   public:
      using Duration = uint16_t;
      static constexpr Duration maxDuration = std::numeric_limits<Duration>::max() - 1;

   public:
      TimeCode();
      TimeCode(uint16_t bar, uchar quarter, uchar tick = 0);
      TimeCode(const Duration& duration);

   public:
      QString text() const;
      Duration toDuration() const;

   public:
      uint16_t bar;
      uchar quarter;
      uchar tick;
   };
} // namespace XX

#endif // NOT XXTimeCodeH
