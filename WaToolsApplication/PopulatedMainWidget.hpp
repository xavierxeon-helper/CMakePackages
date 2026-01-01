#ifndef PopulatedMainWidgetHPP
#define PopulatedMainWidgetHPP

#include "PopulatedMainWidget.h"

// needs to be inline for auto to work

inline QAction* Populated::MainWidget::addAction(QIcon icon, QString text, QString objectName, auto function)
{
   return Abstract::addAction(icon, text, objectName, instance(), function);
}

#endif // NOT PopulatedMainWidgetHPP
