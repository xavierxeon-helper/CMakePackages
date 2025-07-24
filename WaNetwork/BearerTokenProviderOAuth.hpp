#ifndef BearerTokenProviderOAuthHPP
#define BearerTokenProviderOAuthHPP

#include "BearerTokenProviderOAuth.h"

#include <QDesktopServices>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>

#include <FileTools.h>

inline BearerTokenProviderOAuth::BearerTokenProviderOAuth(QObject* parent)
   : BearerTokenProvider(parent)
   , oauthFlow(nullptr)
   , grantConnection()
   , finalHTML()
   , tokenInfoUrl()
{
}

inline QJsonObject BearerTokenProviderOAuth::getTokenInfo(QByteArray token) const
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

inline void BearerTokenProviderOAuth::setTokenInfoUrl(const QString url)
{
   tokenInfoUrl = url;
}

inline void BearerTokenProviderOAuth::setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret)
{
   oauthFlow = new QOAuth2AuthorizationCodeFlow(this);

   oauthFlow->setAuthorizationUrl(QUrl(baseAuthUrl + "/authorize"));
   oauthFlow->setTokenUrl(QUrl(baseAuthUrl + "/token"));
   oauthFlow->setClientIdentifier(clientId);
   oauthFlow->setClientIdentifierSharedKey(clientSecret);

   setTokenInfoUrl(baseAuthUrl + "/tokeninfo");

   initFlow();
}

inline void BearerTokenProviderOAuth::setCustomFlow(QOAuth2AuthorizationCodeFlow* _oauthFlow)
{
   oauthFlow = _oauthFlow;
   initFlow();
}

inline void BearerTokenProviderOAuth::setFinalRedirect(const QString& url)
{
   finalHTML = "<html><head><meta http-equiv=\"refresh\" content=\"0; url=" + url + "\"></head></html>";
}

inline QOAuth2AuthorizationCodeFlow* BearerTokenProviderOAuth::getFlow() const
{
   return oauthFlow;
}

inline bool BearerTokenProviderOAuth::authorizeUser()
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

inline bool BearerTokenProviderOAuth::update()
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
   if (isEmpty())
      return authorizeUser();

   saveRefreshToken(oauthFlow->refreshToken());
   return true;
}

inline void BearerTokenProviderOAuth::saveRefreshToken(const QString& refreshToken)
{
   // do nothing
   Q_UNUSED(refreshToken);
}

inline QString BearerTokenProviderOAuth::loadRefreshToken()
{
   return QString();
}

inline void BearerTokenProviderOAuth::initFlow()
{
   QObject::disconnect(grantConnection);
   grantConnection = QObject::connect(oauthFlow, &QAbstractOAuth::authorizeWithBrowser, &QDesktopServices::openUrl);

   const QString token = loadRefreshToken();
   oauthFlow->setRefreshToken(token);
}

#endif // NOT BearerTokenProviderOAuthHPP
