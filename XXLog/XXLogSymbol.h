#ifndef LogSymbolH
#define LogSymbolH

#include "XXLogExportDef.h"

#include <QString>

struct XXLOG_DECLSPEC LogSymbol
{
   static const QString Warning;
   static const QString Attention;
   static const QString Debug;
   static const QString Info;
};

#endif // NOT LogSymbolH
