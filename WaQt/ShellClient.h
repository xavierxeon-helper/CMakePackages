#ifndef ShellClientH
#define ShellClientH

#include <QObject>

class ShellClient
{
public:
   static QByteArray executeLocal(const QString& command, QByteArray* error = nullptr);
   static QByteArray executeRemote(const QString& host, const QString& command, QByteArray* error = nullptr);

private:
   static QByteArray execute(const QString& program, const QStringList& args, QByteArray* error);
};

#ifndef ShellClientHPP
#include "ShellClient.hpp"
#endif // NOT ShellClientHPP

#endif // NOT ShellClientH
