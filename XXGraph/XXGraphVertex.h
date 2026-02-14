#ifndef XXDiscreteMathsVertexH
#define XXDiscreteMathsVertexH

#include "XXGraphExportDef.h"

#include <QString>

#include "XXGraph.h"

namespace XX
{
   //! @brief a vertex in a graph
   //! @ingroup XXGraph

   class XXGRAPH_DECLSPEC Graph::Vertex
   {
   public:
      Vertex(const QString& name = QString());

   public:
      const QString& getName() const;

   protected:
      QString name;
   };
} // namespace XX

#endif // NOT XXDiscreteMathsVertexH
