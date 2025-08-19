#ifndef WorkFlowQmlWidgetH
#define WorkFlowQmlWidgetH

#include "WaToolsQtExportDef.h"
#include <QQuickWidget>

class WATOOLSQT_DECLSPEC QmlWidget : public QQuickWidget
{
public:
   QmlWidget(QWidget* parent);

public:
   void setQuickProperty(const QString& name, QObject* object);
};

#endif // NOT WorkFlowQmlWidgetH
