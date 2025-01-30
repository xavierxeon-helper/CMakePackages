#ifndef PopulatedMainWindowH
#define PopulatedMainWindowH

#include <QMainWindow>

#include <QDomElement>

class PopulatedMainWindow : public QMainWindow
{
   // do not use Q_OBJECT
   // this file will not be moc'ed

public:
   PopulatedMainWindow();
   virtual ~PopulatedMainWindow();

public:
   static void printSettingsLocation();

protected:
   void populateMenuAndToolBar(const QString& xmlResource);
   virtual void closeEvent(QCloseEvent* ce) override;

private:
   void createToolBar(QDomElement thingElement);
   void createMenu(QDomElement thingElement, QMenu* parentMenu);
};

#ifndef PopulatedMainWindowHPP
#include "PopulatedMainWindow.hpp"
#endif // NOT PopulatedMainWindowHPP

#endif // NOT PopulatedMainWindowH
