#ifndef RestApiHPP
#define RestApiHPP

#include "RestApi.h"

#include <QEventLoop>
#include <QJsonDocument>

#include <FileTools.h>

#include "BearerTokenProvider.h"

// exception

inline RestApi::StatusException::StatusException(int statusCode, const QJsonObject& content)
   : QException()
   , statusCode(statusCode)
   , content(content)
{
}

// rest api

inline RestApi::RestApi(QObject* parent, const QString& baseUrl)
   : QObject(parent)
   , manager(nullptr)
   , provider(nullptr)
   , baseUrl(baseUrl)
   , unauthorizedStatusCodes({401})
   , useExceptions(false)
   , verbose(false)
{
   manager = new QNetworkAccessManager(this);
   provider = new BearerTokenProvider(this);

   unauthorizedStatusCodes.append(401);
}

inline QJsonObject RestApi::get(const QString& endpoint, const QUrlQuery& params) const
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

inline QJsonObject RestApi::post(const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params) const
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

inline QJsonObject RestApi::put(const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params) const
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::put), manager, std::placeholders::_1, data);
   return handleReply(request, replyGenerator);
}

inline void RestApi::putAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params)
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::put), manager, std::placeholders::_1, data);
   handleReplyAsync(callback, request, replyGenerator);
}

inline void RestApi::setBearerTokenProvider(BearerTokenProvider* newProvider)
{
   if (provider)
      delete provider;

   provider = newProvider;
}

inline void RestApi::setUseExceptions(bool enabled)
{
   useExceptions = enabled;
}

inline void RestApi::setVerbose(bool enabled)
{
   verbose = enabled;
}

inline bool RestApi::isVerbose() const
{
   return verbose;
}

inline void RestApi::setBaseUrl(const QString& url)
{
   baseUrl = url;
}

inline void RestApi::addUnauthorizedStatusCode(int code)
{
   if (unauthorizedStatusCodes.contains(code))
      return;

   unauthorizedStatusCodes.append(code);
}

inline QJsonObject RestApi::handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const
{
   QEventLoop loop;
   int statusCode = 0;
   QJsonObject content;

   auto handleReplyInternal = [&]() -> bool
   {
      QNetworkReply* reply = replyGenerator(request);
      reply->ignoreSslErrors();

      QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
      loop.exec();

      statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      const QByteArray replyContent = reply->readAll();
      reply->deleteLater();

      content = FileTools::parseBytes(replyContent);

      if (200 == statusCode)
      {
         if (verbose)
            qDebug() << "good reply for" << request.url().toString();

         return true;
      }
      else if (!unauthorizedStatusCodes.contains(statusCode))
      {
         qWarning() << "unhandled status code" << statusCode << "for" << request.url().toString();
         if (useExceptions)
         {
            throw new StatusException(statusCode, content);
         }
         else
         {
            qWarning() << content;
            return true;
         }
      }
      else if (verbose)
      {
         qDebug() << "STATUS UNAUTHORIZED" << request.url().toString();
         qDebug() << content;
      }
      return false;
   };

   auto updateToken = [&]() -> bool
   {
      if (!provider->update())
         return false;

      provider->setAuthorization(request);
      return true;
   };

   if (provider->isEmpty() && !updateToken())
      return content;

   if (handleReplyInternal())
      return content;

   if (!updateToken())
      return content;

   handleReplyInternal();
   return content;
}

inline QNetworkRequest RestApi::createRequest(const QString& endpoint, const QUrlQuery& params) const
{
   QUrl url(baseUrl + endpoint);
   url.setQuery(params);

   QNetworkRequest request;
   request.setUrl(url);
   request.setRawHeader("Accept", "application/json");

   provider->setAuthorization(request);

   return request;
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

#endif // NOT RestApiHPP
