#ifndef WorkFlowQmlWidgetH
#define WorkFlowQmlWidgetH

#include <QQuickWidget>

class QmlWidget : public QQuickWidget
{
public:
   QmlWidget(QWidget* parent);

public:
   void setQuickProperty(const QString& name, QObject* object);
};

#endif // NOT WorkFlowQmlWidgetH
