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

   protected:
      void loadSettings();
      virtual void closeEvent(QCloseEvent* ce) override;
      virtual void placeMenuBar(QMenuBar* menuBar);

   private:
      QToolBar* findOrCreateToolBar(const QString& objectName);
      QMenu* findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu);

   private:
      QMenuBar* menuBar;
   };
} // namespace Populated

#endif // NOT PopulatedMainWidgetH
