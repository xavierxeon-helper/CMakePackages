#ifndef SharedHPP
#define SharedHPP

#include "Shared.h"

#include <QDir>
#include <QFile>
#include <QLocalSocket>
#include <QProcess>
#include <QStandardPaths>
#include <QThread>

template <CompileTimeString AppName>
QString Shared<AppName>::appName()
{
   static const QString name = QString::fromStdString(AppName.text());
   return name;
}

template <CompileTimeString AppName>
QString Shared<AppName>::compileSharedFileName()
{
   const QString socketPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

   const QString socketName = socketPath + "/." + Shared<AppName>::appName().toLower() + ".shared";
   return socketName;
}

template <CompileTimeString AppName>
QString Shared<AppName>::compileSocketName()
{
   const QString socketPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

   const QString socketName = socketPath + "/." + Shared<AppName>::appName().toLower() + ".socket";
   return socketName;
}

template <CompileTimeString AppName>
bool Shared<AppName>::isServerActive()
{
   const QString socketName = Shared<AppName>::compileSocketName();
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

template <CompileTimeString AppName>
void Shared<AppName>::startApplication()
{
   QProcess::startDetached("open", {"-a", Shared<AppName>::appName()});
   QThread::sleep(1);
}

#endif // NOT SharedHPP
