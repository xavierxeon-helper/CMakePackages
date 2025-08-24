#ifndef ColorSpaceH
#define ColorSpaceH

#include "WaToolsGuiExportDef.h"

#include <QColor>

class WATOOLSGUI_DECLSPEC ColorSpace
{
public:
   struct XYB
   {
      double x = 0.0;
      double y = 0.0;
      double brightness = 0.0;
   };

public:
   static QColor fromCIE(const XYB& xyb);
   static XYB toCIE(const QColor& color);
};

#endif // NOT ColorSpaceH
