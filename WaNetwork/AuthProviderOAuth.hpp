#ifndef AuthProviderOAuthHPP
#define AuthProviderOAuthHPP

#include "AuthProviderOAuth.h"

#include <QDesktopServices>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>

#include <FileTools.h>

inline AuthProvider::OAuth::OAuth(QObject* parent)
   : AuthProvider::General(parent)
   , oauthFlow(nullptr)
   , grantConnection()
   , finalHTML()
   , tokenInfoUrl()
{
}

inline QJsonObject AuthProvider::OAuth::getTokenInfo(QByteArray token) const
{
   if (token.isEmpty())
      token = getBearerToken();

   if (tokenInfoUrl.isEmpty())
      return QJsonObject();

   QUrlQuery params;
   params.addQueryItem("id_token", token);

   QUrl url(tokenInfoUrl);
   url.setQuery(params);

   QNetworkRequest request;
   request.setUrl(url);
   request.setRawHeader("Accept", "application/json");

   QNetworkAccessManager manager;
   QEventLoop loop;
   QNetworkReply* reply = manager.get(request);

   QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
   loop.exec();

   int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
   const QByteArray replyContent = reply->readAll();
   reply->deleteLater();

   if (200 != statusCode)
   {
      qWarning() << "Failed to get token info, status code:" << statusCode;
      return QJsonObject();
   }

   const QJsonObject content = FileTools::parseBytes(replyContent);
   return content;
}

inline void AuthProvider::OAuth::setTokenInfoUrl(const QString url)
{
   tokenInfoUrl = url;
}

inline void AuthProvider::OAuth::setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret)
{
   oauthFlow = new QOAuth2AuthorizationCodeFlow(this);

   oauthFlow->setAuthorizationUrl(QUrl(baseAuthUrl + "/authorize"));
   oauthFlow->setTokenUrl(QUrl(baseAuthUrl + "/token"));
   oauthFlow->setClientIdentifier(clientId);
   oauthFlow->setClientIdentifierSharedKey(clientSecret);

   setTokenInfoUrl(baseAuthUrl + "/tokeninfo");

   initFlow();
}

inline void AuthProvider::OAuth::setCustomFlow(QOAuth2AuthorizationCodeFlow* _oauthFlow)
{
   oauthFlow = _oauthFlow;
   initFlow();
}

inline void AuthProvider::OAuth::setFinalRedirect(const QString& url)
{
   finalHTML = "<html><head><meta http-equiv=\"refresh\" content=\"0; url=" + url + "\"></head></html>";
}

inline void AuthProvider::OAuth::setFinalHTML(const QString& html)
{
   finalHTML = html;
}

inline QOAuth2AuthorizationCodeFlow* AuthProvider::OAuth::getFlow() const
{
   return oauthFlow;
}

inline bool AuthProvider::OAuth::authorizeUser()
{
   QOAuthHttpServerReplyHandler redirectHandler(1234, nullptr);

   if (!finalHTML.isEmpty())
      redirectHandler.setCallbackText(finalHTML);

   QEventLoop loop;
   QObject::connect(oauthFlow, &QAbstractOAuth::granted, &loop, &QEventLoop::quit);

   oauthFlow->setReplyHandler(&redirectHandler);
   if (!redirectHandler.isListening())
      return false;

   oauthFlow->grant();
   loop.exec();

   setBearerToken(oauthFlow->token().toUtf8());
   saveRefreshToken(oauthFlow->refreshToken());

   redirectHandler.close();

   return true;
}

inline bool AuthProvider::OAuth::update()
{
   if (!oauthFlow)
   {
      qWarning() << "No OAuth flow set";
      return false;
   }

   if (oauthFlow->refreshToken().isEmpty())
      return authorizeUser();

   QEventLoop loop;
   QObject::connect(oauthFlow, &QAbstractOAuth::granted, &loop, &QEventLoop::quit);
   QObject::connect(oauthFlow, &QAbstractOAuth::requestFailed, &loop, &QEventLoop::quit);
   oauthFlow->refreshTokens();
   loop.exec();

   setBearerToken(oauthFlow->token().toUtf8());
   if (isNull())
      return authorizeUser();

   saveRefreshToken(oauthFlow->refreshToken());
   return true;
}

inline void AuthProvider::OAuth::saveRefreshToken(const QString& refreshToken)
{
   // do nothing
   Q_UNUSED(refreshToken);
}

inline QString AuthProvider::OAuth::loadRefreshToken()
{
   return QString();
}

inline void AuthProvider::OAuth::initFlow()
{
   QObject::disconnect(grantConnection);
   grantConnection = QObject::connect(oauthFlow, &QAbstractOAuth::authorizeWithBrowser, &QDesktopServices::openUrl);

   const QString token = loadRefreshToken();
   oauthFlow->setRefreshToken(token);
}

#endif // NOT AuthProviderOAuthHPP
