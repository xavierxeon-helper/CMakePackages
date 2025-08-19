#ifndef MessageLabelH
#define MessageLabelH

#include "WaToolsQtExportDef.h"
#include <Logger.h>
#include <QLabel>

#include <QDateTime>

class WATOOLSQT_DECLSPEC MessageLabel : public QLabel, public Logger::Target
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
