#ifndef XXCursorToolsH
#define XXCursorToolsH

#include "XXGuiExportDef.h"

#include <QCursor>

namespace XX
{
   class XXGUI_DECLSPEC CursorTools
   {
   public:
      static QCursor createSvgCursor(const QString& resourcePath, const QSize& size, const QPoint& hotspot, const QColor& tint = QColor());
   };
} // namespace XX

#endif // NOT XXCursorToolsH
