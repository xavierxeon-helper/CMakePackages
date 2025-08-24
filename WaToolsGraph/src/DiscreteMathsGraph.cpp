#include "DiscreteMathsGraph.h"

#include "DiscreteMathsEdge.h"
#include "DiscreteMathsVertex.h"

DiscreteMaths::Graph::Graph()
   : vertexList()
   , edgeList()
{
}

int DiscreteMaths::Graph::addVertex(Vertex* vertex)
{
   if (vertexList.contains(vertex))
      return -1;

   vertexList.append(vertex);
   return vertexList.count() - 1;
}

bool DiscreteMaths::Graph::removeVertex(Vertex* vertex, bool deleteVertex)
{
   if (!vertexList.contains(vertex))
      return false;

   vertexList.removeAll(vertex);

   QList<Edge*> edgeRemoveList; // do not remove element from list while iterating
   for (Edge* edge : edgeList)
   {
      if (edge->linksVertex(vertex))
         edgeRemoveList.append(edge);
   }
   for (Edge* edge : edgeRemoveList)
   {
      edgeList.removeAll(edge);
   }

   if (deleteVertex)
      delete vertex;

   return true;
}

int DiscreteMaths::Graph::vertexIndex(const Vertex* constVertex) const
{
   Vertex* vertex = const_cast<Vertex*>(constVertex);

   if (!vertexList.contains(vertex))
      return -1;

   return vertexList.indexOf(vertex);
}

int DiscreteMaths::Graph::vertexCount() const
{
   return vertexList.count();
}

DiscreteMaths::Vertex* DiscreteMaths::Graph::getVertex(int vertexIndex) const
{
   if (vertexIndex < 0 || vertexIndex >= vertexList.count())
      return nullptr;

   return vertexList.at(vertexIndex);
}

int DiscreteMaths::Graph::addEdge(Edge* edge)
{
   if (edgeList.contains(edge))
      return -1;

   edgeList.append(edge);
   return edgeList.count() - 1;
}

bool DiscreteMaths::Graph::removeEdge(Edge* edge, bool deleteEdge)
{
   if (!edgeList.contains(edge))
      return false;

   edgeList.removeAll(edge);

   if (deleteEdge)
      delete edge;

   return true;
}

int DiscreteMaths::Graph::edgeIndex(const Edge* constEdge) const
{
   Edge* edge = const_cast<Edge*>(constEdge);

   if (!edgeList.contains(edge))
      return -1;

   return edgeList.indexOf(edge);
}

int DiscreteMaths::Graph::edgeCount() const
{
   return edgeList.count();
}

DiscreteMaths::Edge* DiscreteMaths::Graph::getEdge(int edgeIndex) const
{
   if (edgeIndex < 0 || edgeIndex >= edgeList.count())
      return nullptr;

   return edgeList.at(edgeIndex);
}

int DiscreteMaths::Graph::findEdgeIndex(const Vertex* vertexA, const Vertex* vertexB) const
{
   for (int edgeIndex = 0; edgeIndex < edgeList.count(); edgeIndex++)
   {
      const Edge* edge = edgeList.at(edgeIndex);
      if (edge->getVertexA() == vertexA && edge->getVertexB() == vertexB)
         return edgeIndex;
   }

   return -1;
}

void DiscreteMaths::Graph::clear(bool deleteAll)
{
   if (deleteAll)
   {
      for (const Vertex* vertex : vertexList)
         delete vertex;

      for (const Edge* edge : edgeList)
         delete edge;
   }

   vertexList.clear();
   edgeList.clear();
}
