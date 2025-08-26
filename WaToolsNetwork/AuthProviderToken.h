#ifndef AuthProviderTokenH
#define AuthProviderTokenH

#include "WaToolsNetworkExportDef.h"
#include <QObject>

#include <QNetworkRequest>

namespace AuthProvider
{
   /// @brief Token-based authentication provider

   class WATOOLSNETWORK_DECLSPEC Token : public QObject
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

#endif // NOT AuthProviderTokenH
