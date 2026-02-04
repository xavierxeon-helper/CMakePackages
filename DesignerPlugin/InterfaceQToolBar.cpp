#include "InterfaceQToolBar.h"

#include <QToolBar>

QT_BEGIN_NAMESPACE

InterfaceQToolBar::InterfaceQToolBar(QObject* parent)
   : InterfaceAbstract(parent)
{
}

QString InterfaceQToolBar::domXml() const
{
   return readFile(":/QToolBar.xml");
}

QString InterfaceQToolBar::includeFile() const
{
   return "<QToolBar>";
}

QWidget* InterfaceQToolBar::createWidget(QWidget* parent)
{
   QToolBar* toolBar = new QToolBar(parent);
   return toolBar;
}

QString InterfaceQToolBar::name() const
{
   return "QToolBar";
}

QT_END_NAMESPACE