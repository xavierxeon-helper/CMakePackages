#ifndef XXSampleWaveH
#define XXSampleWaveH

#include "XXAudioExportDef.h"
#include "XXSampleAbstract.h"

namespace XX
{
   namespace Sample
   {
      //! @brief wave audio sample
      //! baseclass for Reader and Writer
      //! @ingroup XXAudio

      class XXAUDIO_DECLSPEC Wave : public Abstract
      {
      protected:
         bool load(const QString& fileName) override;
         bool save(const QString& fileName) override;

      private:
         static const float maxValue;
      };
   } // namespace Sample
} // namespace XX

#endif // NOT XXSampleWaveH
