#ifndef RestApiHPP
#define RestApiHPP

#include "RestApi.h"

#include <QEventLoop>
#include <QJsonDocument>

inline RestApi::RestApi(QObject* parent, const QString& baseUrl)
   : QObject(parent)
   , manager(nullptr)
   , bearerToken()
   , baseUrl(baseUrl)
   , verbose(false)
{
   manager = new QNetworkAccessManager(this);
}

inline QJsonObject RestApi::get(const QString& endpoint, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&>(&QNetworkAccessManager::get), manager, std::placeholders::_1);
   return handleReply(request, replyGenerator);
}

inline void RestApi::getAsync(CallbackFunction callback, const QString& endpoint, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&>(&QNetworkAccessManager::get), manager, std::placeholders::_1);
   handleReplyAsync(callback, request, replyGenerator);
}

inline QJsonObject RestApi::post(const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::post), manager, std::placeholders::_1, data);
   return handleReply(request, replyGenerator);
}

inline void RestApi::postAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::post), manager, std::placeholders::_1, data);
   handleReplyAsync(callback, request, replyGenerator);
}

inline void RestApi::setBaseUrl(const QString& url)
{
   baseUrl = url;
}

inline void RestApi::setBearerToken(const QByteArray& token)
{
   bearerToken = token;
}

inline QByteArray RestApi::updateBearerToken()
{
   // do nothing
   return bearerToken;
}

inline void RestApi::setAuthorization(QNetworkRequest& request, const QByteArray& bearerToken)
{
   request.setRawHeader("Authorization", bearerToken);
}

inline QJsonObject RestApi::parseBytes(const QByteArray& data) const
{
   QJsonParseError error;
   QJsonDocument doc = QJsonDocument::fromJson(data, &error);

   if (QJsonParseError::NoError != error.error)
   {
      return QJsonObject();
   }

   return doc.object();
}

inline void RestApi::setVerbose(bool enabled)
{
   verbose = enabled;
}

inline QNetworkRequest RestApi::createRequest(const QString& endpoint, const QUrlQuery& params)
{
   QUrl url(baseUrl + endpoint);
   url.setQuery(params);

   QNetworkRequest request;
   request.setUrl(url);
   request.setRawHeader("Accept", "application/json");

   setAuthorization(request, bearerToken);

   return request;
}

inline QJsonObject RestApi::handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator)
{
   QEventLoop loop;
   int statusCode = 0;
   QJsonObject content;

   auto handleReplyInternal = [&]()
   {
      QNetworkReply* reply = replyGenerator(request);
      reply->ignoreSslErrors();

      QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
      loop.exec();

      statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      const QByteArray replyContent = reply->readAll();
      reply->deleteLater();

      content = parseBytes(replyContent);
   };

   handleReplyInternal();

   if (200 == statusCode)
   {
      if (verbose)
         qDebug() << "good reply for" << request.url().toString();

      return content;
   }
   else if (401 != statusCode)
   {
      qWarning() << "unhandled status code" << statusCode << "for" << request.url().toString();
      qWarning() << content;
      return content;
   }

   bearerToken = updateBearerToken();
   if (bearerToken.isEmpty())
      return QJsonObject();

   setAuthorization(request, bearerToken);

   handleReplyInternal();
   return content;
}

inline void RestApi::handleReplyAsync(CallbackFunction callback, QNetworkRequest request, ReplyGeneratorFunction replyGenerator)
{
   QNetworkReply* reply = replyGenerator(request);
   reply->ignoreSslErrors();

   auto onFinshed = [this, reply, request, callback]()
   {
      const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      const QByteArray replyContent = reply->readAll();
      reply->deleteLater();

      const QJsonObject content = parseBytes(replyContent);

      if (200 == statusCode)
      {
         return callback(content);
      }
      else if (401 != statusCode)
      {
         qWarning() << "unhandled status code" << statusCode << "for" << request.url().toString();
         return callback(content);
      }

      bearerToken = updateBearerToken();
      // TODO : set authorization and redo request
      return callback(content);
   };

   QObject::connect(reply, &QNetworkReply::finished, onFinshed);
}

#endif // NOT RestApiHPP
