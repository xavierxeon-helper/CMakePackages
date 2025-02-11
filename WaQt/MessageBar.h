#ifndef MessageBarH
#define MessageBarH

#include <QStatusBar>

#include <QLabel>

#include <LogInterface.h>

class MessageBar : public QStatusBar, public LogInterface
{
   Q_OBJECT
   // in cmake use:
   // list(APPEND SOURCE_FILES ${WAQT_INCLUDE_DIRS}/MessageBar.h)

public:
   MessageBar(QWidget* parent);

private:
   void print(const QString& text, bool isWarning) override;
};

#ifndef MessageBarHPP
#include "MessageBar.hpp"
#endif // NOT MessageBarHPP

#endif // NOT MessageBarH
