#include "XXScale.h"

const XX::Scale::Map XX::Scale::availableScales = []()
{
   Map map;

   static const bool inScale[12] = {true, false, true, false, true, true, false, true, false, true, false, true};
   auto addScale = [&](const int& offset, QString majorName, QString minorName)
   {
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

   //addScale(-7, "C" + Note::flatSymbol, "");
   addScale(-6, "G" + Note::flatSymbol, "e" + Note::flatSymbol);
   addScale(-5, "D" + Note::flatSymbol, "b" + Note::flatSymbol);
   addScale(-4, "A" + Note::flatSymbol, "f");
   addScale(-3, "E" + Note::flatSymbol, "c");
   addScale(-2, "B" + Note::flatSymbol, "g");
   addScale(-1, "F", "d");
   addScale(0, "C", "a");
   addScale(+1, "G", "e");
   addScale(+2, "D", "b");
   addScale(+3, "A", "f" + Note::sharpSymbol);
   addScale(+4, "E", "c" + Note::sharpSymbol);
   addScale(+5, "B", "g" + Note::sharpSymbol);
   addScale(+6, "F" + Note::sharpSymbol, "d" + Note::sharpSymbol);
   //addScale(+7, "C"+Note::sharpSymbol, "");

   return map;
}();

XX::Scale::List XX::Scale::getList()
{
   return availableScales.values();
}

XX::Scale XX::Scale::getScaleByName(const QString& name, bool isMajor)
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

XX::Scale::KeyList XX::Scale::emptyKeyList()
{
   return KeyList(12, false);
}

const QString XX::Scale::getOffset() const
{
   return QString::number(offset);
}

const QString& XX::Scale::getMajorName() const
{
   return majorName;
}

const QString& XX::Scale::getMinorName() const
{
   return minorName;
}

const XX::Scale::KeyList& XX::Scale::getActiveKeys() const
{
   return active;
}

bool XX::Scale::isActive(const int index) const
{
   if (index < 0 || index >= 12)
      return false;

   return active[index];
}

XX::Note XX::Scale::quantize(const XX::Note& input) const
{
   if (noteInScale(input))
      return input;

   return input.up();
}

bool XX::Scale::noteInScale(const XX::Note& note) const
{
   return isActive(note.getValue());
}

XX::Scale::Scale()
   : offset()
   , majorName()
   , minorName()
   , active(emptyKeyList())
{
}

// Finder

XX::Scale::Finder::Finder()
   : validScales(XX::Scale::getList())
{
}

void XX::Scale::Finder::addNote(const XX::Note& note)
{
   Scale::List filteredScales;
   for (const Scale& scale : validScales)
   {
      if (scale.noteInScale(note))
         filteredScales.append(scale);
   }

   validScales = filteredScales;
}

const XX::Scale::List& XX::Scale::Finder::getScales() const
{
   return validScales;
}