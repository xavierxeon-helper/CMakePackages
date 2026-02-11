#include "XXAuthProviderOAuth.h"

#include <QDesktopServices>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>

#include <XXFileTools.h>

#include "XXRestApiException.h"

// block

XX::AuthProvider::OAuth::BlockState::BlockState(OAuth* auth)
   : auth(auth)
   , previousState(auth->state)
{
   if (auth->state == State::Ready)
   {
      auth->state = State::Blocked;
   }
}

XX::AuthProvider::OAuth::BlockState::~BlockState()
{
   auth->state = previousState;
}

// oauth

XX::AuthProvider::OAuth::OAuth(QObject* parent)
   : AuthProvider::Token(parent)
   , Network::Settings()
   , oauthFlow(nullptr)
   , grantConnection()
   , finalHTML()
   , tokenInfoUrl()
   , state(State::Initial)
{
}

QJsonObject XX::AuthProvider::OAuth::getTokenInfo(QByteArray token) const
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

   const QJsonObject content = FileTools::parseBytes(replyContent);
   if (200 != statusCode)
   {
      if (useExceptions())
      {
         throw new RestApi::StatusException(statusCode, oauthFlow->authorizationUrl(), content);
      }
      else
      {
         qWarning() << "Failed to get token info, status code:" << statusCode;
         return QJsonObject();
      }
   }

   return content;
}

void XX::AuthProvider::OAuth::setTokenInfoUrl(const QString url)
{
   tokenInfoUrl = url;
}

void XX::AuthProvider::OAuth::setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret)
{
   oauthFlow = new QOAuth2AuthorizationCodeFlow(this);

   oauthFlow->setAuthorizationUrl(QUrl(baseAuthUrl + "/authorize"));
   oauthFlow->setTokenUrl(QUrl(baseAuthUrl + "/token"));
   oauthFlow->setClientIdentifier(clientId);
   oauthFlow->setClientIdentifierSharedKey(clientSecret);

   setTokenInfoUrl(baseAuthUrl + "/tokeninfo");

   initFlow();
}

void XX::AuthProvider::OAuth::setCustomFlow(QOAuth2AuthorizationCodeFlow* _oauthFlow)
{
   oauthFlow = _oauthFlow;
   initFlow();
}

void XX::AuthProvider::OAuth::setFinalRedirect(const QString& url)
{
   finalHTML = "<html><head><meta http-equiv=\"refresh\" content=\"0; url=" + url + "\"></head></html>";
}

void XX::AuthProvider::OAuth::setFinalHTML(const QString& html)
{
   finalHTML = html;
}

QOAuth2AuthorizationCodeFlow* XX::AuthProvider::OAuth::getFlow() const
{
   return oauthFlow;
}

bool XX::AuthProvider::OAuth::authorizeUser()
{
   state = State::AuthUser;
   QOAuthHttpServerReplyHandler redirectHandler(1234, nullptr);

   if (!finalHTML.isEmpty())
      redirectHandler.setCallbackText(finalHTML);

   QEventLoop loop;

   auto onError = [&](const QAbstractOAuth::Error error)
   {
      qWarning() << "OAuth error @ authorizeUser():" << (int)error;
      loop.quit();

      if (useExceptions())
      {
         if (QAbstractOAuth::Error::NetworkError == error)
            throw new RestApi::UnreachableException(oauthFlow->authorizationUrl());
         else
            throw new RestApi::StatusException(500 + int(error), oauthFlow->authorizationUrl());
      }
   };

   QObject::connect(oauthFlow, &QAbstractOAuth::granted, &loop, &QEventLoop::quit);
   QObject::connect(oauthFlow, &QAbstractOAuth::requestFailed, onError);

   oauthFlow->setReplyHandler(&redirectHandler);
   if (!redirectHandler.isListening())
      return false;

   oauthFlow->grant();
   loop.exec();

   setBearerToken(oauthFlow->token().toUtf8());
   saveRefreshToken(oauthFlow->refreshToken());

   redirectHandler.close();

   state = State::Ready;
   return true;
}

bool XX::AuthProvider::OAuth::update()
{
   if (!oauthFlow)
   {
      qWarning() << "No OAuth flow set";
      return false;
   }

   if (State::Ready != state)
   {
      return false;
   }

   state = State::Update;

   if (oauthFlow->refreshToken().isEmpty())
      return authorizeUser();

   QEventLoop loop;
   QObject::connect(oauthFlow, &QAbstractOAuth::granted, &loop, &QEventLoop::quit);

   auto onError = [&](const QAbstractOAuth::Error error)
   {
      qWarning() << "OAuth error @ update():" << (int)error;
      loop.quit();

      if (useExceptions())
      {
         if (QAbstractOAuth::Error::NetworkError == error)
            throw new RestApi::UnreachableException(oauthFlow->authorizationUrl());
         else
            throw new RestApi::StatusException(500 + int(error), oauthFlow->authorizationUrl());
      }
   };

   QObject::connect(oauthFlow, &QAbstractOAuth::requestFailed, onError);
   oauthFlow->refreshTokens();
   loop.exec();

   setBearerToken(oauthFlow->token().toUtf8());
   if (isNull())
      return authorizeUser();

   saveRefreshToken(oauthFlow->refreshToken());

   state = State::Ready;
   return true;
}

void XX::AuthProvider::OAuth::saveRefreshToken(const QString& refreshToken)
{
   // do nothing
   Q_UNUSED(refreshToken);
}

QString XX::AuthProvider::OAuth::loadRefreshToken()
{
   return QString();
}

void XX::AuthProvider::OAuth::initFlow()
{
   QObject::disconnect(grantConnection);
   grantConnection = QObject::connect(oauthFlow, &QAbstractOAuth::authorizeWithBrowser, &QDesktopServices::openUrl);

   const QString token = loadRefreshToken();
   oauthFlow->setRefreshToken(token);

   state = State::Ready;
}
