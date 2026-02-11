#ifndef XXSecureNetworkSocketH
#define XXSecureNetworkSocketH

#include "XXNetworkExportDef.h"
#include <QObject>

#include <QPointer>

#include <QSslError>
#include <QSslSocket>

namespace XX
{
   namespace SecureNetwork
   {
      class XXNETWORK_DECLSPEC Socket : public QObject
      {
         Q_OBJECT
      public:
         using Pointer = QPointer<Socket>;

      signals:
         void signalDataReceived(Socket* me, const QByteArray& data);
         void signalConnected(Socket* me);
         void signalDisconnected(Socket* me);
         void signalEncrypted(Socket* me);

      public:
         void sendData(const QByteArray& data);
         QSslCertificate getPeerCertificate() const;
         operator QSslSocket*() const;

      public:
         static bool verbose;

      protected:
         Socket(QObject* parent, QSslSocket* externalSocket = nullptr, bool directAccess = false);
         virtual ~Socket();

      protected:
         QPointer<QSslSocket> sslSocket;
         bool directAccess;

      private:
         friend class Server;
         friend class ServerInternal;

      private slots:
         // socket
         void slotReadyRead();
         void slotConnected();
         void slotDisconnected();
         void slotEncypted();
         void slotErrorOccurred(QAbstractSocket::SocketError socketError);
         void slotStateChanged(QAbstractSocket::SocketState socketState);
         void slotSslErrors(const QList<QSslError>&);
         // ssl
         void slotPeerVerifyError(const QSslError& error);
      };
   } // namespace SecureNetwork
} // namespace XX

#endif // NOT XXSecureNetworkSocketH
