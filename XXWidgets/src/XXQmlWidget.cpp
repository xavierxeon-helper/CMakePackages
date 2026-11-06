#include "XXQmlWidget.h"

#include <QQmlContext>
#include <QQmlEngine>

XX::QmlWidget::QmlWidget(QWidget* parent)
   : QQuickWidget(parent)
{
   setResizeMode(SizeRootObjectToView);
}

void XX::QmlWidget::setQuickProperty(const QString& name, QObject* object)
{
   engine()->rootContext()->setContextProperty(name, object);
}

void XX::QmlWidget::setQuickProperty(const QString& name, const QVariant& value)
{
   engine()->rootContext()->setContextProperty(name, value);
}

// Property Map

XX::QmlWidget::PropertyMap* XX::QmlWidget::PropertyMap::create(QmlWidget* widget, const QString& qmlName)
{
   return new PropertyMap(widget, qmlName);
}

XX::QmlWidget::PropertyMap::PropertyMap(XX::QmlWidget* widget, const QString& qmlName)
   : PropertyMap(this, widget, qmlName) // protected ctor required for subclasses
{
}