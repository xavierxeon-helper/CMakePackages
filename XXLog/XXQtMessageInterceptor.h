#ifndef XXQtMessageInterceptorH
#define XXQtMessageInterceptorH

#include "XXLogExportDef.h"
#include <QObject>

#include <functional>

#include <QColor>
#include <QMap>

namespace XX
{
   namespace QtMessage
   {
      //! @brief intercept the default Qt message handler
      //! @ingroup XXLog

      struct XXLOG_DECLSPEC Interceptor : public QObject
      {
         Q_OBJECT

      public:
         template <typename HandlerClass>
         static bool enable(HandlerClass* instance, void (HandlerClass::*hanlderFunction)(QtMsgType, const QMessageLogContext&, const QString&));

         template <typename HandlerClass>
         static void disable(HandlerClass* instance);

         static QString symbol(const QtMsgType& type);

      private:
         Interceptor();
         ~Interceptor();

      private:
         using Function = std::function<void(QtMsgType, const QMessageLogContext&, const QString&)>;
         using TargetMap = QMap<void*, Function>;

      private:
         Q_INVOKABLE void outputInternal(QtMsgType type, const QMessageLogContext& context, const QString& msg);
         static void output(QtMsgType type, const QMessageLogContext& context, const QString& msg);

      private:
         static Interceptor* me;
         QtMessageHandler systemHandler;
         TargetMap targetMap;
      };
   } // namespace QtMessage
} // namespace XX

#ifndef XXQtMessageInterceptorHPP
#include "XXQtMessageInterceptor.hpp"
#endif // NOT XXQtMessageInterceptorHPP

#endif // NOT XXQtMessageInterceptorH
