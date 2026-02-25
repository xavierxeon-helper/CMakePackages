#ifndef XXDiscreteMathsVertexH
#define XXDiscreteMathsVertexH

#include "XXMathExportDef.h"

#include <QString>

#include "XXGraph.h"

namespace XX
{
   //! @brief a vertex in a graph
   //! @ingroup XXMath

   class XXMATH_DECLSPEC Graph::Vertex
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
