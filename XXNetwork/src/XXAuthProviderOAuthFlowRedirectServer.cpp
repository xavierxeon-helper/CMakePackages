#include "XXAuthProviderOAuthFlowRedirectServer.h"

#include <QTcpSocket>
#include <QUrlQuery>

XX::AuthProvider::OAuthFlow::RedirectServer::RedirectServer(uint port, QObject* parent)
   : QTcpServer(parent)
   , socket(nullptr)
   , code()
   , state()
{
   connect(this, &QTcpServer::newConnection, this, &RedirectServer::slotNewConnection);
   listen(QHostAddress::LocalHost, port);
}

const QByteArray XX::AuthProvider::OAuthFlow::RedirectServer::getCode() const
{
   return code;
}

const QByteArray XX::AuthProvider::OAuthFlow::RedirectServer::getState() const
{
   return state;
}

void XX::AuthProvider::OAuthFlow::RedirectServer::sendResponse(const QString& html)
{
   QByteArray body = html.toUtf8();

   QByteArray response = "HTTP/1.1 200 OK\r\n";
   response += "Content-Type: text/html; charset=utf-8\r\n";
   response += "Content-Length: ";
   response += QByteArray::number(body.size()) + "\r\n";
   response += "Connection: close\r\n";
   response += "\r\n";
   response += body;

   socket->write(response);
   socket->waitForBytesWritten();
   socket->close();
}

void XX::AuthProvider::OAuthFlow::RedirectServer::slotNewConnection()
{
   socket = nextPendingConnection();
   connect(socket, &QTcpSocket::readyRead, this, &RedirectServer::slotReadSocket);
}

void XX::AuthProvider::OAuthFlow::RedirectServer::slotReadSocket()
{
   QByteArray data = socket->readAll();

   QByteArray requestLine = data.split('\r').value(0);
   QByteArray target = requestLine.split(' ').value(1);

   QUrlQuery query(QUrl(QString::fromUtf8(target)).query());

   code = query.queryItemValue("code").toUtf8();
   state = query.queryItemValue("state").toUtf8();

   qDebug() << __FUNCTION__ << "code" << code << "state" << state;

   emit codeReceived();
}