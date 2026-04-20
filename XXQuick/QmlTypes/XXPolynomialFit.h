#ifndef XXPolynomialFitH
#define XXPolynomialFitH

#include <QQuickItem>

#include <XXPolynomialRegression.h>

namespace XX
{
   //! @brief polynomial regressions
   //! @ingroup XXQuick

   class PolynomialFit : public QQuickItem
   {
      Q_OBJECT
      QML_NAMED_ELEMENT(PolynomialFit)

      Q_PROPERTY(size_t size READ getSize WRITE setSize)

   public:
      PolynomialFit(QQuickItem* parent = nullptr);
      ~PolynomialFit();

   public:
      Q_INVOKABLE void setValue(const size_t index, const double& value);
      Q_INVOKABLE void clear();
      Q_INVOKABLE void fit(size_t degree, double threshold, size_t overFit = 2, size_t maxSegmentLength = 50) const;

   private:
      size_t getSize() const;
      void setSize(const size_t& value);

   private:
      XX::Polynomial::Regression* regression;
   };
} // namespace XX

#endif // NOT XXPolynomialFitH
