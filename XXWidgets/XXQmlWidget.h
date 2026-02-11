#ifndef WorkFlowQmlWidgetH
#define WorkFlowQmlWidgetH

#include "XXWidgetsExportDef.h"
#include <QQuickWidget>

class XXWIDGETS_DECLSPEC QmlWidget : public QQuickWidget
{
   Q_OBJECT

public:
   QmlWidget(QWidget* parent);

public:
   void setQuickProperty(const QString& name, QObject* object);
   void setQuickProperty(const QString& name, const QVariant& value);
};

#endif // NOT WorkFlowQmlWidgetH
