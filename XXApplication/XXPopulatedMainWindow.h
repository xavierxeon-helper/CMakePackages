#ifndef XXPopulatedMainWindowH
#define XXPopulatedMainWindowH

#include "XXApplicationExportDef.h"
#include "XXPopulatedAbstract.h"
#include "XXSingleton.h"
#include <QMainWindow>

namespace Populated
{
   class XXAPPLICATION_DECLSPEC MainWindow : public QMainWindow, public Abstract, public Singleton<MainWindow>
   {
      Q_OBJECT

   public:
      MainWindow();

   protected:
      QDockWidget* addDockWidget(QWidget* widget, const Qt::DockWidgetArea& area);

      virtual void closeEvent(QCloseEvent* ce) override;
      virtual QMenu* createPopupMenu() override;

      void saveWindowSettings();

   private:
      QToolBar* findOrCreateToolBar(const QString& objectName);
      QMenu* findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu);
   };
} // namespace Populated

#endif // NOT XXPopulatedMainWindowH
