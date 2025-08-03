#ifndef FastFourierTransfromH
#define FastFourierTransfromH

#include <QException>

#include <complex>

#include "SampleAbstract.h"

// may throw Exception
class FastFourierTransfrom
{
public:
   using ComplexType = std::complex<float>;
   using ComplexData = QList<ComplexType>;

   class Exception : public QException
   {
   public:
      Exception(const QString& message);

   private:
      QString message;
   };

public:
   FastFourierTransfrom(const size_t size);

public:
   static ComplexData fill(const Sample::Data& data);
   static Sample::Data strip(const ComplexData& data);

   static ComplexType cartesianToPolar(const ComplexType& cartesian);
   static ComplexType polarToCartesian(const ComplexType& polar);

   ComplexData forward(const ComplexData& input);
   ComplexData inverse(const ComplexData& input);

   const size_t& getSize() const;
   static bool isPowerOfTwo(const size_t num);

private:
   void bitReverse(ComplexData& data) const;
   void transform(ComplexData& data, bool forward) const;

private:
   const size_t size;
};

#endif // NOT FastFourierTransfromH
