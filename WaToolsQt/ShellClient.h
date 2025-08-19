#ifndef ShellClientH
#define ShellClientH

#include "WaToolsQtExportDef.h"

#include <QObject>

class WATOOLS_QT_DECLSPEC ShellClient
{
public:
   static QByteArray executeLocal(const QString& command, QByteArray* error = nullptr);
   static QByteArray executeRemote(const QString& host, const QString& command, QByteArray* error = nullptr);

private:
   static QByteArray execute(const QString& program, const QStringList& args, QByteArray* error);
};

#endif // NOT ShellClientH
