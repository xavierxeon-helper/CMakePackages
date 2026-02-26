#include "XXPolynomialRegression.h"

XX::Polynomial::Regression::Regression(size_t size)
   : values(size, 0.0)
{
}

void XX::Polynomial::Regression::setValue(const size_t index, const double& value)
{
   if (index >= values.size())
      return;

   values[index] = value;
}

void XX::Polynomial::Regression::clear()
{
   values = QVector<double>(values.size(), 0.0);
}

XX::Polynomial::Regression::Section::List XX::Polynomial::Regression::compileSections(double threshold) const
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

      const double yDiff = std::abs(y2 - y1);
      if (yDiff < threshold)
         continue;

      Section section = {start, index};
      sections.append(section);

      start = index;
   }

   Section section = {start, (size_t)values.size() - 1};
   sections.append(section);

   return sections;
}

const QVector<double>& XX::Polynomial::Regression::getRawValues() const
{
   return values;
}

XX::Polynomial::Segment::Bundle XX::Polynomial::Regression::fit(size_t degree) const
{
   Segment::Bundle bundle;

   return bundle;
}
