#include "XXRestApiBlocking.h"

#include <QEventLoop>
#include <QJsonDocument>

#include <XXFileTools.h>

#include "XXAuthProviderToken.h"
#include "XXRestApiException.h"

RestApi::Blocking::Blocking(QObject* parent, const QString& baseUrl)
   : QObject(parent)
   , Network::Settings()
   , manager(nullptr)
   , provider(nullptr)
   , baseUrl(baseUrl)
   , successStatusCodes{200, 201, 202, 204}
   , unauthorizedStatusCodes({401})
{
   manager = new QNetworkAccessManager(this);
   provider = new AuthProvider::Token(this);

   unauthorizedStatusCodes.append(401);
}

RestApi::Result RestApi::Blocking::get(const QString& endpoint, const QUrlQuery& params) const
{
   QNetworkRequest request = createRequest(endpoint, params);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&>(&QNetworkAccessManager::get), manager, std::placeholders::_1);
   return handleReply(request, replyGenerator);
}

RestApi::ResultRaw RestApi::Blocking::getRaw(const QString& endpoint, const QUrlQuery& params) const
{
   QNetworkRequest request = createRequest(endpoint, params);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&>(&QNetworkAccessManager::get), manager, std::placeholders::_1);
   return handleReplyRaw(request, replyGenerator);
}

RestApi::Result RestApi::Blocking::post(const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params) const
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::post), manager, std::placeholders::_1, data);
   return handleReply(request, replyGenerator);
}

RestApi::Result RestApi::Blocking::put(const QString& endpoint, const QJsonObject& payload, const QUrlQuery& params) const
{
   QNetworkRequest request = createRequest(endpoint, params);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   const QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

   ReplyGeneratorFunction replyGenerator = std::bind(qOverload<const QNetworkRequest&, const QByteArray&>(&QNetworkAccessManager::put), manager, std::placeholders::_1, data);
   return handleReply(request, replyGenerator);
}

const QString& RestApi::Blocking::getBaseUrl() const
{
   return baseUrl;
}

void RestApi::Blocking::setAuthProvider(AuthProvider::Token* newProvider)
{
   if (provider)
      delete provider;

   provider = newProvider;
}

void RestApi::Blocking::setBaseUrl(const QString& url)
{
   baseUrl = url;
}

void RestApi::Blocking::addUnauthorizedStatusCode(int code)
{
   if (unauthorizedStatusCodes.contains(code))
      return;

   unauthorizedStatusCodes.append(code);
}

QNetworkRequest RestApi::Blocking::createRequest(const QString& endpoint, const QUrlQuery& params) const
{
   QUrl url(baseUrl + endpoint);
   url.setQuery(params);

   QNetworkRequest request;
   request.setUrl(url);
   request.setRawHeader("Accept", "application/json");

   provider->setAuthorization(request);

   return request;
}

RestApi::Result RestApi::Blocking::handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const
{
   auto updateToken = [&]() -> bool
   {
      if (!provider->update())
         return false;

      provider->setAuthorization(request);
      return true;
   };

   if (provider->isNull() && !updateToken())
      return Result{};

   QEventLoop loop;
   Result result;

   auto handleReplyInternal = [&]() -> bool
   {
      QNetworkReply* reply = replyGenerator(request);
      reply->ignoreSslErrors();

      QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
      loop.exec();

      result.statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      result.raw = reply->readAll();
      reply->deleteLater();

      result.parseJson();

      if (successStatusCodes.contains(result.statusCode))
      {
         if (verbose())
            qDebug() << "good reply for" << request.url().toString();

         return true;
      }
      else if (!unauthorizedStatusCodes.contains(result.statusCode))
      {
         qWarning() << "unhandled status code" << result.statusCode << "for" << request.url().toString();
         if (useExceptions())
         {
            throw new StatusException(result.statusCode, baseUrl, result.json);
         }
         else
         {
            qWarning() << result.raw;
            return true;
         }
      }
      else if (verbose())
      {
         qDebug() << "STATUS UNAUTHORIZED" << request.url().toString();
         qDebug() << result.raw;
      }
      return false;
   };

   if (handleReplyInternal())
      return result;

   if (!updateToken())
      return result;

   handleReplyInternal();
   return result;
}

RestApi::ResultRaw RestApi::Blocking::handleReplyRaw(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const
{
   auto updateToken = [&]() -> bool
   {
      if (!provider->update())
         return false;

      provider->setAuthorization(request);
      return true;
   };

   if (provider->isNull() && !updateToken())
      return ResultRaw{};

   QEventLoop loop;
   ResultRaw result;

   auto handleReplyInternal = [&]() -> bool
   {
      QNetworkReply* reply = replyGenerator(request);
      reply->ignoreSslErrors();

      QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
      loop.exec();

      result.statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      result.raw = reply->readAll();
      reply->deleteLater();

      if (200 == result.statusCode)
      {
         if (verbose())
            qDebug() << "good reply for" << request.url().toString();

         return true;
      }
      else if (!unauthorizedStatusCodes.contains(result.statusCode))
      {
         qWarning() << "unhandled status code" << result.statusCode << "for" << request.url().toString();
         if (useExceptions())
            throw new StatusException(result.statusCode, baseUrl);
         else
            return true;
      }
      else if (verbose())
      {
         qDebug() << "STATUS UNAUTHORIZED" << request.url().toString();
      }
      return false;
   };

   if (handleReplyInternal())
      return result;

   if (!updateToken())
      return result;

   handleReplyInternal();
   return result;
}
