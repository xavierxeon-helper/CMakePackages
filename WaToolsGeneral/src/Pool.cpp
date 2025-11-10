#include "Pool.h"

// iterator

Pool::Iterator::Iterator(int number, int step, bool isEnd)
   : number(number)
   , step(step)
   , isEnd(isEnd)
{
}

int Pool::Iterator::operator*() const
{
   return number;
}

Pool::Iterator& Pool::Iterator::operator++()
{
   number += step;
   return *this;
}

bool Pool::Iterator::operator==(const Iterator& other) const
{
   if (other.isEnd && number > other.number)
      return true;

   return (number == other.number);
}

bool Pool::Iterator::operator!=(const Iterator& other) const
{
   return !operator==(other);
}

// pool

Pool::Pool(int max)
   : Pool(0, max, 1)
{
}

Pool::Pool(int min, int max, int step)
   : min(min)
   , max(max)
   , step(step)
{
}

Pool::Iterator Pool::begin()
{
   return Iterator(min, step, false);
}

Pool::Iterator Pool::end()
{
   return Iterator(max, step, true);
}
