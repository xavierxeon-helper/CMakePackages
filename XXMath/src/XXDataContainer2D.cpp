#include "XXDataContainer2D.h"

size_t XX::Data::Container2D::Section::length() const
{
   return end - start;
}

//

const double XX::Data::Container2D::nullValue = std::numeric_limits<double>::quiet_NaN();

XX::Data::Container2D::Container2D(size_t size)
   : values(size, nullValue)
{
}

size_t XX::Data::Container2D::size() const
{
   return values.size();
}

void XX::Data::Container2D::setValue(const size_t index, const double& value)
{
   if (index >= values.size())
      return;

   values[index] = value;
}

void XX::Data::Container2D::setNull(const size_t index)
{
   setValue(index, nullValue);
}

void XX::Data::Container2D::clear()
{
   values.fill(nullValue);
}

XX::Data::Container2D::Section::List XX::Data::Container2D::compileSections(double threshold, size_t maxSegmentLength) const
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

      auto getDiff = [&]() -> double
      {
         if (!std::isnan(y1) && std::isnan(y2))
            return y1;
         else if (std::isnan(y1) && !std::isnan(y2))
            return y2;
         else if (std::isnan(y1) && std::isnan(y2))
            return 0.0;

         return std::abs(y2 - y1);
      };

      const double yDiff = getDiff();

      if (yDiff > threshold)
      {
         if (length > 1)
         {
            const double startValue = values.at(start);
            if (!std::isnan(startValue))
            {
               Section section = {start, index, false};
               sections.append(section);
            }
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

   const double startValue = values.at(start);
   if (!std::isnan(startValue))
   {
      Section section = {start, (size_t)values.size() - 1};
      sections.append(section);
   }

   return sections;
}

const QVector<double>& XX::Data::Container2D::getValues() const
{
   return values;
}
