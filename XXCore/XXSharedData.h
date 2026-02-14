#ifndef XXSharedDataH
#define XXSharedDataH

#include <QSharedMemory>

#include <QList>

namespace XX
{
   //! @brief manage shared data across processes
   //! @ingroup XXCore

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
} // namespace XX

#ifndef XXSharedDataHPP
#include "XXSharedData.hpp"
#endif // NOT XXSharedDataHPP

#endif // NOT XXSharedDataH
