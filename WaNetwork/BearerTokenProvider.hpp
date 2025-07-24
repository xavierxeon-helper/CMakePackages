#ifndef BearerTokenProviderHPP
#define BearerTokenProviderHPP

#include "BearerTokenProvider.h"

inline BearerTokenProvider::BearerTokenProvider(QObject* parent)
   : QObject(parent)
   , bearerToken()
{
}

inline const QByteArray& BearerTokenProvider::getBearerToken() const
{
   return bearerToken;
}

inline bool BearerTokenProvider::isEmpty() const
{
   return bearerToken.isEmpty();
}

inline void BearerTokenProvider::setBearerToken(const QByteArray& token)
{
   bearerToken = token;
}

inline bool BearerTokenProvider::update()
{
   return true;
}

inline void BearerTokenProvider::setAuthorization(QNetworkRequest& request) const
{
   request.setRawHeader("Authorization", "Bearer " + bearerToken);
}

#endif // NOT BearerTokenProviderHPP
