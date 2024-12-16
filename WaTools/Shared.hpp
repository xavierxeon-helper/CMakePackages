#ifndef SharedHPP
#define SharedHPP

#include "Shared.h"

#include <QDir>
#include <QFile>
#include <QLocalSocket>
#include <QProcess>
#include <QThread>

template <CompileTimeString AppName>
QString Shared<AppName>::appName()
{
   static const QString name = QString::fromStdString(AppName.text());
   return name;
}

template <CompileTimeString AppName>
QString Shared<AppName>::compileSharedFileName(const QString& suffix, const QStandardPaths::StandardLocation& location)
{
   const QString socketPath = QStandardPaths::writableLocation(location);

   const QString socketName = socketPath + "/." + Shared<AppName>::appName().toLower() + "." + suffix;
   return socketName;
}

template <CompileTimeString AppName>
QString Shared<AppName>::socketName()
{
#if defined(Q_OS_WIN)
   const QString socketPath = "\\\\.\\pipe\\";
#else
   const QString socketPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
#endif
   const QString name = socketPath + "/." + Shared<AppName>::appName().toLower() + ".socket";
   return name;
}

template <CompileTimeString AppName>
bool Shared<AppName>::isServerActive()
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

template <CompileTimeString AppName>
void Shared<AppName>::startApplication()
{
#if defined(__APPLE__)
   QProcess::startDetached("open", {"-a", Shared<AppName>::appName()});
#elif defined(Q_OS_WIN)
   const QString tmpPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
   const QString fileName = tmpPath + "/dummy." + Shared<AppName>::appName().toLower();
   if (!QFile::exists(fileName))
   {
      QFile file(fileName);
      if (!file.open(QIODevice::WriteOnly))
         return;
      file.write("hello");
      file.close();
   }
   QProcess::startDetached("start", {fileName});
#else
   // ???
#endif

   QThread::sleep(1);
}

#endif // NOT SharedHPP
