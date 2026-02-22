
#include "XXQtMessageInterceptor.h"

#include <QThread>

#include "XXLogSymbol.h"

XX::QtMessage::Interceptor* XX::QtMessage::Interceptor::me = nullptr;

XX::QtMessage::Interceptor::Interceptor()
   : QObject(nullptr)
   , systemHandler()
   , targetMap()
{
   me = this;
   systemHandler = qInstallMessageHandler(&Interceptor::output);
}

XX::QtMessage::Interceptor::~Interceptor()
{
   qInstallMessageHandler(systemHandler);
   me = nullptr;
}

QString XX::QtMessage::Interceptor::symbol(const QtMsgType& type)
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

void XX::QtMessage::Interceptor::outputInternal(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   for (const Function& function : targetMap.values())
      function(type, context, msg);

   systemHandler(type, context, msg);
}

void XX::QtMessage::Interceptor::output(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   if (!me)
      return;

   if (QThread::isMainThread())
      me->outputInternal(type, context, msg);
   else
   {
      //QMetaObject::invokeMethod(me, &Interceptor::outputInternal, Qt::QueuedConnection, type, context, msg);
   }
}
