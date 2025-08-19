#ifndef SampleWaveH
#define SampleWaveH

#include "SampleAbstract.h"
#include "WaToolsAudioExportDef.h"

namespace Sample
{
   class WATOOLSAUDIO_DECLSPEC Wave : public Abstract
   {
   protected:
      bool load(const QString& fileName) override;
      bool save(const QString& fileName) override;

   private:
      static const float maxValue;
   };
} // namespace Sample

#endif // NOT SampleWaveH
