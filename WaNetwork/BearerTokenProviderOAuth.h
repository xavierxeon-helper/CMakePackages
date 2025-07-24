#ifndef BearerTokenProviderOAuthH
#define BearerTokenProviderOAuthH

#include "RestApi.h"

#include <QOAuth2AuthorizationCodeFlow>

class BearerTokenProviderOAuth : public BearerTokenProvider
{
   // do not use Q_OBJECT
   // this file will not be moc'ed automatically

public:
   using SaveRefreshTokenFunction = std::function<void(const QString& refreshToken)>;
   using LoadRefreshTokenFunction = std::function<QString()>;

public:
   BearerTokenProviderOAuth(QObject* parent);

public:
   template <typename ClassType>
   void setSaveRefreshTokenFunction(ClassType* instance, void (ClassType::*function)(const QString& refreshToken));

   template <typename ClassType>
   void setLoadRefreshTokenFunction(ClassType* instance, QString (ClassType::*function)());

   void setTokenInfoUrl(const QString url);
   QJsonObject getTokenInfo(QByteArray token = QByteArray()) const;

   void setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret);
   void setCustomFlow(QOAuth2AuthorizationCodeFlow* oauthFlow);
   void setFinalRedirect(const QString& url);
   QOAuth2AuthorizationCodeFlow* getFlow() const;

protected:
   virtual bool authorizeUser();
   virtual bool update() override;

private:
   void initFlow();

private:
   QOAuth2AuthorizationCodeFlow* oauthFlow;
   QMetaObject::Connection grantConnection;
   QString finalHTML;
   QString tokenInfoUrl;
   SaveRefreshTokenFunction saveRefreshTokenFunction;
   LoadRefreshTokenFunction loadRefreshTokenFunction;
};

#ifndef BearerTokenProviderOAuthHPP
#include "BearerTokenProviderOAuth.hpp"
#endif // NOT BearerTokenProviderOAuthHPP

#endif // NOT BearerTokenProviderOAuthH
