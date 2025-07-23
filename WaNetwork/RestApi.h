#ifndef RestApiH
#define RestApiH

#include <QObject>

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QException>

class RestApi : public QObject
{
   // do not use Q_OBJECT
   // this file will not be moc'ed automatically

public:
   using CallbackFunction = std::function<void(QJsonObject result)>;

   class StatusException : public QException
   {
   public:
      StatusException(int statusCode, const QJsonObject& content);

   private:
      int statusCode;
      QJsonObject content;
   };

public:
   RestApi(QObject* parent, const QString& baseUrl);

public:
   virtual QJsonObject get(const QString& endpoint, const QUrlQuery& params = QUrlQuery()) const;
   virtual void getAsync(CallbackFunction callback, const QString& endpoint, const QUrlQuery& params = QUrlQuery());
   virtual QJsonObject post(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery()) const;
   virtual void postAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery());
   virtual QJsonObject put(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery()) const;
   virtual void putAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery());

protected:
   using ReplyGeneratorFunction = std::function<QNetworkReply*(QNetworkRequest request)>;

protected:
   void setUseExceptions(bool enabled);
   void setVerbose(bool enabled);
   bool isVerbose() const;

   void setBaseUrl(const QString& url);
   void setBearerToken(const QByteArray& token);
   const QByteArray& getBearerToken() const;
   virtual QByteArray updateBearerToken() const;
   virtual void setAuthorization(QNetworkRequest& request, const QByteArray& bearerToken) const;
   void addUnauthorizedStatusCode(int code);
   QJsonObject parseBytes(const QByteArray& data) const;
   QJsonObject handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const;

protected:
   QNetworkAccessManager* manager;

private:
   QNetworkRequest createRequest(const QString& endpoint, const QUrlQuery& params) const;
   void handleReplyAsync(CallbackFunction callback, QNetworkRequest request, ReplyGeneratorFunction replyGenerator);

private:
   mutable QByteArray bearerToken;
   QString baseUrl;
   QList<int> unauthorizedStatusCodes;

   bool useExceptions;
   bool verbose;
};

#ifndef RestApiHPP
#include "RestApi.hpp"
#endif // NOT RestApiHPP

#endif // NOT RestApiH
