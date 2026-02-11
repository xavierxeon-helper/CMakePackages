#ifndef MessageLabelH
#define MessageLabelH

#include "XXWidgetsExportDef.h"
#include <XXLogger.h>
#include <QLabel>

#include <QDateTime>

class XXWIDGETS_DECLSPEC MessageLabel : public QLabel, public Logger::Target
{
   Q_OBJECT

public:
   MessageLabel(QWidget* parent, int stackSize = 10);

public:
   void setShowToolTip(bool newShowToolTip);

private slots:
   void slotUpdateTimeout();

private:
   void update(const Entry::Buffer& buffer) override;
   void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
   bool showToolTip;
   QDateTime messageExpiration;
};

#endif // NOT MessageLabelH
