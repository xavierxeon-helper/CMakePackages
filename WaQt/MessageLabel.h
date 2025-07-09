#ifndef MessageLabelH
#define MessageLabelH

#include "Logger.h"
#include <QLabel>

#include <QDateTime>

class MessageLabel : public QLabel, public Logger
{
   Q_OBJECT
   // in cmake use:
   // list(APPEND SOURCE_FILES ${WAQT_INCLUDE_DIRS}/MessageLabel.h)

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

#ifndef MessageLabelHPP
#include "MessageLabel.hpp"
#endif // NOT MessageLabelHPP

#endif // NOT MessageLabelH
