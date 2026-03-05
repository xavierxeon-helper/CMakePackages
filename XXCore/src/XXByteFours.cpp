#include "XXByteFours.h"

const uint8_t XX::ByteFours::mask[4] = {0xC0, 0x30, 0x0C, 0x03};

XX::ByteFours::ByteFours(FoursValue a, FoursValue b, FoursValue c, FoursValue d)
   : fours{a, b, c, d}
{
}

XX::ByteFours::ByteFours(uint8_t byte)
   : ByteFours(O, O, O, O)
{
   for (const uint8_t index : {0, 1, 2, 3})
   {
      uint8_t value = byte & mask[index];
      const uint8_t shift = 2 * (3 - index);
      value = (value >> shift);

      fours[index] = static_cast<FoursValue>(value);
   }
}

XX::ByteFours::FoursValue XX::ByteFours::value(const FoursValue& index) const
{
   return fours[index];
}

XX::ByteFours::operator uint8_t() const
{
   uint8_t value = 0;

   for (const uint8_t index : {0, 1, 2, 3})
   {
      uint8_t part = static_cast<uint8_t>(fours[index]);
      const uint8_t shift = 2 * (3 - index);
      part = (part << shift);

      value += part;
   }

   return value;
}

QString XX::ByteFours::toString() const
{
   QString text = "4x";

   for (const uint8_t index : {0, 1, 2, 3})
   {
      if (ByteFours::O == fours[index])
         text += "O";
      else if (ByteFours::I == fours[index])
         text += "I";
      else if (ByteFours::Z == fours[index])
         text += "Z";
      else if (ByteFours::T == fours[index])
         text += "T";
   }

   return text;
}

//

std::ostream& XX::operator<<(std::ostream& out, const ByteFours& bf)
{
   const QString text = bf.toString();
   out << text.toStdString();

   return out;
}

QDebug XX::operator<<(QDebug stream, const ByteFours& bf)
{
   const QString text = bf.toString();
   stream << qPrintable(text);

   return stream;
}
