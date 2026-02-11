#include "XXRestApiAsync.h"

#include <XXFileTools.h>

#include "XXAuthProviderToken.h"

XX::RestApi::Async::Async(QObject* parent, const QString& baseUrl)
   : Blocking(parent, baseUrl)
{
}

void XX::RestApi::Async::getAsync(CallbackFunction callback, const QString& endpoint, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&>(&QNetworkAccessManager::get), manager, std::placeholders::_1);
   handleReplyAsync(callback, request, replyGenerator);
}

void XX::RestApi::Async::postAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::post), manager, std::placeholders::_1, data);
   handleReplyAsync(callback, request, replyGenerator);
}

void XX::RestApi::Async::putAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::put), manager, std::placeholders::_1, data);
   handleReplyAsync(callback, request, replyGenerator);
}

void XX::RestApi::Async::handleReplyAsync(CallbackFunction callback, QNetworkRequest request, ReplyGeneratorFunction replyGenerator)
{
   if (provider->isNull() && provider->update())
   {
      provider->setAuthorization(request);
   }

   QNetworkReply* reply = replyGenerator(request);
   reply->ignoreSslErrors();

   auto onFinshed = [this, reply, request, callback, replyGenerator]()
   {
      Result result;
      result.statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      result.raw = reply->readAll();
      reply->deleteLater();

      result.parseJson();

      if (200 == result.statusCode)
         return callback(result);

      result = handleReply(request, replyGenerator);
      return callback(result);
   };

   QObject::connect(reply, &QNetworkReply::finished, onFinshed);
}
