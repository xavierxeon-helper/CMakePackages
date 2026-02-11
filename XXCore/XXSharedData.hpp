#ifndef SharedDataHPP
#define SharedDataHPP

#include "XXSharedData.h"

template <typename DataBlock>
SharedData<DataBlock>::List::~List()
{
   for (SharedData* data : *this)
      delete data;

   QList<SharedData*>::clear();
}

template <typename DataBlock>
SharedData<DataBlock>::Guard::Guard(SharedData* instance)
   : instance(instance)
{
   instance->sharedMemory.lock();
}

template <typename DataBlock>
SharedData<DataBlock>::Guard::~Guard()
{
   instance->sharedMemory.unlock();
}

template <typename DataBlock>
SharedData<DataBlock>::SharedData(const QString& uniqueName, bool readOnly)
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
SharedData<DataBlock>::~SharedData()
{
   {
      Guard guard(this);
      //cleanup();
   }

   sharedMemory.detach();
}

template <typename DataBlock>
const QString& SharedData<DataBlock>::getErrorString() const
{
   return errorString;
}

#endif // NOT SharedDataHPP
