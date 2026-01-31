#include "QmlWidget.h"

#include <QQmlContext>
#include <QQmlEngine>

QmlWidget::QmlWidget(QWidget* parent)
   : QQuickWidget(parent)
{
   setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
   setResizeMode(SizeRootObjectToView);
}

void QmlWidget::setQuickProperty(const QString& name, QObject* object)
{
   engine()->rootContext()->setContextProperty(name, object);
}

void QmlWidget::setQuickProperty(const QString& name, const QVariant& value)
{
   engine()->rootContext()->setContextProperty(name, value);
}
