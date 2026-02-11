#ifndef ShellClientH
#define ShellClientH

#include "XXCoreExportDef.h"

#include <QObject>

class XXCORE_DECLSPEC ShellClient
{
public:
   static QByteArray executeLocal(const QString& command, QByteArray* error = nullptr);
   static QByteArray executeRemote(const QString& host, const QString& command, QByteArray* error = nullptr);

private:
   static QByteArray execute(const QString& program, const QStringList& args, QByteArray* error);
};

#endif // NOT ShellClientH
