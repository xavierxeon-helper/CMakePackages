#ifndef RestApiOAuthH
#define RestApiOAuthH

#include "RestApi.h"

#include <QOAuth2AuthorizationCodeFlow>

class RestApiOAuth : public RestApi
{
   // do not use Q_OBJECT
   // this file will not be moc'ed automatically

public:
   RestApiOAuth(QObject* parent, const QString& baseUrl);

public:
   QJsonObject getTokenInfo(QByteArray token = QByteArray()) const;

protected:
   void setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret);
   void setCustomFlow(QOAuth2AuthorizationCodeFlow* oauthFlow);
   void setFinalRedirect(const QString& url);
   QOAuth2AuthorizationCodeFlow* getFlow() const;
   virtual void saveRefreshToken(const QString& refreshToken) const;
   virtual QString loadRefreshToken();
   virtual void setAuthorization(QNetworkRequest& request, const QByteArray& bearerToken) const override;
   virtual QByteArray authorizeUser() const;
   virtual QByteArray updateBearerToken() const override;
   void setTokenInfoUrl(const QString url);

private:
   void initFlow();

private:
   QOAuth2AuthorizationCodeFlow* oauthFlow;
   QMetaObject::Connection grantConnection;
   QString finalRedirectUrl;
   QString tokenInfoUrl;
};

#ifndef RestApiOAuthHPP
#include "RestApiOAuth.hpp"
#endif // NOT RestApiOAuthHPP

#endif // NOT RestApiOAuthH
