#ifndef WorkFlowQmlWidgetH
#define WorkFlowQmlWidgetH

#include "WaToolsWidgetsExportDef.h"
#include <QQuickWidget>

class WATOOLSWIDGETS_DECLSPEC QmlWidget : public QQuickWidget
{
public:
   QmlWidget(QWidget* parent);

public:
   void setQuickProperty(const QString& name, QObject* object);
};

#endif // NOT WorkFlowQmlWidgetH
