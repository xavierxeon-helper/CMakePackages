#ifndef LookH
#define LookH

#include "WaToolsWidgetsExportDef.h"

#include <QWidget>

struct WATOOLSWIDGETS_DECLSPEC Look
{
   static void applyStlyeSheet(const QString& fileName, QWidget* widget);

   static void setDockLabel(const QString& label);
   static void updateDockIcon(const QIcon& icon);

   static void doNotShowMenuIcons();
   static void forceAppMenuBar();
};

#endif // NOT LookH
