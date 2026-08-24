#ifndef XXAuthProviderOAuthFlowRedirectServerH
#define XXAuthProviderOAuthFlowRedirectServerH

#include "XXAuthProviderOAuthFlow.h"
#include <QTcpServer>

namespace XX
{
   namespace AuthProvider
   {
      class OAuthFlow::RedirectServer : public QTcpServer
      {
         Q_OBJECT

      public:
         RedirectServer(uint port, QObject* parent = nullptr);

      signals:
         void codeReceived();

      public:
         const QByteArray getCode() const;
         const QByteArray getState() const;
         void sendResponse(const QString& html);

      private slots:
         void slotNewConnection();
         void slotReadSocket();

      private:
         QTcpSocket* socket;

         QByteArray code;
         QByteArray state;
      };
   } // namespace AuthProvider
} // namespace XX

#endif // NOT XXAuthProviderOAuthFlowRedirectServerH
