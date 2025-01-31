#ifndef PopulatedMainWindowH
#define PopulatedMainWindowH

#include <QMainWindow>

#include <QDomElement>

class PopulatedMainWindow : public QMainWindow
{
   Q_OBJECT
   // in cmake use:
   // list(APPEND SOURCE_FILES ${WAQT_INCLUDE_DIRS}/PopulatedMainWindow.h)

public:
   PopulatedMainWindow();
   virtual ~PopulatedMainWindow();

signals:
   void signalSettingsChanged();

public:
   static PopulatedMainWindow* the();
   static void printSettingsLocation();
   static QAction* addAction(QIcon icon, QString text, QString objectName, QObject* instance, auto slotFunction);

protected:
   void populateMenuAndToolBar(const QString& xmlResource);
   virtual void closeEvent(QCloseEvent* ce) override;
   virtual QMenu* createPopupMenu() override;

private:
   void createToolBar(QDomElement thingElement);
   void createMenu(QDomElement thingElement, QMenu* parentMenu);

private:
   static PopulatedMainWindow* me;
};

#ifndef PopulatedMainWindowHPP
#include "PopulatedMainWindow.hpp"
#endif // NOT PopulatedMainWindowHPP

#endif // NOT PopulatedMainWindowH
