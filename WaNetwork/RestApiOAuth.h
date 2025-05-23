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

protected:
   void setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret);
   void setCustomFlow(QOAuth2AuthorizationCodeFlow* oauthFlow);
   QOAuth2AuthorizationCodeFlow*  getFlow() const;
   virtual void saveRefreshToken(const QString& refreshToken) const;
   virtual QString loadRefreshToken();
   virtual void setAuthorization(QNetworkRequest& request, const QByteArray& bearerToken) override;


private:
   QByteArray updateBearerToken() override;
   QByteArray authorizeUser();
   void initFlow();

private:
   QOAuth2AuthorizationCodeFlow* oauthFlow;
   QMetaObject::Connection grantConnection;
};

#ifndef RestApiOAuthHPP
#include "RestApiOAuth.hpp"
#endif // NOT RestApiOAuthHPP

#endif // NOT RestApiOAuthH
