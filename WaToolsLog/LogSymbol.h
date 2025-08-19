#ifndef LogSymbolH
#define LogSymbolH

#include "WaToolsLogExportDef.h"

#include <QString>

struct WATOOLSLOG_DECLSPEC LogSymbol
{
   static const QString Warning;
   static const QString Attention;
   static const QString Debug;
   static const QString Info;
};

#endif // NOT LogSymbolH
