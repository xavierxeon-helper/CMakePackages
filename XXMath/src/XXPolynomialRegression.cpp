#include "XXPolynomialRegression.h"

#include <QDebug>

#include <XXLinalgMatrix.h>

XX::Polynomial::Regression::Regression(size_t size)
   : values(size, 0.0)
{
}

size_t XX::Polynomial::Regression::size() const
{
   return values.size();
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

XX::Polynomial::Segment::Bundle XX::Polynomial::Regression::fit(size_t degree, double threshold) const
{
   const Section::List sections = compileSections(threshold);

   Segment::Bundle bundle;
   for (const Section& section : sections)
   {
      Segment segment(degree);
      segment.setStart(section.start);
      segment.setEnd(section.end);

      const size_t length = section.end - section.start;

      XX::Linalg::Matrix yMatrix(length, 1);
      XX::Linalg::Matrix xMatrix(length, degree);

      for (size_t index = 0; index < length; index++)
      {
         const double x = (double)(index + section.start);
         const double y = values.at(index + section.start);

         yMatrix.setValue(index, 0, y);
         for (int d = 0; d < degree; d++)
            xMatrix.setValue(index, d, std::pow(x, degree - d));
      }

      const XX::Linalg::Matrix xTrans = xMatrix.transpose();
      const XX::Linalg::Matrix squareMatrix = (xTrans * xMatrix).inverse();
      const XX::Linalg::Matrix coeffMatrix = squareMatrix * xTrans * yMatrix;

      for (int c = 0; c < degree; c++)
         segment.setCoefficient(c, coeffMatrix.getValue(c, 0));

      bundle.append(segment);
   }

   return bundle;
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
