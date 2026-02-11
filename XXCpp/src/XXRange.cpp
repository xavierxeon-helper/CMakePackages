#include "XXRange.h"

#include <limits>

XX::Range::Mapper::Mapper(const float& minInput, const float& maxInput, const float& minOutput, const float& maxOutput)
   : minInput(minInput)
   , maxInput(maxInput)
   , minOutput(minOutput)
   , maxOutput(maxOutput)
{
   updateScale();
}

void XX::Range::Mapper::setMinInput(const float& value)
{
   if (value < maxInput)
   {
      minInput = value;
      updateScale();
   }
}

void XX::Range::Mapper::setMaxInput(const float& value)
{
   if (value > minInput)
   {
      maxInput = value;
      updateScale();
   }
}

void XX::Range::Mapper::setMinOutput(const float& value)
{
   minOutput = value;
   updateScale();
}

void XX::Range::Mapper::setMaxOutput(const float& value)
{
   maxOutput = value;
   updateScale();
}

void XX::Range::Mapper::updateScale()
{
   const float diffOutput = maxOutput - minOutput;
   const float diffInput = maxInput - minInput;

   if (0.0 >= diffInput || 0.0 >= diffOutput)
   {
      scale = 0.0;
   }
   else
   {
      scale = diffOutput / diffInput;
   }
}

float XX::Range::Mapper::operator()(const float& input) const
{
   if (input <= minInput)
      return minOutput;
   if (input >= maxInput)
      return maxOutput;

   const float diff = input - minInput;
   const float output = minOutput + (diff * scale);

   return output;
}

// spread iterator

XX::Range::Spread::Iterator::Iterator(int startValue, int step)
   : number(startValue)
   , step(step)
   , isEnd(false)
{
}

XX::Range::Spread::Iterator::Iterator(int endValue)
   : number(endValue)
   , step(0)
   , isEnd(true)
{
}

int XX::Range::Spread::Iterator::operator*() const
{
   return number;
}

XX::Range::Spread::Iterator& XX::Range::Spread::Iterator::operator++()
{
   number += step;
   return *this;
}

bool XX::Range::Spread::Iterator::operator==(const Iterator& other) const
{
   if (other.isEnd && number > other.number)
      return true;

   return (number == other.number);
}

bool XX::Range::Spread::Iterator::operator!=(const Iterator& other) const
{
   return !operator==(other);
}

// spread

XX::Range::Spread::Spread(int max)
   : Spread(0, max, 1)
{
}

XX::Range::Spread::Spread(int min, int max, int step)
   : min(min)
   , max(max)
   , step(step)
{
}

XX::Range::Spread::Iterator XX::Range::Spread::begin()
{
   return Iterator(min, step);
}

XX::Range::Spread::Iterator XX::Range::Spread::end()
{
   return Iterator(max);
}
