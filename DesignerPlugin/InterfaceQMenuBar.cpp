#include "InterfaceQMenuBar.h"

#include <QMenuBar>

InterfaceQMenuBar::InterfaceQMenuBar(QObject* parent)
   : InterfaceAbstract(parent)
{
}

QString InterfaceQMenuBar::domXml() const
{
   return readFile(":/QMenuBar.xml");
}

QString InterfaceQMenuBar::includeFile() const
{
   return "<QMenuBar>";
}

QWidget* InterfaceQMenuBar::createWidget(QWidget* parent)
{
   return new QMenuBar(parent);
}

QString InterfaceQMenuBar::name() const
{
   return "QMenuBar";
}
