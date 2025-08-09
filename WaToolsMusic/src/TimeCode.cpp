#ifndef TimeCodeHPP
#define TimeCodeHPP

#include "TimeCode.h"

TimeCode::TimeCode()
   : bar(0)
   , quarter(0)
   , tick(0)
{
}

TimeCode::TimeCode(uint16_t bar, uchar quarter, uchar tick)
   : bar(bar)
   , quarter(quarter)
   , tick(tick)
{
}

TimeCode::TimeCode(const Duration& duration)
   : TimeCode()
{
   tick = duration % 4;
   quarter = ((duration - tick) / 4) % 4;

   const uchar restTicks = tick + (quarter * 4);
   const uint16_t barTicks = duration - restTicks;
   bar = barTicks / 16;
}

QString TimeCode::text() const
{
   const QString frontText = QString::number(bar + 1);
   const QString midText = QString::number(quarter + 1);
   const QString backText = QString::number(tick + 1);

   const QString durationText = frontText + " " + midText + " " + backText;
   return durationText;
}

TimeCode::Duration TimeCode::toDuration() const
{
   const Duration duration = (16 * bar) + (4 * quarter) + tick;
   return duration;
}

#endif // NOT TimeCodeHPP
