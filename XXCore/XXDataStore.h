#ifndef XXDataStoreH
#define XXDataStoreH

#include "XXCoreExportDef.h"

#include <QString>

namespace XX
{
   class XXCORE_DECLSPEC DataStore
   {
   public:
      static QString getPath();
      static void setPath(const QString& path, const QString& anchor = QString());

   private:
      static QString path;
   };
} // namespace XX

#endif // NOT XXDataStoreH
