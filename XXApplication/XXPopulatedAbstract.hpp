#ifndef PopulatedAbstractHPP
#define PopulatedAbstractHPP

#include "XXPopulatedAbstract.h"

// needs to be inline for auto to work

inline QAction* Populated::Abstract::addAction(QIcon icon, QString text, QString objectName, QObject* instance, auto slotFunction)
{
   QAction* action = new QAction(icon, text, instance);
   action->setObjectName(objectName);
   QObject::connect(action, &QAction::triggered, instance, slotFunction);

   return action;
}

inline QAction* Populated::Abstract::addFunctorAction(QIcon icon, QString text, QString objectName, QObject* parent, auto functor)
{
   QAction* action = new QAction(icon, text, parent);
   action->setObjectName(objectName);
   QObject::connect(action, &QAction::triggered, functor);

   return action;
}

#endif // NOT PopulatedAbstractHPP
