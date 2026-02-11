#include "XXRange.h"

#include <limits>

Range::Mapper::Mapper(const float& minInput, const float& maxInput, const float& minOutput, const float& maxOutput)
   : minInput(minInput)
   , maxInput(maxInput)
   , minOutput(minOutput)
   , maxOutput(maxOutput)
{
   updateScale();
}

void Range::Mapper::setMinInput(const float& value)
{
   if (value < maxInput)
   {
      minInput = value;
      updateScale();
   }
}

void Range::Mapper::setMaxInput(const float& value)
{
   if (value > minInput)
   {
      maxInput = value;
      updateScale();
   }
}

void Range::Mapper::setMinOutput(const float& value)
{
   minOutput = value;
   updateScale();
}

void Range::Mapper::setMaxOutput(const float& value)
{
   maxOutput = value;
   updateScale();
}

void Range::Mapper::updateScale()
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

float Range::Mapper::operator()(const float& input) const
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

Range::Spread::Iterator::Iterator(int startValue, int step)
   : number(startValue)
   , step(step)
   , isEnd(false)
{
}

Range::Spread::Iterator::Iterator(int endValue)
   : number(endValue)
   , step(0)
   , isEnd(true)
{
}

int Range::Spread::Iterator::operator*() const
{
   return number;
}

Range::Spread::Iterator& Range::Spread::Iterator::operator++()
{
   number += step;
   return *this;
}

bool Range::Spread::Iterator::operator==(const Iterator& other) const
{
   if (other.isEnd && number > other.number)
      return true;

   return (number == other.number);
}

bool Range::Spread::Iterator::operator!=(const Iterator& other) const
{
   return !operator==(other);
}

// spread

Range::Spread::Spread(int max)
   : Spread(0, max, 1)
{
}

Range::Spread::Spread(int min, int max, int step)
   : min(min)
   , max(max)
   , step(step)
{
}

Range::Spread::Iterator Range::Spread::begin()
{
   return Iterator(min, step);
}

Range::Spread::Iterator Range::Spread::end()
{
   return Iterator(max);
}
