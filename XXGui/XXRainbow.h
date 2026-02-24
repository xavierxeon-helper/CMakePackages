#ifndef XXRainbowH
#define XXRainbowH

#include "XXGuiExportDef.h"

#include <QColor>
#include <QMap>

namespace XX
{
   //! @brief generate a rainbow of colors
   //! @ingroup XXGui

   class XXGUI_DECLSPEC Rainbow
   {
   public:
      Rainbow(quint64 maxIndex, quint16 shade = 200);

   public:
      const quint64& getMaxIndex() const;
      void changeShade(quint16 shade);
      QColor getColor(const quint64 offset = 0);
      QColor advanceColor(const quint64& offset = 1);
      QColor lookup(const quint64& value, bool wrap);

   private:
      using ColorMap = QMap<quint64, QColor>;

      struct Section
      {
         QColor color;
         int variableIndex;
         bool up;

         using List = QList<Section>;
      };

   private:
      quint64 maxIndex;
      ColorMap colorMap;
      quint64 currentIndex;
   };
} // namespace XX

#endif // NOT XXRainbowH
