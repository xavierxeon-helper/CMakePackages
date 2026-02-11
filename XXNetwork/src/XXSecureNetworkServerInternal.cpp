#include "XXSecureNetworkServerInternal.h"

#include "../XXSecureNetworkServer.h"
#include "../XXSecureNetworkSocket.h"

SecureNetwork::ServerInternal::ServerInternal(Server* server)
   : QTcpServer(server)
   , server(server)
{
}

void SecureNetwork::ServerInternal::slotEncryptedConnection()
{
   QSslSocket* sslSocket = qobject_cast<QSslSocket*>(sender());
   if (!sslSocket)
      return;

   disconnect(sslSocket, &QSslSocket::encrypted, this, &ServerInternal::slotEncryptedConnection);

   Socket* socket = new Socket(this, sslSocket);
   server->newConnection(socket);
}

void SecureNetwork::ServerInternal::incomingConnection(qintptr socketDescriptor)
{
   QSslSocket* sslSocket = new QSslSocket(this);
   connect(sslSocket, &QSslSocket::encrypted, this, &ServerInternal::slotEncryptedConnection);

   sslSocket->setSocketDescriptor(socketDescriptor);
   sslSocket->setSslConfiguration(server->sslConfiguration);
   sslSocket->startServerEncryption();

   addPendingConnection(sslSocket);
}
