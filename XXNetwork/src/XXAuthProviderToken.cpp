#include "XXAuthProviderToken.h"

XX::AuthProvider::Token::Token(QObject* parent)
   : QObject(parent)
   , bearerToken()
{
}

const QByteArray& XX::AuthProvider::Token::getBearerToken() const
{
   return bearerToken;
}

bool XX::AuthProvider::Token::isNull() const
{
   return bearerToken.isEmpty();
}

void XX::AuthProvider::Token::setBearerToken(const QByteArray& token)
{
   bearerToken = token;
}

bool XX::AuthProvider::Token::update()
{
   return true;
}

void XX::AuthProvider::Token::setAuthorization(QNetworkRequest& request) const
{
   request.setRawHeader("Authorization", "Bearer " + bearerToken);
}
