#ifndef PopulatedMainWidgetH
#define PopulatedMainWidgetH

#include "PopulatedAbstract.h"
#include "WaToolsApplicationExportDef.h"
#include <QWidget>

#include <QMenuBar>

namespace Populated
{
   class WATOOLSAPPLICATION_DECLSPEC MainWidget : public QWidget, public Abstract
   {
      Q_OBJECT

   public:
      MainWidget();

   protected:
      virtual void closeEvent(QCloseEvent* ce) override;
      QToolBar* findOrCreateToolBar(const QString& objectName);
      QMenu* findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu);

   protected:
      QMenuBar* menuBar;
   };
} // namespace Populated

#endif // NOT PopulatedMainWidgetH
