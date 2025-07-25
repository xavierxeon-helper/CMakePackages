#ifndef RestApiAsyncH
#define RestApiAsyncH

#include "RestApiBlocking.h"

namespace RestApi
{
   class Async : public Blocking
   {
      // do not use Q_OBJECT
      // this file will not be moc'ed automatically

   public:
      using CallbackFunction = std::function<void(QJsonObject result)>;

   public:
      Async(QObject* parent, const QString& baseUrl);

   public:
      virtual void getAsync(CallbackFunction callback, const QString& endpoint, const QUrlQuery& params = QUrlQuery());
      virtual void postAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery());
      virtual void putAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery());

   private:
      void handleReplyAsync(CallbackFunction callback, QNetworkRequest request, ReplyGeneratorFunction replyGenerator);
   };
} // namespace RestApi

#ifndef RestApiAsyncHPP
#include "RestApiAsync.hpp"
#endif // NOT RestApiAsyncHPP

#endif // NOT RestApiAsyncH
