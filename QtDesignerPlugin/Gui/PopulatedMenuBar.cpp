#include "PopulatedMenuBar.h"

Populated::MenuBar::MenuBar(QWidget* parent)
   : QMenuBar(parent)
   , menuName()
{
}

const QString& Populated::MenuBar::getMenuName() const
{
   return menuName;
}

void Populated::MenuBar::setMenuName(const QString& name)
{
   if (menuName == name)
      return;

   menuName = name;
   emit menuNameChanged();

   qDebug() << __FUNCTION__ << name;
}