#include "DiscreteMathsEdge.h"

#include <cmath>

const double DiscreteMaths::Edge::invalidWeight = std::numeric_limits<double>::quiet_NaN();

DiscreteMaths::Edge::Edge(Vertex* vertexA, Vertex* vertexB, const double& weightForward, const double& weightBackward)
   : vertexA(vertexA)
   , vertexB(vertexB)
   , weightForward(weightForward)
   , weightBackward(weightBackward)
{
}

DiscreteMaths::Edge::~Edge()
{
}

double DiscreteMaths::Edge::getForwardWeight() const
{
   return weightForward;
}

double DiscreteMaths::Edge::getBackwardWeight() const
{
   return weightBackward;
}

bool DiscreteMaths::Edge::hasForwardLink() const
{
   return !std::isnan(getForwardWeight());
}

bool DiscreteMaths::Edge::hasBackwardLink() const
{
   return !std::isnan(getBackwardWeight());
}

bool DiscreteMaths::Edge::linksVertex(const Vertex* vertex) const
{
   if (vertex == vertexA)
      return true;
   else if (vertex == vertexB)
      return true;

   return false;
}

const DiscreteMaths::Vertex* DiscreteMaths::Edge::getVertexA() const
{
   return vertexA;
}

const DiscreteMaths::Vertex* DiscreteMaths::Edge::getVertexB() const
{
   return vertexB;
}
