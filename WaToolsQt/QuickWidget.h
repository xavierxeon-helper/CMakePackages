#ifndef WorkFlowQuickWidgetH
#define WorkFlowQuickWidgetH

#include <QQuickWidget>

class QuickWidget : public QQuickWidget
{
public:
   QuickWidget(QWidget* parent);

public:
   void setQuickProperty(const QString& name, QObject* object);
};

#endif // NOT WorkFlowQuickWidgetH
