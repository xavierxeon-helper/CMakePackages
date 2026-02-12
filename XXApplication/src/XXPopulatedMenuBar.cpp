#include "XXPopulatedMenuBar.h"

XX::Populated::MenuBar::MenuBar(QWidget* parent)
   : QMenuBar(parent)
   , menuBarName()
{
}

const QString& XX::Populated::MenuBar::getMenuBarName() const
{
   return menuBarName;
}

void XX::Populated::MenuBar::setMenuBarName(const QString& name)
{
   if (menuBarName == name)
      return;

   menuBarName = name;
   emit menuBarNameChanged();
}

void XX::Populated::MenuBar::init()
{
   setObjectName(menuBarName);
}
