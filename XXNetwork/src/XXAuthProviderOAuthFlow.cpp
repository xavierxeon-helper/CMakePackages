#include "XXAuthProviderOAuthFlow.h"

#include <QCryptographicHash>
#include <QDesktopServices>
#include <QEventLoop>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRandomGenerator>
#include <QUrlQuery>

#include <XXFileTools.h>

#include "XXAuthProviderOAuthFlowRedirectServer.h"

// see https://datatracker.ietf.org/doc/html/rfc7636

XX::AuthProvider::OAuthFlow::OAuthFlow(QObject* parent)
   : XX::AuthProvider::Token(parent)
   , Network::Settings()
   , authUrl()
   , tokenUrl()
   , clientId()
   , clientSecret()
   , scopeTokens()
   , refreshToken()
   , finalHTML()
   , verifierBytes()
{
}

void XX::AuthProvider::OAuthFlow::setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret)
{
   authUrl = baseAuthUrl + "/authorize";
   tokenUrl = baseAuthUrl + "/token";
   this->clientId = clientId;
   this->clientSecret = clientSecret;

   refreshToken = loadRefreshToken();
}

void XX::AuthProvider::OAuthFlow::setFinalRedirect(const QString& url)
{
   finalHTML = "<html><head><meta http-equiv=\"refresh\" content=\"0; url=" + url + "\"></head></html>";
}

void XX::AuthProvider::OAuthFlow::setFinalHTML(const QString& html)
{
   finalHTML = html;
}

void XX::AuthProvider::OAuthFlow::setRequestedScopeTokens(QSet<QByteArray> scopeTokens)
{
   this->scopeTokens = scopeTokens;
}

bool XX::AuthProvider::OAuthFlow::update()
{
   if (refreshToken.isEmpty())
      refreshToken = "check database connection";

   RefreshData refreshData = manualRefresh(refreshToken, tokenUrl);
   if (refreshData.accessToken.isNull())
      return authorizeUser();

   setBearerToken(refreshData.accessToken.toUtf8());
   refreshToken = refreshData.refreshToken;
   saveRefreshToken(refreshToken);

   return true;
}

bool XX::AuthProvider::OAuthFlow::authorizeUser()
{
   verifierBytes = generateBytes(43);

   QByteArray code = getAuthCode();
   if (code.isEmpty())
      return false;

   QUrlQuery postData;
   postData.addQueryItem("client_id", clientId);
   postData.addQueryItem("client_secret", clientSecret);
   postData.addQueryItem("code", code);
   postData.addQueryItem("code_verifier", QString::fromUtf8(verifierBytes));
   postData.addQueryItem("grant_type", "authorization_code");
   postData.addQueryItem("redirect_uri", "oob");

   QNetworkRequest request;
   request.setUrl(tokenUrl);
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
      return false;

   refreshToken = content["refresh_token"].toString();
   saveRefreshToken(refreshToken);

   QString accessToken = content["access_token"].toString();
   setBearerToken(accessToken.toUtf8());

   return true;
}

void XX::AuthProvider::OAuthFlow::saveRefreshToken(const QString& refreshToken)
{
   // do nothing
   Q_UNUSED(refreshToken);
}

QString XX::AuthProvider::OAuthFlow::loadRefreshToken()
{
   return QString();
}

QByteArray XX::AuthProvider::OAuthFlow::generateBytes(uint length)
{
   static const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~";

   QByteArray bytes;
   bytes.reserve(length);

   for (uint i = 0; i < length; ++i)
   {
      quint32 index = QRandomGenerator::global()->bounded(static_cast<quint32>(sizeof(characters) - 1));
      bytes.append(characters[index]);
   }

   return bytes;
}

QString XX::AuthProvider::OAuthFlow::generateCodeChallenge()
{
   QByteArray hashBytes = QCryptographicHash::hash(verifierBytes, QCryptographicHash::Sha256);
   QString challenge = QString::fromUtf8(
      hashBytes.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals));

   return challenge;
}

QByteArray XX::AuthProvider::OAuthFlow::getAuthCode()
{
   QByteArray verifyState = generateBytes(8);

   QUrlQuery queryGetCode;
   queryGetCode.addQueryItem("client_id", clientId);
   queryGetCode.addQueryItem("code_challenge", generateCodeChallenge());
   queryGetCode.addQueryItem("code_challenge_method", "S256");
   queryGetCode.addQueryItem("redirect_uri", "http://127.0.0.1:1234/");
   queryGetCode.addQueryItem("response_type", "code");
   if (!scopeTokens.empty())
      queryGetCode.addQueryItem("scope", scopeTokens.values().join(" "));
   queryGetCode.addQueryItem("state", verifyState);

   QUrl getCodehUrl(authUrl);
   getCodehUrl.setQuery(queryGetCode);
   qDebug() << "Request URL: " << getCodehUrl.toString();

   RedirectServer redirectServer(1234);
   QEventLoop loop;
   connect(&redirectServer, &RedirectServer::codeReceived, &loop, &QEventLoop::quit);

   QDesktopServices::openUrl(getCodehUrl);
   loop.exec();

   redirectServer.sendResponse(finalHTML);

   QByteArray state = redirectServer.getState();
   if (state != verifyState)
      return QByteArray();

   QByteArray code = redirectServer.getCode();
   return code;
}
