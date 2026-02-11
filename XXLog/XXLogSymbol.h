#ifndef XXLogSymbolH
#define XXLogSymbolH

#include "XXLogExportDef.h"

#include <QString>

namespace XX
{
   struct XXLOG_DECLSPEC LogSymbol
   {
      static const QString Warning;
      static const QString Attention;
      static const QString Debug;
      static const QString Info;
   };
} // namespace XX

#endif // NOT XXLogSymbolH
