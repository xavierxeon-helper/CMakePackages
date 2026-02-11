#ifndef XXMessageHandlerHPP
#define XXMessageHandlerHPP

#include "XXMessageHandler.h"

template <typename HandlerClass>
bool XX::MessageHandler::enable(HandlerClass* instance, void (HandlerClass::*hanlderFunction)(QtMsgType, const QMessageLogContext&, const QString&))
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
void XX::MessageHandler::disable(HandlerClass* instance)
{
   if (!me)
      return;

   void* target = static_cast<void*>(instance);
   me->targetMap.remove(target);
}

#endif // NOT XXMessageHandlerHPP
