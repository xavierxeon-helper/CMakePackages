#ifndef XXRegressionContainer2DH
#define XXRegressionContainer2DH

#include "XXMathExportDef.h"

#include <QList>

namespace XX
{
   namespace Regression
   {
      class XXMATH_DECLSPEC Container2D
      {
      public:
         Container2D(size_t size);

      public:
         struct Section
         {
            size_t start = 0;
            size_t end = 0;
            bool steady = false; // no jump to next section

            size_t length() const;

            using List = QList<Section>;
         };

      public:
         size_t size() const;
         void setValue(const size_t index, const double& value);
         void clear();

         // set negative maxSegmentLength to disable segment length limit
         Section::List compileSections(double threshold, size_t maxSegmentLength = 50) const;
         const QVector<double>& getValues() const;

      private:
         QVector<double> values;
      };
   } // namespace Regression
} // namespace XX

#endif // NOT XXRegressionContainer2DH
