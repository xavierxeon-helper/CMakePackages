#ifndef PopulatedMainWidgetH
#define PopulatedMainWidgetH

#include "PopulatedAbstract.h"
#include "Singleton.h"
#include "WaToolsApplicationExportDef.h"
#include <QWidget>

#include <QMenuBar>

namespace Populated
{
   class WATOOLSAPPLICATION_DECLSPEC MainWidget : public QWidget, public Abstract, public Singleton<MainWidget>
   {
      Q_OBJECT

   public:
      MainWidget();

   public:
      static QAction* addAction(QIcon icon, QString text, QString objectName, auto function);

   protected:
      void loadSettings();
      virtual void closeEvent(QCloseEvent* ce) override;

   protected:
      QMenuBar* menuBar;

   private:
      QToolBar* findOrCreateToolBar(const QString& objectName);
      QMenu* findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu);
   };
} // namespace Populated

#ifndef PopulatedMainWidgetHPP
#include "PopulatedMainWidget.hpp"
#endif // NOT PopulatedMainWidgetHPP

#endif // NOT PopulatedMainWidgetH
