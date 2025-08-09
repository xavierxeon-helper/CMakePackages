#include "QuickWidget.h"

#include <QQmlContext>
#include <QQmlEngine>

QuickWidget::QuickWidget(QWidget* parent)
   : QQuickWidget(parent)
{
   setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
   setResizeMode(SizeRootObjectToView);
}

void QuickWidget::setQuickProperty(const QString& name, QObject* object)
{
   engine()->rootContext()->setContextProperty(name, object);
}
