#ifndef TimeCodeH
#define TimeCodeH

#include <limits>

#include <QString>

class TimeCode
{
public:
   using Duration = uint16_t;
   static constexpr Duration maxDuration = std::numeric_limits<Duration>::max() - 1;

public:
   TimeCode();
   TimeCode(uint16_t bar, uint8_t quarter, uint8_t tick = 0);
   TimeCode(const Duration& duration);

public:
   QString text() const;
   Duration toDuration() const;

public:
   uint16_t bar;
   uint8_t quarter;
   uint8_t tick;
};

#endif // NOT TimeCodeH
