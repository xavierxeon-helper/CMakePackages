#ifndef XXSecureNetworkClientH
#define XXSecureNetworkClientH

#include "XXNetworkExportDef.h"
#include "XXSecureNetworkSocket.h"

#include <QSslConfiguration>

namespace SecureNetwork
{
   class XXNETWORK_DECLSPEC Client : public Socket
   {
      Q_OBJECT
   public:
      Client(QObject* parent, bool directAccess = false);

   public:
      void connectToHost(const QString& hostName, const quint16& port);
      void disconnectFromHost();
      bool setEncryptionWithPasswordFile(const QString& p12FileName, const QString& passwordFileName);
      bool setEncryption(const QString& p12FileName, const QByteArray& password);
      void setConfiguration(const QSslConfiguration& newSslConfiguration);
      static QByteArray readPassword(const QString& passwordFileName);
      const QSslConfiguration& getConfiguration() const;

   private:
      QSslConfiguration sslConfiguration;
   };
} // namespace SecureNetwork

#endif // NOT XXSecureNetworkClientH
