#ifndef XXSharedDataHPP
#define XXSharedDataHPP

#include "XXSharedData.h"

template <typename DataBlock>
XX::SharedData<DataBlock>::List::~List()
{
   for (SharedData* data : *this)
      delete data;

   QList<SharedData*>::clear();
}

template <typename DataBlock>
XX::SharedData<DataBlock>::Guard::Guard(SharedData* instance)
   : instance(instance)
{
   instance->sharedMemory.lock();
}

template <typename DataBlock>
XX::SharedData<DataBlock>::Guard::~Guard()
{
   instance->sharedMemory.unlock();
}

template <typename DataBlock>
XX::SharedData<DataBlock>::SharedData(const QString& uniqueName, bool readOnly)
   : dataBlock(nullptr)
   , readOnly(readOnly)
   , sharedMemory(uniqueName)
   , errorString()
{
   const QSharedMemory::AccessMode mode = readOnly ? QSharedMemory::ReadOnly : QSharedMemory::ReadWrite;
   if (sharedMemory.create(sizeof(DataBlock), mode))
   {
      dataBlock = reinterpret_cast<DataBlock*>(sharedMemory.data());
      return;
   }

   errorString = sharedMemory.errorString();
   if (QSharedMemory::AlreadyExists == sharedMemory.error())
   {
      sharedMemory.attach(mode);
      if (0 == sharedMemory.size())
      {
         sharedMemory.detach();
         sharedMemory.create(sizeof(DataBlock), mode);
      }
      errorString = sharedMemory.errorString();
      dataBlock = reinterpret_cast<DataBlock*>(sharedMemory.data());
   }
}

template <typename DataBlock>
XX::SharedData<DataBlock>::~SharedData()
{
   {
      Guard guard(this);
      //cleanup();
   }

   sharedMemory.detach();
}

template <typename DataBlock>
const QString& XX::SharedData<DataBlock>::getErrorString() const
{
   return errorString;
}

#endif // NOT XXSharedDataHPP
