#ifndef BearerTokenProviderOAuthH
#define BearerTokenProviderOAuthH

#include "BearerTokenProvider.h"

#include <QJsonObject>
#include <QOAuth2AuthorizationCodeFlow>

class BearerTokenProviderOAuth : public BearerTokenProvider
{
   // do not use Q_OBJECT
   // this file will not be moc'ed automatically

public:
   BearerTokenProviderOAuth(QObject* parent);

public:
   void setTokenInfoUrl(const QString url);
   QJsonObject getTokenInfo(QByteArray token = QByteArray()) const;

   void setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret);
   void setCustomFlow(QOAuth2AuthorizationCodeFlow* oauthFlow);
   void setFinalRedirect(const QString& url);
   QOAuth2AuthorizationCodeFlow* getFlow() const;

protected:
   virtual bool authorizeUser();
   virtual bool update() override;

   virtual void saveRefreshToken(const QString& refreshToken);
   virtual QString loadRefreshToken();

private:
   void initFlow();

private:
   QOAuth2AuthorizationCodeFlow* oauthFlow;
   QMetaObject::Connection grantConnection;
   QString finalHTML;
   QString tokenInfoUrl;
};

#ifndef BearerTokenProviderOAuthHPP
#include "BearerTokenProviderOAuth.hpp"
#endif // NOT BearerTokenProviderOAuthHPP

#endif // NOT BearerTokenProviderOAuthH
