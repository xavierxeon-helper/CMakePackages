#ifndef AuthProviderGeneralHPP
#define AuthProviderGeneralHPP

#include "AuthProviderGeneral.h"

inline AuthProvider::General::General(QObject* parent)
   : QObject(parent)
   , bearerToken()
{
}

inline const QByteArray& AuthProvider::General::getBearerToken() const
{
   return bearerToken;
}

inline bool AuthProvider::General::isNull() const
{
   return bearerToken.isEmpty();
}

inline void AuthProvider::General::setBearerToken(const QByteArray& token)
{
   bearerToken = token;
}

inline bool AuthProvider::General::update()
{
   return true;
}

inline void AuthProvider::General::setAuthorization(QNetworkRequest& request) const
{
   request.setRawHeader("Authorization", "Bearer " + bearerToken);
}

#endif // NOT AuthProviderGeneralHPP
