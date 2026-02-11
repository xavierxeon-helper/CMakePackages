#ifndef XXPopulatedMainWidgetH
#define XXPopulatedMainWidgetH

#include "XXApplicationExportDef.h"
#include "XXPopulatedAbstract.h"
#include "XXSingleton.h"
#include <QWidget>

#include <QMenuBar>

namespace Populated
{
   class XXAPPLICATION_DECLSPEC MainWidget : public QWidget, public Abstract, public Singleton<MainWidget>
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

#endif // NOT XXPopulatedMainWidgetH
