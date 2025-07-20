#ifndef RestApiOAuthHPP
#define RestApiOAuthHPP

#include "RestApiOAuth.h"

#include <QDesktopServices>
#include <QEventLoop>
#include <QOAuthHttpServerReplyHandler>

inline RestApiOAuth::RestApiOAuth(QObject* parent, const QString& baseUrl)
   : RestApi(parent, baseUrl)
   , oauthFlow(nullptr)
   , grantConnection()
   , finalRedirectUrl()
{
}

inline void RestApiOAuth::setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret)
{
   oauthFlow = new QOAuth2AuthorizationCodeFlow(this);

   oauthFlow->setAuthorizationUrl(QUrl(baseAuthUrl + "/authorize"));
   oauthFlow->setTokenUrl(QUrl(baseAuthUrl + "/token"));
   oauthFlow->setClientIdentifier(clientId);
   oauthFlow->setClientIdentifierSharedKey(clientSecret);

   initFlow();
}

inline void RestApiOAuth::setCustomFlow(QOAuth2AuthorizationCodeFlow* _oauthFlow)
{
   oauthFlow = _oauthFlow;
   initFlow();
}

inline void RestApiOAuth::setFinalRedirect(const QString& url)
{
   finalRedirectUrl = url;
}

inline QOAuth2AuthorizationCodeFlow* RestApiOAuth::getFlow() const
{
   return oauthFlow;
}

inline void RestApiOAuth::saveRefreshToken(const QString& refreshToken) const
{
   Q_UNUSED(refreshToken);
}

inline QString RestApiOAuth::loadRefreshToken()
{
   return QString();
}

inline void RestApiOAuth::setAuthorization(QNetworkRequest& request, const QByteArray& bearerToken)
{
   request.setRawHeader("Authorization", "Bearer " + bearerToken);
}


inline QByteArray RestApiOAuth::authorizeUser()
{
   if(isVerbose())
      qDebug() << __FUNCTION__;

   QOAuthHttpServerReplyHandler redirectHandler(1234, this);
   if (!finalRedirectUrl.isEmpty())
   {
      const QString html = "<html><head><meta http-equiv=\"refresh\" content=\"0; url=" + finalRedirectUrl + "\"></head></html>";
      redirectHandler.setCallbackText(html);
   }

   QEventLoop loop;
   connect(oauthFlow, &QAbstractOAuth::granted, &loop, &QEventLoop::quit);

   auto onError = [&](const QAbstractOAuth::Error error)
   {
      if(isVerbose())
         qDebug() << "OAUTH ERROR @ authorizeUser" << (int)error;
      loop.quit();
   };
   connect(oauthFlow, &QAbstractOAuth::requestFailed, onError);

   auto replyDataReceived = [&](const QByteArray &data)
   {
      if(isVerbose())
         qDebug() << "DATA RECEIVED @ authorizeUser" << data;
   };
   connect(oauthFlow, &QAbstractOAuth::replyDataReceived, replyDataReceived);

   oauthFlow->setReplyHandler(&redirectHandler);
   if (!redirectHandler.isListening())
      return QByteArray();

   oauthFlow->grant();
   loop.exec();

   const QByteArray bearerToken = oauthFlow->token().toUtf8();
   saveRefreshToken(oauthFlow->refreshToken().toUtf8());

   redirectHandler.close();

   return bearerToken;
}

inline QByteArray RestApiOAuth::updateBearerToken()
{
   if(isVerbose())
      qDebug() << __FUNCTION__;

   if (!oauthFlow)
   {
      qWarning() << "No OAuth flow set";
      return QByteArray();
   }

   if (oauthFlow->refreshToken().isEmpty())
      return authorizeUser();

   QEventLoop loop;
   connect(oauthFlow, &QAbstractOAuth::granted, &loop, &QEventLoop::quit);

   auto onError = [&](const QAbstractOAuth::Error error)
   {
      if(isVerbose())
         qDebug() << "OAUTH ERROR @ updateBearerToken" << (int)error;
      loop.quit();
   };
   connect(oauthFlow, &QAbstractOAuth::requestFailed, onError);

   auto replyDataReceived = [&](const QByteArray &data)
   {
      if(isVerbose())
         qDebug() << "DATA RECEIVED @ updateBearerToken" << data;
   };
   connect(oauthFlow, &QAbstractOAuth::replyDataReceived, replyDataReceived);

   oauthFlow->refreshTokens();
   loop.exec();

   const QByteArray bearerToken = oauthFlow->token().toUtf8();
   if (bearerToken.isEmpty())
      return authorizeUser();

   saveRefreshToken(oauthFlow->refreshToken());
   return bearerToken;
}


inline void RestApiOAuth::initFlow()
{
   disconnect(grantConnection);
   grantConnection = connect(oauthFlow, &QAbstractOAuth::authorizeWithBrowser, this, &QDesktopServices::openUrl);

   const QString token = loadRefreshToken();
   oauthFlow->setRefreshToken(token);
}

#endif // NOT RestApiOAuthHPP
