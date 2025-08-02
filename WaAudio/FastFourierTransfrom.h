#ifndef FastFourierTransfromH
#define FastFourierTransfromH

#include <QException>

#include <complex>

#include <QList>
#include <QString>

// may throw Exception
class FastFourierTransfrom
{
public:
   using Data = QList<float>;
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
   ComplexData convert(const Data& data);
   Data strip(const ComplexData& data);

   ComplexData forward(const ComplexData& input);
   ComplexData inverse(const ComplexData& input);

private:
   bool isPowerOfTwo(const size_t num) const;
   void prepareData(ComplexData& data) const;
   void transform(ComplexData& data, bool forward) const;

private:
   const size_t size;
};

#endif // NOT FastFourierTransfromH
