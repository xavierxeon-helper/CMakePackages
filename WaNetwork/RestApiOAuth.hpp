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
{
}

inline void RestApiOAuth::setFlow(QOAuth2AuthorizationCodeFlow* _oauthFlow)
{
   oauthFlow = _oauthFlow;

   disconnect(grantConnection);
   grantConnection = connect(oauthFlow, &QAbstractOAuth::authorizeWithBrowser, this, &QDesktopServices::openUrl);

   const QString token = loadRefreshToken();
   oauthFlow->setRefreshToken(token);
}

inline QOAuth2AuthorizationCodeFlow*  RestApiOAuth::flow() const
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

inline QByteArray RestApiOAuth::updateBearerToken()
{
   if (!oauthFlow)
   {
      qWarning() << "No OAuth flow set";
      return QByteArray();
   }

   if (oauthFlow->refreshToken().isEmpty())
      return authorizeUser();

   QEventLoop loop;
   QObject::connect(oauthFlow, &QAbstractOAuth::granted, &loop, &QEventLoop::quit);
   QObject::connect(oauthFlow, &QAbstractOAuth::requestFailed,  &loop, &QEventLoop::quit);
   oauthFlow->refreshAccessToken();
   loop.exec();

   const QByteArray bearerToken = oauthFlow->token().toUtf8();
   if (bearerToken.isEmpty())
      return authorizeUser();

   saveRefreshToken(oauthFlow->refreshToken());
   return bearerToken;
}

inline QByteArray RestApiOAuth::authorizeUser()
{
   QOAuthHttpServerReplyHandler redirectHandler(1234, this);

   QEventLoop loop;
   QObject::connect(oauthFlow, &QAbstractOAuth::granted, &loop, &QEventLoop::quit);

   oauthFlow->setReplyHandler(&redirectHandler);
   if (!redirectHandler.isListening())
      return QByteArray();

   oauthFlow->grant();
   loop.exec();

   const QByteArray bearerToken = oauthFlow->token().toUtf8();
   saveRefreshToken(oauthFlow->refreshToken());

   redirectHandler.close();

   return bearerToken;
}

#endif // NOT RestApiOAuthHPP
