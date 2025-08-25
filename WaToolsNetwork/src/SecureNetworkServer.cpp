#include "SecureNetworkServer.h"

#include <QFile>
#include <QSslCertificate>
#include <QSslKey>
#include <QSslSocket>

#include "SecureNetworkServerInternal.h"
#include "SecureNetworkSocket.h"

SecureNetwork::Server::Server(QObject* parent)
   : QObject(parent)
   , internal(nullptr)
   , sslConfiguration()
   , socketList()
   , issuerName()
   , peerCommonNameList()
{
   internal = new ServerInternal(this);
}

SecureNetwork::Server::~Server()
{
   for (Socket::Pointer& socketPointer : socketList)
   {
      if (socketPointer.isNull())
         continue;

      delete socketPointer;
   }
   socketList.clear();
}

void SecureNetwork::Server::listen(const quint16& port)
{
   if (sslConfiguration.isNull())
      return;

   internal->listen(QHostAddress::Any, port);
}

bool SecureNetwork::Server::setEncryption(const QString& caCertFileName, const QString& serverCertFileName, const QString& serverKeyFileName)
{
   sslConfiguration = QSslConfiguration::defaultConfiguration();

   {
      QFile caCertFile(caCertFileName);
      if (!caCertFile.open(QIODevice::ReadOnly))
         return false;

      QSslCertificate caCerttificate(caCertFile.readAll());
      caCertFile.close();

      QList<QSslCertificate> caCertificates = sslConfiguration.caCertificates();
      caCertificates.append(caCerttificate);
      sslConfiguration.setCaCertificates(caCertificates);
   }

   {
      QFile certFile(serverCertFileName);
      if (!certFile.open(QIODevice::ReadOnly))
         return false;

      QSslCertificate serverCerttificate(certFile.readAll());
      certFile.close();

      issuerName = serverCerttificate.subjectInfo(QSslCertificate::CommonName).at(0);

      QList<QSslCertificate> localCertificates = sslConfiguration.localCertificateChain();
      localCertificates.append(serverCerttificate);
      sslConfiguration.setLocalCertificateChain(localCertificates);
   }

   {
      QFile keyFile(serverKeyFileName);
      if (!keyFile.open(QIODevice::ReadOnly))
         return false;

      QSslKey serverKey(keyFile.readAll(), QSsl::Rsa);
      keyFile.close();

      sslConfiguration.setPrivateKey(serverKey);
   }

   sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyPeer);
   sslConfiguration.setProtocol(QSsl::SecureProtocols);

   return true;
}

void SecureNetwork::Server::setConfiguration(const QSslConfiguration& newSslConfiguration)
{
   sslConfiguration = newSslConfiguration;
}

bool SecureNetwork::Server::setPeerCommmonNameList(const QString& authUserFileName)
{
   QFile userAuthFile(authUserFileName);
   if (!userAuthFile.open(QIODevice::ReadOnly))
      return false;

   while (!userAuthFile.atEnd())
   {
      QString line = QString::fromUtf8(userAuthFile.readLine()).simplified();
      if (!line.startsWith("/CN="))
         continue;
      line = line.mid(4);

      const int index = line.indexOf(":");
      line = line.mid(0, index);

      peerCommonNameList.append(line);
   }

   userAuthFile.close();
   return true;
}

const QList<SecureNetwork::Socket::Pointer>& SecureNetwork::Server::getSocketList() const
{
   return socketList;
}

void SecureNetwork::Server::newConnection(Socket* socket)
{
   QSslSocket* sslSocket = socket->sslSocket; // server internal has made sure this socket is encrypted

   const QSslCertificate peerCertificate = sslSocket->peerCertificate();
   const QString commonName = peerCertificate.subjectInfo(QSslCertificate::CommonName).at(0);
   if (!peerCommonNameList.isEmpty() && !peerCommonNameList.contains(commonName))
   {
      sslSocket->close();
      sslSocket->deleteLater();
      return;
   }

   socketList.append(socket);
   emit signalNewEncryptedConnection(socket);
}

void SecureNetwork::Server::removeSocket(Socket* socket)
{
   socketList.removeAll(socket);

   QSslSocket* sslSocket = socket->sslSocket;
   sslSocket->close();
   sslSocket->deleteLater();
}

const QSslConfiguration& SecureNetwork::Server::getConfiguration() const
{
   return sslConfiguration;
}
