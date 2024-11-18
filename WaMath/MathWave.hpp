#ifndef MathWaveHPP
#define MathWaveHPP

#include "MathWave.h"

#include <cmath>

inline Math::Wave::Wave(const Size& size, const int& threadCount)
   : size(size)
   , threadCount(threadCount)
   , threads(threadCount)
   , lineLists()
   , frequency(1.0)
   , speed(1.0)
   , omega(2.0 * M_PI)
   , heightField(Matrix<double>(size, 0.0), Matrix<double>(size, 0.0))
{
   const int maxCount = std::ceil(size.height / threadCount);

   LineList list;
   for (uint16_t x = 0; x < size.width; x++)
   {
      list.push_back(x);
      if (list.size() >= maxCount)
      {
         lineLists.push_back(list);
         list.clear();
      }
   }
   if (0 < list.size())
      lineLists.push_back(list);
}

inline void Math::Wave::step(const double& time)
{
   heightField.swap();

   for (uint16_t index = 0; index < threadCount; index++)
      threads[index] = std::thread(&Wave::advanceLines, this, index);

   for (uint16_t index = 0; index < threadCount; index++)
      threads[index].join();
}

inline const Matrix<double>& Math::Wave::getHeightField() const
{
   return heightField.current();
}

inline const Size& Math::Wave::getSize() const
{
   return size;
}

inline const double& Math::Wave::getFrequency() const
{
   return frequency;
}

inline void Math::Wave::setFrequency(const double& value)
{
   frequency = value;
   omega = value * 2.0 * M_PI;
}

inline const double& Math::Wave::getSpeed() const
{
   return speed;
}

inline void Math::Wave::setSpeed(const double& value)
{
   speed = value;
}

inline void Math::Wave::advanceLines(const quint16 lineIndex)
{
   const double damping = 1.0;

   Matrix<double>& current = heightField.current();
   const Matrix<double>& previous = heightField.previous();

   const LineList& lineList = lineLists[lineIndex];
   for (const uint16_t x : lineList)
   {
      for (uint16_t y = 0; y < size.height; y++)
      {
         double height = 0.0;
         const double center = current[x][y];

         if (x > 0)
            height += previous[x - 1][y];
         if (x + 1 < size.width)
            height += previous[x + 1][y];
         if (y > 0)
            height += previous[x][y - 1];
         if (y + 1 < size.height)
            height += previous[x][y + 1];

         current[x][y] = (0.5 * height) - center;
         current[x][y] *= damping;
      }
   }
}

#endif // NOT MathWaveHPP
