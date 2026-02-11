#include "XXMidiCommon.h"

Bytes& operator<<(Bytes& data, const uchar& byte)
{
   data.push_back(byte);
   return data;
}

bool Midi::isEvent(const uchar value, const Midi::Event mask)
{
   const bool isSystemEvent = (0xf0 == (value & 0xf0));

   if (isSystemEvent)
      return (mask == (mask & value));
   else
      return (mask == (value & 0xf0));
}

bool Midi::hasFirstBit(const uchar value)
{
   static const uchar checkMask = 0x80; // bit 7 only

   bool test = ((value & checkMask) == checkMask);
   return test;
}

uchar Midi::removeFirstBit(const uchar value)
{
   static const uchar valueMask = 0x7f; // all but bit 7

   return (value & valueMask);
}
