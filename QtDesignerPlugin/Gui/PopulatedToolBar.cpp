#include "PopulatedToolBar.h"

Populated::ToolBar::ToolBar(QWidget* parent)
   : QToolBar(parent)
   , toolBarName()
{
}

const QString& Populated::ToolBar::getToolBarName() const
{
   return toolBarName;
}

void Populated::ToolBar::setToolBarName(const QString& name)
{
   if (toolBarName == name)
      return;

   toolBarName = name;
   emit toolBarNameChanged();

   qDebug() << __FUNCTION__ << name;
}