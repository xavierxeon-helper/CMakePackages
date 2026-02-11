#include "XXSecureNetworkClient.h"

#include <QFile>
#include <QSslCertificate>
#include <QSslKey>

XX::SecureNetwork::Client::Client(QObject* parent, bool directAccess)
   : Socket(parent, nullptr, directAccess)
   , sslConfiguration()

{
}

void XX::SecureNetwork::Client::connectToHost(const QString& hostName, const quint16& port)
{
   if (sslConfiguration.isNull())
      return;

   sslSocket->setSslConfiguration(sslConfiguration);
   sslSocket->connectToHostEncrypted(hostName, port, QIODevice::ReadWrite);
}

void XX::SecureNetwork::Client::disconnectFromHost()
{
   if (sslSocket->isOpen())
      sslSocket->disconnectFromHost();
}

bool XX::SecureNetwork::Client::setEncryptionWithPasswordFile(const QString& p12FileName, const QString& passwordFileName)
{
   const QByteArray password = readPassword(passwordFileName);
   if (password.isEmpty())
   {
      qWarning() << "uanble to open password file";
      return false;
   }

   return setEncryption(p12FileName, password);
}

bool XX::SecureNetwork::Client::setEncryption(const QString& p12FileName, const QByteArray& password)
{
   sslConfiguration = QSslConfiguration::defaultConfiguration();

   QFile certFile(p12FileName);
   if (!certFile.open(QFile::ReadOnly))
      return false;

   // import
   QSslKey key;
   QSslCertificate certificate;
   QList<QSslCertificate> importedCaCertificates;

   bool imported = QSslCertificate::importPkcs12(&certFile, &key, &certificate, &importedCaCertificates, password);
   certFile.close();

   if (!imported)
      return false;

   // apply
   sslConfiguration.setPrivateKey(key);

   QList<QSslCertificate> localCertificates = sslConfiguration.localCertificateChain();
   localCertificates.append(certificate);
   sslConfiguration.setLocalCertificateChain(localCertificates);

   QList<QSslCertificate> caCertificates = sslConfiguration.caCertificates();
   caCertificates.append(importedCaCertificates);
   sslConfiguration.setCaCertificates(caCertificates);

   sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
   sslConfiguration.setProtocol(QSsl::SecureProtocols);

   return true;
}

void XX::SecureNetwork::Client::setConfiguration(const QSslConfiguration& newSslConfiguration)
{
   sslConfiguration = newSslConfiguration;
}

QByteArray XX::SecureNetwork::Client::readPassword(const QString& passwordFileName)
{
   QFile file(passwordFileName);
   if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
      qWarning() << "uanble to open password file";
      return QByteArray();
   }

   const QByteArray password = file.readLine().simplified();
   file.close();

   return password;
}

const QSslConfiguration& XX::SecureNetwork::Client::getConfiguration() const
{
   return sslConfiguration;
}
