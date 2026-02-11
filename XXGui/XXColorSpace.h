#ifndef XXColorSpaceH
#define XXColorSpaceH

#include "XXGuiExportDef.h"

#include <QColor>

namespace XX
{
   class XXGUI_DECLSPEC ColorSpace
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
} // namespace XX

#endif // NOT XXColorSpaceH
