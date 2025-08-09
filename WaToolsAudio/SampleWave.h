#ifndef SampleWaveH
#define SampleWaveH

#include "SampleAbstract.h"

namespace Sample
{
   class Wave : public Abstract
   {
   protected:
      bool load(const QString& fileName) override;
      bool save(const QString& fileName) override;

   private:
      static const float maxValue;
   };
} // namespace Sample

#endif // NOT SampleWaveH
