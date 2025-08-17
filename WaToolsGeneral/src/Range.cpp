#include "Range.h"

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
