#ifndef SampleAbstractH
#define SampleAbstractH

#include <QList>
#include <QString>

namespace Sample
{
   using Data = QList<float>;
   using Channels = QList<Data>;

   struct Meta
   {
      uint8_t noOfChannels = 1;
      uint16_t sampleRate = 1;
      size_t numberOfSamples = 0;

      size_t noOfSamplesPerChannel() const;
      double totalLength() const;
   };

   class Abstract
   {
   public:
      Abstract();

   protected:
      virtual bool load(const QString& fileName) = 0;
      virtual bool save(const QString& fileName) = 0;

      static Data interlace(const Channels& input);
      static Channels deinterlace(const Data& input, const uint8_t numberOfChannels = 2);

   protected:
      Data interlacedContent;
      Meta meta;
   };
} // namespace Sample

#endif // NOT SampleAbstractH
