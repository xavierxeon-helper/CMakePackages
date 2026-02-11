#include "XXGraphEdge.h"

#include <cmath>

const double Graph::Edge::invalidWeight = std::numeric_limits<double>::quiet_NaN();

Graph::Edge::Edge(Vertex* vertexA, Vertex* vertexB, const double& weightForward, const double& weightBackward)
   : vertexA(vertexA)
   , vertexB(vertexB)
   , weightForward(weightForward)
   , weightBackward(weightBackward)
{
}

double Graph::Edge::getForwardWeight() const
{
   return weightForward;
}

double Graph::Edge::getBackwardWeight() const
{
   return weightBackward;
}

bool Graph::Edge::hasForwardLink() const
{
   return !std::isnan(getForwardWeight());
}

bool Graph::Edge::hasBackwardLink() const
{
   return !std::isnan(getBackwardWeight());
}

bool Graph::Edge::linksVertex(const Vertex* vertex) const
{
   if (vertex == vertexA)
      return true;
   else if (vertex == vertexB)
      return true;

   return false;
}

const Graph::Vertex* Graph::Edge::getVertexA() const
{
   return vertexA;
}

const Graph::Vertex* Graph::Edge::getVertexB() const
{
   return vertexB;
}
