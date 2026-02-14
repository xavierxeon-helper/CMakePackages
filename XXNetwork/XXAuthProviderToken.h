#ifndef XXAuthProviderTokenH
#define XXAuthProviderTokenH

#include "XXNetworkExportDef.h"
#include <QObject>

#include <QNetworkRequest>

namespace XX
{
   namespace AuthProvider
   {
      //! @brief Token-based authentication provider

      class XXNETWORK_DECLSPEC Token : public QObject
      {
         Q_OBJECT

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
} // namespace XX

#endif // NOT XXAuthProviderTokenH
