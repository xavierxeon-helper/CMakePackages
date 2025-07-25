#ifndef RestApiAsyncHPP
#define RestApiAsyncHPP

#include "RestApiAsync.h"

inline RestApi::Async::Async(QObject* parent, const QString& baseUrl)
   : Blocking(parent, baseUrl)
{
}

inline void RestApi::Async::getAsync(CallbackFunction callback, const QString& endpoint, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&>(&QNetworkAccessManager::get), manager, std::placeholders::_1);
   handleReplyAsync(callback, request, replyGenerator);
}

inline void RestApi::Async::postAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::post), manager, std::placeholders::_1, data);
   handleReplyAsync(callback, request, replyGenerator);
}

inline void RestApi::Async::putAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::put), manager, std::placeholders::_1, data);
   handleReplyAsync(callback, request, replyGenerator);
}

inline void RestApi::Async::handleReplyAsync(CallbackFunction callback, QNetworkRequest request, ReplyGeneratorFunction replyGenerator)
{
   QNetworkReply* reply = replyGenerator(request);
   reply->ignoreSslErrors();

   auto onFinshed = [this, reply, request, callback]()
   {
      const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      const QByteArray replyContent = reply->readAll();
      reply->deleteLater();

      const QJsonObject content = FileTools::parseBytes(replyContent);

      if (200 == statusCode)
      {
         return callback(content);
      }
      else if (!unauthorizedStatusCodes.contains(statusCode))
      {
         if (useExceptions)
         {
            throw new StatusException(statusCode, content);
         }
         else
         {
            qWarning() << "unhandled status code" << statusCode << "for" << request.url().toString();
            return callback(content);
         }
      }

      provider->update();
      // TODO : set authorization and redo request
      return callback(content);
   };

   QObject::connect(reply, &QNetworkReply::finished, onFinshed);
}

#endif // NOT RestApiAsyncHPP
