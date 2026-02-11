#include "XXGraphEdge.h"

#include <cmath>

const double XX::Graph::Edge::invalidWeight = std::numeric_limits<double>::quiet_NaN();

XX::Graph::Edge::Edge(Vertex* vertexA, Vertex* vertexB, const double& weightForward, const double& weightBackward)
   : vertexA(vertexA)
   , vertexB(vertexB)
   , weightForward(weightForward)
   , weightBackward(weightBackward)
{
}

double XX::Graph::Edge::getForwardWeight() const
{
   return weightForward;
}

double XX::Graph::Edge::getBackwardWeight() const
{
   return weightBackward;
}

bool XX::Graph::Edge::hasForwardLink() const
{
   return !std::isnan(getForwardWeight());
}

bool XX::Graph::Edge::hasBackwardLink() const
{
   return !std::isnan(getBackwardWeight());
}

bool XX::Graph::Edge::linksVertex(const Vertex* vertex) const
{
   if (vertex == vertexA)
      return true;
   else if (vertex == vertexB)
      return true;

   return false;
}

const XX::Graph::Vertex* XX::Graph::Edge::getVertexA() const
{
   return vertexA;
}

const XX::Graph::Vertex* XX::Graph::Edge::getVertexB() const
{
   return vertexB;
}
