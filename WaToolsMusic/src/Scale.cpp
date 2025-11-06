#include "Scale.h"

const Scale::Map Scale::availableScales = []()
{
   Map map;

   static const bool inScale[12] = {true, false, true, false, true, true, false, true, false, true, false, true};
   auto addScale = [&](const int& offset, QString majorName, QString minorName)
   {
      majorName.replace("sharp", Note::sharpSymbol);
      majorName.replace("flat", Note::flatSymbol);

      minorName.replace("sharp", Note::sharpSymbol);
      minorName.replace("flat", Note::flatSymbol);

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

      map.insert(offset, data);
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

   return map;
}();

Scale::List Scale::getList()
{
   return availableScales.values();
}

Scale Scale::getScaleByName(const QString& name, bool isMajor)
{
   for (const Scale& scale : availableScales)
   {
      if (isMajor && scale.getMajorName() == name)
         return scale;
      if (!isMajor && scale.getMinorName() == name)
         return scale;
   }
   return availableScales.value(0, Scale());
}

Scale::KeyList Scale::emptyKeyList()
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
   if (noteInScale(input))
      return input;

   return input.up();
}

bool Scale::noteInScale(const Note& note) const
{
   return isActive(note.getValue());
}

Scale::Scale()
   : offset()
   , majorName()
   , minorName()
   , active(emptyKeyList())
{
}

// Finder

Scale::Finder::Finder()
   : validScales(Scale::getList())
{
}

void Scale::Finder::addNote(const Note& note)
{
   Scale::List filteredScales;
   for (const Scale& scale : validScales)
   {
      if (scale.noteInScale(note))
         filteredScales.append(scale);
   }

   validScales = filteredScales;
}

const Scale::List& Scale::Finder::getScales() const
{
   return validScales;
}