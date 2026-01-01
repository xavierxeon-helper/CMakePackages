#ifndef PopulatedMainWindowHPP
#define PopulatedMainWindowHPP

#include "PopulatedMainWindow.h"

// needs to be inline for auto to work

inline QAction* Populated::MainWindow::addAction(QIcon icon, QString text, QString objectName, auto function)
{
   return Abstract::addAction(icon, text, objectName, the(), function);
}

#endif // NOT PopulatedMainWindowHPP
