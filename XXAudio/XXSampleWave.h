#ifndef SampleWaveH
#define SampleWaveH

#include "XXSampleAbstract.h"
#include "XXAudioExportDef.h"

namespace Sample
{
   class XXAUDIO_DECLSPEC Wave : public Abstract
   {
   protected:
      bool load(const QString& fileName) override;
      bool save(const QString& fileName) override;

   private:
      static const float maxValue;
   };
} // namespace Sample

#endif // NOT SampleWaveH
