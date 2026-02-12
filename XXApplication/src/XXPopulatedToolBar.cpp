#include "XXPopulatedToolBar.h"

XX::Populated::ToolBar::ToolBar(QWidget* parent)
   : QToolBar(parent)
   , toolBarName()
{
   // default values
   setIconSize(QSize(24, 24));
   setMovable(false);
   setFloatable(false);
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
}

void XX::Populated::ToolBar::init()
{
   setObjectName(toolBarName);
}
