#ifndef XXColorSpaceH
#define XXColorSpaceH

#include "XXGuiExportDef.h"

#include <QColor>

namespace XX
{
   //! @brief color space conversions
   //! @ingroup XXGui

   class XXGUI_DECLSPEC ColorSpace
   {
   public:
      //! @brief CIE 1931 color space coordinates with brightness
      /*!
         @details see https://en.wikipedia.org/wiki/CIE_1931_color_space
      */

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
