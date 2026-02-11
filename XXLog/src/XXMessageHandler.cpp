
#include "XXMessageHandler.h"

#include <QThread>

MessageHandler* MessageHandler::me = nullptr;

MessageHandler::MessageHandler()
   : QObject(nullptr)
   , systemHandler()
   , targetMap()
{
   me = this;
   systemHandler = qInstallMessageHandler(&MessageHandler::output);
}

MessageHandler::~MessageHandler()
{
   qInstallMessageHandler(systemHandler);
   me = nullptr;
}

void MessageHandler::outputInternal(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   for (Function function : targetMap.values())
      function(type, context, msg);

   systemHandler(type, context, msg);
}

void MessageHandler::output(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   if (!me)
      return;

   if (QThread::isMainThread())
      me->outputInternal(type, context, msg);
   else
   {
      //QMetaObject::invokeMethod(me, &MessageHandler::outputInternal, Qt::QueuedConnection, type, context, msg);
   }
}
