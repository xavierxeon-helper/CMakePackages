#ifndef XXIndexedDBH
#define XXIndexedDBH

#include "XXWebAssemblyExportDef.h"

#include <QCoreApplication>

namespace XX
{
   //! @brief allows to use the IndexedDB as file system
   //! @details all paths must be relative to the base path, as set in initFileSystem()
   //! @ingroup XXWebAssembly

   class XXWEBASSEMBLY_DECLSPEC IndexedDB
   {
   public:
      static void initFileSystem(bool printContent = false, const QString& basePath = "/" + QCoreApplication::applicationName());
      static bool checkFileSystem();
   };
} // namespace XX

#endif // NOT XXIndexedDBH
