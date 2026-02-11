#include "XXSecureNetworkSocket.h"

bool XX::SecureNetwork::Socket::verbose = false;

XX::SecureNetwork::Socket::Socket(QObject* parent, QSslSocket* externalSocket, bool directAccess_)
   : QObject(parent)
   , sslSocket(externalSocket)
   , directAccess(directAccess_)
{
   if (!sslSocket)
   {
      sslSocket = new QSslSocket(parent);
      // qDebug() << __FUNCTION__ << "Client" << this;
   }
   else
   {
      sslSocket->setParent(this);
      // qDebug() << __FUNCTION__ << "Server" << this;
   }

   if (!directAccess)
      connect(sslSocket, &QAbstractSocket::readyRead, this, &Socket::slotReadyRead);

   connect(sslSocket, &QAbstractSocket::connected, this, &Socket::slotConnected);
   connect(sslSocket, &QAbstractSocket::disconnected, this, &Socket::slotDisconnected);
   connect(sslSocket, &QAbstractSocket::stateChanged, this, &Socket::slotStateChanged);
   connect(sslSocket, &QAbstractSocket::errorOccurred, this, &Socket::slotErrorOccurred);

   connect(sslSocket, &QSslSocket::peerVerifyError, this, &Socket::slotPeerVerifyError);
   connect(sslSocket, &QSslSocket::sslErrors, this, &Socket::slotSslErrors);
   connect(sslSocket, &QSslSocket::encrypted, this, &Socket::slotEncypted);
}

XX::SecureNetwork::Socket::~Socket()
{
   if (sslSocket.isNull())
      return;

   if (!directAccess)
      disconnect(sslSocket, &QAbstractSocket::readyRead, this, &Socket::slotReadyRead);

   disconnect(sslSocket, &QAbstractSocket::connected, this, &Socket::slotConnected);
   disconnect(sslSocket, &QAbstractSocket::disconnected, this, &Socket::slotDisconnected);
   disconnect(sslSocket, &QAbstractSocket::stateChanged, this, &Socket::slotStateChanged);
   disconnect(sslSocket, &QAbstractSocket::errorOccurred, this, &Socket::slotErrorOccurred);

   disconnect(sslSocket, &QSslSocket::peerVerifyError, this, &Socket::slotPeerVerifyError);
   disconnect(sslSocket, &QSslSocket::sslErrors, this, &Socket::slotSslErrors);
   connect(sslSocket, &QSslSocket::encrypted, this, &Socket::slotEncypted);

   // qDebug() << __FUNCTION__ << this;
}

void XX::SecureNetwork::Socket::sendData(const QByteArray& data)
{
   if (sslSocket.isNull())
      return;

   sslSocket->write(data);
}

QSslCertificate XX::SecureNetwork::Socket::getPeerCertificate() const
{
   return sslSocket->peerCertificate();
}

XX::SecureNetwork::Socket::operator QSslSocket*() const
{
   return sslSocket.data();
}

void XX::SecureNetwork::Socket::slotReadyRead()
{
   if (sslSocket.isNull())
      return;

   emit signalDataReceived(this, sslSocket->readAll());
}

void XX::SecureNetwork::Socket::slotConnected()
{
   if (sslSocket.isNull())
      return;

   if (verbose)
      qDebug() << __FUNCTION__ << this;

   emit signalConnected(this);
}

void XX::SecureNetwork::Socket::slotDisconnected()
{
   if (sslSocket.isNull())
      return;

   if (verbose)
      qDebug() << __FUNCTION__ << this;

   emit signalDisconnected(this);
}

void XX::SecureNetwork::Socket::slotEncypted()
{
   if (sslSocket.isNull())
      return;

   if (verbose)
      qDebug() << __FUNCTION__ << this;

   emit signalEncrypted(this);
}

void XX::SecureNetwork::Socket::slotErrorOccurred(QAbstractSocket::SocketError socketError)
{
   switch (socketError)
   {
      case QAbstractSocket::RemoteHostClosedError:
      case QAbstractSocket::SslInternalError:
         return;
      default:
         break;
   }

   qDebug() << __FUNCTION__ << this << socketError;
}

void XX::SecureNetwork::Socket::slotStateChanged(QAbstractSocket::SocketState socketState)
{
   if (verbose)
      qDebug() << __FUNCTION__ << this << socketState;
}

void XX::SecureNetwork::Socket::slotSslErrors(const QList<QSslError>& errors)
{
   qWarning() << __FUNCTION__ << this << errors;
}

void XX::SecureNetwork::Socket::slotPeerVerifyError(const QSslError& error)
{
   qWarning() << __FUNCTION__ << this << error;
}
