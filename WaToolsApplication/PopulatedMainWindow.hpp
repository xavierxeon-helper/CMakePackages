#ifndef PopulatedMainWindowHPP
#define PopulatedMainWindowHPP

#include "PopulatedMainWindow.h"

// needs to be inline for auto to work

inline QAction* Populated::MainWindow::addAction(QIcon icon, QString text, QString objectName, auto function)
{
   return Abstract::addAction(icon, text, objectName, instance(), function);
}

inline QAction* Populated::MainWindow::addFunctorAction(QIcon icon, QString text, QString objectName, auto functor)
{
   QAction* action = new QAction(icon, text, instance());
   action->setObjectName(objectName);
   QObject::connect(action, &QAction::triggered, functor);

   return action;
}

#endif // NOT PopulatedMainWindowHPP
