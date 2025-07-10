#ifndef PopulatedMainWindowHPP
#define PopulatedMainWindowHPP

#include "PopulatedMainWindow.h"

// needs to be inline for auto to work
inline QAction* PopulatedMainWindow::addAction(QIcon icon, QString text, QString objectName, QObject* instance, auto slotFunction)
{
   QAction* action = new QAction(icon, text, instance);
   action->setObjectName(objectName);
   connect(action, &QAction::triggered, instance, slotFunction);

   return action;
}

#endif // NOT PopulatedMainWindowHPP
