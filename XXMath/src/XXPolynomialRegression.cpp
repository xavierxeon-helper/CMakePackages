#include "XXPolynomialRegression.h"

#include <QDebug>

#include <XXLinalgMatrix.h>

size_t XX::Polynomial::Regression::Section::length() const
{
   return end - start;
}

//

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

XX::Polynomial::Segment::Bundle XX::Polynomial::Regression::fit(size_t degree, double threshold, size_t overFit, size_t maxSegmentLength) const
{
   const Section::List sections = compileSections(threshold, maxSegmentLength);

   Segment::Bundle bundle;
   for (int sectionIndex = 0; sectionIndex < sections.size(); sectionIndex++)
   {
      const Section& section = sections.at(sectionIndex);

      Segment segment(degree);
      segment.setStart(section.start);
      segment.setEnd(section.end);

      size_t length = section.length();
      size_t start = section.start;

      std::function<void(const size_t)> extendBackwards = [&](const size_t offset)
      {
         if (overFit == offset)
            return;

         const size_t compareIndex = sectionIndex - offset;
         if (0 == compareIndex)
            return;

         const Section& prevSection = sections.at(compareIndex - 1);
         if (prevSection.steady)
         {
            length += prevSection.length();
            start = prevSection.start;

            extendBackwards(offset + 1);
         }
      };

      extendBackwards(0);

      std::function<void(const size_t)> extendForwards = [&](const size_t offset)
      {
         if (overFit == offset)
            return;

         const size_t compareIndex = sectionIndex + offset;
         if (compareIndex + 1 >= sections.size())
            return;

         const Section& compareSecton = sections.at(compareIndex);
         if (!compareSecton.steady)
            return;

         const Section& nextSection = sections.at(compareIndex + 1);
         length += nextSection.length();

         extendForwards(offset + 1);
      };

      extendForwards(0);

      size_t xOffset = section.start - start;

      XX::Linalg::Matrix yMatrix(length, 1);
      XX::Linalg::Matrix xMatrix(length, degree);

      for (size_t index = 0; index < length; index++)
      {
         const double x = (double)index - (double)xOffset;
         const double y = values.at(index + start);

         yMatrix.setValue(index, 0, y);
         for (size_t d = 0; d < degree; d++)
         {
            const size_t expo = degree - (d + 1);
            xMatrix.setValue(index, d, std::pow(x, expo));
         }
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

XX::Polynomial::Regression::Section::List XX::Polynomial::Regression::compileSections(double threshold, size_t maxSegmentLength) const
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
      else if (length > maxSegmentLength)
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

const QVector<double>& XX::Polynomial::Regression::getValues() const
{
   return values;
}
