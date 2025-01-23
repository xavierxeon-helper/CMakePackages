#ifndef MessageBarH
#define MessageBarH

#include <QStatusBar>

#include <QLabel>

#include <IOChannel.h>

class MessageBar : public QStatusBar
{
   // do not use Q_OBJECT
   // this file will not be moc'ed

public:
   MessageBar(QWidget* parent);
   ~MessageBar();

public:
   static QTextStream message();
   static QTextStream warning();

private:
   void print(const QString& text, bool isWarning = false);

private:
   static MessageBar* me;
   IOChannel* messageChannel;
   IOChannel* warningChannel;
};

#ifndef MessageBarHPP
#include "MessageBar.hpp"
#endif // NOT MessageBarHPP

#endif // NOT MessageBarH
