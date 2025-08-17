#include "AuthProviderToken.h"

AuthProvider::Token::Token(QObject* parent)
   : QObject(parent)
   , bearerToken()
{
}

const QByteArray& AuthProvider::Token::getBearerToken() const
{
   return bearerToken;
}

bool AuthProvider::Token::isNull() const
{
   return bearerToken.isEmpty();
}

void AuthProvider::Token::setBearerToken(const QByteArray& token)
{
   bearerToken = token;
}

bool AuthProvider::Token::update()
{
   return true;
}

void AuthProvider::Token::setAuthorization(QNetworkRequest& request) const
{
   request.setRawHeader("Authorization", "Bearer " + bearerToken);
}
