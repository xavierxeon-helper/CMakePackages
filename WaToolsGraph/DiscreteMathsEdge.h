#ifndef DiscreteMathsEdgeH
#define DiscreteMathsEdgeH

#include "WaToolsGraphExportDef.h"

namespace DiscreteMaths
{
   class Vertex;
   class Graph;

   class WATOOLSGRAPH_DECLSPEC Edge
   {
   public:
      static const double invalidWeight;

   public:
      Edge(Vertex* vertexA = nullptr, Vertex* vertexB = nullptr, const double& weightForward = 1.0, const double& weightBackward = Edge::invalidWeight);
      virtual ~Edge();

   public:
      virtual double getForwardWeight() const;
      virtual double getBackwardWeight() const;
      bool hasForwardLink() const;
      bool hasBackwardLink() const;
      bool linksVertex(const Vertex* vertex) const;

      const Vertex* getVertexA() const;
      const Vertex* getVertexB() const;

   protected:
      Vertex* vertexA;
      Vertex* vertexB;
      double weightForward;
      double weightBackward;

   private:
      friend class Graph;
   };
} // namespace DiscreteMaths

#endif // NOT GraphAbstractEdgeH
