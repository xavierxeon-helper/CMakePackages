#ifndef MessageBarH
#define MessageBarH

#include "Logger.h"
#include <QStatusBar>

class MessageBar : public QStatusBar, public Logger
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
