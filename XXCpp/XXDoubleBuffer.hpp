#ifndef XXDoubleBufferHPP
#define XXDoubleBufferHPP

#include "XXDoubleBuffer.h"

template <typename DataType>
inline XX::DoubleBuffer<DataType>::DoubleBuffer(const DataType& init1, const DataType& init2)
   : buffer{init1, init2}
   , firstIsCurrent(true)
{
}

template <typename DataType>
inline void XX::DoubleBuffer<DataType>::swap()
{
   firstIsCurrent ^= true;
}

template <typename DataType>
inline DataType& XX::DoubleBuffer<DataType>::current()
{
   return firstIsCurrent ? buffer[0] : buffer[1];
}

template <typename DataType>
inline const DataType& XX::DoubleBuffer<DataType>::current() const
{
   return firstIsCurrent ? buffer[0] : buffer[1];
}

template <typename DataType>
inline DataType& XX::DoubleBuffer<DataType>::previous()
{
   return firstIsCurrent ? buffer[1] : buffer[0];
}

#endif // NOT XXDoubleBufferHPP
