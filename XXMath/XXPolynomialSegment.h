#ifndef XXPolynomialSegmentH
#define XXPolynomialSegmentH

#include "XXMathExportDef.h"
#include "XXPolynomial.h"

#include <QList>

namespace XX
{
   //! @brief a polynomial segment
   //! @ingroup XXMath

   class XXMATH_DECLSPEC Polynomial::Segment : public Polynomial
   {
   public:
      using List = QList<Segment>;
      class Bundle;

   public:
      Segment(size_t degree = 0);
      Segment(QVector<double> coefficents);

   public:
      const double& getStart() const;
      const double& getEnd() const;

      double getLength() const;

      void setStart(const double& value);
      void setEnd(const double& value);

   private:
      double start;
      double end;
   };
} // namespace XX

#endif // NOT XXPolynomialSegmentH
