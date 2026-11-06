#ifndef XXQmlWidgetHPP
#define XXQmlWidgetHPP

#include "XXQmlWidget.h"

template <typename DerivedClass>
XX::QmlWidget::PropertyMap::PropertyMap(DerivedClass* derivedInstance, XX::QmlWidget* widget, const QString& qmlName)
   : QQmlPropertyMap(derivedInstance, widget) // protected ctor required for subclasses
{
   static_assert(std::is_base_of<PropertyMap, DerivedClass>::value, "DerivedClass must be derived from XX::QmlWidget::PropertyMap");
   widget->setQuickProperty(qmlName, this);
}

#endif // NOT XXQmlWidgetHPP
