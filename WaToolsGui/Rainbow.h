#ifndef RainbowH
#define RainbowH

#include "WaToolsGuiExportDef.h"

#include <QColor>
#include <QMap>

class WATOOLSGUI_DECLSPEC Rainbow
{
public:
   Rainbow(quint64 maxIndex, quint16 shade = 200);

public:
   QColor getColor();
   QColor advanceColor();
   QColor lookup(quint64 value, bool wrap);

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

#endif // NOT RainbowH
