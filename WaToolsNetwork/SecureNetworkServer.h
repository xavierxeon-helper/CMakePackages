#ifndef SecureNetworkServerH
#define SecureNetworkServerH

#include "WaToolsNetworkExportDef.h"
#include <QObject>

#include <QSslConfiguration>

#include "SecureNetworkSocket.h"

namespace SecureNetwork
{
   class Socket;
   class ServerInternal;

   class WATOOLSNETWORK_DECLSPEC Server : public QObject
   {
      Q_OBJECT
   public:
      Server(QObject* parent);
      ~Server();

   signals:
      void signalNewEncryptedConnection(Socket* socket);

   public:
      void listen(const quint16& port);
      bool setEncryption(const QString& caCertFileName, const QString& serverCertFileName, const QString& serverKeyFileName);
      void setConfiguration(const QSslConfiguration& newSslConfiguration);
      bool setPeerCommmonNameList(const QString& authUserFileName);
      const QList<Socket::Pointer>& getSocketList() const;
      void removeSocket(Socket* socket);
      const QSslConfiguration& getConfiguration() const;

   private:
      friend class ServerInternal;

   private:
      void newConnection(Socket* socket);

   private:
      ServerInternal* internal;
      QSslConfiguration sslConfiguration;
      QList<Socket::Pointer> socketList;
      QString issuerName;
      QStringList peerCommonNameList;
   };

} // namespace SecureNetwork

#endif // NOT SecureNetworkServerH
