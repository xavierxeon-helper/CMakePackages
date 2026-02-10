#ifndef AnalogClockH
#define AnalogClockH

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT AnalogClock : public QWidget
{
   Q_OBJECT

public:
   explicit AnalogClock(QWidget* parent = nullptr);

protected:
   void paintEvent(QPaintEvent* event) override;
};

#endif // NOT AnalogClockH
