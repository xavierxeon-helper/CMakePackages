#ifndef InterfaceNamedAbstractHPP
#define InterfaceNamedAbstractHPP

#include "InterfaceNamedAbstract.h"

template <typename WidgetClass>
Interface::NamedAbstract<WidgetClass>::NamedAbstract(QObject* parent)
   : Abstract(parent)
   , widgetClassName(WidgetClass::staticMetaObject.className())
   , widgetFileName()
{
   widgetFileName = QString(widgetClassName).replace("::", "");
   static_assert(std::is_base_of<QWidget, WidgetClass>::value, "WidgetClass must be a subclass of QWidget");
   //qDebug() << __FUNCTION__ << widgetClassName << widgetFileName;
}

template <typename WidgetClass>
QString Interface::NamedAbstract<WidgetClass>::domXml() const
{
   return readFile(":/xml/" + widgetFileName + ".xml");
}

template <typename WidgetClass>
QString Interface::NamedAbstract<WidgetClass>::includeFile() const
{
   return widgetFileName + ".h";
}

template <typename WidgetClass>
QWidget* Interface::NamedAbstract<WidgetClass>::createWidget(QWidget* parent)
{
   WidgetClass* widget = new WidgetClass(parent);
   return widget;
}

template <typename WidgetClass>
QString Interface::NamedAbstract<WidgetClass>::name() const
{
   return widgetClassName;
}

#endif // NOT InterfaceNamedAbstractHPP