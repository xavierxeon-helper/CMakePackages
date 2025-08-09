#ifndef AuthProviderTokenH
#define AuthProviderTokenH

#include <QObject>

#include <QNetworkRequest>

namespace AuthProvider
{
   class Token : public QObject
   {
      // do not use Q_OBJECT
      // this file will not be moc'ed automatically

   public:
      Token(QObject* parent);

   public:
      const QByteArray& getBearerToken() const;
      bool isNull() const;

      void setBearerToken(const QByteArray& token);
      virtual bool update();
      virtual void setAuthorization(QNetworkRequest& request) const;

   protected:
      QByteArray bearerToken;
   };
} // namespace AuthProvider

#ifndef AuthProviderTokenHPP
#include "AuthProviderToken.hpp"
#endif // NOT AuthProviderTokenHPP

#endif // NOT AuthProviderTokenH
