#ifndef ColorSpaceH
#define ColorSpaceH

#include "WaToolsQtExportDef.h"

#include <QColor>

class WATOOLS_QT_DECLSPEC ColorSpace
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
