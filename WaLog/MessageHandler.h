#ifndef MessageHandlerH
#define MessageHandlerH

#include <functional>

#include <QMap>

struct MessageHandler
{
public:
   template <typename HandlerClass>
   static bool enable(HandlerClass* instance, void (HandlerClass::*hanlderFunction)(QtMsgType, const QMessageLogContext&, const QString&));

   template <typename HandlerClass>
   static void disable(HandlerClass* instance);

private:
   MessageHandler();
   ~MessageHandler();

private:
   using Function = std::function<void(QtMsgType, const QMessageLogContext&, const QString&)>;
   using TargetMap = QMap<void*, Function>;

private:
   static void output(QtMsgType type, const QMessageLogContext& context, const QString& msg);

private:
   static MessageHandler* me;
   QtMessageHandler systemHandler;
   TargetMap targetMap;
};

#ifndef MessageHandlerHPP
#include "MessageHandler.hpp"
#endif // NOT MessageHandlerHPP

#endif // NOT MessageHandlerH
