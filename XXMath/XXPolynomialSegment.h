#ifndef XXPolynomialSegmentH
#define XXPolynomialSegmentH

#include "XXMathExportDef.h"
#include "XXPolynomial.h"

#include <QDebug>
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

      double value(const double& x) const override;

   private:
      friend XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Segment& segment);

   private:
      double start;
      double end;
   };

   /*!
      @addtogroup Streaming
      @{
      @ingroup XXMath
   */

   XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Polynomial::Segment& segment);

   //! @}

} // namespace XX

#endif // NOT XXPolynomialSegmentH
