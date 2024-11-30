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
QString LocalServer<Tag>::compileSocketName()
{
   const QString socketPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

   static const QString tagName = QString::fromStdString(Tag.text());
   const QString socketName = socketPath + "/." +  tagName.toLower() + ".socket";
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
   static const QString tagName = QString::fromStdString(Tag.text());
   QProcess::startDetached("open", {"-a", tagName});
   QThread::sleep(1);
}

#endif // NOT LocalServerHPP
