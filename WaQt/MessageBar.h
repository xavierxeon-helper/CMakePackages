#ifndef MessageBarH
#define MessageBarH

#include "Logger.h"
#include <QStatusBar>

#include <QDateTime>
#include <QLabel>

class MessageBar : public QStatusBar, public Logger
{
   Q_OBJECT
   // in cmake use:
   // list(APPEND SOURCE_FILES ${WAQT_INCLUDE_DIRS}/MessageBar.h)

public:
   MessageBar(QWidget* parent, int stackSize = 0);

private slots:
   void slotUpdateTimeout();

private:
   void print(const QString& text, bool isWarning) override;
   bool eventFilter(QObject* obj, QEvent* event) override;

private:
   QLabel* messageLabel;
   const int stackSize;
   QStringList messageStack;
   QDateTime messageExpiration;
};

#ifndef MessageBarHPP
#include "MessageBar.hpp"
#endif // NOT MessageBarHPP

#endif // NOT MessageBarH
