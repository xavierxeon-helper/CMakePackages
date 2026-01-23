#ifndef PopulatedMainWidgetHPP
#define PopulatedMainWidgetHPP

#include "PopulatedMainWidget.h"

// needs to be inline for auto to work
inline QAction* Populated::MainWidget::addFunctorAction(QIcon icon, QString text, QString objectName, auto functor)
{
   QAction* action = new QAction(icon, text, instance());
   action->setObjectName(objectName);
   QObject::connect(action, &QAction::triggered, functor);

   return action;
}

#endif // NOT PopulatedMainWidgetHPP
