#ifndef MessageHandlerHPP
#define MessageHandlerHPP

#include "MessageHandler.h"

inline MessageHandler* MessageHandler::me = nullptr;

inline MessageHandler::MessageHandler()
   : systemHandler()
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

inline void MessageHandler::output(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   if (!me)
      return;

   for (Function function : me->targetMap.values())
      function(type, context, msg);

   me->systemHandler(type, context, msg);
}

#endif // NOT MessageHandlerHPP
