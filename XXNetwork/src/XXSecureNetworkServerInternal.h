#ifndef XXSecureNetworkServerInternalH
#define XXSecureNetworkServerInternalH

#include <QTcpServer>

#include <QSslConfiguration>

namespace XX
{
   namespace SecureNetwork
   {
      class Socket;
      class Server;

      class ServerInternal : public QTcpServer
      {
         Q_OBJECT
      public:
         ServerInternal(Server* server);

      private slots:
         void slotEncryptedConnection();

      private:
         void incomingConnection(qintptr socketDescriptor) override;

      private:
         Server* server;
      };
   } // namespace SecureNetwork
} // namespace XX

#endif // NOT XXSecureNetworkServerInternalH
