#ifndef DataStoreH
#define DataStoreH

#include "WaToolsCoreExportDef.h"

#include <QString>

class WATOOLSCORE_DECLSPEC DataStore
{
public:
   static QString getPath();
   static void setPath(const QString& path, const QString& anchor = QString());

private:
   static QString path;
};

#endif // NOT DataStoreH
