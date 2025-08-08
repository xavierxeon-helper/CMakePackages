#ifndef ScaleH
#define ScaleH

#include <QIcon>

class Scale
{
public:
   using List = QList<Scale>;
   using KeyList = QList<bool>;

   static const QString sharpSymbol;
   static const QString flatSymbol;

public:
   static List compileList();
   static KeyList initKeyList();

public:
   const QString getOffset() const;
   const QString& getMajorName() const;
   const QString& getMinorName() const;

   const KeyList& getActivceKeys() const;
   bool isActive(const int index) const;

private:
   Scale();

private:
   int offset;
   QString majorName;
   QString minorName;

   KeyList active;
};

#endif // NOT ScaleH
