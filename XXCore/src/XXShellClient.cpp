#include "XXShellClient.h"

#include <QProcess>

QByteArray ShellClient::executeLocal(const QString& command, QByteArray* error)
{
   return execute("bash", {"-c", command}, error);
}

QByteArray ShellClient::executeRemote(const QString& host, const QString& command, QByteArray* error)
{
   return execute("ssh", {"-T", host, command}, error);
}

QByteArray ShellClient::execute(const QString& program, const QStringList& args, QByteArray* error)
{
#ifdef Q_OS_IOS
   return QByteArray();
#else
   QProcess process;
   process.start(program, args);
   process.waitForFinished();

   if (error)
      *error = process.readAllStandardError();

   const QByteArray output = process.readAllStandardOutput();
   return output;
#endif
}
