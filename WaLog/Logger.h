#ifndef LoggerH
#define LoggerH

#include <QTextStream>

#include "IOChannel.h"

class Logger
{
public:
   Logger();
   ~Logger();

public:
   static QTextStream message();
   static QTextStream warning();
   static void showLogger();
   void addAdditionalPrinter(IOChannel::PrintFunction printFunction, bool isWarning);

protected:
   virtual void reveal();
   virtual void print(const QString& text, bool isWarning);

private:
   static Logger* me;
   IOChannel* messageChannel;
   IOChannel* warningChannel;
};

#ifndef LoggerHPP
#include "Logger.hpp"
#endif // NOT LoggerHPP

#endif // NOT LoggerH
