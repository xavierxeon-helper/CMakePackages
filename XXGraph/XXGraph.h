#ifndef XXDiscreteMathsGraphH
#define XXDiscreteMathsGraphH

#include "XXGraphExportDef.h"

#include <QList>

namespace XX
{
   //! @brief graph structure
   /*!
      @details fill with \ref Vertex "vertices" and  \ref Edge "edges", then use \ref Algorithm "algorithms" to process the graph data
   */
   //! @ingroup XXGraph

   class XXGRAPH_DECLSPEC Graph
   {
   public:
      class Algorithm;
      class Vertex;
      class Edge;

   public:
      Graph();

   public:
      int addVertex(Vertex* vertex);
      bool removeVertex(Vertex* vertex, bool deleteVertex = false);
      int vertexIndex(const Vertex* vertex) const;
      int vertexCount() const;
      Vertex* getVertex(int vertexIndex) const;
      Vertex* findVertexByName(const QString& name) const;

      int addEdge(Edge* edge);
      bool removeEdge(Edge* edge, bool deleteEdge = false);
      int edgeIndex(const Edge* edge) const;
      int edgeCount() const;
      Edge* getEdge(int edgeIndex) const;
      int findEdgeIndex(const Vertex* vertexA, const Vertex* vertexB) const;

      void clear(bool deleteAll = false);

   private:
      QList<Vertex*> vertexList;
      QList<Edge*> edgeList;
   };
} // namespace XX

#endif // NOT XXDiscreteMathsGraphH
