#include "Graph.h"

#include "GraphEdge.h"
#include "GraphVertex.h"

Graph::Graph()
   : vertexList()
   , edgeList()
{
}

int Graph::addVertex(Vertex* vertex)
{
   if (vertexList.contains(vertex))
      return -1;

   vertexList.append(vertex);
   return vertexList.count() - 1;
}

bool Graph::removeVertex(Vertex* vertex, bool deleteVertex)
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

int Graph::vertexIndex(const Vertex* constVertex) const
{
   Vertex* vertex = const_cast<Vertex*>(constVertex);

   if (!vertexList.contains(vertex))
      return -1;

   return vertexList.indexOf(vertex);
}

int Graph::vertexCount() const
{
   return vertexList.count();
}

Graph::Vertex* Graph::getVertex(int vertexIndex) const
{
   if (vertexIndex < 0 || vertexIndex >= vertexList.count())
      return nullptr;

   return vertexList.at(vertexIndex);
}

Graph::Vertex* Graph::findVertexByName(const QString& name) const
{
   for (Vertex* vertex : vertexList)
   {
      if (vertex->getName() == name)
         return vertex;
   }

   return nullptr;
}

int Graph::addEdge(Edge* edge)
{
   if (edgeList.contains(edge))
      return -1;

   edgeList.append(edge);
   return edgeList.count() - 1;
}

bool Graph::removeEdge(Edge* edge, bool deleteEdge)
{
   if (!edgeList.contains(edge))
      return false;

   edgeList.removeAll(edge);

   if (deleteEdge)
      delete edge;

   return true;
}

int Graph::edgeIndex(const Edge* constEdge) const
{
   Edge* edge = const_cast<Edge*>(constEdge);

   if (!edgeList.contains(edge))
      return -1;

   return edgeList.indexOf(edge);
}

int Graph::edgeCount() const
{
   return edgeList.count();
}

Graph::Edge* Graph::getEdge(int edgeIndex) const
{
   if (edgeIndex < 0 || edgeIndex >= edgeList.count())
      return nullptr;

   return edgeList.at(edgeIndex);
}

int Graph::findEdgeIndex(const Vertex* vertexA, const Vertex* vertexB) const
{
   for (int edgeIndex = 0; edgeIndex < edgeList.count(); edgeIndex++)
   {
      const Edge* edge = edgeList.at(edgeIndex);
      if (edge->getVertexA() == vertexA && edge->getVertexB() == vertexB)
         return edgeIndex;
   }

   return -1;
}

void Graph::clear(bool deleteAll)
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
