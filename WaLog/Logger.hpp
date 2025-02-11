#ifndef LoggerHPP
#define LoggerHPP

#include "Logger.h"

inline Logger* Logger::me = nullptr;

inline Logger::Logger()
   : messageChannel(nullptr)
   , warningChannel(nullptr)
{
   me = this;

   auto printFunction = [&](bool isWarning)
   {
      return std::bind(&Logger::print, this, std::placeholders::_1, isWarning);
   };

   messageChannel = new IOChannel(nullptr, printFunction(false));
   warningChannel = new IOChannel(nullptr, printFunction(true));
}

inline Logger::~Logger()
{
   me = nullptr;
   messageChannel->deleteLater();
   warningChannel->deleteLater();
}

inline QTextStream Logger::message()
{
   if (!me)
      return QTextStream();

   return me->messageChannel->stream();
}

inline QTextStream Logger::warning()
{
   if (!me)
      return QTextStream();

   return me->warningChannel->stream();
}

inline void Logger::addAdditionalPrinter(IOChannel::PrintFunction printFunction, bool isWarning)
{
   if (isWarning)
      warningChannel->addPrinter(printFunction);
   else
      messageChannel->addPrinter(printFunction);
}

inline void Logger::print(const QString& text, bool isWarning)
{
   if (isWarning)
      qWarning() << qPrintable(text);
   else
      qDebug() << qPrintable(text);
}

#endif // NOT LoggerHPP
