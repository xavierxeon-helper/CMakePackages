#ifndef MessageHandlerHPP
#define MessageHandlerHPP

#include "MessageHandler.h"

#include <QThread>

inline MessageHandler* MessageHandler::me = nullptr;

inline MessageHandler::MessageHandler()
   : QObject(nullptr)
   , systemHandler()
   , targetMap()
{
   me = this;
   systemHandler = qInstallMessageHandler(&MessageHandler::output);
}

inline MessageHandler::~MessageHandler()
{
   qInstallMessageHandler(systemHandler);
   me = nullptr;
}

template <typename HandlerClass>
bool MessageHandler::enable(HandlerClass* instance, void (HandlerClass::*hanlderFunction)(QtMsgType, const QMessageLogContext&, const QString&))
{
   if (!me)
      new MessageHandler();

   void* target = static_cast<void*>(instance);
   if (me->targetMap.contains(target))
      return false;

   Function function = std::bind(hanlderFunction, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   me->targetMap[target] = function;
   return true;
}

template <typename HandlerClass>
void MessageHandler::disable(HandlerClass* instance)
{
   if (!me)
      return;

   void* target = static_cast<void*>(instance);
   me->targetMap.remove(target);
}

inline void MessageHandler::outputInternal(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   for (Function function : targetMap.values())
      function(type, context, msg);

   systemHandler(type, context, msg);
}

inline void MessageHandler::output(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   if (!me)
      return;

   if(QThread::isMainThread())
       me->outputInternal(type, context, msg);
   else
   {
      //QMetaObject::invokeMethod(me, &MessageHandler::outputInternal, Qt::QueuedConnection, type, context, msg);
   }

}

#endif // NOT MessageHandlerHPP
