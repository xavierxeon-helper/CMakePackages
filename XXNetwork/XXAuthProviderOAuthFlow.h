#ifndef XXAuthProviderOAuthFlowH
#define XXAuthProviderOAuthFlowH

#include "XXAuthProviderToken.h"
#include "XXNetworkExportDef.h"

namespace XX
{
   namespace AuthProvider
   {
      class XXNETWORK_DECLSPEC OAuthFlow : public Token
      {
         Q_OBJECT

      public:
         class RedirectServer;

      public:
         OAuthFlow(QObject* parent);

      public:
         void setStandardFlow(const QString& baseAuthUrl, const QString& clientId, const QString& clientSecret);
         void setFinalRedirect(const QString& url);
         void setFinalHTML(const QString& html);
         void setRequestedScopeTokens(QSet<QByteArray> scopeTokens);

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
            BlockState(OAuthFlow* auth);
            ~BlockState();

         private:
            OAuthFlow* auth;
            State previousState;
         };

      protected:
         virtual bool update() override;
         virtual bool authorizeUser();
         virtual void saveRefreshToken(const QString& refreshToken);
         virtual QString loadRefreshToken();
         void overrideAuthUrl(const QString& url);
         void overrideTokenUrl(const QString& url);

      private:
         QByteArray generateBytes(uint length);
         QString generateCodeChallenge();
         QByteArray getAuthCode();

      private:
         QString authUrl;
         QString tokenUrl;
         QString clientId;
         QString clientSecret;
         QSet<QByteArray> scopeTokens;

         QString refreshToken;
         QString finalHTML;

         QByteArray verifierBytes;
         State state;
      };
   } // namespace AuthProvider
} // namespace XX

#endif // NOT XXAuthProviderOAuthFlowH
