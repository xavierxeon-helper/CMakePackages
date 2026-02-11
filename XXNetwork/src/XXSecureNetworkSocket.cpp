#include "XXSecureNetworkSocket.h"

bool SecureNetwork::Socket::verbose = false;

SecureNetwork::Socket::Socket(QObject* parent, QSslSocket* externalSocket, bool directAccess_)
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

SecureNetwork::Socket::~Socket()
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

void SecureNetwork::Socket::sendData(const QByteArray& data)
{
   if (sslSocket.isNull())
      return;

   sslSocket->write(data);
}

QSslCertificate SecureNetwork::Socket::getPeerCertificate() const
{
   return sslSocket->peerCertificate();
}

SecureNetwork::Socket::operator QSslSocket*() const
{
   return sslSocket.data();
}

void SecureNetwork::Socket::slotReadyRead()
{
   if (sslSocket.isNull())
      return;

   emit signalDataReceived(this, sslSocket->readAll());
}

void SecureNetwork::Socket::slotConnected()
{
   if (sslSocket.isNull())
      return;

   if (verbose)
      qDebug() << __FUNCTION__ << this;

   emit signalConnected(this);
}

void SecureNetwork::Socket::slotDisconnected()
{
   if (sslSocket.isNull())
      return;

   if (verbose)
      qDebug() << __FUNCTION__ << this;

   emit signalDisconnected(this);
}

void SecureNetwork::Socket::slotEncypted()
{
   if (sslSocket.isNull())
      return;

   if (verbose)
      qDebug() << __FUNCTION__ << this;

   emit signalEncrypted(this);
}

void SecureNetwork::Socket::slotErrorOccurred(QAbstractSocket::SocketError socketError)
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

void SecureNetwork::Socket::slotStateChanged(QAbstractSocket::SocketState socketState)
{
   if (verbose)
      qDebug() << __FUNCTION__ << this << socketState;
}

void SecureNetwork::Socket::slotSslErrors(const QList<QSslError>& errors)
{
   qWarning() << __FUNCTION__ << this << errors;
}

void SecureNetwork::Socket::slotPeerVerifyError(const QSslError& error)
{
   qWarning() << __FUNCTION__ << this << error;
}
