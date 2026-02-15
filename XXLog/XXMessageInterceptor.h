#ifndef XXMessageInterceptorH
#define XXMessageInterceptorH

#include "XXLogExportDef.h"
#include <QObject>

#include <functional>

#include <QMap>

namespace XX
{
   //! @brief intercept the default Qt message handler
   //! @ingroup XXLog

   struct XXLOG_DECLSPEC MessageInterceptor : public QObject
   {
      Q_OBJECT

   public:
      template <typename HandlerClass>
      static bool enable(HandlerClass* instance, void (HandlerClass::*hanlderFunction)(QtMsgType, const QMessageLogContext&, const QString&));

      template <typename HandlerClass>
      static void disable(HandlerClass* instance);

      static QString symbol(const QtMsgType& type);

   private:
      MessageInterceptor();
      ~MessageInterceptor();

   private:
      using Function = std::function<void(QtMsgType, const QMessageLogContext&, const QString&)>;
      using TargetMap = QMap<void*, Function>;

   private:
      Q_INVOKABLE void outputInternal(QtMsgType type, const QMessageLogContext& context, const QString& msg);
      static void output(QtMsgType type, const QMessageLogContext& context, const QString& msg);

   private:
      static MessageInterceptor* me;
      QtMessageHandler systemHandler;
      TargetMap targetMap;
   };
} // namespace XX

#ifndef XXMessageInterceptorHPP
#include "XXMessageInterceptor.hpp"
#endif // NOT XXMessageInterceptorHPP

#endif // NOT XXMessageInterceptorH
