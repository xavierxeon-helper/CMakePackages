#ifndef XXSharedHPP
#define XXSharedHPP

#include "XXShared.h"

#include <QDir>
#include <QFile>
#include <QLocalSocket>
#include <QProcess>
#include <QThread>

template <XX::CompileTimeString AppName>
QString XX::Shared<AppName>::appName()
{
   static const QString name = QString::fromStdString(AppName.text());
   return name;
}

template <XX::CompileTimeString AppName>
QString XX::Shared<AppName>::compileSharedFileName(const QString& suffix, const QStandardPaths::StandardLocation& location)
{
   const QString path = QStandardPaths::writableLocation(location);

   const QString fileName = path + "/." + Shared<AppName>::appName().toLower() + "." + suffix;
   return fileName;
}

template <XX::CompileTimeString AppName>
QString XX::Shared<AppName>::socketName()
{
#if defined(Q_OS_WIN)
   const QString socketPath = "\\\\.\\pipe\\";
#else
   const QString socketPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
#endif
   const QString name = socketPath + "/." + Shared<AppName>::appName().toLower() + ".socket";
   return name;
}

template <XX::CompileTimeString AppName>
bool XX::Shared<AppName>::isServerActive()
{
   const QString socketName = Shared<AppName>::socketName();
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

template <XX::CompileTimeString AppName>
void XX::Shared<AppName>::startApplication()
{
#if defined(__APPLE__)
   QProcess::startDetached("open", {"-a", Shared<AppName>::appName()});
#elif defined(Q_OS_WIN)

   const QString pwd = qgetenv("LOCALAPPDATA") + "/" + Shared<AppName>::appName();
   const QString application = pwd + "/" + Shared<AppName>::appName() + ".exe";

   QProcess::startDetached(application, {}, pwd);
#else
   // ???
#endif

   QThread::sleep(1);
}

#endif // NOT XXSharedHPP
