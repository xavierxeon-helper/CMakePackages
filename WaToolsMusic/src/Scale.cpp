#include "Scale.h"

#include <QDirIterator>

const QString Scale::sharpSymbol = QString::fromUtf8("\u266F");
const QString Scale::flatSymbol = QString::fromUtf8("\u266D");

Scale::List Scale::compileList()
{
   List list;

   static const bool inScale[12] = {true, false, true, false, true, true, false, true, false, true, false, true};
   auto addScale = [&](const int& offset, QString majorName, QString minorName)
   {
      majorName.replace("sharp", sharpSymbol);
      majorName.replace("flat", flatSymbol);

      minorName.replace("sharp", sharpSymbol);
      minorName.replace("flat", flatSymbol);

      Scale data;
      data.offset = offset;
      data.majorName = majorName;
      data.minorName = minorName;

      for (int index = 0; index < 12; index++)
      {
         int note = (index + (7 * offset)) % 12;
         if (note < 0)
            note += 12;
         //qDebug() << offset << index << note << inScale[index];
         data.active[note] = inScale[index];
      }

      list.append(data);
   };

   //addScale(-7, "Cflat", "");
   addScale(-6, "Gflat", "eflat");
   addScale(-5, "Dflat", "bflat");
   addScale(-4, "Aflat", "f");
   addScale(-3, "Eflat", "c");
   addScale(-2, "Bflat", "g");
   addScale(-1, "F", "d");
   addScale(0, "C", "a");
   addScale(+1, "G", "e");
   addScale(+2, "D", "b");
   addScale(+3, "A", "fsharp");
   addScale(+4, "E", "csharp");
   addScale(+5, "B", "gsharp");
   addScale(+6, "Fsharp", "dsharp");
   //addScale(+7, "Csharp", "");

   return list;
}

Scale::KeyList Scale::initKeyList()
{
   return KeyList(12, false);
}

const QString Scale::getOffset() const
{
   return QString::number(offset);
}

const QString& Scale::getMajorName() const
{
   return majorName;
}

const QString& Scale::getMinorName() const
{
   return minorName;
}

const Scale::KeyList& Scale::getActiveKeys() const
{
   return active;
}

bool Scale::isActive(const int index) const
{
   if (index < 0 || index >= 12)
      return false;

   return active[index];
}

Note Scale::quantize(const Note& input) const
{
   const bool noteActive = isActive(input.getValue());
   if (noteActive)
      return input;

   return input.up();
}

Scale::Scale()
   : offset()
   , majorName()
   , minorName()
   , active(initKeyList())
{
}
