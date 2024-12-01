#ifndef LocalServerHPP
#define LocalServerHPP

#include "LocalServer.h"

#include <QDir>
#include <QFile>
#include <QLocalSocket>
#include <QProcess>
#include <QStandardPaths>
#include <QThread>

template <CompileTimeString Tag>
QString LocalServer<Tag>::tagName()
{
   static const QString tagName = QString::fromStdString(Tag.text());
   return tagName;
}

template <CompileTimeString Tag>
QString LocalServer<Tag>::compileSharedFileName()
{
   const QString socketPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

   const QString socketName = socketPath + "/." +  LocalServer<Tag>::tagName().toLower() + ".shared";
   return socketName;

}

template <CompileTimeString Tag>
QString LocalServer<Tag>::compileSocketName()
{
   const QString socketPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

   const QString socketName = socketPath + "/." +  LocalServer<Tag>::tagName().toLower() + ".socket";
   return socketName;
}

template <CompileTimeString Tag>
bool LocalServer<Tag>::isServerActive()
{
   const QString socketName = LocalServer<Tag>::compileSocketName();
   if (!QFile::exists(socketName))
      return false;

   QLocalSocket socket;
   socket.connectToServer(socketName);
   if (socket.waitForConnected())
   {
      socket.disconnectFromServer();
      return true;
   }

   if (!QFile::remove(socketName))
      return true;

   return false;
}

template <CompileTimeString Tag>
void LocalServer<Tag>::startApplication()
{
   QProcess::startDetached("open", {"-a", LocalServer<Tag>::tagName()});
   QThread::sleep(1);
}

#endif // NOT LocalServerHPP
