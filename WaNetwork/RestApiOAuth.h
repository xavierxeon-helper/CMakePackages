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
   void setFlow(QOAuth2AuthorizationCodeFlow* oauthFlow);
   virtual void saveRefreshToken(const QString& refreshToken) const;
   virtual QString loadRefreshToken();

private:
   QByteArray updateBearerToken() override;
   QByteArray authorizeUser();

private:
   QOAuth2AuthorizationCodeFlow* oauthFlow;
   QMetaObject::Connection grantConnection;
};

#ifndef RestApiOAuthHPP
#include "RestApiOAuth.hpp"
#endif // NOT RestApiOAuthHPP

#endif // NOT RestApiOAuthH
