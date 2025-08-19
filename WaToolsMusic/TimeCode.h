#ifndef TimeCodeH
#define TimeCodeH

#include "WaToolsMusicExportDef.h"

#include <limits>

#include <QString>

class WATOOLSMUSIC_DECLSPEC TimeCode
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

#endif // NOT TimeCodeH
