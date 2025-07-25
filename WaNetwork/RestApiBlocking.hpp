#ifndef RestApiBlockingHPP
#define RestApiBlockingHPP

#include "RestApiBlocking.h"

#include <QEventLoop>
#include <QJsonDocument>

#include <FileTools.h>

#include "AuthProviderToken.h"
#include "RestApiStatusException.h"

inline RestApi::Blocking::Blocking(QObject* parent, const QString& baseUrl)
   : QObject(parent)
   , manager(nullptr)
   , provider(nullptr)
   , baseUrl(baseUrl)
   , unauthorizedStatusCodes({401})
   , useExceptions(false)
   , verbose(false)
{
   manager = new QNetworkAccessManager(this);
   provider = new AuthProvider::Token(this);

   unauthorizedStatusCodes.append(401);
}

inline QJsonObject RestApi::Blocking::get(const QString& endpoint, const QUrlQuery& params) const
{
   QNetworkRequest request = createRequest(endpoint, params);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&>(&QNetworkAccessManager::get), manager, std::placeholders::_1);
   return handleReply(request, replyGenerator);
}
inline QJsonObject RestApi::Blocking::post(const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params) const
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::post), manager, std::placeholders::_1, data);
   return handleReply(request, replyGenerator);
}

inline QJsonObject RestApi::Blocking::put(const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params) const
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::put), manager, std::placeholders::_1, data);
   return handleReply(request, replyGenerator);
}

inline void RestApi::Blocking::setAuthProvider(AuthProvider::Token* newProvider)
{
   if (provider)
      delete provider;

   provider = newProvider;
}

inline void RestApi::Blocking::setUseExceptions(bool enabled)
{
   useExceptions = enabled;
}

inline void RestApi::Blocking::setVerbose(bool enabled)
{
   verbose = enabled;
}

inline bool RestApi::Blocking::isVerbose() const
{
   return verbose;
}

inline void RestApi::Blocking::setBaseUrl(const QString& url)
{
   baseUrl = url;
}

inline void RestApi::Blocking::addUnauthorizedStatusCode(int code)
{
   if (unauthorizedStatusCodes.contains(code))
      return;

   unauthorizedStatusCodes.append(code);
}

inline QNetworkRequest RestApi::Blocking::createRequest(const QString& endpoint, const QUrlQuery& params) const
{
   QUrl url(baseUrl + endpoint);
   url.setQuery(params);

   QNetworkRequest request;
   request.setUrl(url);
   request.setRawHeader("Accept", "application/json");

   provider->setAuthorization(request);

   return request;
}

inline QJsonObject RestApi::Blocking::handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const
{
   auto updateToken = [&]() -> bool
   {
      if (!provider->update())
         return false;

      provider->setAuthorization(request);
      return true;
   };

   if (provider->isNull() && !updateToken())
      return QJsonObject();

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


   if (handleReplyInternal())
      return content;

   if (!updateToken())
      return content;

   handleReplyInternal();
   return content;
}

#endif // NOT RestApiBlockingHPP
