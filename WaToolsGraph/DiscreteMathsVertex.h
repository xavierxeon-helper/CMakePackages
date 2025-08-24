#ifndef DiscreteMathsVertexH
#define DiscreteMathsVertexH

#include "WaToolsGraphExportDef.h"

#include <QString>

namespace DiscreteMaths
{
   class WATOOLSGRAPH_DECLSPEC Vertex
   {
   public:
      Vertex(const QString& name = QString());

   public:
      const QString& getName() const;

   protected:
      QString name;
   };
} // namespace DiscreteMaths

#endif // NOT GraphAbstractVertexH
