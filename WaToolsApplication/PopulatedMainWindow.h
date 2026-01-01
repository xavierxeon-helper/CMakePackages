#ifndef PopulatedMainWindowH
#define PopulatedMainWindowH

#include "PopulatedAbstract.h"
#include "WaToolsApplicationExportDef.h"
#include <QMainWindow>

namespace Populated
{
   class WATOOLSAPPLICATION_DECLSPEC MainWindow : public QMainWindow, public Abstract
   {
      Q_OBJECT

   public:
      MainWindow();
      virtual ~MainWindow();

   public:
      static MainWindow* the();
      static QAction* addAction(QIcon icon, QString text, QString objectName, auto function);

   protected:
      QDockWidget* addDockWidget(QWidget* widget, const Qt::DockWidgetArea& area);

      virtual void closeEvent(QCloseEvent* ce) override;
      virtual QMenu* createPopupMenu() override;

      void saveWindowSettings();

   private:
      QToolBar* findOrCreateToolBar(const QString& objectName);
      QMenu* findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu);

   private:
      static MainWindow* me;
   };
} // namespace Populated

#ifndef PopulatedMainWindowHPP
#include "PopulatedMainWindow.hpp"
#endif // NOT PopulatedMainWindowHPP

#endif // NOT PopulatedMainWindowH
