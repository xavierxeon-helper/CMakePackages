#include "XXShellClient.h"

#include <QProcess>

QByteArray XX::ShellClient::executeLocal(const QString& command, QByteArray* error)
{
   return execute("bash", {"-c", command}, error);
}

QByteArray XX::ShellClient::executeRemote(const QString& host, const QString& command, QByteArray* error)
{
   return execute("ssh", {"-T", host, command}, error);
}

QByteArray XX::ShellClient::execute(const QString& program, const QStringList& args, QByteArray* error)
{
#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID) || defined(Q_OS_WASM)
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
