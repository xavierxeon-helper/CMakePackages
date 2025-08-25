#ifndef InfoH
#define InfoH

#include "WaToolsCoreExportDef.h"

#include <QString>

struct WATOOLSCORE_DECLSPEC Info
{
   static QString getHostName();
   static QString whatCppStandard();
};

#endif // NOT InfoH
