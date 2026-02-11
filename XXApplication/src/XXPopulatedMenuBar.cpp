#include "XXPopulatedMenuBar.h"

XX::Populated::MenuBar::MenuBar(QWidget* parent)
   : QMenuBar(parent)
   , menuName()
{
}

const QString& XX::Populated::MenuBar::getMenuName() const
{
   return menuName;
}

void XX::Populated::MenuBar::setMenuName(const QString& name)
{
   if (menuName == name)
      return;

   menuName = name;
   emit menuNameChanged();

   setObjectName(name);
}