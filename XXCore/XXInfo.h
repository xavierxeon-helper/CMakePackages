#ifndef InfoH
#define InfoH

#include "XXCoreExportDef.h"

#include <QString>

struct XXCORE_DECLSPEC Info
{
   static QString getHostName();
   static QString whatCppStandard();
};

#endif // NOT InfoH
