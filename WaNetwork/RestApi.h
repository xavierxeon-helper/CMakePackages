#ifndef RestApiH
#define RestApiH

#include <QObject>

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

class RestApi : public QObject
{
   // do not use Q_OBJECT
   // this file will not be moc'ed automatically

public:
   using CallbackFunction = std::function<void(QJsonObject result)>;

public:
   RestApi(QObject* parent, const QString& baseUrl);

public:
   virtual QJsonObject get(const QString& endpoint, const QUrlQuery& params = QUrlQuery());
   virtual void getAsync(CallbackFunction callback, const QString& endpoint, const QUrlQuery& params = QUrlQuery());
   virtual QJsonObject post(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery());
   virtual void postAsync(CallbackFunction callback, const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery());

protected:
   void setBearerToken(const QByteArray& token);
   virtual QByteArray updateBearerToken() = 0;
   virtual void setAuthorization(QNetworkRequest& request, const QByteArray& bearerToken);

   QJsonObject parseBytes(const QByteArray& data);
   void setVerbose(bool enabled);

private:
   using ReplyGeneratorFunction = std::function<QNetworkReply*(QNetworkRequest request)>;

private:
   QNetworkRequest createRequest(const QString& endpoint, const QUrlQuery& params);
   QJsonObject handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator);
   void handleReplyAsync(CallbackFunction callback, QNetworkRequest request, ReplyGeneratorFunction replyGenerator);

private:
   QNetworkAccessManager* manager;
   QByteArray bearerToken;
   QString baseUrl;

   bool verbose;
};

#ifndef RestApiHPP
#include "RestApi.hpp"
#endif // NOT RestApiHPP

#endif // NOT RestApiH
