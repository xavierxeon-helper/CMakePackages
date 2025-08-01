#ifndef SampleOscilatorH
#define SampleOscilatorH

#include <QString>

#include "SampleWave.h"

// wav file only!
namespace Sample
{
   class Reader : public Wave
   {
   public:
      Reader(const QString& fileName);

   public:
      const Meta& getMeta() const;
      Data get(const size_t& position, const size_t& numberOfSamples);

      size_t getPlayhead() const;
      void resetPlayhead();
      bool atEnd() const;
      void advancePlayhead();

      float getSound(uint8_t channel);

   private:
      size_t playhead;
   };
} // namespace Sample

#endif // NOT SampleOscilatorH
