#include "InterfaceQMenuBar.h"

#include <QMenuBar>

QT_BEGIN_NAMESPACE

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
   QMenuBar* menuBar = new QMenuBar(parent);
   return menuBar;
}

QString InterfaceQMenuBar::name() const
{
   return "QMenuBar";
}

QT_END_NAMESPACE