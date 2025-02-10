#ifndef LogInterfaceH
#define LogInterfaceH

#include <QTextStream>

#include "IOChannel.h"

class LogInterface
{
public:
   LogInterface();
   ~LogInterface();

public:
   static QTextStream message();
   static QTextStream warning();

protected:
   virtual void print(const QString& text, bool isWarning);

private:
   static LogInterface* me;
   IOChannel* messageChannel;
   IOChannel* warningChannel;
};

#ifndef LogInterfaceHPP
#include "LogInterface.hpp"
#endif // NOT LogInterfaceHPP

#endif // NOT LogInterfaceH
