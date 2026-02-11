#include "XXPopulatedToolBar.h"

XX::Populated::ToolBar::ToolBar(QWidget* parent)
   : QToolBar(parent)
   , toolBarName()
{
   setIconSize(QSize(16, 16));
}

const QString& XX::Populated::ToolBar::getToolBarName() const
{
   return toolBarName;
}

void XX::Populated::ToolBar::setToolBarName(const QString& name)
{
   if (toolBarName == name)
      return;

   toolBarName = name;
   emit toolBarNameChanged();

   setObjectName(name);
}