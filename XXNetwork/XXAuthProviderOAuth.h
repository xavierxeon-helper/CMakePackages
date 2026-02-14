#ifndef XXAuthProviderOAuthH
#define XXAuthProviderOAuthH

#include "XXAuthProviderToken.h"
#include "XXNetworkExportDef.h"
#include "XXNetworkSettings.h"

#include <QJsonObject>
#include <QOAuth2AuthorizationCodeFlow>

namespace XX
{
   namespace AuthProvider
   {
      //! @brief OAuth2 authentication provider
      //! @details redirect url is http://127.0.0.1:1234/

      class XXNETWORK_DECLSPEC OAuth : public Token, public Network::Settings
      {
         Q_OBJECT

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
         enum class State
         {
            Initial,
            AuthUser,
            Update,
            Blocked,
            Ready
         };

         class XXNETWORK_DECLSPEC BlockState
         {
         public:
            BlockState(OAuth* auth);
            ~BlockState();

         private:
            OAuth* auth;
            State previousState;
         };

      protected:
         virtual bool
         update() override;
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
         State state;
      };
   } // namespace AuthProvider
} // namespace XX

#endif // NOT XXAuthProviderOAuthH
