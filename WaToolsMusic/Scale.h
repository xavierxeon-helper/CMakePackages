#ifndef ScaleH
#define ScaleH

#include "WaToolsMusicExportDef.h"

#include "Note.h"

class WATOOLSMUSIC_DECLSPEC Scale
{
public:
   using List = QList<Scale>;
   using KeyList = QList<bool>;

   static const QString sharpSymbol;
   static const QString flatSymbol;

   class Finder;

public:
   static List compileList();
   static KeyList initKeyList();

public:
   const QString getOffset() const;
   const QString& getMajorName() const;
   const QString& getMinorName() const;

   const KeyList& getActiveKeys() const;
   bool isActive(const int index) const;

   Note quantize(const Note& input) const;
   bool noteInScale(const Note& note) const;

private:
   Scale();

private:
   int offset;
   QString majorName;
   QString minorName;

   KeyList active;
};

class WATOOLSMUSIC_DECLSPEC Scale::Finder
{
public:
   Finder();

public:
   Scale::List addNote(const Note& note);
};

#endif // NOT ScaleH
