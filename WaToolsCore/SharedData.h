#ifndef SharedDataH
#define SharedDataH

#include <QSharedMemory>

#include <QList>

template <typename DataBlock>
class SharedData
{
public:
   class List : public QList<SharedData*>
   {
   public:
      List() = default;
      ~List();
   };

   class Guard
   {
   public:
      Guard(SharedData* instance);
      ~Guard();

   private:
      SharedData* instance;
   };

public:
   SharedData(const QString& uniqueName, bool readOnly);
   virtual ~SharedData();

public:
   const QString& getErrorString() const;

protected:
   DataBlock* dataBlock;
   bool readOnly;

private:
   QSharedMemory sharedMemory;
   QString errorString;
};

#ifndef SharedDataHPP
#include "SharedData.hpp"
#endif // NOT SharedDataHPP

#endif // NOT SharedDataH
