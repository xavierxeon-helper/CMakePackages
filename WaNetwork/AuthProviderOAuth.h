#ifndef AuthProviderOAuthH
#define AuthProviderOAuthH

#include "AuthProviderToken.h"
#include "NetworkSettings.h"

#include <QJsonObject>
#include <QOAuth2AuthorizationCodeFlow>

namespace AuthProvider
{
   class OAuth : public Token, public Network::Settings
   {
      // do not use Q_OBJECT
      // this file will not be moc'ed automatically

   public:
      OAuth(QObject* parent);

   public:
      void setTokenInfoUrl(const QString url);
      QJsonObject getTokenInfo(QByteArray token = QByteArray()) const;

      void setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret);
      void setCustomFlow(QOAuth2AuthorizationCodeFlow* oauthFlow);
      void setFinalRedirect(const QString& url);
      void setFinalHTML(const QString& html);
      QOAuth2AuthorizationCodeFlow* getFlow() const;

   protected:
      virtual bool update() override;
      virtual bool authorizeUser();

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
} // namespace AuthProvider

#ifndef AuthProviderOAuthHPP
#include "AuthProviderOAuth.hpp"
#endif // NOT AuthProviderOAuthHPP

#endif // NOT AuthProviderOAuthH
