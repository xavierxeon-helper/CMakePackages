#include "XXAuthProviderToken.h"

XX::AuthProvider::Token::Token(QObject* parent)
   : QObject(parent)
   , bearerToken()
{
}

const QByteArray& XX::AuthProvider::Token::getBearerToken() const
{
   return bearerToken;
}

bool XX::AuthProvider::Token::isNull() const
{
   return bearerToken.isEmpty();
}

void XX::AuthProvider::Token::setBearerToken(const QByteArray& token)
{
   bearerToken = token;
}

bool XX::AuthProvider::Token::update()
{
   return true;
}

void XX::AuthProvider::Token::setAuthorization(QNetworkRequest& request) const
{
   request.setRawHeader("Authorization", "Bearer " + bearerToken);
}

XX::AuthProvider::Token::RefreshData XX::AuthProvider::Token::maualRefresh(const QString& oldRefreshToken, const QString& tokenRefreshUrl)
{
   if (oldRefreshToken.isEmpty())
      return RefreshData{};

   QUrlQuery postData;
   postData.addQueryItem("grant_type", "refresh_token");
   postData.addQueryItem("refresh_token", oldRefreshToken);

   QNetworkRequest request;
   request.setUrl(tokenRefreshUrl);
   request.setRawHeader("Accept", "application/json");
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

   QNetworkAccessManager manager;
   QEventLoop loop;
   QNetworkReply* reply = manager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

   QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
   loop.exec();

   int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
   const QByteArray replyContent = reply->readAll();
   reply->deleteLater();

   const QJsonObject content = XX::FileTools::parseBytes(replyContent);
   if (200 != statusCode)
      return RefreshData{};

   RefreshData data;
   data.refreshToken = content["refresh_token"].toString();
   data.accessToken = content["access_token"].toString();

   const float expires = content["expires"].toDouble();
   data.expireTime = QDateTime::fromSecsSinceEpoch((int)expires);

   return data;
}