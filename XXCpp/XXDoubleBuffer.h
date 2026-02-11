#ifndef XXDoubleBufferH
#define XXDoubleBufferH

namespace XX
{
   template <typename DataType>
   class DoubleBuffer
   {
   public:
      DoubleBuffer(const DataType& init1 = DataType(), const DataType& init2 = DataType());

   public:
      void swap();

      DataType& current();
      const DataType& current() const;

      DataType& previous();

   private:
      DataType buffer[2];
      bool firstIsCurrent;
   };
} // namespace XX

#ifndef XXDoubleBufferHPP
#include "XXDoubleBuffer.hpp"
#endif // NOT XXDoubleBufferHPP

#endif // NOT XXDoubleBufferH
