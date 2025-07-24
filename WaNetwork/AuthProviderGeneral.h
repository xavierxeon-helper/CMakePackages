#ifndef AuthProviderGeneralH
#define AuthProviderGeneralH

#include <QObject>

#include <QNetworkRequest>

namespace AuthProvider
{
   class General : public QObject
   {
      // do not use Q_OBJECT
      // this file will not be moc'ed automatically

   public:
      General(QObject* parent);

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

#ifndef AuthProviderGeneralHPP
#include "AuthProviderGeneral.hpp"
#endif // NOT AuthProviderGeneralHPP

#endif // NOT AuthProviderGeneralH
