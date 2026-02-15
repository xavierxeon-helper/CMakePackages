#ifndef XXMessageHandlerH
#define XXMessageHandlerH

#include "XXLogExportDef.h"
#include <QObject>

#include <functional>

#include <QMap>

namespace XX
{
   //! @brief override the default Qt message handler
   //! @ingroup XXLog

   struct XXLOG_DECLSPEC MessageHandler : public QObject
   {
      Q_OBJECT

   public:
      template <typename HandlerClass>
      static bool enable(HandlerClass* instance, void (HandlerClass::*hanlderFunction)(QtMsgType, const QMessageLogContext&, const QString&));

      template <typename HandlerClass>
      static void disable(HandlerClass* instance);

      static QString symbol(const QtMsgType& type);

   private:
      MessageHandler();
      ~MessageHandler();

   private:
      using Function = std::function<void(QtMsgType, const QMessageLogContext&, const QString&)>;
      using TargetMap = QMap<void*, Function>;

   private:
      Q_INVOKABLE void outputInternal(QtMsgType type, const QMessageLogContext& context, const QString& msg);
      static void output(QtMsgType type, const QMessageLogContext& context, const QString& msg);

   private:
      static MessageHandler* me;
      QtMessageHandler systemHandler;
      TargetMap targetMap;
   };
} // namespace XX

#ifndef XXMessageHandlerHPP
#include "XXMessageHandler.hpp"
#endif // NOT XXMessageHandlerHPP

#endif // NOT XXMessageHandlerH
