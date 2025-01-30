#ifndef PopulatedMainWindowH
#define PopulatedMainWindowH

#include <QMainWindow>

#include <QDomElement>

class PopulatedMainWindow : public QMainWindow
{
   Q_OBJECT
   // see https://doc.qt.io/qt-6/qt-wrap-cpp.html

public:
   PopulatedMainWindow();
   virtual ~PopulatedMainWindow();

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
