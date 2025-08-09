#ifndef AuthProviderTokenHPP
#define AuthProviderTokenHPP

#include "AuthProviderToken.h"

inline AuthProvider::Token::Token(QObject* parent)
   : QObject(parent)
   , bearerToken()
{
}

inline const QByteArray& AuthProvider::Token::getBearerToken() const
{
   return bearerToken;
}

inline bool AuthProvider::Token::isNull() const
{
   return bearerToken.isEmpty();
}

inline void AuthProvider::Token::setBearerToken(const QByteArray& token)
{
   bearerToken = token;
}

inline bool AuthProvider::Token::update()
{
   return true;
}

inline void AuthProvider::Token::setAuthorization(QNetworkRequest& request) const
{
   request.setRawHeader("Authorization", "Bearer " + bearerToken);
}

#endif // NOT AuthProviderTokenHPP
