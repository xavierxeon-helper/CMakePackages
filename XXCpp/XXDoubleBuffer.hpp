#ifndef DoubleBufferHPP
#define DoubleBufferHPP

#include "XXDoubleBuffer.h"

template <typename DataType>
inline DoubleBuffer<DataType>::DoubleBuffer(const DataType& init1, const DataType& init2)
   : buffer{init1, init2}
   , firstIsCurrent(true)
{
}

template <typename DataType>
inline void DoubleBuffer<DataType>::swap()
{
   firstIsCurrent ^= true;
}

template <typename DataType>
inline DataType& DoubleBuffer<DataType>::current()
{
   return firstIsCurrent ? buffer[0] : buffer[1];
}

template <typename DataType>
inline const DataType& DoubleBuffer<DataType>::current() const
{
   return firstIsCurrent ? buffer[0] : buffer[1];
}

template <typename DataType>
inline DataType& DoubleBuffer<DataType>::previous()
{
   return firstIsCurrent ? buffer[1] : buffer[0];
}


#endif // NOT DoubleBufferHPP
