#ifndef XXLookH
#define XXLookH

#include "XXWidgetsExportDef.h"

#include <QWidget>

namespace XX
{
   struct XXWIDGETS_DECLSPEC Look
   {
      static void applyStlyeSheet(const QString& fileName, QWidget* widget);

      static void setDockLabel(const QString& label);
      static void updateDockIcon(const QIcon& icon);

      static void doNotShowMenuIcons();
      static void forceAppMenuBar();
   };
} // namespace XX

#endif // NOT XXLookH
