#include "XXRegressionContainer2D.h"

size_t XX::Regression::Container2D::Section::length() const
{
   return end - start;
}

//

XX::Regression::Container2D::Container2D(size_t size)
   : values(size, std::numeric_limits<double>::quiet_NaN())
{
}

size_t XX::Regression::Container2D::size() const
{
   return values.size();
}

void XX::Regression::Container2D::setValue(const size_t index, const double& value)
{
   if (index >= values.size())
      return;

   values[index] = value;
}

void XX::Regression::Container2D::clear()
{
   values.fill(std::numeric_limits<double>::quiet_NaN());
}

XX::Regression::Container2D::Section::List XX::Regression::Container2D::compileSections(double threshold, size_t maxSegmentLength) const
{
   Section::List sections;
   if (threshold <= 0)
   {
      Section all = {0, (size_t)values.size()};
      sections.append(all);
      return sections;
   }

   threshold = std::abs(threshold);

   size_t start = 0;
   for (size_t index = 1; index < values.size(); index++)
   {
      const double y1 = values.at(index - 1);
      const double y2 = values.at(index);

      const size_t length = index - start;
      const double yDiff = std::abs(y2 - y1);

      if (yDiff > threshold)
      {
         if (length > 1)
         {
            Section section = {start, index, false};
            sections.append(section);
         }

         start = index;
      }
      else if (maxSegmentLength > 0.0 && length > maxSegmentLength)
      {
         Section section = {start, index, true};
         sections.append(section);

         start = index;
      }
   }

   Section section = {start, (size_t)values.size() - 1};
   sections.append(section);

   return sections;
}

const QVector<double>& XX::Regression::Container2D::getValues() const
{
   return values;
}
