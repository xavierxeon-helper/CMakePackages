#ifndef RestApiAsyncH
#define RestApiAsyncH

#include "RestApiBlocking.h"
#include "WaToolsNetworkExportDef.h"

namespace RestApi
{
   /// @brief Asynchronous REST API client

   class WATOOLSNETWORK_DECLSPEC Async : public Blocking
   {
      Q_OBJECT

   public:
      using CallbackFunction = std::function<void(Result result)>;

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

#endif // NOT RestApiAsyncH
