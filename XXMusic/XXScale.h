#ifndef ScaleH
#define ScaleH

#include "XXMusicExportDef.h"

#include <QMap>

#include "XXNote.h"

class XXMUSIC_DECLSPEC Scale
{
public:
   using List = QList<Scale>;
   using KeyList = QList<bool>;

   class Finder;

public:
   static List getList();
   static KeyList emptyKeyList();
   static Scale getScaleByName(const QString& name, bool isMajor = true);

public:
   const QString getOffset() const;
   const QString& getMajorName() const;
   const QString& getMinorName() const;

   const KeyList& getActiveKeys() const;
   bool isActive(const int index) const;

   Note quantize(const Note& input) const;
   bool noteInScale(const Note& note) const;

private:
   using Map = QMap<int, Scale>;

private:
   Scale();

private:
   int offset;
   QString majorName;
   QString minorName;

   KeyList active;

   static const Map availableScales;
};

class XXMUSIC_DECLSPEC Scale::Finder
{
public:
   Finder();

public:
   void addNote(const Note& note);
   const Scale::List& getScales() const;

private:
   Scale::List validScales;
};

#endif // NOT ScaleH
