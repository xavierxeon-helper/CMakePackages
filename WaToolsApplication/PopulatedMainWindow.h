#ifndef PopulatedMainWindowH
#define PopulatedMainWindowH

#include "WaToolsApplicationExportDef.h"
#include <QMainWindow>

#include "ActionPopulation.h"

class WATOOLSAPPLICATION_DECLSPEC PopulatedMainWindow : public QMainWindow
{
   Q_OBJECT

public:
   PopulatedMainWindow();
   virtual ~PopulatedMainWindow();

public:
   static PopulatedMainWindow* the();
   static void printSettingsLocation();
   static QAction* addAction(QIcon icon, QString text, QString objectName, auto function);
   static QAction* addAction(QIcon icon, QString text, QString objectName, QObject* instance, auto slotFunction);

protected:
   void populateMenuAndToolBar(const QString& xmlResource);
   QDockWidget* addDockWidget(QWidget* widget, const Qt::DockWidgetArea& area);

   virtual void closeEvent(QCloseEvent* ce) override;
   virtual QMenu* createPopupMenu() override;

   void saveWindowSettings();

private:
   QToolBar* findOrCreateToolBar(const QString& objectName);
   QMenu* findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu);

private:
   static PopulatedMainWindow* me;
   ActionPopulation* actionPopulation;
};

#ifndef PopulatedMainWindowHPP
#include "PopulatedMainWindow.hpp"
#endif // NOT PopulatedMainWindowHPP

#endif // NOT PopulatedMainWindowH
