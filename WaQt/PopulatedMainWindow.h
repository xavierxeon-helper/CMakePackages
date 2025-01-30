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
