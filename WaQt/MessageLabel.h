#ifndef MessageLabelH
#define MessageLabelH

#include "Logger.h"
#include <QLabel>

#include <QDateTime>

class MessageLabel : public QLabel, public Logger
{
   Q_OBJECT

public:
   MessageLabel(QWidget* parent, int stackSize = 0);

private slots:
   void slotUpdateTimeout();

private:
   void print(const QString& text, bool isWarning) override;
   void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
   const int stackSize;
   QStringList messageStack;
   QDateTime messageExpiration;
};

#endif // NOT MessageLabelH
