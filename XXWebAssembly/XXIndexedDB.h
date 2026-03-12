#ifndef XXIndexedDBH
#define XXIndexedDBH

#include "XXWebAssemblyExportDef.h"

#include <QCoreApplication>

namespace XX
{
   class XXWEBASSEMBLY_DECLSPEC IndexedDB
   {
   public:
      static void initFileSystem(bool printContent = false, const QString& basePath = "/" + QCoreApplication::applicationName());
      static bool checkFileSystem();
   };
} // namespace XX

#endif // NOT XXIndexedDBH
