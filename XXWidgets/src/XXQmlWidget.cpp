#include "XXQmlWidget.h"

#include <QQmlContext>
#include <QQmlEngine>

XX::QmlWidget::QmlWidget(QWidget* parent)
   : QQuickWidget(parent)
{
   setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
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
