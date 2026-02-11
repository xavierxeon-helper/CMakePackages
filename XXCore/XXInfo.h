#ifndef XXInfoH
#define XXInfoH

#include "XXCoreExportDef.h"

#include <QString>

namespace XX
{
   struct XXCORE_DECLSPEC Info
   {
      static QString getHostName();
      static QString whatCppStandard();
   };
} // namespace XX

#endif // NOT XXInfoH
