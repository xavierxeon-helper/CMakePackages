#ifndef LogSymbolH
#define LogSymbolH

#include <QString>

struct LogSymbol
{
   static const QString Warning;
   static const QString Attention;
   static const QString Debug;
   static const QString Info;
};

#ifndef LogSymbolHPP
#include "LogSymbol.hpp"
#endif // NOT LogSymbolHPP

#endif // NOT LogSymbolH
