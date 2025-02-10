#ifndef LogInterfaceHPP
#define LogInterfaceHPP

#include "LogInterface.h"

inline LogInterface* LogInterface::me = nullptr;

inline LogInterface::LogInterface()
   : messageChannel(nullptr)
   , warningChannel(nullptr)

{
   me = this;

   auto printFunction = [&](bool isWarning)
   {
      return std::bind(&LogInterface::print, this, std::placeholders::_1, isWarning);
   };

   messageChannel = new IOChannel(nullptr, printFunction(false));
   warningChannel = new IOChannel(nullptr, printFunction(true));
}

inline LogInterface::~LogInterface()
{
   me = nullptr;
   messageChannel->deleteLater();
   warningChannel->deleteLater();
}

inline QTextStream LogInterface::message()
{
   if (!me)
      return QTextStream();

   return me->messageChannel->stream();
}

inline QTextStream LogInterface::warning()
{
   if (!me)
      return QTextStream();

   return me->warningChannel->stream();
}

inline void LogInterface::print(const QString& text, bool isWarning)
{
   if (isWarning)
      qWarning() << qPrintable(text);
   else
      qDebug() << qPrintable(text);
}

#endif // NOT LogInterfaceHPP
