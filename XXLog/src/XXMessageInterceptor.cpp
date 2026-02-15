
#include "XXMessageInterceptor.h"

#include <QThread>

#include "XXLogSymbol.h"

XX::MessageInterceptor* XX::MessageInterceptor::me = nullptr;

XX::MessageInterceptor::MessageInterceptor()
   : QObject(nullptr)
   , systemHandler()
   , targetMap()
{
   me = this;
   systemHandler = qInstallMessageHandler(&MessageInterceptor::output);
}

XX::MessageInterceptor::~MessageInterceptor()
{
   qInstallMessageHandler(systemHandler);
   me = nullptr;
}

QString XX::MessageInterceptor::symbol(const QtMsgType& type)
{
   QString symbol;
   switch (type)
   {
      case QtDebugMsg:
         symbol = XX::LogSymbol::Debug;
         break;
      case QtInfoMsg:
         symbol = XX::LogSymbol::Info;
         break;
      default:
         symbol = XX::LogSymbol::Warning;
         break;
   }

   return symbol;
}

void XX::MessageInterceptor::outputInternal(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   for (Function function : targetMap.values())
      function(type, context, msg);

   systemHandler(type, context, msg);
}

void XX::MessageInterceptor::output(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   if (!me)
      return;

   if (QThread::isMainThread())
      me->outputInternal(type, context, msg);
   else
   {
      //QMetaObject::invokeMethod(me, &MessageInterceptor::outputInternal, Qt::QueuedConnection, type, context, msg);
   }
}
